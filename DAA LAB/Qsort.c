#include <stdio.h>
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int low, int high, int arr[]) {
    int i = low;
    int j = high;
    int pivot = arr[low];
    while(i < j) {
        while(arr[i] <= pivot) i++;
        while(arr[j] > pivot) j--;
        if(i < j) swap(&arr[i], &arr[j]);
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void qSort(int low, int high, int arr[]) {
    if(low < high) {
        int loc = partition(low, high, arr);
        qSort(low, loc-1, arr);
        qSort(loc+1, high, arr);
    }
}


int main() {
    int arr[] = {54, 32, 62, 26, 52, 58, 56};
    int size = sizeof(arr) / sizeof(arr[0]);
    qSort(0, size-1, arr);
    printf("Sorted Element : ");
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}