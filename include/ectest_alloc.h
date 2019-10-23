#ifndef ECTEST_ALLOC__
#define ECTEST_ALLOC__

struct {
    struct ect_memnode__ *suite_root;
    struct ect_memnode__ *module_root;
    struct ect_memnode__ *test_root;
} *ECT_MEMROOT__;

#define ECT_MEMNODE_LINK__(prev_, node_, next_)                                 \
    do{                                                                         \
        node_->next = next_;                                                    \
        node_->prev = prev_;                                                    \
        next_->prev = node_;                                                    \
        prev_->next = node_;                                                    \
    }while(0)

#define ECT_MEMNODE_UNLINK__(node_)                                             \
    do{                                                                         \
        node_->next->prev = node_->prev;                                        \
        node_->prev->next = node_->next;                                        \
    }while(0)

#define ECT_MEMROOT_GETBYTAG__(root, tag)                                       \
    do{                                                                         \
        switch(tag){                                                            \
            case ECT_MEMTAG_SUITE__:                                            \
                root = ECT_MEMROOT__->suite_root;                               \
                break;                                                          \
            case ECT_MEMTAG_MODULE__:                                           \
                root = ECT_MEMROOT__->module_root;                              \
                break;                                                          \
            case ECT_MEMTAG_TEST__:                                             \
                root = ECT_MEMROOT__->test_root;                                \
                break;                                                          \
            default:                                                            \
                ECT_ELOG__("Faulty memtag value: %d", tag);                     \
                abort();                                                        \
        }                                                                       \
    }while(0)

static inline void ect_mem_init__(void)
{
    ECT_MEMROOT__ = malloc(sizeof *ECT_MEMROOT__);
    ECT_MEMROOT__->suite_root = malloc(sizeof *ECT_MEMROOT__->suite_root);
    ECT_MEMROOT__->module_root = malloc(sizeof *ECT_MEMROOT__->module_root);
    ECT_MEMROOT__->test_root = malloc(sizeof *ECT_MEMROOT__->test_root);
    
    ECT_MEMNODE_LINK__(ECT_MEMROOT__->suite_root,
                    ECT_MEMROOT__->suite_root, 
                    ECT_MEMROOT__->suite_root);
    ECT_MEMNODE_LINK__(ECT_MEMROOT__->module_root,
                    ECT_MEMROOT__->module_root,
                    ECT_MEMROOT__->module_root);
    ECT_MEMNODE_LINK__(ECT_MEMROOT__->test_root,
                    ECT_MEMROOT__->test_root,
                    ECT_MEMROOT__->test_root);
}

static inline void *ect_malloc__(size_t size, enum ect_memtag__ tag)
{
    struct ect_memnode__ *root, *mnode;
    void *ptr = malloc(size + sizeof *mnode);
    ECT_DLOG__("Allocating %zuB at address: %p", size, ptr);

    mnode = ptr;
    ECT_MEMROOT_GETBYTAG__(root, tag);

    ECT_MEMNODE_LINK__(root, mnode, root->next);
    return ptr + sizeof *mnode;
}

static inline void ect_free__(void *ptr)
{
    if(!ptr) return;
    struct ect_memnode__ *mnode;
    ECT_DLOG__("Freeing memory at address: %p", ptr - sizeof *mnode);
    mnode = ptr - sizeof *mnode;

    ECT_MEMNODE_UNLINK__(mnode);

    free(ptr-sizeof *mnode);
}

static inline void ect_memtag_move__(void *ptr, enum ect_memtag__ moveto)
{
    struct ect_memnode__ *root, *mnode = ptr-sizeof *mnode;
    ECT_MEMNODE_UNLINK__(mnode);
    ECT_MEMROOT_GETBYTAG__(root, moveto);
    ECT_MEMNODE_LINK__(root, mnode, root->next);
}

static inline void ect_free_tag__(enum ect_memtag__ tag)
{
    struct ect_memnode__ *root, *cur, *tmp;
    ECT_DLOG__("Deallocating all memory with tag '%s'", ECT_MEMTAG_STR__[tag]);
    ECT_MEMROOT_GETBYTAG__(root, tag);
    cur = root->next;
    while(cur != root){
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    ECT_MEMNODE_LINK__(root, root, root);
}

static inline void ect_memroot_free__(void)
{
    ECT_DLOG__("Deallocating all memory beneath memory root");
    ect_free_tag__(ECT_MEMTAG_SUITE__);
    ect_free_tag__(ECT_MEMTAG_MODULE__);
    ect_free_tag__(ECT_MEMTAG_TEST__);
    ECT_DLOG__("Memory beneath memory root deallocated");
}

static inline void ect_mem_release__(void)
{
    ECT_DLOG__("Releasing all allocated memory");
    ect_memroot_free__();
    free(ECT_MEMROOT__->suite_root);
    free(ECT_MEMROOT__->module_root);
    free(ECT_MEMROOT__->test_root);
    ECT_DLOG__("Deallocating memory root");
    free(ECT_MEMROOT__);
    ECT_DLOG__("All memory released");
}

#endif /*ECTEST_ALLOC__*/
