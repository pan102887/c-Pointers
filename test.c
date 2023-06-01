#include <stdio.h>
#include <stdlib.h>

#define N 8

int board[N][N];

void print_board() {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int is_valid(int row, int col) {
    int i, j;
    for (i = 0; i < row; i++) {
        if (board[i][col]) {
            return 0;
        }
    }
    for (i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return 0;
        }
    }
    for (i = row-1, j = col+1; i >= 0 && j < N; i--, j++) {
        if (board[i][j]) {
            return 0;
        }
    }
    return 1;
}

int solve(int row) {
    int col, found = 0;
    if (row == N) {
        print_board();
        return 1;
    }
    for (col = 0; col < N; col++) {
        if (is_valid(row, col)) {
            board[row][col] = 1;
            found |= solve(row+1);
            board[row][col] = 0;
        }
    }
    return found;
}

#define ARRAY(p, i) (*((int*)(p + i)))
int main() {
    // solve(0);
    int * p = malloc(sizeof(int) * 10);
    p[5] = 9;
    printf("%d\n", ARRAY(p, 5));
    return 0;
}