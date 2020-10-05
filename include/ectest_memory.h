
#ifndef __ECTEST_MEMORY_H_
#define __ECTEST_MEMORY_H_

#include <stdlib.h>

enum __ectest_memtag{
    __ECTEST_MEMTAG_TEST,
    __ECTEST_MEMTAG_MOD,
    __ECTEST_MEMTAG_SUITE
};

struct __ectest_memnode{
    struct __ectest_memnode *prev;
    struct __ectest_memnode *next;
};

struct{
    struct __ectest_memnode *troot;
    struct __ectest_memnode *mroot;
    struct __ectest_memnode *sroot;
} *__ectest_memroot;

#define __ECTEST_MEMNODE_LINK(_prev, _node, _next)\
    do{\
        _node->next = _next;\
        _node->prev = _prev;\
        _next->prev = _node;\
        _prev->next = _node;\
    }while(0)

#define __ECTEST_MEMNODE_UNLINK(_node)\
    do{\
        _node->next->prev = _node->prev;\
        _node->prev->next = _node->next;\
    }while(0)

#define __ECTEST_MEMROOT_BYTAG(root, tag)\
    do{\
        switch(tag){\
            case __ECTEST_MEMTAG_TEST:\
                root = __ectest_memroot->troot;\
                break;\
            case __ECTEST_MEMTAG_MOD:\
                root = __ectest_memroot->mroot;\
                break;\
            case __ECTEST_MEMTAG_SUITE:\
                root = __ectest_memroot->sroot;\
                break;\
            default:\
                /*TODO LOG*/\
                abort();\
        }\
    }while(0)

static inline void __ectest_meminit(void)
{
    __ectest_memroot  = malloc(sizeof *__ectest_memroot);
    __ectest_memroot->troot = malloc(sizeof *__ectest_memroot->troot);
    __ectest_memroot->mroot = malloc(sizeof *__ectest_memroot->mroot);    
    __ectest_memroot->sroot = malloc(sizeof *__ectest_memroot->sroot);
    
    __ECTEST_MEMNODE_LINK(__ectest_memroot->troot, __ectest_memroot->troot, __ectest_memroot->troot);
    __ECTEST_MEMNODE_LINK(__ectest_memroot->mroot, __ectest_memroot->mroot, __ectest_memroot->mroot);
    __ECTEST_MEMNODE_LINK(__ectest_memroot->sroot, __ectest_memroot->sroot, __ectest_memroot->sroot);
}

static inline void *__ectest_malloc(size_t size, enum __ectest_memtag tag)
{
    struct __ectest_memnode *root, *node;

    void *ptr =  malloc(size + sizeof *node);
    node = ptr;

    __ECTEST_MEMROOT_BYTAG(root, tag);
    __ECTEST_MEMNODE_LINK(root, node, root->next);

    return ptr + sizeof *node;
}

static inline void __ectest_free(void *ptr)
{
    if(!ptr) return;
    struct __ectest_memnode *node = ptr - sizeof *node;
    __ECTEST_MEMNODE_UNLINK(node);
    free(ptr-sizeof *node);
}

static inline void __ectest_mtfree(enum __ectest_memtag tag)
{
    struct __ectest_memnode *root, *cur, *tmp;
    __ECTEST_MEMROOT_BYTAG(root, tag);
    cur = root->next;
    while(cur != root){
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    __ECTEST_MEMNODE_LINK(root, root, root);
}

static inline void __ectest_mrfree(void)
{
    __ectest_mtfree(__ECTEST_MEMTAG_TEST);
    __ectest_mtfree(__ECTEST_MEMTAG_MOD);
    __ectest_mtfree(__ECTEST_MEMTAG_SUITE);
}

static inline void __ectest_memrelease(void)
{
    __ectest_mrfree();
    free(__ectest_memroot->troot);
    free(__ectest_memroot->mroot);
    free(__ectest_memroot->sroot);
    free(__ectest_memroot);
}

#endif /*__ECTEST_MEMORY_H_*/

