#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *filename = fopen("Hello.txt", "w");
    if(!filename) {
        perror("Error opening file");
        return 1;
    }
    char ptr[100];
    printf("Enter String : ");
    fgets(ptr, sizeof(ptr), stdin);
    fprintf(filename, "%s", ptr);
    fclose(filename);
    return 0; 
}
