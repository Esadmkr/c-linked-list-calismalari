#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PrintJob {
    char fileName[50];
    struct PrintJob* next;
} PrintJob;

typedef struct Queue {
    PrintJob* front;
    PrintJob* rear;
} Queue;


void enqueuePrintJob(Queue* q, char* fileName);
void processNextJob(Queue* q);
void showQueue(Queue q);

int main() {
    
    Queue q;
    q.front = NULL;
    q.rear = NULL;

    int choice;
    char fileName[50];

    while (1) {
        printf("\n--- PRINTER QUEUE MENU ---\n");
        printf("1) Add new file (Enqueue)\n");
        printf("2) Print (Process Next Job)\n");
        printf("3) Show queue\n");
        printf("4) Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                fgets(fileName, sizeof(fileName), stdin);
                fileName[strcspn(fileName, "\n")] = 0; 
                enqueuePrintJob(&q, fileName);
                break;

            case 2:
                processNextJob(&q);
                break;

            case 3:
                showQueue(q);
                break;

            case 4:
                printf("Exiting application...\n");
                
                while (q.front != NULL) {
                    processNextJob(&q);
                }
                return 0;

            default:
                printf("Invalid option! Please try again.\n");
        }
    }

    return 0;
}


void enqueuePrintJob(Queue* q, char* fileName) {
    PrintJob* newJob = (PrintJob*)malloc(sizeof(PrintJob));
    if (newJob == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    strcpy(newJob->fileName, fileName);
    newJob->next = NULL;

    
    if (q->rear == NULL) {
        q->front = newJob;
        q->rear = newJob;
    } else {
        q->rear->next = newJob;
        q->rear = newJob;
    }

    printf("File '%s' added to the print queue.\n", fileName);
}


void processNextJob(Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty! No jobs to print.\n");
        return;
    }

    PrintJob* temp = q->front;
    printf("Printing file: %s...\n", temp->fileName);

    q->front = q->front->next;

    
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
}


void showQueue(Queue q) {
    if (q.front == NULL) {
        printf("Queue is empty!\n");
        return;
    }

    printf("\n--- CURRENT PRINT QUEUE ---\n");
    PrintJob* temp = q.front;
    int index = 1;
    while (temp != NULL) {
        printf("%d. %s\n", index++, temp->fileName);
        temp = temp->next;
    }
}