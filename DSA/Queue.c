#include <stdio.h>
#include <stdlib.h>
#define N 5

int rear = -1, front = -1;

void enqueue(int val, int arr[]) {
    if(front == N - 1) {
        printf("\nQueue is Full ! ");
        return;
    }
    if(rear == -1 && front == -1) {
        rear = front = 0;
        printf("\nElement inserted : %d", val);
        arr[front] = val;
        return;
    }
    printf("\nElement inserted : %d", val);
    arr[++front] = val;
}

void dequeue(int arr[]) {
    if(rear == -1 || rear > front) {
        printf("\nQueue is Empty ! ");
        return;
    }
    if(rear == front) {
        printf("\nElement Deleted : %d", arr[rear]);
        rear = front = -1;
        return;
    }
    printf("\nElement Deleted : %d", arr[rear++]);
}

void display(int arr[]) {
    if(rear == -1) {
        printf("\nQueue is Empty !");
        return;
    }
    for(int i = rear; i <= front; i++) {
        printf("%d\t", arr[i]);
    }
}

int main() {
    int arr[N];
    int choice, val;
    do {
        printf("\n1) Insert ");
        printf("\n2) Delete ");
        printf("\n3) Display ");
        printf("\n4) Exit ");
        printf("\nEnter Your Choice : ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("\nEnter the Element : ");
                scanf("%d", &val);
                enqueue(val, arr);
                break;
            case 2:
                dequeue(arr);
                break;
            case 3:
                display(arr);
                break;
            case 4:
                printf("\nExiting.....!\n");
                exit(0);
            default:
                printf("\nInvalid Input\n");
        }
    }while(choice != 4);
    return 0;
}