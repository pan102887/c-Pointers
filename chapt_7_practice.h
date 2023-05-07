#ifndef _CHAPT_7_PRACTICE_H_
#define _CHAPT_7_PRACTICE_H_

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

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
void chapt_7_run(void);
__fortify_function int my_printf(const char *__restrict __fmt, ...);

#endif