#include "eight_queens.h"

#include "global.h"

#include <stdio.h>
#include <stdlib.h>
#define BOARD_SIZE 8

/**
 * @brief 整形指针访问
 *
 */

static int *get_allowed_col(int **position, int current_row)
{
    int *allowed_col = malloc(sizeof(int) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        allowed_col[i] = 1;
    }

    for (int i = 0; i < current_row; i++)
    {
        const int row = position[i][0];
        const int col = position[i][1];
        if (row <= 0 || col <= 0 || row > BOARD_SIZE || col > BOARD_SIZE)
        {
            continue;
        }

        allowed_col[col - 1] = 0;
        const int distance = current_row - row;
        const int postive_distance = col + distance;
        const int negative_distance = col - distance;
        if (postive_distance > 0 && postive_distance <= BOARD_SIZE)
        {
            allowed_col[postive_distance - 1] = 0;
        }
        if (negative_distance > 0 && negative_distance <= BOARD_SIZE)
        {
            allowed_col[negative_distance - 1] = 0;
        }
    }
    return allowed_col;
}

/**
 * @brief 初始化皇后的位置
 *
 * @return int** 位置的指针
 */
static int **init_position()
{
    int **position = malloc(sizeof(int *) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        position[i] = malloc(sizeof(int) * 2);
        position[i][0] = 0;
        position[i][1] = 0;
    }
    return position;
}

/**
 * @brief Set the queens object
 *
 * @param result
 * @param nresult result 的长度
 * @param position (row, col)
 * @param current_row 当前行
 */
static void set_queens(int ***result, int *nresult, int **position, int current_row)
{
    int *allowed_col = get_allowed_col(position, current_row);
    printf("current %d:", current_row);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("%d ", allowed_col[i]);
    }
    printf("\n");

    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (allowed_col[j] == 1)
        {
            position[current_row - 1][0] = current_row;
            position[current_row - 1][1] = j + 1;
            if (current_row == BOARD_SIZE)
            {
                // result = realloc(result, sizeof(int**) * (*nresult + 1));
                // result[*nresult] = position;
                (*nresult)++;

                // for (int i = 0; i < BOARD_SIZE; i++)
                // {
                //     printf("(%d, %d)", position[i][0], position[i][1]);
                // }
            }
            else
            {
                set_queens(result, nresult, position, current_row + 1);
            }
        }
    }
    free(allowed_col);
}

/**
 * @brief
 *
 * @param result
 * @return int
 */
int eight_queens(int ***result)
{
    int *nresult = malloc(sizeof(int));
    *nresult = 0;
    int **position = init_position();
    int row = 1;
    for (int col = 1; col <= 8; col++)
    {
        position[0][0] = row;
        position[0][1] = col;
        set_queens(result, nresult, position, ++row);
    }
    printf("nresult: %d\n", *nresult);
    return *nresult;
}

#ifdef _TEST_
#include <assert.h>

static void init_position_test()
{
    int **position = init_position();
    for (int i = 0; i < 8; i++)
    {
        assert(position[i][0] == 0);
        assert(position[i][1] == 0);
    }
}

static void get_allowed_col_test()
{
    int **position = init_position();
    int *allowed_col = get_allowed_col(position, 1);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("%d ", allowed_col[i]);
    }
    printf("\n");

    position[0][0] = 1;
    position[0][1] = 1;
    position[1][0] = 2;
    position[1][1] = 3;
    position[2][0] = 3;
    position[2][1] = 5;
    allowed_col = get_allowed_col(position, 4);
    assert(allowed_col[2] == 0);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("%d ", allowed_col[i]);
    }
    printf("\n");
}

static void set_queen_test()
{
    int **position = init_position();
    int *nresult = malloc(sizeof(int));
    *nresult = 0;
    set_queens(NULL, nresult, position, 1);
}
void eight_queens_test()
{
    // init_position_test();
    // get_allowed_col_test();
    // set_queen_test();
    // eight_queens(NULL);
}
#endif