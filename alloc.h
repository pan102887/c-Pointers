#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stdlib.h>


#define malloc /*don;t call malloc directly*/
#define MALLOC(num, type) (type *)alloc((num) * sizeof(type))
#define FREE(pp) dealloc((void **)(pp))
extern void *alloc(size_t size);
extern void dealloc(void **pp);
#endif