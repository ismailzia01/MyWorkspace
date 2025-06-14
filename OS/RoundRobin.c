#include <stdio.h>
#define MAX 100

void roundRobin(int p[], int n, int bt[], int q) {
    int remaining_bt[MAX], wt[MAX] = {0}, tat[MAX];
    int time = 0, completed = 0;
    int queue[MAX], front = 0, rear = 0;
    int in_queue[MAX] = {0};

    //copy burst time and initialize queue
    for(int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
        queue[rear++] = i;
        in_queue[i] = 1;
    }
    while(front < rear) {
        int i = queue[front++];
        if(remaining_bt[i] > 0) {
            if(remaining_bt[i] > q) {
                time += q;
                remaining_bt[i] -= q;
                queue[rear++] = i;
            }
            else {
                time += remaining_bt[i];
                wt[i] = time - bt[i];
                remaining_bt[i] = 0;
                completed++;
            }
        }
    }
    for(int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
    printf("\nProcess\tBurstTime\tWaitingTime\tTurnAroundTime\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n",p[i], bt[i], wt[i], tat[i]);
    }
}
int main() {
    int process[] = {1,2,3,4};
    int n = sizeof(process) / sizeof(process[0]);
    int burst_time[] =  {8, 4, 9, 5};
    int quantum = 3;
    roundRobin(process, n, burst_time, quantum);
    return 0;
}