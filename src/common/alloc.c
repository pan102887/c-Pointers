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

extern void *renew(void *p, size_t size)
{
    void *new_p = realloc(p, size);
    if (NULL == new_p) {
        fprintf(stderr, "Out of memory\n");
        perror("renew");
        exit(1);
    }
    return new_p;
}