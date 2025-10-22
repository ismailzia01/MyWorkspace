#include<stdio.h>

int parant[10];

int find(int i) {
    while(parant[i] != i)
        i = parant[i];
    return i;
}

void uni(int i, int j) {
    int a = find(i);
    int b = find(j);
    parant[a] = b;
}

int main() {
    int n, e;
    int s, d, w;
    int min, total_cost = 0;
    int cost[10][10];
    int u , v;

    printf("enter no. of nodes : ");
    for(int i = 0; i<n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if(cost[i][j]==0)
                cost[i][j] = 999;
        }
    }
    for(int i = 0; i < n; i++) {
        parant[i] = i;
    }
    e=0;
    while(e < n-1) {
        min = 999;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j <n; j++) {
                if(find(i) != find(j) && cost[i][j] < min){
                    min = cost[i][j];
                    s = i;
                    d = j;
                }
            }
        }
    
        uni(s, d);
        printf("%d -> %d cost %d", s, d, min);
        total_cost += min;
        cost[s][d] = cost[d][s] = 999;
        e++;
    }
    printf("MAx profit %d ", total_cost);
    return 0;
}