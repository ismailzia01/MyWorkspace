#include <stdio.h>

void bubbleSort(int arr[], int n) {
    int temp;
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n - i - 1; j++) {
            if(arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
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
    bubbleSort(arr, size);
    printf("\nAfter Bubble Sort : ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}