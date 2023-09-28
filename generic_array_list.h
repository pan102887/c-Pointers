#ifndef _GENERIC_ARRAY_LIST_H_
#define _GENERIC_ARRAY_LIST_H_

#include <stddef.h>

typedef struct
{
    char * element_data;
    size_t size;
    size_t capacity;
} generic_araay_list ;

#endif