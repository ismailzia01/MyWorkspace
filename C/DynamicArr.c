#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = NULL;
    int size = 0;
    int capacity = 1;
    int input;

    arr = (int*)malloc(capacity * sizeof(int));

    printf("Enter numbers (non-integer like 'q' to stop):\n");

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

    free(arr);
    return 0;
}

