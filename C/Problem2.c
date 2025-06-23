/*
Problem:
Write a program that:

Takes a filename as input

Reads the file character by character

Prints it on the screen

Use both fgetc() (stdio) and read() (syscall) versions.
*/
#include<stdio.h>
#include<stdlib.h>

int main() {
    char filename[100];
    printf("Enter filename: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    if(!fp) {
        perror("Error opening file");
        return 1;
    }

    int ch;
    while((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);
    return 0;
}