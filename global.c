#include "global.h"

#include <stdio.h>
#include <string.h>

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
