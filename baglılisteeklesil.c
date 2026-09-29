#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;


void insertAt(Node** head, int value, int position) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    
    if (position <= 0 || *head == NULL) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    
    Node* current = *head;
    for (int i = 0; i < position - 1 && current->next != NULL; i++) {
        current = current->next;
    }

    
    newNode->next = current->next;
    current->next = newNode;
}


void deleteAt(Node** head, int position) {
   
    if (*head == NULL || position < 0) {
        return;
    }

    
    if (position == 0) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    
    Node* current = *head;
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }

    
    if (current == NULL || current->next == NULL) {
        return;
    }

    
    Node* target = current->next;
    current->next = target->next;
    free(target);
}


void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}


void clear(Node** head) {
    Node* current = *head;
    Node* nextNode = NULL;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    *head = NULL;
}

int main() {
    Node* head = NULL;

    printf("--- Pozisyona Gore Ekleme Testleri ---\n");
    insertAt(&head, 10, 0);   
    insertAt(&head, 20, 1);   
    insertAt(&head, 5, -3);   
    insertAt(&head, 15, 2);   
    insertAt(&head, 30, 100); 
    
    printf("Liste: ");
    printList(head); 

    printf("\n--- Pozisyona Gore Silme Testleri ---\n");
    deleteAt(&head, 0);       
    printf("0. pozisyon silindi: ");
    printList(head); 
    deleteAt(&head, 1);       
    printf("1. pozisyon silindi: ");
    printList(head); 

    deleteAt(&head, 50);      
    printf("Gecersiz pozisyon (50) denendi: ");
    printList(head); 
    printf("\n--- Listeyi Temizleme ---\n");
    clear(&head);
    printf("Temizlendikten sonra: ");
    printList(head); 
    return 0;
}