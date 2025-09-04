#include <stdio.h>

void Merge(int low, int mid, int high, int arr[]) {
    int i = low, k = 0, j = mid+1;
    int brr[high+1];
    while(i <= mid && j <= high) {
        if(arr[i] < arr[j])
            brr[k++] = arr[i++];
        else    
            brr[k++] = arr[j++];
    }
    while(i <= mid)
        brr[k++] = arr[i++];
    while(j <= high)
        brr[k++] = arr[j++];
    for(int i = 0; i < k; i++) 
        arr[low + i] = brr[i];
}

void mergeSort(int low, int high, int arr[]) {
    if(low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(low, mid, arr);
        mergeSort(mid+1, high, arr);
        Merge(low, mid, high, arr);
    }
}
int main() {
    int arr[] = {20, 30, 10, 50, 80, 70, 60, 40};
    int size = sizeof(arr) / sizeof(arr[0]);
    mergeSort(0, size-1, arr);
    printf("Sorted Array  ");
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}