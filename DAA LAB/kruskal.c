#include <stdio.h>

int parent[10];

// Find function
int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

// Union function
void union_set(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

int main() {
    int n, e;
    int u, v, w;
    int total = 0;
    int min, a, b;
    int cost[10][10];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter cost matrix (0 if no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = 999; // infinity
        }
    }

    // initialize parent
    for (int i = 0; i < n; i++)
        parent[i] = i;

    e = 0;
    printf("\nEdges in Minimum Spanning Tree:\n");

    while (e < n - 1) {
        min = 999;
        // find minimum edge
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (find(i) != find(j) && cost[i][j] < min) {
                    min = cost[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        union_set(a, b);
        printf("%d -> %d  cost = %d\n", a, b, min);
        total += min;
        cost[a][b] = cost[b][a] = 999; // mark edge as used
        e++;
    }

    printf("\nTotal cost of MST = %d\n", total);
    return 0;
}
