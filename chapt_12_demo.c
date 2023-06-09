#include "chapt_12_demo.h"

#include "alloc.h"

#include <stdlib.h>


typedef struct LinkedList
{
    void *data;
    struct LinkedList *next;
    int (*push_back)(struct LinkedList *tail, void *data, size_t size);
} LinkedList;

int push_back(LinkedList *tail, void *data, size_t size) 
{
    LinkedList *new_node = MALLOC(1, LinkedList);

    new_node->data = alloc(size);
    memcpy(new_node->data, data, size);
    new_node->next = NULL;
    tail->next = new_node;
    return 1;
}

LinkedListEntry *linked_list_entry_new()
{
    LinkedList *head = MALLOC(1, LinkedList);
    head->data = NULL;
    head->next = NULL;
    head->push_back = push_back;
    
    LinkedListEntry *entry = MALLOC(1, LinkedListEntry);
    
    entry->linkedList = head;
    return entry;
}