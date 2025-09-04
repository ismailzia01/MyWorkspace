#include <stdio.h>
#include <stdlib.h>

void Merge(int low, int mid, int high, int arr[]) {
    int i = low, k = 0, j = mid + 1;
    int *brr = malloc((high - low + 1) * sizeof(int));
    while(i <= mid  && j <= high) {
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
    free(brr);
}

void MergeSort(int low, int high, int arr[]) {
    if(low < high) {
        int mid = low + (high - low)/2;
        MergeSort(low, mid, arr);
        MergeSort(mid+1, high, arr);
        Merge(low, mid, high, arr);
    }
}

int main() {
    int *arr = NULL;
    int size = 0;
    int capacity = 1;
    int input;

    arr = (int*)malloc(capacity *sizeof(int));


    while (scanf("%d", &input) == 1) {
        if (size >= capacity) {
            capacity *= 2;
            arr = (int*)realloc(arr, capacity * sizeof(int));
        }
        arr[size++] = input;
    }

    printf("\nYou entered %d numbers:\n", size);
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    MergeSort(0, size-1, arr);
    printf("Sorted Array is :");
    for(int i = 0; i < size; i++) 
        printf("%d ", arr[i]);
    pritnf("\n");
    free(arr);
    return 0;
}