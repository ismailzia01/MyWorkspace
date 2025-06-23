#include<stdio.h>
#include<stdlib.h>
 
int main(int argc, char *argv[]) {
    
    if(argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];

    FILE *fp = fopen(filename, "r");
    if(!fp) {
        perror("Error opening file");
        return 1;
    }

    int ch;
    int char_count = 0;
    while((ch = fgetc(fp)) != EOF) {
        char_count++;
    }
    
    fclose(fp);

    printf("Total Characters : %d\n", char_count);

    return 0;
}
    

