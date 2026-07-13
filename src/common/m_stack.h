#ifndef CP_COMMON_M_STACK_H
#define CP_COMMON_M_STACK_H

#include <stddef.h>

#include "m_vector.h"

typedef struct stack_node
{
    void *data;
} stack_node;

typedef struct stack
{
    size_t size;
    stack_node *top;
    stack_node *element_array;
} stack;

#endif