#ifndef ECTEST_ALLOC__
#define ECTEST_ALLOC__

/*static struct ect_memnode__ ECT_MEMROOT__ = {
    .next = &ECT_MEMROOT__,
    .prev = &ECT_MEMROOT__,
    .tag = ECT_MEMTAG_ROOT__
    //TODO set root tag when tags added
};*/

static struct {
    struct ect_memnode__ *suite_root;
    struct ect_memnode__ *module_root;
    struct ect_memnode__ *test_root;
} ECT_MEMROOT__ = {
    .suite_root = NULL,
    .module_root = NULL,
    .test_root = NULL
};

#define ECT_MEM_SIZE__ (sizeof(struct ect_memnode__) + sizeof(char))

static inline void *ect_malloc__(size_t size, enum ect_memtag__ tag)
{
    ECT_DLOG__("Allocating:%zuB", size);
    void *ptr = malloc(size + ECT_MEM_SIZE__);
    (*(char*)ptr) = tag;
    struct ect_memnode__ *mnode = ptr++;

    __typeof__(ECT_MEMROOT__) *memroot = &ECT_MEMROOT__;
    switch (tag){
        case ECT_MEMTAG_SUITE__:    
            break;
        case ECT_MEMTAG_MODULE__: 
            break;
        case ECT_MEMTAG_TEST__: 
            break;
        default: 
            ECT_ELOG__("Faulty memtag value: %d", tag); 
            abort();
    }

    //TODO fix memnode stuff

    return ptr+ECT_MEM_SIZE__;
}

static inline void ect_free__(void *ptr)
{
    if(!ptr) return;
    ECT_DLOG__("Freeing");
    struct ect_memnode__ *mnode = ptr-sizeof(*mnode);
    mnode->prev->next = mnode->next;
    mnode->next->prev = mnode->prev;

    free(mnode);
}

//TODO add function for changing memory tag when tags added???

static inline void ect_free_tag__(enum ect_memtag__ tag)
{
    struct ect_memnode__ *tmp, *cur, *start;
    switch (tag){
    case ECT_MEMTAG_SUITE__: 
        start = ECT_MEMROOT__.suite_root; 
        break;
    case ECT_MEMTAG_MODULE__: 
        start = ECT_MEMROOT__.module_root; 
        break;
    case ECT_MEMTAG_TEST__: 
        start = ECT_MEMROOT__.test_root; 
        break;
    default:
        break;
    }
    cur = start;
    while(cur != start){
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
}

static inline void ect_memroot_free__()
{
    ECT_DLOG__("Cleaning up allocated memory");
    ect_free_tag__(ECT_MEMTAG_SUITE__);
    ect_free_tag__(ECT_MEMTAG_MODULE__);
    ect_free_tag__(ECT_MEMTAG_TEST__);
}

#endif /*ECTEST_ALLOC__*/
