//printing 2d array using pointer 
#include <stdio.h>

int main() {
    int *arr = NULL; //Decalaring a pointer
    int size = 0;
    int capacity = 1;
    int val;
    arr = (int*)malloc(capacity *sizeof(int));//allocating memory for the arr
    printf("Enter elements (press q two stop): ");
    while((scanf("%d", &val))==1){
        if(size >= capacity) {
            capacity *= 2;
            arr = (int*)realloc(arr, (capacity * sizeof(int)));
        }
        arr[size++] = val;
    }

}