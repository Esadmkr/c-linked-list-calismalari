#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* findMiddle(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* slow = head;
    Node* fast = head;

    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
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


void append(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;

    
    append(&list1, 10);
    append(&list1, 20);
    append(&list1, 30);
    append(&list1, 40);
    append(&list1, 50);

    printf("Liste 1 (Tek sayida eleman): ");
    printList(list1);
    Node* mid1 = findMiddle(list1);
    if (mid1 != NULL) {
        printf("Ortadaki dugum degeri: %d\n\n", mid1->data);
    }

    // Test 2: Cift sayida eleman (1, 2, 3, 4, 5, 6)
    append(&list2, 1);
    append(&list2, 2);
    append(&list2, 3);
    append(&list2, 4);
    append(&list2, 5);
    append(&list2, 6);

    printf("Liste 2 (Cift sayida eleman): ");
    printList(list2);
    Node* mid2 = findMiddle(list2);
    if (mid2 != NULL) {
        printf("Ortadaki dugum degeri (ikinci orta): %d\n\n", mid2->data);
    }

    
    Node* emptyList = NULL;
    Node* midEmpty = findMiddle(emptyList);
    printf("Bos liste icin donen sonuc: %s\n\n", midEmpty == NULL ? "NULL" : "Dugum var");

    
    clear(&list1);
    clear(&list2);

    return 0;
}
