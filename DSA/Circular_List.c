#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data; 
    struct Node *next;
};

void insertAtBeg(int val, struct Node **head, int *count) {
    if(*head == NULL) {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        new_node->data = val;
        new_node->next = *head;
        *count++;
        return;
    }
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->next = *head;
    *head = new_node;
    *count++;
}

void insertAtEnd(int val, struct Node **head, int *count) {
    if(*head == NULL) {
        insertAtBeg(val, head, count);
        return;   
    }
    struct Node *temp = *head;
    while(temp->next != *head) {
        temp = temp->next;
    }
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    temp->next = new_node;
    new_node->data = val;
    new_node->next = *head;
    (*count)++;
}

void insertAtPos(int val, struct Node **head, int *count, int pos) {
    if(*head == NULL) {
        insertAtBeg(val, head, count);
        return;
    }
    if(pos == count + 1) {
        insertAtEnd(val, head, count);
        return;
    }
    int cnt = 1;
    struct Node *temp = *head;
    while(cnt < pos-1) {
        temp = temp->next;
        cnt++;
    }
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = val;
    new_node->next = temp->next;
    temp->next = new_node;
    (*count)++;
}

void deleteAtBeg(struct Node **head, int *count) {
    if(*head == NULL) {
        printf("\nList is Empty ! \n");
        return;
    }
    struct Node *temp = *head;
    *head = (*head)->next;
    free(temp);
    (*count)--;
}

void deleteAtEnd(struct Node **head, int *count) {
    if(*head == NULL) {
        printf("\nList is Empty ! \n");
        return;
    }
    struct Node *temp = *head;
    while(temp->next->next != NULL) {
        temp = temp->next;
    }
    struct Node *del = temp->next;
    temp->next = *head;
    free(del);
    (*count)--;
}

void deleteAtPos(struct Node **head, int pos, int *count) {
    if(*head == NULL) {
        printf("\nList is Empty ! \n");
        return;
    }
    struct Node *temp = *head;
    int cnt = 1;
    while(cnt < pos - 1) {
        temp = temp->next;
        cnt++;
    }
    struct Node *del = temp->next;
    temp->next = del->next;
    free(del);
    (*count)--;
}
void displaY(struct Node **head) {
    if(*head == NULL) {
        printf("\nList is Empty ! \n");
        return;
    }
    struct Node *temp = *head;
    while(temp->next != *head) {
        printf("%d->", temp->data);
    }
    printf("NULL");
}