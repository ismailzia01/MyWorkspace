#include<stdio.h>
void prims(int n, int cost[10][10]) {
    int v, u, min, mincost = 0, visited[10] = {0};
    visited[0] = 1;
    min = 999;
    for(int i = 0; i < n; i++) {
        min = 999;
        for(int j = 0; j < n; j++) {
            if(cost[i][j] < min) {
                min = cost[i][j];
                u = i;
                v = j;
            } 
        }
        if(visited[v]==0) {
            mincost += min;
            visited[v] = 1;
        }
        cost[u][v] = cost [v][u] = 999;
    }
    printf("\nMinimum cost is %d ", mincost);
}
void main() {
    int n = 3, cost[10][10] = {{0, 5, 10}, {5, 0, 5}, {10, 5, 0}};
    for(int i = 0; i < n; i++) {
        printf("\n");
        for(int j = 0; j < n; j++) {
            printf("%d ", cost[i][j]);
            if(cost[i][j]==0) cost[i][j] = 999;
        }
    }
    printf("\n\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) 
            printf("%d ", cost[i][j]);
        printf("\n");
    }
    prims(n, cost);
}