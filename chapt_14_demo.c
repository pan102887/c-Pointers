#include "chapt_14_demo.h"
#include "global.h"

#include <stdio.h>

void macro_test(void)
{
    char *file_name = __FILE__;
    printf("current file name: %s\n", file_name);

    int line_num = __LINE__;
    printf("current line: %d\n", line_num);

    char *date = __DATE__;
    printf("compile date: %s\n", date);

    char *time = __TIME__;
    printf("compile time: %s\n", time);

    int is_ansic = __STDC__;
    printf("is ansic: %d\n", is_ansic);
}

#define SQUARE(x) ((x) * (x))
void square_test(void)
{
    double x = 4.0;
    printf("x: %f\n", (x++));
    printf("x: %f\n", (x++));

    x = 4.0;
    double y = SQUARE(x++);
    printf("y: %f\n", y);
    print_dividing_line("");

    x = 4.0;
    printf("x: %f, x: %f\n", (++x), (x++));

    x = 4.0;
    y = ((++x) * (x++));
    printf("y: %f\n", y);
}
#define PRINT(FORMAT, ...) printf("the value of " #__VA_ARGS__ " is: " #FORMAT "\n", __VA_ARGS__)
static void print_test(void)
{
    PRINT("%d, %d, %d", 10, 20, 3 + 8);
}

#define ADD_TO_SUM(sum_number, value) sum##sum_number += value
static void add_to_sum_test(void)
{
    int sum1 = 0;
    int sum2 = 0;
    int sum_number = 1;
    ADD_TO_SUM(1, 10);
    ADD_TO_SUM(2, 20);
    ADD_TO_SUM(_number, 30);
    printf("sum1: %d, sum2: %d\n", sum1, sum2);
    printf("sum_number: %d\n", sum_number);
}

void chapt_14_demo_run(void)
{
    print_dividing_line("chapt_14_demo_run");
    macro_test();
    square_test();
    print_test();
    add_to_sum_test();
    print_dividing_line("");
}
