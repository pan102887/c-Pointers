#include "alloc.h"

#include <stdio.h>
#undef malloc

extern void *alloc(size_t size)
{
    void *p = malloc(size);
    if (NULL == p) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    return p;
}

extern void dealloc(void **pp)
{   
    if (NULL == pp || NULL == *pp) {
        return;
    }
    free(*pp);
    *pp = NULL;
}