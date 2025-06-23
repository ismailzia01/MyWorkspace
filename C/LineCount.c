/*
C Program to count the lines in a file
*/
#include<stdio.h>

int main(int argc, char *argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Usage : %s <filename>\n", argv[0]);
        return 1;
    }
    int lines = 0;
    FILE *fp = fopen(argv[1], "r");
    char ch;
    while((ch = fgetc(fp))!= EOF) { 
        if(ch == '\n')
            lines++;
    };
    fclose(fp);
    printf("%d %s\n", lines, argv[1]);
    return 0;
}