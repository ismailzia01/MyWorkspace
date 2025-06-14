#include <stdio.h>
#define n 5
int arrivalTime[n], burstTime[n], completionTime[n], turnAroundTime[n], waitingTime[n], process[n];

double completion_Time(int ct[], int at[], int bt[]) {
    ct[0] = at[0] + bt[0];
    for(int i = 1; i < n; i++) {
        if(at[i] > ct[i-1])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];
    }
    double tct = 0;
    for(int i = 0; i < n; i++) {
        tct += ct[i];
    }
    return tct;
}
double turnAround_Time(int ct[], int at[]) {
    double ttat = 0;
    for(int i = 0; i < n; i++) {
        turnAroundTime[i] = ct[i] - at[i];
        ttat += turnAroundTime[i];
    }
    return ttat;
}
double waiting_Time(int tat[], int bt[]) {
    double twt = 0;
    for(int i = 0; i < n; i++) {
        waitingTime[i] = tat[i] - bt[i];
        twt += waitingTime[i];
    }
    return twt;
}
int main() {
    printf("Enter 5 process \n");
    printf("Enter arrival and burst time respectively \n");
    for(int i = 0; i < n; i++) {
        process[i] = i+1;
        scanf("%d %d", &arrivalTime[i], &burstTime[i]);
    }
    double totalCompletionTime = completion_Time(completionTime, arrivalTime, burstTime);
    double totalTurnAroundTime =  turnAround_Time(completionTime, arrivalTime);
    double totalWaitingTime = waiting_Time(turnAroundTime, burstTime);
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", process[i], arrivalTime[i], burstTime[i], completionTime[i], turnAroundTime[i], waitingTime[i]);
    }

    printf("\nTotal Completion Time = %lf", totalCompletionTime);
    printf("\nTotal Turn Around Time = %lf", totalTurnAroundTime);
    printf("\nTotal Waiting Time = %lf", totalWaitingTime);
    double avgCT = totalCompletionTime / (double)n;
    double avgTAT = totalTurnAroundTime / (double)n;
    double avgWT = totalWaitingTime / (double)n;
    printf("\nAverage Completion Time = %lf", avgCT);
    printf("\nAverage Turn Around Time = %lf", avgTAT);
    printf("\nAverage Waiting Time = %lf\n", avgWT);
    return 0;
}