#include <stdio.h>

void subsetSum(int arr[], int n, int index, int target, int currentSum, int subset[], int subsetSize) {
    // ✅ If sum matches target, print solution
    if (currentSum == target) {
        printf("{ ");
        for (int i = 0; i < subsetSize; i++) {
            printf("%d ", subset[i]);
        }
        printf("}\n");
        return;
    }

    // ❌ Stop if out of elements or sum exceeded
    if (index == n || currentSum > target) {
        return;
    }

    // ✅ Choice 1: INCLUDE arr[index]
    subset[subsetSize] = arr[index];
    subsetSum(arr, n, index + 1, target, currentSum + arr[index], subset, subsetSize + 1);

    // ✅ Choice 2: EXCLUDE arr[index]
    subsetSum(arr, n, index + 1, target, currentSum, subset, subsetSize);
}
void sort(int n, int arr[]) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] < arr[j+1]) {
                int temp3 = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp3;
            }
        }
    }
}

int main() {
    int arr[] = {7, 2, 6, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    sort(n, arr);
    int target = 8;
    int subset[n];  // temp array to hold current subset

    printf("Subsets with sum %d:\n", target);
    subsetSum(arr, n, 0, target, 0, subset, 0);

    return 0;
}
