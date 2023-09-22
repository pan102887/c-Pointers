#include "m_array_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define DEFAULT_CAPACITY 10
#define MAX_ARRAY_SIZE ((size_t)pow(2, 32) - 1)

static inline void ensure_capacity_internal(m_array_list *list, size_t min_capacity);
static inline void ensure_explicit_capacity(m_array_list *list, size_t min_capacity);
static inline size_t calculate_capacity(m_array_list *list, size_t min_capacity);
static inline void grow(m_array_list *list, size_t min_capacity);
static inline void list_null_check(m_array_list *list);
static inline void remove_item_from_array(void **list, size_t array_size, size_t item_index);

/**
 * ===================   ██▀ ▀▄▀ ▀█▀ ██▀ █▀▄ █▄ █ ▄▀▄ █    =========================
 * ===================   █▄▄ █ █  █  █▄▄ █▀▄ █ ▀█ █▀█ █▄▄  =========================
 */

extern m_array_list *m_array_list_new()
{
    m_array_list *list = malloc(sizeof(m_array_list));
    if (NULL == list)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    list->capacity = DEFAULT_CAPACITY;
    list->size = 0;
    list->element_data = malloc(sizeof(void *) * DEFAULT_CAPACITY);
    return list;
}

extern m_array_list *m_array_list_new_with_capacity(size_t capacity)
{
    if (capacity < 0)
    {
        perror("capacity must be positive");
        exit(EXIT_FAILURE);
    }

    m_array_list *list = malloc(sizeof(m_array_list));
    if (NULL == list)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    list->capacity = capacity;
    list->size = 0;
    list->element_data = malloc(sizeof(void *) * capacity);
    if (NULL == list->element_data)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return list;
}

extern m_array_list *m_array_list_new_with_array(void **array, size_t array_size)
{
    if (NULL == array)
    {
        perror("array must not be null");
        exit(EXIT_FAILURE);
    }
    if (array_size < 0)
    {
        perror("array_size must be positive");
        exit(EXIT_FAILURE);
    }

    m_array_list *list = malloc(sizeof(m_array_list));
    if (NULL == list)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    list->capacity = array_size;
    list->size = array_size;
    list->element_data = malloc(sizeof(void *) * array_size);
    if (NULL == list->element_data)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < array_size; i++)
    {
        list->element_data[i] = array[i];
    }
    return list;
}

extern void m_array_list_free(m_array_list *list)
{
    if (NULL == list)
    {
        return;
    }
    if (NULL != list->element_data)
    {
        free(list->element_data);
    }
    free(list);
}

extern void m_array_list_and_data_free(m_array_list **list, void (*free_element)(void *))
{
    if (NULL == list || NULL == *list)
    {
        return;
    }
    if (NULL != (*list)->element_data)
    {
        // todo: 解决指针相同时重复释放的问题
        for (size_t i = 0; i < (*list)->size; i++)
        {
            if (NULL != (*list)->element_data[i])
            {
                free_element((*list)->element_data[i]);
                (*list)->element_data[i] = NULL;
            }
        }
        free((*list)->element_data);
    }
    free(*list);
    *list = NULL;
}

extern void *array_list_get(m_array_list *list, size_t index)
{
    if (NULL == list)
    {
        perror("list must not be null");
        exit(EXIT_FAILURE);
    }
    if (index < 0 || index >= list->size)
    {
        perror("index out of bounds");
        exit(EXIT_FAILURE);
    }
    return list->element_data[index];
}

extern void array_list_set(m_array_list *list, size_t index, void *element)
{
    if (NULL == list)
    {
        perror("list must not be null");
        exit(EXIT_FAILURE);
    }
    if (index < 0 || index >= list->size)
    {
        perror("index out of bounds");
        exit(EXIT_FAILURE);
    }
    list->element_data[index] = element;
}

extern bool array_list_add(m_array_list *list, void *element)
{
    if (NULL == list)
    {
        perror("list must not be null");
        exit(EXIT_FAILURE);
    }
    ensure_capacity_internal(list, list->size + 1);
    list->element_data[list->size++] = element;
    return true;
}

extern size_t array_list_size(m_array_list *list)
{
    if (NULL == list)
    {
        perror("list must not be null");
        exit(EXIT_FAILURE);
    }
    return list->size;
}

extern void *array_list_get_and_delete(m_array_list *list, size_t index)
{
    if (NULL == list)
    {
        perror("list must not be null");
        exit(EXIT_FAILURE);
    }
    if (index < 0 || index >= list->size)
    {
        perror("index out of bounds");
        exit(EXIT_FAILURE);
    }
    void *temp = array_list_get(list, index);
    remove_item_from_array(list->element_data, list->size, index);
    list->size--;
    return temp;
}

extern bool remove_from_array_list_by_value(m_array_list *list, void *value)
{
    list_null_check(list);
    void *temp;
    for (size_t i = 0; i < list->size; i++)
    {
        if (list->element_data[i] == value)
        {
            remove_item_from_array(list->element_data, list->size, i);
            return true;
        }
    }
    return false;
}

extern bool remove_from_list_by_predicate_and_release_data(m_array_list *list, int(*predicate(void *)), void (*release_data)(void *))
{
    list_null_check(list);
    if (NULL == predicate)
    {
        perror("the predicate function must be not NULL");
        exit(EXIT_FAILURE);
    }
    int release_data_memory = 1;
    if (NULL == release_data)
    {
        release_data_memory = 0;
        perror("the release_data function is null, a memory leak may result");
    }
    bool op_result = false;
    for (size_t i = 0; i < list->size; i++)
    {
        if (predicate(list->element_data[i]))
        {
            op_result = true;
            if (release_data_memory)
            {
                release_data(list->element_data[i]);
            }
            remove_item_from_array(list->element_data, list->size, i);
            list->size--;
        }
    }
    return op_result;
}

extern bool remove_from_list_by_cmp_and_release_data(m_array_list *list, void *value, int(*cmp(void *, void *)), void (*release_data)(void *))
{
    list_null_check(list);
    if (NULL == cmp)
    {
        perror("the cmp function must be not NULL");
        exit(EXIT_FAILURE);
    }
    int release_data_memory = 1;
    if (NULL == release_data)
    {
        release_data_memory = 0;
        perror("the release_data function is null, a memory leak may result");
    }
    bool op_result = false;

    for (size_t i = 0; i < list->size; i++)
    {
        if (0 == cmp(value, list->element_data[i]))
        {
            op_result = true;
            if (release_data_memory)
            {
                release_data(list->element_data[i]);
            }
            remove_item_from_array(list->element_data, list->size, i);
            list->size--;
        }
    }
    return op_result;
}

/**
 * ======================== █ █▄ █ ▀█▀ ██▀ █▀▄ █▄ █ ▄▀▄ █   =========================
 * ======================== █ █ ▀█  █  █▄▄ █▀▄ █ ▀█ █▀█ █▄▄ =========================
 */

static inline void ensure_capacity_internal(m_array_list *list, size_t min_capacity)
{
    ensure_explicit_capacity(list, calculate_capacity(list, min_capacity));
}

static inline void ensure_explicit_capacity(m_array_list *list, size_t min_capacity)
{
    if (min_capacity > list->capacity)
    {
        grow(list, min_capacity);
    }
}

static inline size_t calculate_capacity(m_array_list *list, size_t min_capacity)
{
    return min_capacity;
}

static inline void grow(m_array_list *list, size_t min_capacity)
{
    list_null_check(list);
    if (min_capacity < 0)
    {
        perror("min_capacity must be positive");
        exit(EXIT_FAILURE);
    }
    if (min_capacity > MAX_ARRAY_SIZE)
    {
        perror("min_capacity must be less than MAX_ARRAY_SIZE");
        exit(EXIT_FAILURE);
    }
    size_t old_capacity = list->capacity;
    size_t new_capacity = old_capacity + (old_capacity >> 1);
    if (new_capacity < min_capacity)
    {
        new_capacity = min_capacity;
    }
    if (new_capacity > MAX_ARRAY_SIZE)
    {
        new_capacity = MAX_ARRAY_SIZE;
    }
    list->element_data = realloc(list->element_data, sizeof(void *) * new_capacity);
    if (NULL == list->element_data)
    {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    list->capacity = new_capacity;
}

static inline void list_null_check(m_array_list *list)
{
    if (NULL == list)
    {
        perror("list must not be null");
        exit(EXIT_FAILURE);
    }
}

static inline void remove_item_from_array(void **list, size_t array_size, size_t item_index)
{
    if (NULL == list || item_index == array_size - 1)
    {
        array_size--;
        return;
    }
    if (item_index >= array_size)
    {
        perror("index out of bounds");
        exit(EXIT_FAILURE);
    }
    for (size_t i = item_index; i < array_size - 1; i++)
    {
        list[i] = list[i + 1];
    }
    list[array_size] = NULL;
}

/**
 * =============================== ▀█▀ ██▀ ▄▀▀ ▀█▀ ==================================
 * ===============================  █  █▄▄ ▄█▀  █  ==================================
 */

#if defined(_TEST_)

static inline void int_free(void *p)
{
    if (NULL == p)
    {
        return;
    }
    free(p);
}

static inline void array_list_nornal_test(void)
{
    m_array_list *list = m_array_list_new();

    int *p;
    for (size_t i = 0; i < 20; i++)
    {
        p = malloc(sizeof(int));
        *p = i;
        array_list_add(list, (void *)p);
        printf("lsit's size: %zu\n", list->size);
        printf("list's capacity: %zu\n", list->capacity);
    }

    for (size_t i = 0; i < list->size; i++)
    {
        printf("the element of index %zu is %d\n", i, *((int *)array_list_get(list, i)));
    }

    printf("list's size: %zu\n", list->size);
    p = array_list_get_and_delete(list, 0);

    printf("list[0]: %d\n", *p);
    printf("list's size: %zu\n", list->size);
    m_array_list_and_data_free(&list, int_free);
}

extern void array_list_test(void)
{
    array_list_nornal_test();
}
#endif
