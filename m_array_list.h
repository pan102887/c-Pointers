#ifndef _M_ARRAY_LIST_H_
#define _M_ARRAY_LIST_H_

#include "stddef.h"
#include <stdbool.h>
/**
 * @brief 类型无关的数组列表
 * 
 * 队列中究竟存储的是数据的指针，还是数据本身呢？
 */

typedef struct
{
    void **element_data;
    size_t size;
    size_t capacity;
    void* (*get)(size_t index);
} m_array_list;

extern m_array_list *m_array_list_new();
extern m_array_list *m_array_list_new_with_capacity(size_t capacity);
extern m_array_list *m_array_list_new_with_array(void **array, size_t array_size);
extern void m_array_list_free(m_array_list *list);
extern void m_array_list_and_data_free(m_array_list *list, void (*free_element)(void*));
extern void* get(m_array_list* list, size_t index);
extern void set(m_array_list* list, size_t index, void* element);
extern bool add(m_array_list* list, void* element);

#if defined(_TEST_)
extern void array_list_test(void);
#endif

#endif