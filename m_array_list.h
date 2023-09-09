#ifndef _M_ARRAY_LIST_H_
#define _M_ARRAY_LIST_H_

#include "stddef.h"

typedef struct
{
    void **element_data;
    size_t size;

} m_array_list;

extern m_array_list *m_array_list_new();
extern m_array_list *m_array_list_new_with_capacity(size_t capacity);
extern m_array_list *m_array_list_new_with_array(void **array, size_t array_size);
// todo: improve this List interface

#endif