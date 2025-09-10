#include<stdio.h>
#include<stdlib.h>
#define N 10
int profit[N], weight[N];
double pw[N];

void sort(int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(pw[j] < pw[j+1]) {
                double temp3 = pw[j];
                pw[j] = pw[j+1];
                pw[j+1] = temp3;

                int temp = profit[j];
                profit[j] = profit[j+1];
                profit[j+1] = temp;

                int temp2 = weight[j];
                weight[j] = weight[j+1];
                weight[j+1] = temp2;
            }
        }
    }
}

double greedyKnapSack(int n, int m) {
    double max_profit = 0;
    for(int i = 0; i < n; i++) {
        if(weight[i] <= m) {
            max_profit += profit[i];
            m -= weight[i];
        }
        else {
            max_profit += pw[i] * m;
            break;
        }
    }
    return max_profit;
}


int main() {
        
    int m, n;
    printf("Enter no. of elements : ");
    scanf("%d", &n);
    printf("Enter Profits : ");
    for(int i = 0; i < n; i++) 
        scanf("%d", &profit[i]);
    printf("\nEnter Weights : ");
    for(int i = 0; i < n; i++) 
        scanf("%d", &weight[i]);
    printf("\nEnter size : ");
    scanf("%d", &m);
    for(int i = 0; i < n; i++)
    printf("%d ", profit[i]);
    printf("\n");
    for(int i = 0; i < n; i++)
    printf("%d ", weight[i]);
    for(int i = 0; i < n; i++)
        pw[i] = (double)profit[i] / weight[i];
    sort(n);
    printf("\nProfit : %f \n", greedyKnapSack(n, m));
    return 0;
}