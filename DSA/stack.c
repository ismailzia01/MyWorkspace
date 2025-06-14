#include<stdio.h>
#include<stdlib.h>
#define N 50

static int top = -1;

void push(int val, int arr[]) {
    if(top == N) {
        printf("\nStack is Full !\n");
        return;
    }
    printf("\nPushed Element : %d", val);
    if(top == -1) {
        top++;
        arr[top] = val;
    }
    arr[++top] = val;
}
void pop(int arr[]) {
    if(top == -1) {
        printf("\nStack is Empty !");
        return;
    }
    printf("\nPopped Element : %d", arr[top--]);
}
void peek(int arr[]) {
    if(top == -1) {
        printf("\nStack is Empty !");
        return;
    }
    printf("\nPeek Element : %d", arr[top]);
}
void display(int arr[]) {
    if(top == -1) {
        printf("\nStack is Empty !\n");
        return;
    }
    printf("\nStack Elements\n");
    for(int i = top; i > 0; i--) {
        printf("%d\n", arr[i]);
    }
}
int main() {
    int arr[N];
    int choice;
    int val;
    do {
        printf("\n1) Push ");
        printf("\n2) Pop ");
        printf("\n3) Peek ");
        printf("\n4) Display ");
        printf("\n5) Exit ");
        printf("\nEnter your Choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nEnter the Element to Push in Stack : ");
            scanf("%d", &val);
            push(val, arr);
            break;
        case 2:
            pop(arr);
            break;
        case 3:
            peek(arr);
            break;
        case 4:
            display(arr);
            break;
        case 5:
            printf("\nExiting.......!\n");
            exit(0);
        default:
            printf("\nInvalid Input\n");
        }
    }while(choice != 5);
    return 0;
}