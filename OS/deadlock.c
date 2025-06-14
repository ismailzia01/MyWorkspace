#include <stdio.h>
#define MAX_PROCESSSES 5
#define MAX_RESOURCES 3
int allocation[MAX_PROCESSSES][MAX_RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
        };
int max[MAX_PROCESSSES][MAX_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
        };
int need[MAX_PROCESSSES][MAX_RESOURCES];
int safeSequence[MAX_PROCESSSES];
int available[MAX_RESOURCES] = {3, 3, 2};
int finished[MAX_PROCESSSES] = {0};

void calculateNeed() {
    for(int i = 0; i < MAX_PROCESSSES; i++) {
        for(int j = 0 ; j < MAX_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}
int isSafe() {
    int work[MAX_RESOURCES];
    for(int i = 0; i < MAX_RESOURCES; i++) 
        work[i] = available[i];
    int count = 0; 
    while(count < MAX_PROCESSSES) {
        int found = 0;
        for(int i = 0; i < MAX_PROCESSSES; i++) {
            if(!finished[i]) {
                int j;
                for(j = 0; j < MAX_RESOURCES; j++) {
                    if(need[i][j] > work[j]) 
                        break;
                }
                if(j == MAX_RESOURCES) {
                    for(int k = 0; k < MAX_RESOURCES; k++)
                        work[k] += allocation[i][k];
                    safeSequence[count++]=i;
                    finished[i]=1;
                    found = 1;
                }
            }
        }
        if(!found)
            return 0;
    }
    return 1;
}
void display() {
    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    printf("-------\t----------\t---\t\t----\n");
    for(int i = 0; i < MAX_PROCESSSES; i++) {
        printf("P%d\t", i);
        for(int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\t\t");
        for(int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\t\t");
        for(int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

int main() {
    calculateNeed();
    display();
    if(isSafe()) {
        printf("System is in safe sequence : ");
        for(int i = 0; i < MAX_PROCESSSES; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    }
    else {
        printf("System is not in safe sequence !\n");
        printf("System is in deadlock state \n");
    }
    return 0;
}