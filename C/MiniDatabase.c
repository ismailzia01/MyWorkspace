#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FILENAME "dataset.csv"

 typedef struct {
    char name[100];
    char email[100];
    char number[100];
} Data;

Data *data = NULL;
int total_data = 0;

void addDataToMemory(Data newData) {
    Data *temp = realloc(data, (total_data+1)*sizeof(Data));
    if(!temp) {
        perror("realloc failed ");
        return;
    }
    data = temp;
    data[total_data++] = newData;
}

void appendDataToFile(Data *c) {
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_APPEND , 0644);
    if(fd == -1) {
        perror("Error opening file");
        return;
    }
    dprintf(fd, "%s, %s, %s\n", c->name, c->number, c->email);
    close(fd);
}
void loadDataFile() {
    int fd = open(FILENAME, O_RDONLY);
    if(fd == -1) {
        //file may not exist
        perror("Error opening file");
        return;
    }
    char buffer[1024];
    ssize_t bytes_read;
    int pos = 0;
    memset(buffer, 0, sizeof(buffer));
    while((bytes_read = read(fd, (buffer + pos), sizeof(buffer) - pos -1))> 0){
        pos += bytes_read;
        buffer[pos] = '\0';

        char *line = strtok(buffer, "\n");
        while(line != NULL) {
            Data temp;
            if(sscanf(line, "%99[^,],%99[^,],%99[^,\n]", temp.name, temp.number, temp.email) == 3){
                addDataToMemory(temp);
            }
            line = strtok(NULL, "\n");
        }
    }
    close(fd);

}
Data getUserData() {

    Data data;
    //printf("Enter data \n");
    printf("Name :");
    fgets(data.name, sizeof(data.name), stdin);
    data.name[strcspn(data.name, "\n")] = '\0';

    printf("Phone : ");
    fgets(data.number, sizeof(data.number), stdin);
    data.number[strcspn(data.number, "\n")] = '\0';

    printf("Email : ");
    fgets(data.email, sizeof(data.email), stdin);
    data.email[strcspn(data.email, "\n")] = '\0';

    return data;
}
void printData() {
    if(total_data == 0) {
        printf("No data found \n");
        return;
    }
    printf("\n📒 Contact List:\n");
    for(int i = 0; i < total_data; i++) {
        printf("%d) %s | %s | %s \n", i+1, data[i].name, data[i].number, data[i].email);
    }
}

int main() {
    loadDataFile();
    
    int choice;
    while(1){
        printf("\n1) View Data\n");
        printf("2) Store Data\n");
        printf("3) Exit\n");
        printf("> ");
        scanf("%d", &choice);
        getchar();//clear new line input buffer
        switch(choice) {
            case 1: printData(); break;
            case 2:
                Data c = getUserData();
                addDataToMemory(c);
                appendDataToFile(&c);
                printf("✔ Contact saved!\n");
                break;
            case 3: printf("Exiting...!\nGoodBye!\n");
                free(data);
                exit(EXIT_SUCCESS);
            default: printf("invalid choice");
        }
    }
    return 0;
}

