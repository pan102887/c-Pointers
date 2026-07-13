#ifndef CP_COMMON_RUNABLE_H
#define CP_COMMON_RUNABLE_H

#include <stddef.h>
typedef struct Runable
{
    void (*run)(void);
    char *name;
} Runable;
#endif // CP_COMMON_RUNABLE_H
