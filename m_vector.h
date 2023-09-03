#ifndef _M_VECTOR_H_
#define _M_VECTOR_H_

#include <stddef.h>
#include <stdlib.h>

typedef struct m_vector
{
    size_t element_count;
    void **element_array;
    size_t capacity;
    size_t capacity_increment;
} m_vector;

extern m_vector *m_vector_new(size_t capacity, size_t capacity_increment);
extern void m_vector_free(m_vector *vector);

#endif