#include<stdio.h>
#include<stdlib.h>
#define N 10
int profit[N] = {10, 5, 15, 7, 6, 18, 3};
int weight[N] = {2, 3, 5, 7, 1, 4, 1};
double pw[N];
int n = 7, m = 15;
void sort() {
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

double greedyKnapSack() {
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
    for(int i = 0; i < n; i++)
        pw[i] = (double)profit[i] / weight[i];
    sort();
    printf("\nProfit : %f \n", greedyKnapSack());
    return 0;
}