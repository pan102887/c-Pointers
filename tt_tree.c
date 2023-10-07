#include "tt_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========================= struct define ===========================

/* ******** node struct ********* */
/*|————————————————————————————————————————————|*/
/*|head:                                       |*/
/*|       node_info_t node_info;               |*/
/*|       size_t left_key_size;                |*/
/*|       size_t left_data_size;               |*/
/*|       size_t right_key_size;               |*/
/*|       size_t right_data_size;              |*/
/*|————————————————————————————————————————————|*/
/*|left:  void *left_child                     |*/
/*|————————————————————————————————————————————|*/
/*|right: void *midle_child                    |*/
/*|————————————————————————————————————————————|*/
/*|right: void *right_child                    |*/
/*|————————————————————————————————————————————|*/
/*|right: void *fourth_child                   |*/
/*|————————————————————————————————————————————|*/
/*|data:  tt_key_t left_key;                   |*/
/*|       value_t left_value;                  |*/
/*|       tt_key_t right_key;                  |*/
/*|       value_t right_value;                 |*/
/*|————————————————————————————————————————————|*/

typedef unsigned char node_info_t;


#define NODE_TYPE_MASK ((node_info_t)0xC0) /*1100 0000*/

#define TWO_NODE_TYPE ((node_info_t)(0))
#define THREE_NODE_TYPE ((node_info_t)(1))
#define FOUR_NODE_TYPE ((node_info_t)(2))
#define DETAULT_NODE_TYPE TWO_NODE_TYPE

#define NODE_INFO(node) (*(node_info_t *)node)
#define SET_NODE_TYPE(node, type) (NODE_INFO(node) = (NODE_INFO(node) & ~NODE_TYPE_MASK) | (type << 6))
#define GET_NODE_TYPE(node) ((NODE_INFO(node) & NODE_TYPE_MASK) >> 6)

#define IS_TWO_NODE(node) (GET_NODE_TYPE(node) == TWO_NODE_TYPE)
#define IS_THREE_NODE(node) (GET_NODE_TYPE(node) == THREE_NODE_TYPE)
#define IS_FOUR_NODE(node) (GET_NODE_TYPE(node) == FOUR_NODE_TYPE)

#define LEFT_KEY_SIZE(node) (*(size_t*)(node + sizeof(node_info_t)))
#define LEFT_DATA_SIZE(node) (*(size_t *)(node + sizeof(node_info_t) + sizeof(size_t)))

#define RIGHT_KEY_SIZE(node) (*(size_t*)(node + sizeof(node_info_t) + sizeof(size_t) * 2))
#define RIGHT_DATA_SIZE(node) (*(size_t *)(node + sizeof(node_info_t) + sizeof(size_t) * 3))
#define HEAD_SIZE (sizeof(node_info_t) + (sizeof(size_t) * 4))


#define LEFT_CHILD(node) (*(void **)(node + HEAD_SIZE))
#define MIDDLE_CHILD(node) (*(void **)(node + HEAD_SIZE + sizeof(void *)))
#define RIGHT_CHILD(node) (*(void **)(node + HEAD_SIZE + sizeof(void *) * 2))
#define TEMP_CHILD(node) (*(void **)(node + HEAD_SIZE + sizeof(void *) * 3))

#define CHILD_P_SIZE (sizeof(void *) * 4)


#define LEFT_KEY(node) (*(tt_key_t*)(node + HEAD_SIZE + CHILD_P_SIZE))
#define LEFT_DATA(node) (*(value_t*)(node + HEAD_SIZE + CHILD_P_SIZE + sizeof(tt_key_t)))

#define RIGHT_KEY(node) (*(tt_key_t*)(node + HEAD_SIZE + CHILD_P_SIZE + sizeof(tt_key_t) + sizeof(value_t)))
#define RIGHT_DATA(node) (*(value_t*)(node + HEAD_SIZE + CHILD_P_SIZE + sizeof(tt_key_t) + sizeof(value_t) + sizeof(tt_key_t)))

#define KEY_VALUE_SIZE (sizeof(tt_key_t) + sizeof(value_t))
#define DATA_P_SIZE (KEY_VALUE_SIZE * 2)
#define NODE_SIZE (HEAD_SIZE + CHILD_P_SIZE + DATA_P_SIZE)

// ========================= macro define ===========================



#define POINTER_FREE(ptr) \
    do                    \
    {                     \
        if (NULL == ptr)  \
            break;        \
        free(ptr);        \
        ptr = NULL;       \
    } while (0)

#define SET_DATA(data_ptr,data,size)    \
    do                                  \
    {                                   \
        if (NULL != data_ptr)           \
        {                               \
            free(data_ptr);             \
            data_ptr = NULL;            \
        }                               \
        data_ptr = malloc(size);        \
        if (NULL == data_ptr)           \
        {                               \
            perror("malloc");           \
            exit(EXIT_FAILURE);         \
        }                               \
        memcpy(data_ptr, data, size);   \
    } while (0)

// ========================= static function ===========================

static inline void *new_node(void);
static inline void free_node(void **node);
static inline void set_left_data(void *node, char *data, size_t size);
static inline void set_right_data(void *node, char *data, size_t size);

static inline void *new_node(void)
{
    void *node = NULL;
    node = malloc(NODE_SIZE);
    if (node == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    SET_NODE_TYPE(node, DETAULT_NODE_TYPE);

    LEFT_KEY_SIZE(node) = 0;
    LEFT_DATA_SIZE(node) = 0;
    RIGHT_KEY_SIZE(node) = 0;
    RIGHT_DATA_SIZE(node) = 0;

    LEFT_CHILD(node) = NULL;
    MIDDLE_CHILD(node) = NULL;
    RIGHT_CHILD(node) = NULL;
    TEMP_CHILD(node) = NULL;

    LEFT_KEY(node) = NULL;
    LEFT_DATA(node) = NULL;
    RIGHT_KEY(node) = NULL;
    RIGHT_DATA(node) = NULL;
    return node;
}

static inline void free_node(void **node)
{
    if (NULL == node || NULL == *node)
    {
        return;
    }
    POINTER_FREE(LEFT_CHILD(*node));
    POINTER_FREE(MIDDLE_CHILD(*node));
    POINTER_FREE(RIGHT_CHILD(*node));
    POINTER_FREE(TEMP_CHILD(*node));
    POINTER_FREE(LEFT_KEY(*node));
    POINTER_FREE(LEFT_DATA(*node));
    POINTER_FREE(RIGHT_KEY(*node));
    POINTER_FREE(RIGHT_DATA(*node));
    POINTER_FREE(*node);
}

static inline void set_left_data(void *node, char *data, size_t size)
{
    if (NULL == node || NULL == data || size == 0)
    {
        return;
    }
    LEFT_DATA_SIZE(node) = size;
    SET_DATA(LEFT_DATA(node), data, size);
}

static inline void set_right_data(void *node, char *data, size_t size)
{
    if (NULL == node || NULL == data || size == 0)
    {
        return;
    }
    RIGHT_DATA_SIZE(node) = size;
    SET_DATA(RIGHT_DATA(node), data, size);
}


extern tt_tree_entry *tt_tree_create(void)
{
    tt_tree_entry *tree = NULL;
    tree = malloc(sizeof(tt_tree_entry));
    if (NULL == tree)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    tree->root = new_node();
    return tree;
}
extern void tt_tree_destroy(tt_tree_entry *tree)
{
    if (NULL == tree)
    {
        return;
    }
    free_node(&tree->root);
    POINTER_FREE(tree);
}
extern void tt_tree_insert(tt_tree_entry *tree, tt_key_t key, value_t value, int (*compare)(value_t, value_t))
{
    if (NULL == tree || NULL == key || NULL == value || NULL == compare)
    {
        return;
    }
    void *node = NULL;
    node = tree->root;
}
extern void tt_tree_delete(tt_tree_entry *tree, tt_key_t key);
extern value_t tt_tree_search(tt_tree_entry *tree, tt_key_t key);

/**
 * ======================== ▀█▀ ██▀ ▄▀▀ ▀█▀  ========================
 * ========================  █  █▄▄ ▄█▀  █   ========================
 */
#ifdef _TEST_
#include <assert.h>

static inline void free_test(void)
{
    void *node = NULL;
    node = new_node();
    assert(node != NULL);

    set_left_data(node, "hello", 6);
    assert(LEFT_DATA_SIZE(node) == 6);
    assert(LEFT_DATA(node) != NULL);
    
    POINTER_FREE(LEFT_DATA(node));
    assert(LEFT_DATA(node) == NULL);

    free_node(&node);
    assert(node == NULL);
}
static inline void micro_test(void)
{
    void *node = NULL;
    node = new_node();
    printf("node type: %s\n", IS_TWO_NODE(node) ? "two node" : "three node");

    set_left_data(node, "hello", 6);
    set_right_data(node, "world", 6);
    printf("left data size: %ld\n", LEFT_DATA_SIZE(node));
    printf("left data: %s\n", LEFT_DATA(node));
    printf("right data size: %ld\n", RIGHT_DATA_SIZE(node));
    printf("right data: %s\n", RIGHT_DATA(node));
    free_node(&node);
    printf("node: %p\n", node);
}
extern void tt_tree_test(void)
{
    free_test();
    micro_test();
}
#endif
