#include <stdio.h>

int binarySearch(int arr[], int target, int low, int high) {
    if(low > high) return -1;
    int mid = low + (high - low) / 2;//avoiding overflow condition
    if(target == arr[mid]) return mid; //base condition
    else if(target > arr[mid]) return binarySearch(arr, target, mid+1, high);//searching in right half of the array
    else return binarySearch(arr, target, low, mid-1);//searching in left part of the array , 
}

int main() {
    int arr[] = {26, 32, 52, 54, 56, 58, 62};
    int size = sizeof(arr)/sizeof(arr[0]);
    int val;
    printf("Enter the element to search : ");
    scanf("%d", &val);
    int bs = binarySearch(arr, val, 0, size-1);
    if(bs == -1)
        printf("%d not fount in the array \n", val);
    else
        printf("%d found at %d position \n", val, bs+1);
    return 0;
}