#include<stdio.h>
#define N 4
int board[N][N];

void printboard() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

//check if a queen can be placed at board
int isSafe(int row, int col) {
    for(int i = 0; i < col; i++) 
        if(board[row][i]) return 0;
    for(int i = row, j = col; i >= 0 && j>=0; i--, j--) 
        if(board[i][j]) return 0;
    for(int i = row, j = col; i < N && j >= 0; i++, j--)
        if(board[i][j]) return 0;
    return 1;
}

int NQP(int col) {
    int res = 0;
    if(col >= N) {
        printboard();
        return 1;
    }
    for(int i = 0; i < N; i++) {
        if(isSafe(i, col)) {
            board[i][col] = 1;
            res = NQP(col+1) || res;
            board[i][col] = 0;
        }
    }
    return res;
}

int main() {
    if(!NQP(0))
        printf("Solution does not exist");
    return 0;
}