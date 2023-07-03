#ifndef _MY_DATA_H_
#define _MY_DATA_H_

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
