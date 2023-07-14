#include "chapt_12_demo.h"

#include "global.h"
#include "alloc.h"

#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNode
{
    ListData *data;
    struct LinkedListNode *next;
} LinkedListNode;

void list_entry_init(ListEntry *entry);

/**
 * @brief create a new list entry object
 *
 * @return ListEntry* pointer to new list entry object
 */
ListEntry *new_entry()
{
    ListEntry *entry = MALLOC(1, ListEntry);
    entry->root = NULL;
    entry->tail = NULL;
    entry->back = NULL;
    entry->free_list = NULL;
    entry->front = NULL;
    entry->get = NULL;
    entry->pop_back = NULL;
    entry->pop_front = NULL;
    entry->push_back = NULL;
    entry->push_front = NULL;

    list_entry_init(entry);
    return entry;
}

/**
 * @brief copy list data
 *
 * @param data list data
 * @return ListData* pointer to new list data
 */
ListData *list_data_cpy(ListData *data)
{
    ListData *new_data = alloc(sizeof(ListData));
    new_data->data = alloc(data->data_size);
    memcpy(new_data->data, data->data, data->data_size);
    new_data->data_size = data->data_size;
    return new_data;
}

/**
 * @brief push back
 *
 * @param this list entry
 * @param data need to push back data
 * @param size data size
 */
void push_back(ListEntry *this, ListData *data)
{
    if (NULL == data || NULL == this || NULL == this->root || NULL == this->tail)
    {
        return;
    }

    while (this->tail != NULL && ((LinkedListNode *)(this->tail))->next != NULL)
    {
        this->tail = ((LinkedListNode *)(this->tail))->next;
    }

    LinkedListNode *new_node = MALLOC(1, LinkedListNode);
    new_node->data = list_data_cpy(data);
    new_node->next = NULL;

    ((LinkedListNode *)(this->tail))->next = new_node;
    this->tail = ((LinkedListNode *)(this->tail))->next;
}

/**
 * @brief push front
 * 
 * @param this list entry
 * @param data push front data
 */
void push_front(ListEntry *this, ListData *data)
{
    if (NULL == data || NULL == this || NULL == this->root)
    {
        return;
    }

    LinkedListNode *new_node = MALLOC(1, LinkedListNode);
    new_node->data = list_data_cpy(data);
    new_node->next = ((LinkedListNode *)(this->root))->next;

    ((LinkedListNode *)(this->root))->next = new_node;
}

ListData *pop_front(ListEntry *this)
{
    if (NULL == this || NULL == this->root || NULL == ((LinkedListNode *)(this->root))->next)
    {
        return NULL;
    }

    LinkedListNode *node = ((LinkedListNode *)(this->root))->next;
    ListData *data = node->data;
    ((LinkedListNode *)(this->root))->next = node->next;
    free(node);
    return data;
}

ListData *pop_back(ListEntry *this)
{
    if (NULL == this || NULL == this->root || NULL == ((LinkedListNode *)(this->root))->next)
    {
        return NULL;
    }

    LinkedListNode *node = ((LinkedListNode *)(this->root))->next;
    LinkedListNode *prev = NULL;
    while (node->next != NULL)
    {
        prev = node;
        node = node->next;
    }

    ListData *data = node->data;
    prev->next = NULL;
    free(node);
    return data;
}

ListData *front(ListEntry *this)
{
    if (NULL == this || NULL == this->root || NULL == ((LinkedListNode *)(this->root))->next)
    {
        return NULL;
    }

    return ((LinkedListNode *)(this->root))->next->data;
}

ListData *back(ListEntry *this)
{
    if (NULL == this || NULL == this->tail)
    {
        return NULL;
    }

    return ((LinkedListNode *)this->tail)->data;
}

ListData *get(ListEntry *this, size_t index)
{
    if (NULL == this || NULL == this->root || NULL == ((LinkedListNode *)(this->root))->next)
    {
        return NULL;
    }

    LinkedListNode *node = ((LinkedListNode *)(this->root))->next;
    size_t i = 0;
    while (node != NULL && i < index)
    {
        node = node->next;
        i++;
    }

    if (NULL == node)
    {
        return NULL;
    }

    return node->data;
}

/**
 * @brief init list entry
 *
 * @param entry list entry
 */

void free_list(ListEntry **this)
{
    if (NULL == this || NULL == *this)
    {
        return;
    }

    LinkedListNode *node = ((LinkedListNode *)((*this)->root))->next;
    LinkedListNode *next = NULL;
    while (node != NULL)
    {
        next = node->next;
        if (node->data != NULL)
        {
            if (node->data->data != NULL)
            {
                free(node->data->data);
            }
            free(node->data);
        }
        free(node);
        node = next;
    }
    free(*this);
    *this = NULL;
}

void list_entry_init(ListEntry *entry)
{
    if (NULL == entry)
    {
        exit(1);
    }
    LinkedListNode *root = MALLOC(1, LinkedListNode);
    root->data = NULL;
    root->next = NULL;

    entry->root = root;
    entry->tail = root;
    entry->push_back = push_back;
    entry->push_front = push_front;
    entry->pop_front = pop_front;
    entry->pop_back = pop_back;
    entry->front = front;
    entry->back = back;
    entry->free_list = free_list;
}

#ifdef _TEST_
#include <stdio.h>

void chapt_12_demo_test(void) {
    print_dividing_line("chapt_12_demo_test");
    ListEntry *entry = new_entry();

    ListData data;
    data.data = "hello world";
    data.data_size = strlen(data.data) + 1;
    entry->push_back(entry, &data);

    data.data = "hello world 2";
    data.data_size = strlen(data.data) + 1;
    entry->push_back(entry, &data);

    ListData *datap = entry->front(entry);
    printf("data: %s\n", (char *)datap->data);

    ListData *datap2 = entry->back(entry);
    printf("data: %s\n", (char *)datap2->data);

    ListData *datap3 = entry->pop_front(entry);
    printf("data: %s\n", (char *)datap3->data);

    ListData *datap4 = entry->front(entry);
    printf("data: %s\n", (char *)datap4->data);

    free_list(&entry);
    multi_dividing_line(2, "chapt_12_demo_test", "end");
}
#endif // _TEST_