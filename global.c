#include "global.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define DIVIDING_LINE_LEN 100

static void print_prefix(size_t len, char c)
{
    for (size_t i = 0; i < len; i++)
    {
        printf("%c", c);
    }
}

static void print_suffix(size_t len, char c)
{
    for (size_t i = 0; i < len; i++)
    {
        printf("%c", c);
    }
    printf("\n");
}

void print_dividing_line(const char *str)
{
    size_t str_len = strlen(str);
    if (str_len >= DIVIDING_LINE_LEN)
    {
        printf("%s\n", str);
        return;
    }

    size_t prefix_len = (DIVIDING_LINE_LEN - str_len) / 2;
    size_t subfix_len = DIVIDING_LINE_LEN - str_len - prefix_len;
    print_prefix(prefix_len, '-');
    printf("%s", str);
    print_suffix(subfix_len, '-');
}

void multi_dividing_line(int n_str, char const *str, ...)
{
    const char *str_array[n_str];
    size_t str_len_sum = 0;
    va_list ap;
    va_start(ap, str);
    for (int i = 0; i < n_str; i++)
    {
        str_array[i] = str;
        str_len_sum += strlen(str);
        str = va_arg(ap, char const *);
    }

    str_len_sum += n_str - 1;
    size_t prefix_len = (DIVIDING_LINE_LEN - str_len_sum) / 2;
    size_t subfix_len = DIVIDING_LINE_LEN - str_len_sum - prefix_len;
    print_prefix(prefix_len, '-');
    for (int i = 0; i < n_str; i++)
    {
        printf("%s", str_array[i]);
        if (i != n_str - 1)
        {
            printf("-");
        }
    }
    print_suffix(subfix_len, '-');
    va_end(ap);
}
