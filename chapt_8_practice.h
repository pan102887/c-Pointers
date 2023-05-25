#ifndef _CHAPTER_8_PRACTICE_H_
#define _CHAPTER_8_PRACTICE_H_

#include <stdio.h>

int identity_matrix(int *mat, int nmat);
/**
 * mat1 是一个 x * y 的矩阵
 * mat2 是一个 y * z 的矩阵
 * 这个函数的作用是将 mat1 与 mat2 相乘，结果存储在 r 中，r 是一个 x * z 的矩阵
 */
int matrix_multiply(int *mat1, int *mat2, int *r, int x, int y, int z);
void chapt_8_practice_run(void);

#endif