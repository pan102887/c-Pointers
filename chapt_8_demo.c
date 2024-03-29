#include "chapt_8_demo.h"

#include "global.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

char const *keyword[] = {
    "do",
    "for",
    "if",
    "register",
    "return",
    "switch",
    "while",
    NULL};

#define NKEYS (sizeof(keyword) / sizeof(keyword[0]))

int lookup_keyword(char const *const desired_word, char const *keyword_table[], int const size)
{
    char const **kwp;
    for (kwp = keyword_table; kwp < keyword_table + size; kwp++)
    {
        if (strcmp(desired_word, *kwp) == 0)
        {
            return kwp - keyword_table;
        }
    }
    return -1;
}

int lookup_keyword_without_length(char const *const desired_word, char const *keyword_table[])
{
    char const **kwp;
    for (kwp = keyword_table; *kwp != NULL; kwp++)
    {
        if (strcmp(desired_word, *kwp) == 0)
        {
            return kwp - keyword_table;
        }
    }
    return -1;
}

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

void func_1(int *mat, int row, int col)
{
    int sum = 0;
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++, mat++)
        {
            sum += *mat;
        }
    }
    printf("sum: %d\n", sum);
}

void func_2(int mat[3][10])
{
    int sum = 0;
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 10; j++)
        {
            sum += mat[i][j];
        }
    }
    printf("sum: %d\n", sum);
}
double average(int n_value, ...)
{

    int count = 0;
    double sum = 0;

    va_list var_arg;
    va_start(var_arg, n_value);

    for (; count < n_value; count += 1)
    {
        int p = (va_arg(var_arg, int));
        printf("%d\n", p);
        sum += p;
    }

    va_end(var_arg);
    return sum / n_value;
}

void test_average()
{
    double a = average(5, 2, 3, 4, 5, 8);
    printf("average: %lf\n", a);
}

#ifdef _TEST_
static const char *memory_boundary_alignment = "chapt_8_demo";
void chapt_8_demo_run()
{
    print_dividing_line(memory_boundary_alignment);
    array_demo();
    int mat[3][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {9, 8, 7, 6, 5, 4, 3, 2, 1},
        {1, 3, 5, 7, 9, 2, 4, 6, 8}};
    func_1(mat[0], 3, 10);
    func_2(mat);
    int i = lookup_keyword("while", keyword, NKEYS);
    printf("i: %d\n", i);

    i = lookup_keyword_without_length("while", keyword);
    printf("i: %d\n", i);
    test_average();

    print_dividing_line("");
}
#endif