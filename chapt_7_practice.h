#ifndef _CHAPT_7_PRACTICE_H_
#define _CHAPT_7_PRACTICE_H_
#include <stdio.h>

/**
 * Hermite Polynomials(厄密多项式)
 */
int hermite(int n, int x);

/**
 * GCD
 */

int my_gcd(int M, int N);
int ascii_to_integer(char *string);
int max_list(int n_numbers, ...);

__fortify_function int my_printf(const char *__restrict __fmt, ...);

#ifdef _TEST_
void chapt_7_practice_run(void);
#endif // _TEST_
#endif // _CHAPT_7_PRACTICE_H_