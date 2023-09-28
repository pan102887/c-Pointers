#include "tt_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ******** node struct ********* */
/*|——————————————————————————————|*/
/*|head:  sizeof(unsigned char)  |*/
/*|     + sizeof(size_t) * 2     |*/
/*|——————————————————————————————|*/
/*|left:  sizeof(void*)          |*/
/*|——————————————————————————————|*/
/*|right: sizeof(void*)          |*/
/*|——————————————————————————————|*/
/*|midle: sizeof(void*)          |*/
/*|——————————————————————————————|*/
/*|data:  sizeof(char*) * 2      |*/
/*|——————————————————————————————|*/

typedef unsigned char node_info_t;
#define HEAD_SIZE (sizeof(node_info_t) + (sizeof(size_t) * 2))
#define CHILD_P_SIZE (sizeof(void *) * 3)
#define DATA_P_SIZE (sizeof(char *) * 2)
#define NODE_SIZE (HEAD_SIZE + CHILD_P_SIZE + DATA_P_SIZE)

#define LEFT_DATA_SIZE(node) (*(size_t *)(node + sizeof(node_info_t)))
#define RIGHT_DATA_SIZE(node) (*(size_t *)(node + sizeof(node_info_t) + sizeof(size_t)))
#define LEFT_DATA(node) (*(char **)(node + HEAD_SIZE + CHILD_P_SIZE))
#define RIGHT_DATA(node) (*(char **)(node + HEAD_SIZE + CHILD_P_SIZE + sizeof(char *)))

#define NODE_INFO(node) (*(node_info_t *)node)
#define NODE_TYPE_MASK ((node_info_t)0x80) /*1000 0000*/
#define TWO_NODE_TYPE ((node_info_t)(0 << 7))
#define THREE_NODE_TYPE ((node_info_t)(1 << 7))

#define DETAULT_NODE_TYPE TWO_NODE_TYPE

#define SET_NODE_TYPE(node, type) (NODE_INFO(node) = (NODE_INFO(node) & ~NODE_TYPE_MASK) | (type))
#define IS_TWO_NODE(node) ((NODE_INFO(node) & NODE_TYPE_MASK) < NODE_TYPE_MASK)
#define IS_THREE_NODE(node) (!IS_TWO_NODE(node))

#define LEFT_CHILD(node) (*(void **)(node + HEAD_SIZE))
#define MIDDLE_CHILD(node) (*(void **)(node + HEAD_SIZE + sizeof(void *)))
#define RIGHT_CHILD(node) (*(void **)(node + HEAD_SIZE + sizeof(void *) * 2))

#define POINTER_FREE(ptr) \
    do                    \
    {                     \
        if (NULL == ptr)  \
            break;        \
        free(ptr);        \
        ptr = NULL;       \
    } while (0)

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
    LEFT_CHILD(node) = NULL;
    RIGHT_CHILD(node) = NULL;
    MIDDLE_CHILD(node) = NULL;

    LEFT_DATA_SIZE(node) = 0;
    LEFT_DATA(node) = NULL;
    RIGHT_DATA_SIZE(node) = 0;
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
    POINTER_FREE(LEFT_DATA(*node));
    POINTER_FREE(RIGHT_DATA(*node));
    POINTER_FREE(*node);
}

static inline void set_left_data(void *node, char *data, size_t size)
{
    if (NULL != LEFT_DATA(node) && LEFT_DATA_SIZE(node) < size)
    {
        LEFT_DATA(node) = realloc(LEFT_DATA(node), sizeof(char) * size);
    }
    else
    {
        LEFT_DATA(node) = malloc(sizeof(char) * size);
    }
    LEFT_DATA_SIZE(node) = size;
    for (size_t i = 0; i < size; i++)
    {
        LEFT_DATA(node)
        [i] = data[i];
    }
}

static inline void set_right_data(void *node, char *data, size_t size)
{
    if (NULL != RIGHT_DATA(node) && RIGHT_DATA_SIZE(node) < size)
    {
        RIGHT_DATA(node) = realloc(RIGHT_DATA(node), sizeof(char) * size);
    }
    else
    {
        RIGHT_DATA(node) = malloc(sizeof(char) * size);
    }
    RIGHT_DATA_SIZE(node) = size;
    for (size_t i = 0; i < size; i++)
    {
        RIGHT_DATA(node)
        [i] = data[i];
    }
}
/**
 * ======================== ▀█▀ ██▀ ▄▀▀ ▀█▀  ========================
 * ========================  █  █▄▄ ▄█▀  █   ========================
 */

#ifdef _TEST_
static inline void micro_test(void)
{
    void *node = NULL;
    node = new_node();
    printf("node type: %s\n", IS_TWO_NODE(node) ? "two node" : "three node");

    set_left_data(node, "hello", 6);
    set_right_data(node, "world", 6);
    printf("left data: %s\n", LEFT_DATA(node));
    printf("right data: %s\n", RIGHT_DATA(node));
    free_node(&node);
    printf("node: %p\n", node);
}
extern void tt_tree_test(void)
{
    micro_test();
}
#endif
