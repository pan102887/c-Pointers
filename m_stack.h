#ifndef _M_STACK_H_
#define _M_STACK_H_

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