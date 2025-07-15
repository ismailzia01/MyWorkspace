/*
Problem:
Define a struct Line that stores a line of text and its length.
Then dynamically store multiple lines in an array using realloc().
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char *text;
    int length;
}Line;

int main() {
    Line *lines = NULL;//dynamic array of line structs
    int count = 0; // number of lines entered
    char buffer[250];//temporary buffer

    printf("Enter lines of text (empty line to stop):\n");

    while(1) {
        printf("Line %d: ", (count+1));
        fgets(buffer, sizeof(buffer), stdin);
        //remove newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';
        //stop on empty input
        if(strlen(buffer)==0)
            break;
        //resize the array to hold one more line
        Line *temp = realloc(lines, (count + 1)*sizeof(Line));
        if(!temp) {
            perror("realloc failed");
            break;
        }
        lines = temp;

        //allocate and copy the text
        lines[count].length = strlen(buffer);
        lines[count].text = malloc(lines[count].length + 1);
        if(!lines[count].text) {
            perror("malloc failed");
            return 1;
        }
        strcpy(lines[count].text, buffer);

        count++;
    }
    //print the stored lines'
    printf("\n---You Entered---\n");
    for(int i = 0; i < count; i++) {
        printf("%d | (%d chars): %s\n", (i+1), lines[i].length,lines[i].text);
        free(lines[i].text);//free each line's text
    }
    free(lines);//free the array of structs
    return 0;
}
