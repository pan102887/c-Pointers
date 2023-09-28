#include "tt_tree.h"
#include <stdio.h>
#include <stdlib.h>

/*|————————————————|*/
/*|head:  char     |*/
/*|————————————————|*/
/*|data:  void*    |*/
/*|————————————————|*/
/*|left:  void*    |*/
/*|————————————————|*/
/*|right: void*    |*/
/*|————————————————|*/
/*|<midle: void*>  |*/
/*|————————————————|*/
typedef struct
{
    unsigned char head_info;
    size_t data_size;
} node_info;

typedef unsigned char node_type;
#define TWO_NODE (node_type)0x10000000
#define THREE_NODE (node_type)0x00000000
#define IS_TWO_NODE(node) (NODE_INFO(node).head_info>>7)

#define NODE_INFO_SIZE (sizeof(node_info))
#define THREE_NODE_SIZE (NODE_INFO_SIZE+sizeof(void*)*4)
#define TWO_NODE_SIZE (NODE_INFO_SIZE+sizeof(void*)*3)

#define NODE_INFO(node) (*(node_info*)node)
#define DATA(node) (*(void**)(node+NODE_INFO_SIZE))
#define LEFT_CHILD(node) (*(void**)(node+NODE_INFO_SIZE+sizeof(void*)))
#define RIGHT_CHILD(node) (*(void**)(node+NODE_INFO_SIZE+sizeof(void*)*2))
#define MIDDLE_CHILD(node) (*(void**)(node+NODE_INFO_SIZE+sizeof(void*)*3))

static inline void *new_node(node_type type)
{
    void *node = NULL;
    node = malloc(THREE_NODE_SIZE);
    if (node == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    NODE_INFO(node).head_info = type;
    DATA(node) = NULL;
    LEFT_CHILD(node) = NULL;
    RIGHT_CHILD(node) = NULL;
    MIDDLE_CHILD(node) = NULL;
    return node;
}
/**
 * ======================== ▀█▀ ██▀ ▄▀▀ ▀█▀  ========================
 * ========================  █  █▄▄ ▄█▀  █   ========================
 */

#ifdef _TEST_
static inline void micro_test(void)
{
    int *i = malloc(sizeof(int));
    *i = 10;

    char *p = new_node(TWO_NODE);
    LEFT_CHILD(p) = (void *)i;
    printf("i = %d\n", *((int*)(LEFT_CHILD(p))));
    free(p);
    printf("node type: %s\n", IS_TWO_NODE(p) ? "two node" : "three node");
}
extern void tt_tree_test(void)
{
    micro_test();
}
#endif




