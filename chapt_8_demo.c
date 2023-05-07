#include "chapt_8_demo.h"

void array_demo(void)
{
    int *c = malloc(5 * sizeof(int));

    int value;
    int i = 0;
    while ((value = i++) < 5)
    {
        c[value] = value;
    }
    int a[5] = {4, 3, 2, 1, 0};

    i = 0;
    while ((value = i++) < 5)
    {
        printf("%d ", c[value]);
    }
    printf("\n");

    c = a;
    i = 0;
    while ((value = i++) < 5)
    {
        printf("%d ", c[value]);
    }
    printf("\n");
}

void chapt_8_demo_run(void)
{
    printf("--------------------chapt_8_demo--------------------\n");
    array_demo();
    printf("====================chapt_8_demo====================\n\n");
}