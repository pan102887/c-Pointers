#ifndef _M_ARRAY_LIST_H_
#define _M_ARRAY_LIST_H_

#include "stddef.h"
#include <stdbool.h>
/**
 * @brief 存放内存地址的数组列表
 *
 */

typedef struct
{
    void **element_data;
    size_t size;
    size_t capacity;
    void *(*get)(size_t index);
} m_array_list;

extern m_array_list *m_array_list_new();
extern m_array_list *m_array_list_new_with_capacity(size_t capacity);
extern m_array_list *m_array_list_new_with_array(void **array, size_t array_size);
extern void m_array_list_free(m_array_list *list);
extern void m_array_list_and_data_free(m_array_list *list, void (*free_element)(void *));
extern void *array_list_get(m_array_list *list, size_t index);
extern void array_list_set(m_array_list *list, size_t index, void *element);
extern bool array_list_add(m_array_list *list, void *element);

/**
 * @brief 根据元素位置从list删除元素（需要手动释放元素内存）
 *
 * @param list list
 * @param index 元素内存位置
 * @return void* 元素内存地址
 */
extern void *remove_from_array_list_by_index(m_array_list *list, size_t index);

/**
 * @brief 根据地址value从list删除元素（需要手动释放元素内存）
 *
 * @param list 列表
 * @param value 地址value
 * @return true 操作成功
 * @return false 操作失败
 */
extern bool remove_from_array_list_by_value(m_array_list *list, void *value);

/**
 * @brief 根据predicate判断结果（为真则）删除元素，并释放元素
 *
 * @param list 列表
 * @param predicate 判断方法
 * @param release_data 元素释放方法
 * @return true
 * @return false
 */
extern bool remove_from_list_by_predicate_and_release_data(m_array_list *list, int(*predicate(void *)), void (*release_data)(void *));
extern bool remove_from_list_by_cmp_and_release_data(m_array_list *list, void *value, int(*cmp(void *, void *)), void (*release_data)(void *));

#if defined(_TEST_)
extern void array_list_test(void);
#endif

#endif