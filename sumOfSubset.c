#include <stdio.h>
#include <stdlib.h>

void sumOfSubset(int *arr, int size, int target, int index, int currentSum, int subset[], int subsetSize) {
    if(currentSum == target) {
        for(int i = 0; i < subsetSize; i++) {
            printf("%d ", subset[i]);
        }
        printf("\n");
        return;
    }

    if(index > size-1 || currentSum > target) 
        return;

    subset[subsetSize] = arr[index];

    sumOfSubset(arr, size, target, index+1, currentSum + arr[index], subset, subsetSize+1);
    sumOfSubset(arr, size, target, index+1, currentSum, subset, subsetSize);

}

int main() {
    int *arr = NULL;
    int size = 0;
    int capacity = 2;
    int val;
    printf("Enter elements : ");
    arr = (int*)malloc(capacity *sizeof(int));
    while((scanf("%d", &val)==1)) {
        if(size >= capacity) {
            capacity *= 2;
            arr = (int*)realloc(arr, capacity * sizeof(int));
        }
        arr[size++] = val;
    }
    printf("\n");
    int target;
    printf("Enter target : ");
    scanf("%d", &target);
    int subset[size];
    sumOfSubset(arr, size, target,  0, 0, subset, 0);
    return 0;
}