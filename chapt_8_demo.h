#ifndef _CHAPT_8_PRACTICE_H_
#define _CHAPT_8_PRACTICE_H_
#include "global.h"

void array_demo(void);
void func_1(int *mat, int row, int col);
void func_2(int mat[3][10]);
int lookup_keyword(char const * const desired_word, char const *keyword_table[], int const size);
double average(int n_value, ...);

#ifdef _TEST_
void chapt_8_demo_run(void);
#endif
#endif