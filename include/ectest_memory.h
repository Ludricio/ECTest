
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

static inline void __ect_mem_init(void)
{
    __ectest_memroot  = malloc(sizeof *__ectest_memroot);
}

#endif /*__ECTEST_MEMORY_H_*/

