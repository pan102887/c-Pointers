#ifndef _M_VECTOR_H_
#define _M_VECTOR_H_

#include <stddef.h>
#include <stdlib.h>

typedef struct m_vector
{
    // vector中元素个数
    size_t element_count;
    // vector中元素数组(元素为数据的地址指针void*)
    void **element_array;
    // 数组容量
    size_t capacity;
    // 数组容量增量
    size_t capacity_increment;
} m_vector;

#ifdef __cplusplus
extern "C" {
#endif
extern m_vector *m_vector_new();
extern m_vector *m_vector_new_with_capacity(size_t capacity);
extern void m_vector_free(m_vector *vector);
extern void m_vector_add(m_vector *vector, void *element);
extern void *m_vector_get(m_vector *vector, size_t index);
extern void m_vector_set(m_vector *vector, size_t index, void *element);
extern void m_vector_remove(m_vector *vector, size_t index);
extern void m_vector_clear(m_vector *vector);
#ifdef __cplusplus
}
#endif

#endif