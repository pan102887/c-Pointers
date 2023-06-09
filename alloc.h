#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stdlib.h>


#define malloc
#define MALLOC(num, type) (type *)alloc((num) * sizeof(type))
extern void *alloc(size_t size);
extern void dealloc(void *ptr);
#endif