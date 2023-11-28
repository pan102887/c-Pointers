#include "my_data.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief data compare
 * 
 * @param data1 
 * @param data2 
 * @return int 
 */
int data_compare(DATA *data1, DATA *data2) {
    int min_size = data1->data_size < data2->data_size ? data1->data_size : data2->data_size;
    int result;
    if (data1->data_size != data2->data_size) {
        result = memcmp(data1->data, data2->data, min_size);
        if (result != 0) {
            return result;
        } else {
            return data1->data_size - data2->data_size;
        }
    }
    else
    {
        return memcmp(data1->data, data2->data, data1->data_size);
    }
}

/**
 * @brief copy data
 * 
 * @param data 
 * @return DATA* 
 */
DATA *cpy_data(DATA *data) {
    DATA *new_data = malloc(sizeof(DATA));
    new_data->data = malloc(data->data_size);
    memcpy(new_data->data, data->data, data->data_size);
    new_data->data_size = data->data_size;
    return new_data;
}