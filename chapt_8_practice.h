#ifndef _CHAPTER_8_PRACTICE_H_
#define _CHAPTER_8_PRACTICE_H_

int identity_matrix(int *mat, int nmat);
/**
 * mat1 是一个 x * y 的矩阵
 * mat2 是一个 y * z 的矩阵
 * 这个函数的作用是将 mat1 与 mat2 相乘，结果存储在 r 中，r 是一个 x * z 的矩阵
 */
int matrix_multiply(int *mat1, int *mat2, int *r, int x, int y, int z);
/**
 * @brief 这个函数接受一些用于描述伪数组的维数的信息以及一组下标值。
 *        然后它使用这些信息把下标值翻译为一个整数，用于表示一个向
 *        量（一维数组）的下标。
 *        arrayinfo[0]: 伪数组具有的维数
 *        arrayinfo[1], arrayinfo[2] 第一维的下标范围（从 arrayinfo[1] 到 arrayinfo[2]）
 *        arrayinfo[3], arrayinfo[4] 第二维的下标范围（从 arrayinfo[3] 到 arrayinfo[4]）
 *        以此类推
 *        行主序
 *
 * @param arrayinfo 描述伪数组的维数的信息
 * @param ... 一组下标值
 * @return int 用于表示一个向量（一维数组）的下标
 */
int array_offset(int arrayinfo[], ...);
#ifdef _TEST_
void chapt_8_practice_run(void);
#endif

#endif