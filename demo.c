#include <stdio.h>

#define ARRAY_SIZE 5
int main(void) {
    int array[ARRAY_SIZE] = {0, 1, 2, 3, 4};
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += array[i];
    }
    printf("sum = %d\n", sum);
    printf("str test\n");
    return 0;
}