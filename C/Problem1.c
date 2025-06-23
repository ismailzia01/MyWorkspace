/*
Problem:
Write a function that takes an integer
 array and its size, allocates a new array 
 dynamically, copies the elements, 
 doubles each one, and returns the new array.*/
#include<stdio.h>
#include <stdlib.h>

int* doubleArray(const int *arr, int size) {
    int *newArr = malloc(size * sizeof(int));//allocate new array
    if(!newArr) {
        printf("malloc failed ");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < size; i++) {
        newArr[i] = arr[i] * 2;//Double each element
    }

    return newArr;
}

int main() {
    int arr[] = {1,2,3};
    int *newArr = doubleArray(arr, 3);
    int n = sizeof(arr)/sizeof(arr[0]);
    for(int i = 0; i < n; i++) {
        printf("%d ", newArr[i]);
    }

    printf("\n");

    free(newArr);//always free dybamicall allocated memory
    return 0;
}

