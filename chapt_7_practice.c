#include "chapt_7_practice.h"

#include "global.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

int hermite(int n, int x)
{
    if (n <= 0)
    {
        return 1;
    }
    if (n > 0 && n < 2)
    {
        return 2 * x;
    }
    if (n >= 2)
    {
        return 2 * x * hermite(n - 1, x) - 2 * (n - 1) * hermite(n - 2, x);
    }
}

int my_gcd(int M, int N)
{
    if (M <= 0 || N <= 0)
    {
        return 0;
    }
    if (M < N)
    {
        int temp = M;
        M = N;
        N = temp;
    }

    int remainder = M % N;
    if (remainder == 0)
    {
        return N;
    }
    else
    {
        return my_gcd(N, remainder);
    }
}

int ascii_to_integer(char *string)
{
    int result = 0;
    // printf("value string: %s\n", string);
    char value;
    while ((value = *string++) != '\0')
    {
        result *= 10;
        result += ((int)value - '0');
        // printf("pointer: %ld,   value:%c,   result: %d\n", (long)string, value, result);
    }
    return result;
}

int max_list(int n_numbers, ...)
{
    va_list var_arg;
    va_start(var_arg, n_numbers);
    int max = va_arg(var_arg, int);

    int count = 1;
    while (count++ < n_numbers)
    {
        int current = va_arg(var_arg, int);
        max = max < current ? current : max;
    }
    va_end(var_arg);
    return max;
}

__fortify_function int my_printf(const char *__restrict __fmt, ...)
{
    return __printf_chk(__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack());
}

#ifdef _TEST_

static const char *memory_boundary_alignment = "chapt_7_practice";
void chapt_7_practice_run(void)
{
    print_dividing_line(memory_boundary_alignment);
    printf("hermite(3, 2)-> expect: 40, actual: %d\n", hermite(3, 2));
    printf("my_gcd(6, 3)-> expect: 3, actual: %d\n", my_gcd(6, 3));
    printf("my_gcd(6, 4)-> expect: 2, actual: %d\n", my_gcd(6, 4));
    printf("ascii_to_integer(\"123\")-> expect: 123, actual: %d\n", ascii_to_integer("123"));
    printf("max_list(4, 3, 2, 5, 6)-> expect: 6, actual: %d\n", max_list(4, 3, 2, 5, 6));
    my_printf("this is test for \"my_print\", number:%d\n", 10);
    print_dividing_line("");
}
#endif