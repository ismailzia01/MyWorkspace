/*
Description:
Build a basic terminal program that:

Takes a filename as an argument

Reads the file line by line

Stores each line in a dynamically  array of struct Line

Prints the lines with line numbers

Sample Output:
bash
Copy code
$ ./line_viewer hello.txt
1 | Hello, World!
2 | This is a text file.
Bonus: Add support for:

Counting total lines

Handling files of unknown length

Handling very long lines
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *text; // Pointer to dynamically allocated text
    int length; // Length of the line
}Line;

int main(int argc, char *argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        perror("Error opening file");
        return 1;
    }
    Line *lines = NULL;//Dynamic array of lines struct
    int count = 0;//number of lines entered
    char buffer[300];//temporary buffer
    while(fgets(buffer, sizeof(buffer), fp)) {//read one line at a time
        buffer[strcspn(buffer, "\n")] = '\0';//remove newline char if present
        Line *temp = realloc(lines, (count+1)*sizeof(Line));//resize the array to hold one more line
        if(!temp) {
            perror("realloc failed");
            return 1;
        }

        lines = temp;
        lines[count].length = strlen(buffer);
        lines[count].text = malloc(lines[count].length +1);
        if(!lines[count].text) {
            perror("malloc failed");
            return 1;
        }

        strcpy(lines[count].text, buffer);
        count++;
        }
        for(int i = 0; i < count; i++) {
        printf("%d | (%d chars): %s\n", (i+1), lines[i].length,lines[i].text);
        free(lines[i].text);//free each line's text
        }
        free(lines);//free the array of structs
        return 0;
}