
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;


void addOrdered(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    
    if (*head == NULL || value < (*head)->data) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    
    Node* current = *head;
    while (current->next != NULL && current->next->data < value) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}


void removeNode(Node** head, int value) {
    if (*head == NULL) {
        return;
    }

    Node* current = *head;
    Node* previous = NULL;

    
    if (current->data == value) {
        *head = current->next;
        free(current);
        return;
    }

    
    while (current != NULL && current->data != value) {
        previous = current;
        current = current->next;
    }

    
    if (current != NULL) {
        previous->next = current->next;
        free(current);
    }
}


int count(Node* head) {
    int total = 0;
    Node* current = head;
    while (current != NULL) {
        total++;
        current = current->next;
    }
    return total;
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

    
    int values[] = {23, 11, 5, 9, 6, 4, 12, 24};
    int n = sizeof(values) / sizeof(values[0]);

    printf("Elemanlar sirayla ekleniyor...\n");
    for (int i = 0; i < n; i++) {
        addOrdered(&head, values[i]);
    }

    
    printf("Sirali Liste: ");
    printList(head);
    printf("Toplam Dugum Sayisi: %d\n\n", count(head));

    
    printf("9 degeri siliniyor...\n");
    removeNode(&head, 9);
    printList(head);

    printf("Bastan 4 degeri siliniyor...\n");
    removeNode(&head, 4);
    printList(head);
    printf("Kalan Dugum Sayisi: %d\n\n", count(head));

    
    printf("Liste tamamen temizleniyor...\n");
    clear(&head);
    printf("Temizleme sonrasi liste: ");
    printList(head);
    printf("Dugum Sayisi: %d\n", count(head));

    return 0;
}
