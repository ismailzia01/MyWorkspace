#include <stdio.h>
#include <stdlib.h>

int findClosest(int arr[], int n, int target) {
    int min_diff = 1000;
    int closest_index = -1;
    for(int i = 0; i < n; i++) {
        if (abs(arr[i] - target) < min_diff && arr[i] != -1) {
            min_diff = abs(arr[i] - target);
            closest_index = i;
        }
    }
    return closest_index;
}
void SSTF(int request[], int n, int head) {
    int total_seek_time = 0;
    int completed[n];
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }
    printf("Disk head starts at : %d\n", head);
    for(int i = 0; i < n; i++) {
        int closest_index = findClosest(request, n, head);
        if (closest_index == -1) {
            break;
        }
        int seek_time = abs(request[closest_index] - head);
        total_seek_time += seek_time;
        printf("Moving head from %d to %d, seek time: %d\n", head, request[closest_index], seek_time);
        head = request[closest_index];
        completed[closest_index] = 1;
        request[closest_index] = -1; // Mark as completed

    }
    printf("Total seek time: %d\n", total_seek_time);
    printf("Average seek time: %.2f\n", (float)total_seek_time / n);
    printf("Total number of requests: %d\n", n);
    printf("Total number of completed requests: %d\n", n);
    printf("Total number of uncompleted requests: %d\n", 0);
    printf("Total number of seek operations: %d\n", n);
}
int main() {
    int request[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(request) / sizeof(request[0]);
    int head = 53; // Initial head position
    SSTF(request, n, head);
    return 0;
}