#ifndef _M_ARRAY_LIST_H_
#define _M_ARRAY_LIST_H_

#include "stddef.h"
#include <stdbool.h>
/**
 * @brief 存放内存地址的数组列表
 *
 */

typedef void *ele_t;
typedef struct
{
    ele_t *element_data;
    size_t size;
    size_t capacity;
    ele_t (*get)(size_t index);
} m_array_list, *m_array_list_p;


#ifdef __cplusplus
extern "C" {
#endif
extern m_array_list_p m_array_list_new();
extern m_array_list_p m_array_list_new_with_capacity(size_t capacity);
extern m_array_list_p m_array_list_new_with_array(ele_t *array_p, size_t array_size);
extern void m_array_list_free(m_array_list_p *lis_pp);
extern void m_array_list_and_data_free(m_array_list_p *list_pp, void (*free_element)(ele_t));
extern ele_t array_list_get(m_array_list_p list_p, size_t index);
extern void array_list_set(m_array_list_p list_p, size_t index, ele_t element);
extern bool array_list_add(m_array_list_p list_p, ele_t element);
extern ele_t array_list_get_and_delete(m_array_list_p list_p, size_t index);

/**
 * @brief 根据地址value从list删除元素（需要手动释放元素内存）
 *
 * @param list 列表
 * @param value 地址value
 * @return true 操作成功
 * @return false 操作失败
 */
extern bool remove_from_array_list_by_value(m_array_list_p list_p, ele_t element);

/**
 * @brief 根据predicate判断结果（为真则）删除元素，并释放元素
 *
 * @param list 列表
 * @param predicate 判断方法
 * @param release_data 元素释放方法
 * @return true
 * @return false
 */
extern bool remove_from_list_by_predicate_and_release_data(m_array_list_p list_p, int(*predicate(ele_t)), void (*release_data)(ele_t));
extern bool remove_from_list_by_cmp_and_release_data(m_array_list_p list_p, ele_t element, int(*cmp(ele_t, ele_t)), void (*release_data)(ele_t));
#ifdef __cplusplus
}
#endif

#if defined(_TEST_)
extern void array_list_test(void);
#endif

#endif