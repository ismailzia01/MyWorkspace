#include <stdio.h>
#include <stdlib.h>
void cScan(int request[], int n, int head, int disksize){
    int headCount = 0;
    int i = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - i -1; j++) {
            if(request[j] > request[j+1]) {
                int temp = request[j];
                request[j] = request[j+1];
                request[j+1] = temp;
            }
        }
    }
    int startIndex;
    for(int i = 0; i < n; i++) {
        if(head >= request[i]) {
            startIndex = i;
            break;
        }
    }
    //calculate right portion of the array
    for(int i = startIndex; i < n; i++) {
        headCount += abs(head - request[i]);
        head = request[i];
    }

    headCount += abs(head - (disksize-1));
    head = 0;

    for(int i = 0; i < startIndex; i++) {
        headCount += abs(head - request[i]);
        head = request[i];
    }
    printf("Total head count %d \n", headCount);
}

int main() {
    int request[] = {14, 37, 53, 66, 69, 98, 124, 187};
    int n = sizeof (request) / sizeof(request[0]);
    int head = 53;//intial position
    int disksize = 200;//disk size
    cScan(request, n, head, disksize);
    return 0;
}