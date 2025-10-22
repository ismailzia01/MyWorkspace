#include<stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int low, int high, int arr[]) {
    int i = low, j = high, pivot = arr[low];
    while(i < j) {
        while(arr[i] <= pivot) i++;
        while(arr[j] > pivot) j--;
        if(i < j) swap(&arr[i], &arr[j]);
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void qs(int low, int high, int arr[]) {
    if(low < high) {
        int loc = partition(low, high, arr);
        qs(low, loc-1, arr);
        qs(loc+1, high, arr);
    }
}

int main() {
    int arr[] = {32, 26, 52, 62, 58, 56, 54};
    int size = sizeof(arr)/sizeof(arr[0]);
    qs(0, size-1, arr);
    printf("Sorted : ");
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}