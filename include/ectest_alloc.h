#ifndef ECTEST_ALLOC__
#define ECTEST_ALLOC__

static struct ect_memnode__ ECT_MEMROOT__ = {.next = &ECT_MEMROOT__, .prev = &ECT_MEMROOT__};

static inline void *ect_alloc__(size_t size)
{
    ECT_DLOG__("Allocating:%zuB", size);
    void *ptr = malloc(size + sizeof(struct ect_memnode__));
    struct ect_memnode__ *mnode = ptr;
    mnode->next = ECT_MEMROOT__.next;
    mnode->prev = &ECT_MEMROOT__;
    ECT_MEMROOT__.next = mnode;
    return ptr+sizeof(*mnode);
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

static inline void ect_memroot_free__()
{
    ECT_DLOG__("Cleaning up allocated memory");
    struct ect_memnode__ *tmp, *current = ECT_MEMROOT__.next;
    while(current != &ECT_MEMROOT__){
        tmp = current->next;
        free(current);
        current = tmp;
    }
}

#endif /*ECTEST_ALLOC__*/

