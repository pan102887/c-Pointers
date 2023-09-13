#ifndef _CHAPT_12_DEMO_H_
#define _CHAPT_12_DEMO_H_
#include <stddef.h>

typedef struct ListData
{
    void *data;
    size_t data_size;
} ListData;

typedef struct ListEntry
{
    void *root;
    void *tail;
    /**
     * @brief push a new data to list back
     * 
     */
    void (*push_back)(struct ListEntry *this, ListData *data);
    /**
     * @brief push a new data to list front
     * 
     */
    void (*push_front)(struct ListEntry *this, ListData *data);
    /**
     * @brief get data from list front
     * 
     */
    ListData *(*pop_front)(struct ListEntry *this);
    /**
     * @brief get data from list back
     * 
     */
    ListData *(*pop_back)(struct ListEntry *this);
    /**
     * @brief front
     * 
     */
    ListData *(*front)(struct ListEntry *this);
    /**
     * @brief back
     * 
     */
    ListData *(*back)(struct ListEntry *this);
    ListData *(*get)(struct ListEntry *this, size_t index);
    void (*free_list)(struct ListEntry **this);
} ListEntry;

ListEntry *new_entry();


#ifdef _TEST_
void chapt_12_demo_test(void);
#endif // _TEST_

#endif // _CHAPT_12_DEMO_H_