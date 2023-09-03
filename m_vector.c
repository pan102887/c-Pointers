#include "m_vector.h"

#include "m_def.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief create a new m_vector object
 *
 * @param capacity the initial capacity of the vector
 * @param capacity_increment the increment of the capacity when the vector is full
 * @return m_vector*
 */
extern m_vector *m_vector_new(size_t capacity, size_t capacity_increment)
{
    m_vector *vector = malloc(sizeof(m_vector));
    if (NULL == vector)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    vector->element_count = 0;
    vector->capacity = capacity <= 0 ? 1 : capacity;
    vector->capacity_increment = capacity_increment <= 0 ? 1 : capacity_increment;
    vector->element_array = malloc(capacity * sizeof(void *));
    return vector;
}
