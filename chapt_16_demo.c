#include "chapt_16_demo.h"

#ifdef _TEST_
#include <stdio.h>

extern void chapt_16_demo_run(void)
{
    int array[] = {1, 2, 3, 4, 5};
    printf("this size of array is %ld\n", sizeof(array) / sizeof(int));
    int *p = array;
    printf("this size of pointer is %ld\n", sizeof(p) / sizeof(int));
}
#endif