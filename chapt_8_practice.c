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

int array_offset(int arrayinfo[], ...)
{
    int *witch_width = malloc(sizeof(int) * arrayinfo[0]);
    for (int i = 0; i < arrayinfo[0]; i++)
    {
        witch_width[i] = arrayinfo[2 * i + 2] - arrayinfo[2 * i + 1] + 1;
    }

    int *index = malloc(sizeof(int) * arrayinfo[0]);
    va_list index_params;
    va_start(index_params, arrayinfo[0]);
    int i = 0;
    while (i < arrayinfo[0])
    {
        index[i] = va_arg(index_params, int);
        i++;
    }
    va_end(index_params);

    i = arrayinfo[0] - 1;
    int loc = (index[i] - arrayinfo[2 * i + 1]);
    int width = 1;
    i--;
    while (!(i < 0))
    {
        width *= witch_width[i + 1];
        loc += (index[i] - arrayinfo[2 * i + 1]) * width;
        i--;
    }
    free(witch_width);
    free(index);
    return loc;
}

void test_array_offset(void)
{
    int arrayinfo[7] = {3, 4, 6, 1, 5, -3, 3};
    int result1 = array_offset(arrayinfo, 4, 1, -3);
    assert(result1 == 0 || !printf("result actual is: %d\n", result1));

    int result2 = array_offset(arrayinfo, 4, 1, 3);
    assert(result2 == 6 || !printf("result actual is: %d\n", result2));

    int result3 = array_offset(arrayinfo, 5, 1, -3);
    assert(result3 == 35 || !printf("result actual is: %d\n", result3));

    int result4 = array_offset(arrayinfo, 4, 1, -2);
    assert(result4 == 1 || !printf("result actual is: %d\n", result4));

    int result5 = array_offset(arrayinfo, 4, 2, -3);
    assert(result5 == 7 || !printf("result actual is: %d\n", result5));

    int result6 = array_offset(arrayinfo, 6, 3, 1);
    assert(result6 == 88 || !printf("result actual is: %d\n", result6));
}

double average_1(int nnumber, ...)
{
    va_list number_params;
    va_start(number_params, nnumber);
    double sum = 0;
    for (int i = 0; i < nnumber; i++)
    {
        sum += va_arg(number_params, int);
    }
    va_end(number_params);
    return sum / nnumber;
}

void test_average(void)
{
    double result1 = average_1(3, 1, 2, 3);
    assert(result1 == 2.0 || !printf("result actual is: %f\n", result1));

    double result2 = average_1(5, 1, 2, 3, 4, 5);
    assert(result2 == 3.0 || !printf("result actual is: %f\n", result2));
}

void chapt_8_practice_run(void)
{
    printf("--------------------chapt_8_practice--------------------\n");
    test_identity_matrix();
    test_matrix_multiply();
    test_array_offset();
    test_average();
    printf("====================chapt_8_practice====================\n\n");
}