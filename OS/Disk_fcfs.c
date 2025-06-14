#include <stdio.h>
#include <stdlib.h>
void FCFS(int request[], int n, int head) {
    int total_seek_time = 0;
    printf("Disk head starts at %d \n", head);
    printf("Order of requests: ");
    for (int i = 0; i < n; i++) {
        int seek_time = abs(request[i] - head);
        total_seek_time += seek_time;
        printf("Moving from %d to %d, seek time = %d\n", head, request[i], seek_time);
        head = request[i];
    }
    printf("Total seek time = %d\n", total_seek_time);
    printf("Average seek time = %.2f\n", (float)total_seek_time / n);
    printf("Total number of requests = %d\n", n);
}
int main() {
    int request[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(request) / sizeof(request[0]);
    int head = 53; // Initial head position
    FCFS(request, n, head);
    return 0;
}