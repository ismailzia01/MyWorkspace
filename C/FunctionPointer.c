#include<stdio.h>

void sayHello() {
    printf("Hello, World!\n");
}

void sayBye() {
    printf("Goodbye, World!\n");
}

void sayThanks() {
    printf("Thank you, World!\n");
}

void invalidOption(){
    printf("Invalid option selected.\n");
}

int main() {
    //arrray of function pointers
    void (*main[]) (void) = {sayHello, sayBye, sayThanks};
    int choice;
    while(1) {
        printf("\nMenu:\n");
        printf("0. Say Hello\n");
        printf("1. Say Goodbye\n");
        printf("2. Say Thanks\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if(choice >= 0 && choice < 3) {
            main[choice]();//call the selected function
        } else {
            invalidOption();
        }
    }
    return 0;
}