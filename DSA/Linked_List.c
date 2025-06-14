#include <stdio.h>
#include <stdlib.h>
//creation of the  node that 
//consist of data and a pointer to next node
struct Node {
    int data;
    struct Node *next;
};
//Counter for the Nodes
int count;
//Function For Insertin a val at beginning
void insertAtHead(int val, struct Node **head) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = val;
    new_node->next = *head;
    *head = new_node;
    count++;
    printf("\nElement Inserted : %d ", val);
}
void insertAtEnd(int val, struct Node **head) {
    if(count == 0) {
        insertAtHead(val, head);
        return;
    }
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    struct Node *temp = *head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->data = val;
    new_node->next = NULL;
    count++;
    printf("\nElement Inserted : %d", val);
}
void insertAtPos(int val, struct Node **head, int pos) {
    if(pos == 1) {
        insertAtHead(val, head);
        return;
    }
    if(pos == count + 1) {
        insertAtEnd(val, head);
        return;
    }
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    struct Node *temp = *head;
    int cnt = 1;
    while(cnt < pos-1) {
        temp = temp->next;
        cnt++;
    }
    new_node->data = val;
    new_node->next = temp->next;
    temp->next = new_node;
    count++;
    printf("\nElement Inserted : %d ", val);
}
void deleteAtHead(struct Node **head) {
    if(*head == NULL) {
        printf("\nEmpty Link List \nNothing to Delete ");
        return;
    }
    if((*head)->next == NULL) {
        struct Node *temp = *head;
        printf("Deleted Element : %d", (*head)->data);
        free(temp);
        count--;
        *head = NULL;
        return;
    }
    struct Node *temp = *head;
    *head = temp->next;
    printf("Element Deleted : %d", temp->data);
    free(temp);
    count--;

}
void deleteAtEnd(struct Node **head) {
    if(*head == NULL) {
        printf("\nEmpty Link List \nNothing to Delete ");
        return;
    }
    if((*head)->next == NULL) {
        struct Node *temp = *head;
        printf("Deleted Element : %d", (*head)->data);
        free(temp);
        count--;
        *head = NULL;
        return;
    }
    struct Node *temp = *head;
    while(temp->next->next != NULL) {
        temp = temp->next;
    }
    struct Node *del = temp->next;
    temp->next = NULL;
    printf("Deleted Element : %d", del->data);
    free(del);
    count--;
}
void deleteAtPos(struct Node **head, int pos) {
    if(*head == NULL) {
        printf("\nEmpty Link List \nNothing to Delete ");
        return;
    }
    if(pos == 1) {
        deleteAtHead(head);
        return;
    }
    if(pos == count) {
        deleteAtEnd(head);
        return;
    }
    struct Node *temp = *head;
    int cnt = 1;
    while(cnt < pos-1) {
        temp = temp->next;
        cnt++;
    }
    struct Node *del = temp->next;
    temp->next = del->next;
    printf("Deleted Element : %d", del->data);
    free(del);
    count--;
}
void nodeCount() {
    if(count == 0) {
        printf("\nEmpty Link List ");
        return;
    }
    printf("\nTotal Nodes : %d", count);
}
void display(struct Node *head) {
    struct Node *temp = head;
    if(temp == NULL) {
        printf("\nEmpty Link List ");
        return;
    }
    while(temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
// Main function 
int main() {
    // Head Pointer 
    struct Node *head = NULL;
    struct Node *next = NULL;
    int choice, val, pos;
    do {
        printf("\n1) Insert at Head ");
        printf("\n2) Insert at End ");
        printf("\n3) Insert at Position ");
        printf("\n4) Delete at Head ");
        printf("\n5) Delete  at End ");
        printf("\n6) Delete at Position ");
        printf("\n7) Display ");
        printf("\n8) Node Count ");
        printf("\n9) Exit ");
        printf("\nEnter Your Choice :");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("\nEnter the Elemen : ");
                scanf("%d", &val);
                insertAtHead(val, &head);
                break;
            case 2:
                printf("\nEnter the Element : ");
                scanf("%d", &val);
                insertAtEnd(val, &head);
                break;
            case 3:
            printf("\nEnter the Element : ");
            scanf("%d", &val);
            printf("\nEnter the position : ");
            scanf("%d", &pos);
            if(pos <= 0 || pos > count + 1) {
                printf("\nInvalid Input ");
                break;
            }
            insertAtPos(val, &head, pos);
            break;
        case 4:
            deleteAtHead(&head);
            break;
        case 5:
            deleteAtEnd(&head);
            break;
        case 6:
            printf("\nEnter the position : ");
            scanf("%d", &pos);
            if(pos <= 0 || pos > count) {
                printf("\nInvalid Position : ");
                break;
            }
            deleteAtPos(&head, pos);
            break;
        case 7:
            display(head);
            break;
        case 8:
            nodeCount();
            break;
        case 9:
            printf("\nExiting.......!\n");
            exit(0);
        default:
            printf("\nInvalid Input ");
        }
    }while(choice != 9);
    return 0;
}
