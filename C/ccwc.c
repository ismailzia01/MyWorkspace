#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int countChars(const char *filename) {
    int fd = open(filename, O_RDONLY);

    if(fd < 0) {
        perror("Error opening file");
        return 1;
    }
    
    int count = 0;
    char buffer[1];
    //read() returns 0 at the end of file , and -1 for error
    while(read(fd, buffer, 1) > 0) {
        count++;
    }
    close(fd);
    return count;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Usage : %s <filename> ", argv[0]);
        return 1;
    }
    char *filename = argv[1];
    printf("%d %s\n", countChars(filename), filename);
    return 0;
}
