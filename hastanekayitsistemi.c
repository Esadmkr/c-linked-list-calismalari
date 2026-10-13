#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct HastaNode {
    int id;
    char isim[50];
    char durum[20];
    struct HastaNode* next;
} HastaNode;


typedef struct Queue {
    HastaNode* front;
    HastaNode* rear;
} Queue;

Queue* createQueue(){
    Queue* q =(Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
}

void enqueue(Queue* q, int id, const char*isim){
    HastaNode* newNode  =(HastaNode*)malloc(sizeof(HastaNode));
    newNode->id = id;
    strcpy(newNode->isim, isim);
    strcpy(newNode->durum, "bekliyor");
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;

}
HastaNode* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    HastaNode* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }
    temp->next = NULL;
    return temp;
}
typedef struct Stack {
    HastaNode* top;
} Stack;

Stack* createStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}
void push(Stack* s, HastaNode* node) {
    if (node == NULL) return;
    strcpy(node->durum, "muayenede");
    node->next = s->top;
    s->top = node;
}
HastaNode* pop(Stack* s) {
    if (s->top == NULL) return NULL; 

    HastaNode* temp = s->top;
    s->top = s->top->next;
    temp->next = NULL;
    return temp;
}
typedef struct List {
    HastaNode* head;
} List;

List* createList() {
    List* l = (List*)malloc(sizeof(List));
    l->head = NULL;
    return l;
}
void listeyeEkle(List* l, HastaNode* node) {
    if (node == NULL) return;
    strcpy(node->durum, "tamamlandi");
    node->next = NULL;

    if (l->head == NULL) {
        l->head = node;
        return;
    }
    HastaNode* temp = l->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
}
void muayeneyeAl(Queue* q, Stack* s) {
    HastaNode* hasta = dequeue(q);
    if (hasta != NULL) {
        push(s, hasta);
    } else {
        printf("Bekleyen hasta yok!\n");
    }
}
void muayeneTamamla(Stack* s, List* l) {
    HastaNode* hasta = pop(s);
    if (hasta != NULL) {
        listeyeEkle(l, hasta);
    } else {
        printf("Muayene odasında hasta yok!\n");
    }
}
void durumuYazdir(Queue* q, Stack* s, List* l) {
    printf("--- Bekleyen Hastalar ---\n");
    HastaNode* temp = q->front;
    if (temp == NULL) {
        printf("Hasta yok.\n");
    } else {
        while (temp != NULL) {
            printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->id, temp->isim, temp->durum);
            temp = temp->next;
        }
    }

    printf("\n--- Muayene Odasindaki Hastalar ---\n");
    temp = s->top;
    if (temp == NULL) {
        printf("Hasta yok.\n");
    } else {
        while (temp != NULL) {
            printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->id, temp->isim, temp->durum);
            temp = temp->next;
        }
    }

    printf("\n--- Tamamlanan Hastalar ---\n");
    temp = l->head;
    if (temp == NULL) {
        printf("Hasta yok.\n");
    } else {
        while (temp != NULL) {
            printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->id, temp->isim, temp->durum);
            temp = temp->next;
        }
    }
    printf("\n");
}
int main() {
    Queue* bekleyenler = createQueue();
    Stack* muayenedekiler = createStack();
    List* tamamlananlar = createList();
    enqueue(bekleyenler, 1, "Ahmet");
    enqueue(bekleyenler, 2, "Mehmet");
    enqueue(bekleyenler, 3, "Ayse");
    muayeneyeAl(bekleyenler, muayenedekiler);
    muayeneTamamla(muayenedekiler, tamamlananlar);
    muayeneyeAl(bekleyenler, muayenedekiler);
    muayeneTamamla(muayenedekiler, tamamlananlar);
printf("=== Tum Islemler Sonrasi ===\n\n");
    durumuYazdir(bekleyenler, muayenedekiler, tamamlananlar);

    return 0;
}

