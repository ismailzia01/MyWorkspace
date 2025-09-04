#include <stdio.h>
#include <stdlib.h>

int BinarySearch(int arr[], int low, int val, int high) {
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(val == arr[mid])
            return mid;
        else if(val > arr[mid]) {
            low = mid+1;
        } 
        else if(val < arr[mid]) {
            high = mid;
        }
    }
    return -1;
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

    printf("Enter the element you want to search : ");
    int val;
    scanf("%d", &val);
    int bs = BinarySearch(arr, 0, val, size);
    if(bs == -1)
        printf("%d not found in Array \n", val);
    else
        printf("%d found at %d Position ", val, bs+1);
    
    free(arr);
    return 0;
}