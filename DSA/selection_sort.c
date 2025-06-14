#include <stdio.h>

void selectionSort(int arr[], int n) {
    int temp;
    for(int i = 0; i < n; i++) {
        int min = arr[i];
        for(int j = i; j < n; j++) {
            if(min > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    printf("Enter the no. of elements : ");
    int size;
    scanf("%d", &size);
    int arr[size];
    printf("Enter %d elements of array : ");
    for(int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    printf("\nBefore Sorting : ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    selectionSort(arr, size);
    printf("\nAfter Selection Sort : ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}