#include <stdio.h>
//bubble sort for sorting the burst time
void sort(int bt[], int n, int btt[]) {
    for(int i = 0; i < n -1; i++) {
        for(int j = 0; j < n - i- 1; j++) {
            if(bt[j] > bt[j+1]){
                int temp = bt[j];
                bt[j] = bt[j+1];
                bt[j+1] = temp;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        btt[i] = bt[i];
    }
}
void findWaitingTime(int p[], int n, int bt[], int wt[]){
    wt[0] = 0;
    for(int i = 1; i < n; i++)
        wt[i] = bt[i-1] + wt[i-1];
}
void findTurnAroundTime(int p[], int n, int bt[], int wt[], int tat[]) {
    for(int i = 0; i < n; i++) 
        tat[i] = wt[i] + bt[i];
}
void findAverageTime(int p[], int n, int bt[]){
    int wt[n], tat[n];
    int total_wt = 0;
    int total_tat = 0;
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

int main(){
    int processes[] = {1,2,3,4,5};
    int n = sizeof(processes)/sizeof(processes[0]);
    int bt[] = {10, 1, 2, 1, 5};
    int btt[n];
    sort(bt, n, btt);
    findAverageTime(processes, n, btt);
    return 0;
}