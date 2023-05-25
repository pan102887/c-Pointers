#include "chapt_8_practice.h"

int identity_matrix(int *mat, int nmat)
{
    for (int i = 0; i < nmat; i++)
    {
        for (int j = 0; j < nmat; j++)
        {
            if (i == j)
            {
                if (*(mat + i * nmat + j) != 1)
                {
                    return 0;
                }
            }
            else
            {
                if (*(mat + i * nmat + j) != 0)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void test_identity_matrix(void)
{
    int mat[3][3] = {{1, 0, 0},
                     {0, 1, 0},
                     {0, 0, 1}};
    int nmat = 3;
    int *pmat = &mat[0][0];
    int result = identity_matrix(pmat, nmat);
    printf("result: %d\n", result);

    int mat2[3][3] = {{1, 0, 0},
                      {0, 1, 0},
                      {0, 0, 0}};

    int *pmat2 = &mat2[0][0];
    int result2 = identity_matrix(pmat2, nmat);
    printf("result2: %d\n", result2);
}

int matrix_multiply(int *mat1, int *mat2, int *r, int x, int y, int z)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < z; j++)
        {
            int sum = 0;
            for (int k = 0; k < y; k++)
            {

                sum += *(mat1 + i * y + k) * *(mat2 + k * z + j);
            }
            *(r + i * z + j) = sum;
        }
    }
    return 1;
}

void test_matrix_multiply(void)
{
    int mat1[2][3] = {{1, 2, 3},
                      {4, 5, 6}};
    int mat2[3][2] = {{1, 2},
                      {3, 4},
                      {5, 6}};
    int r[2][2] = {0};
    int x = 2;
    int y = 3;
    int z = 2;
    int *pmat1 = &mat1[0][0];
    int *pmat2 = &mat2[0][0];
    int *pr = &r[0][0];
    matrix_multiply(pmat1, pmat2, pr, x, y, z);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < z; j++)
        {
            printf("%d ", *(pr + i * z + j));
        }
        printf("\n");
    }
}

void chapt_8_practice_run(void)
{
    printf("--------------------chapt_8_practice--------------------\n");
    test_identity_matrix();
    test_matrix_multiply();
    printf("====================chapt_8_practice====================\n\n");
}