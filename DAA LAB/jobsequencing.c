#include<stdio.h>

struct Job {
    int id;
    int profit;
    int deadline;
};

void sort(struct Job jobs[], int n) {
    for(int i = 0; i < n; i++ ) {
        for(int j = 0; j < n; j++) {
            if(jobs[j].profit < jobs[j+1].profit) {
                struct Job temp = jobs[j];
                jobs[j] = jobs[j+1];
                jobs[j+1] = temp;
            }
        }
    }
}

int main() {
    struct Job jobs[] = {{1, 20, 2}, {2, 15, 2}, {3, 10, 1}, {4, 5, 3}, {5, 1, 3}};
    int size = sizeof(jobs)/sizeof(jobs[0]);
    int slot[10] = {0}, total_profit = 0;
    sort(jobs, size);

    for(int i = 0; i < size; i++) {
        for(int j = jobs[i].deadline-1;j>=0; j--) {
            if(slot[j] == 0) {
                slot[j] = jobs[i].id;
                total_profit += jobs[i].profit;
                break;
            }
        }
    }
    printf("JObs in order : ");
    for(int i = 0; i < size; i++) {
        if(slot[i] !=0) {
            printf("J%d ", slot[i]);
        }
    }
    printf("\nMAximum Profit : %d\n", total_profit);
    return 0;
}