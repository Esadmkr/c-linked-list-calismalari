#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    char text[50];
    struct Word* next;
} Word;


void pushWord(Word** top, char* text);
void popWord(Word** top);
void showWords(Word* top);

int main() {
    Word* top = NULL;
    char command[100];
    char word[50];

    printf("--- UNDO SIMULATION PROGRAM ---\n");
    printf("Commands: 'add ', 'undo', 'show', 'exit'\n\n");

    while (1) {
        printf("> ");
        if (fgets(command, sizeof(command), stdin) == NULL) break;

        
        command[strcspn(command, "\n")] = 0;

        if (strncmp(command, "add ", 4) == 0) {
            strcpy(word, command + 4);
            pushWord(&top, word);
        } 
        else if (strcmp(command, "undo") == 0) {
            popWord(&top);
        } 
        else if (strcmp(command, "show") == 0) {
            printf("show -> ");
            if (top == NULL) {
                printf("(empty)");
            } else {
                showWords(top);
            }
            printf("\n");
        } 
        else if (strcmp(command, "exit") == 0) {
            printf("Exiting application...\n");
            break;
        } 
        else {
            printf("Invalid command! Use 'add ', 'undo', 'show', or 'exit'.\n");
        }
    }

    
    while (top != NULL) {
        popWord(&top);
    }

    return 0;
}


void pushWord(Word** top, char* text) {
    Word* newWord = (Word*)malloc(sizeof(Word));
    if (newWord == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(newWord->text, text);
    newWord->next = *top;
    *top = newWord;
}


void popWord(Word** top) {
    if (*top == NULL) {
        printf("Nothing to undo!\n");
        return;
    }
    Word* temp = *top;
    *top = (*top)->next;
    free(temp);
}


void showWords(Word* top) {
    if (top == NULL) {
        return;
    }
    
    showWords(top->next);
    
    
    printf("%s ", top->text);
}