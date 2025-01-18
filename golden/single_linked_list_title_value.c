#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int value;
    char* title;
    struct Node* next;
};

struct List {
    struct Node* head;
    int size;
};

// Inizializzazione
struct List* initList() {
    struct List* list = (struct List*)malloc(sizeof(struct List));
    list->head = NULL;
    list->size = 0;
    return list;
}

// Inserimento
void insert(struct List* list, int value, const char* title) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->title = strdup(title);
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

// Ricerca
struct Node* searchByTitle(struct List* list, const char* title) {
    struct Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) return current;
        current = current->next;
    }
    return NULL;
}

// Eliminazione
int delete(struct List* list, const char* title) {
    struct Node* current = list->head;
    struct Node* prev = NULL;

    while (current != NULL && strcmp(current->title, title) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return 0;

    if (prev == NULL) {
        list->head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current->title);
    free(current);
    list->size--;
    return 1;
}

// Stampa
void printList(struct List* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("Value: %d, Title: %s\n", current->value, current->title);
        current = current->next;
    }
}

// Libera memoria
void freeList(struct List* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp->title);
        free(temp);
    }
    free(list);
}

// Utility
int size(struct List* list) {
    return list->size;
}

int isEmpty(struct List* list) {
    return list->size == 0;
}

void sortByValue(struct List* list) {
    if (list->size < 2) return;

    struct Node* i;
    struct Node* j;
    int temp_value;
    char* temp_title;

    for (i = list->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->value > j->value) {
                // Scambia value
                temp_value = i->value;
                i->value = j->value;
                j->value = temp_value;

                // Scambia title
                temp_title = i->title;
                i->title = j->title;
                j->title = temp_title;
            }
        }
    }
}

void sortByTitle(struct List* list) {
    if (list->size < 2) return;

    struct Node* i;
    struct Node* j;
    int temp_value;
    char* temp_title;

    for (i = list->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->title, j->title) > 0) {
                // Scambia value
                temp_value = i->value;
                i->value = j->value;
                j->value = temp_value;

                // Scambia title
                temp_title = i->title;
                i->title = j->title;
                j->title = temp_title;
            }
        }
    }
}