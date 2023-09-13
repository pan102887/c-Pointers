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

extern void dealloc(void *ptr)
{   
    if (NULL == ptr) {
        return;
    }
    free(ptr);
    ptr = NULL;
}