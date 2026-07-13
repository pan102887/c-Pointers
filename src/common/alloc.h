#ifndef CP_COMMON_ALLOC_H
#define CP_COMMON_ALLOC_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
#define malloc /*don;t call malloc directly*/
#define CP_MALLOC(num, type) (type *)alloc((num) * sizeof(type))
#define CP_NEW(type, num) CP_MALLOC((num), type)
#define CP_RENEW(ptr, type, num) (type *)renew((ptr), (num) * sizeof(type))
#define CP_FREE(pp) dealloc((void **)(pp))
extern void *alloc(size_t size);
extern void dealloc(void **pp);
extern void *renew(void *p, size_t size);
#ifdef __cplusplus
}
#endif

#endif