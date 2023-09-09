#include "m_array_list.h"

#include <stdlib.h>

#define initial_capacity 10

extern m_array_list *m_array_list_new_with_capacity(size_t capacity)
{
    m_array_list *array_list = malloc(sizeof(m_array_list));
    if (capacity > 0)
    {
        array_list->element_data = malloc(capacity * sizeof(void *));
    }
    else if (capacity == 0)
    {
        array_list->element_data = NULL;
    }
    else
    {
        perror("capacity must be greater than or equal to 0");
        exit(EXIT_FAILURE);
    }
}

extern m_array_list *m_array_list_new()
{
    return m_array_list_new_with_capacity(initial_capacity);
}

extern m_array_list *m_array_list_new_with_array(void **array, size_t array_size)
{
    if (array_size < 0)
    {
        perror("array_size must be greater than or equal to 0");
        exit(EXIT_FAILURE);
    }
    m_array_list *array_list = malloc(sizeof(m_array_list));
    array_list->element_data = malloc(array_size * sizeof(void *));
    for (size_t i = 0; i < array_size; i++)
    {
        array_list->element_data[i] = array[i];
    }
    return array_list;
}