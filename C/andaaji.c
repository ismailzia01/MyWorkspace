#include<stdio.h>

int main() {
    int a[10][10], i, j, n;
    
    printf("Enter the number of lines: ");
    scanf("%d", &n);

    // Generate Pascal's Triangle
    for(i = 0; i < n; i++) {
        for(j = 0; j <= i; j++) {
            if(j == 0 || i == j)
                a[i][j] = 1;
            else
                a[i][j] = a[i-1][j-1] + a[i-1][j];
        }
    }

    // Print Pascal's Triangle
    printf("Pascal Triangle:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j <= i; j++) {
            printf("%d\t", a[i][j]);
        }
        printf("\n"); // Move to the next line after printing each row
    }
    
    return 0;
}
