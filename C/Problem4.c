/*
Problem:
Write a program that:

Takes a filename as input

Reads the file character by character

Prints it on the screen

Use both fgetc() (stdio) and read() (syscall) versions.
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>//for open()
#include <unistd.h>//for read() , close()

int main() {
    char filename[100];
    printf("Enter the filename:");
    scanf("%s", filename);
    int fd = open(filename, O_RDONLY);
    if(fd < 0) {
        perror("Error opening file");
        return 1;
    }
    char buffer[1];//read one byte at a time 
    ssize_t bytesRead;
    while((bytesRead = read(fd, buffer, 1)) > 0) {
        write(STDOUT_FILENO, buffer, 1);//write to stdout
    }

    if(bytesRead < 0) {
        perror("Error reading file");
        return 1;
    }
    close(fd);
    return 0;
}

