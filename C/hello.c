#include<stdio.h>

void print(char str[]) {
    printf("%s", str);
}

int main() {
    printf("Enter a String : ");
    char str[50];
    fgets(str, sizeof(str), stdin);
    print(str);
    return 0;
}

