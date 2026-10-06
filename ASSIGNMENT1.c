#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[50];
    struct Song* next;
    struct Song* prev;
} Song;


void addSongToEnd(Song** head, char* name);
void removeSong(Song** head, char* name);
void playNext(Song** current);
void playPrevious(Song** current);
void displayPlaylist(Song* head);

int main() {
    Song* head = NULL;
    Song* current = NULL;
    int choice;
    char songName[50];

    while (1) {
        printf("\n--- MUSIC PLAYER MENU ---\n");
        printf("1. Add Song\n");
        printf("2. Remove Song\n");
        printf("3. Play Next Song\n");
        printf("4. Play Previous Song\n");
        printf("5. Display Playlist\n");
        printf("6. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Enter song name: ");
                fgets(songName, sizeof(songName), stdin);
                songName[strcspn(songName, "\n")] = 0; 
                addSongToEnd(&head, songName);
                if (current == NULL) {
                    current = head; 
                }
                break;

            case 2:
                if (head == NULL) {
                    printf("List is empty!\n");
                    break;
                }
                printf("Enter song name to remove: ");
                fgets(songName, sizeof(songName), stdin);
                songName[strcspn(songName, "\n")] = 0;

                
                if (current != NULL && strcmp(current->name, songName) == 0) {
                    if (current->next != NULL) {
                        current = current->next;
                    } else if (current->prev != NULL) {
                        current = current->prev;
                    } else {
                        current = NULL;
                    }
                }

                removeSong(&head, songName);
                break;

            case 3:
                playNext(&current);
                break;

            case 4:
                playPrevious(&current);
                break;

            case 5:
                displayPlaylist(head);
                break;

            case 6:
                printf("Exiting application...\n");
                
                return 0;

            default:
                printf("Invalid selection! Try again.\n");
        }
    }

    return 0;
}


void addSongToEnd(Song** head, char* name) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->name, name);
    newSong->next = NULL;
    newSong->prev = NULL;

    if (*head == NULL) {
        *head = newSong;
        printf("Song '%s' added to the playlist.\n", name);
        return;
    }

    Song* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newSong;
    newSong->prev = temp;
    printf("Song '%s' added to the playlist.\n", name);
}


void removeSong(Song** head, char* name) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }

    Song* temp = *head;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Song '%s' not found in playlist.\n", name);
        return;
    }

    
    if (*head == temp) {
        *head = temp->next;
    }

    
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }

    free(temp);
    printf("Song '%s' removed from playlist.\n", name);
}


void playNext(Song** current) {
    if (*current == NULL) {
        printf("List is empty!\n");
        return;
    }

    if ((*current)->next != NULL) {
        *current = (*current)->next;
        printf("Now playing: %s\n", (*current)->name);
    } else {
        printf("You are at the end of the playlist. Current song: %s\n", (*current)->name);
    }
}


void playPrevious(Song** current) {
    if (*current == NULL) {
        printf("List is empty!\n");
        return;
    }

    if ((*current)->prev != NULL) {
        *current = (*current)->prev;
        printf("Now playing: %s\n", (*current)->name);
    } else {
        printf("You are at the beginning of the playlist. Current song: %s\n", (*current)->name);
    }
}


void displayPlaylist(Song* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    printf("\n--- PLAYLIST ---\n");
    Song* temp = head;
    int index = 1;
    while (temp != NULL) {
        printf("%d. %s\n", index++, temp->name);
        temp = temp->next;
    }
}