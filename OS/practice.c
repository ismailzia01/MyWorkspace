#include <stdio.h>
int findClosest(int request[], int n, int target) {
    int min_diff = 1000;
    int closest_index = -1;
    for(int i = 0; i < n; i++) {
        if((abs(request[i]-target) < min_diff) && request[i] != -1) {
            min_diff = abs(request[i]-target);
            closest_index = i;
        }
    }
    return closest_index;
}
void SSTF(int request[], int n, int head) {
    int total_seek = 0;
    int completed[n];
    for(int i = 0; i < n; i++) 
        completed[i] = 0;
    for(int i = 0; i < n; i++) {
        int closest_index = findClosest(request, n, head);
        if(closest_index == -1)
            break;
        int seek_time = abs(request[closest_index]-head);
        total_seek += seek_time;
        head = request[closest_index];
        completed[closest_index] = 1;
        request[closest_index] = -1;
    }
}
int main() {
    int request[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(request) / sizeof(request[0]);
    int head = 53; // Initial head position
    SSTF(request, n, head);
    return 0;
}