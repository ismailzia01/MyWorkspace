#include<stdio.h>


#define INF 999
#define MAX 10

int n, s;
int cost[MAX][MAX], dist[MAX], visited[MAX];


void dijkstras() {
    int count, min, v;

    // Initialize
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        dist[i] = cost[s][i];
    }

    visited[s] = 1;
    dist[s] = 0;
    count = 1;

    while (count < n - 1) {
        min = INF;

        // Find vertex with minimum distance
        for (int i = 0; i < n; i++) {
            if (dist[i] < min && !visited[i]) {
                min = dist[i];
                v = i;
            }
        }

        visited[v] = 1;

        // Relax edges
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] > dist[v] + cost[v][i])
                dist[i] = dist[v] + cost[v][i];
        }

        count++;
    }
}

int main() {
    printf("Enter no. of nodes: ");
    scanf("%d", &n);

    printf("Enter cost matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0 && i != j)
                cost[i][j] = INF; // replace 0 with INF except diagonal
        }
    }

    printf("Enter source node: ");
    scanf("%d", &s);

    dijkstras();

    printf("\nShortest paths from node %d:\n", s);
    for (int i = 0; i < n; i++) {
        if (i != s)
            printf("%d -> %d = %d\n", s, i, dist[i]);
    }

    return 0;
}