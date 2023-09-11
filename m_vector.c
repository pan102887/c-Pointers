#include "m_vector.h"

#include "m_def.h"
#include <stdlib.h>
#include <stdio.h>

#define INITAL_CAPACITY 10
/**
 * @brief create a new m_vector object
 *
 * @param capacity the initial capacity of the vector
 * @param capacity_increment the increment of the capacity when the vector is full
 * @return m_vector*
 */
extern m_vector *m_vector_new_with_capacity(size_t capacity)
extern m_vector *m_vector_new_with_capacity(size_t capacity)
{
    m_vector *vector = malloc(sizeof(m_vector));
    if (NULL == vector)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if (capacity > 0)
    {
        vector->capacity = capacity;
        vector->element_array = malloc(sizeof(void *) * capacity);
    }
    else if (capacity == 0)
    {
        vector->capacity = 0;
        vector->element_array = NULL;
    }
    else {
        perror("capacity must be positive");
        exit(EXIT_FAILURE);
    }
    return vector;
}

extern void m_vector_free(m_vector *vector)
{
    if (NULL == vector)
    {
        return;
    }
    if (NULL != vector->element_array)
    {
        free(vector->element_array);
    }
    free(vector);
}
extern void m_vector_add(m_vector *vector, void *element)
{

}
extern void *m_vector_get(m_vector *vector, size_t index);
extern void m_vector_set(m_vector *vector, size_t index, void *element);
extern void m_vector_remove(m_vector *vector, size_t index);
extern void m_vector_clear(m_vector *vector);
