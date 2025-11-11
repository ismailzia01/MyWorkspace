#include<stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low, j = high;
    while(i < j) {
        while(arr[i] <= pivot) i++;
        while(arr[j] > pivot) j--;
        if(i < j) swap(&arr[i], &arr[j]);
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void quickSort(int arr[], int low, int high) {
    if(low < high) {
        int loc = partition(arr, low, high);
        quickSort(arr, low, loc-1);
        quickSort(arr, loc+1, high);
    }
}

int main() {
    int arr[] = {52, 32, 58, 26, 62, 56, 54};
    int size = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr, 0, size-1);
    printf("Sorted Array : ");
    for(int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}