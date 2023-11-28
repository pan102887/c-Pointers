#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
#define malloc /*don;t call malloc directly*/
#define MALLOC(num, type) (type *)alloc((num) * sizeof(type))
#define NEW(type, num) MALLOC((num), type)
#define RENEW(ptr, type, num) (type *)renew((ptr), (num) * sizeof(type))
#define FREE(pp) dealloc((void **)(pp))
extern void *alloc(size_t size);
extern void dealloc(void **pp);
extern void *renew(void *p, size_t size);
#ifdef __cplusplus
}
#endif

#endif