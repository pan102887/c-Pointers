#ifndef CP_DATA_STRUCTURES_MY_DATA_H
#define CP_DATA_STRUCTURES_MY_DATA_H

#include <stddef.h>

typedef struct DATA
{
    void *data;
    size_t data_size;

    int (*compare)(struct DATA *data1, struct DATA *data2);
} DATA;

int data_compare(DATA *data1, DATA *data2);
DATA *cpy_data(DATA *data);

#endif
