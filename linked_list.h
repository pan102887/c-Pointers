#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#include "my_data.h"
#include <stdbool.h>

/**
 * @brief 一个简单的链表
 *        一个链表的节点包含一个存储的数据和一个指向下一个节点的指针，
 *        若需要链表支持泛型，难点在于需要在编译时如何确定数据所占用
 *        的存储空间大小。
 *        可以认识到，
 */
typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

bool sll_insert(register Node **linkp, Node *new_node, int (*compare)(void *data1, void *data2));
bool sll_insert_cpy(register Node **linkp, void *data, int (*compare)(void *data1, void *data2), void *(*cpy)(void *data));

#endif