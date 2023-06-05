#ifndef _EIGHT_QUEENS_H_
#define _EIGHT_QUEENS_H_

/**
 * @brief 八皇后问题
 *        皇后可以攻击同一行、同一列、同一对角线上的棋子
 *        在一个 8 * 8 的棋盘上，放置 8 个皇后，使得任意两个皇后都不能互相攻击
 *        
 * 
 * @return int[8][2] 八个皇后的位置
 */
int eight_queens(int ***result);

#ifdef _TEST_
void eight_queens_test();
#endif

#endif