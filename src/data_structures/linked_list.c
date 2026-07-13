#include "linked_list.h"

#include "global.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



bool sll_insert(register Node **linkp, register Node *new_node, int (*compare)(void *, void *))
{
    register Node *current;

    while ((current = *linkp) != NULL && compare(current->data, new_node->data) < 0)
    {
        linkp = &current->next;
    }

    new_node->next = current;
    *linkp = new_node;
    return true;
}

bool sll_insert_cpy(register Node **linkp, void *data, int (*compare)(void *, void *), void *(*cpy)(void *))
{
    register Node *current;
    register Node *new_node;
    while ((current = *linkp) != NULL && compare(current->data, data) < 0)
    {
        linkp = &current->next;
    }

    void *data_cpy = cpy(data);
    new_node = malloc(sizeof(Node));
    new_node->data = data_cpy;
    new_node->next = current;

    *linkp = new_node;
    return true;
}

