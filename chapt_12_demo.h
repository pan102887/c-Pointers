#ifndef _CHAPT_12_DEMO_H_
#define _CHAPT_12_DEMO_H_
#include <stddef.h>

typedef struct LinkedListEntry
{
    void *linkedList;
    void *linkedListTail;
    int (*push_back)(void *data, size_t size);
} LinkedListEntry;

LinkedListEntry *linked_list_entry_new();


#endif