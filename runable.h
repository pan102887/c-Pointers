#ifndef _RUNABLE_H_
#define _RUNABLE_H_

#include <stddef.h>
typedef struct Runable
{
    void (*run)(void);
    char *name;
} Runable;
#endif // _MAIN_EXTENSION_H_