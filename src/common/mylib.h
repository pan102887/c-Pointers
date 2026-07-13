#ifndef CP_COMMON_MYLIB_H
#define CP_COMMON_MYLIB_H
#include <stddef.h>

#ifndef cp_offset
// #define cp_offset(type, member) ((size_t)(&(((type *)0)->member)))
#define cp_offset(type, member) offsetof(type, member)
#endif

#ifndef cp_container_of
#if defined(__GNUC__) || defined(__clang__)
#define cp_container_of(ptr, type, member)                                     \
  ({                                                                           \
    const __typeof__(((type *)0)->member) *cp_mptr = (ptr);                    \
    (type *)((char *)cp_mptr - cp_offset(type, member));                       \
  })
#else
#define cp_container_of(ptr, type, member)                                     \
  ((type *)((char *)(ptr) - cp_offset(type, member)))
#endif
#endif

#endif // CP_COMMON_MYLIB_H
