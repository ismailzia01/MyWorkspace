#include <stdio.h>
//function to find waiting time 
void findWaitingTime(int p[], int n, int bt[], int wt[]) {
    wt[0] = 0;
    for(int i = 1; i < n; i++) {
        wt[i] = bt[i-1] + wt[i-1];
    }
}
//function to find turn around time
void findTurnAroundTime(int p[], int n, int bt[], int wt[], int tat[]) {
    for(int i = 0; i < n; i++) 
        tat[i] = wt[i] + bt[i];
}
void findAverageTime(int p[], int n, int bt[]) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;
    findWaitingTime(p, n, bt, wt);
    findTurnAroundTime(p, n, bt, wt, tat);
    for(int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("\nProcess\tBurstTime\tWaitingTime\tTurnAroundTime\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }
    printf("\n");
    printf("Average Waiting Time : %.2f", (float)total_wt/n);
    printf("Average Turn Around Time : %.2f", (float)total_tat/n);
}
int main() {
    int processes[] = {1,2,3,4,5};
    int n = 5;
    int burst_time[] = {10, 1, 2, 1, 5};
    findAverageTime(processes, n, burst_time);
    return 0;
}