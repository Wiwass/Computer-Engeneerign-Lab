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

int main() {
    struct List* list = initList();

    // Inserisci alcuni nodi nella lista
    insert(list, 10, "Title1");
    insert(list, 5, "Title3");
    insert(list, 20, "Title2");

    // Stampa la lista
    printf("Lista originale:\n");
    printList(list);

    // Ordina la lista per valore e stampa
    sortByValue(list);
    printf("\nLista ordinata per valore:\n");
    printList(list);

    // Ordina la lista per titolo e stampa
    sortByTitle(list);
    printf("\nLista ordinata per titolo:\n");
    printList(list);

    // Cerca un nodo per titolo
    struct Node* found = searchByTitle(list, "Title2");
    if (found != NULL) {
        printf("\nNodo trovato: Value: %d, Title: %s\n", found->value, found->title);
    } else {
        printf("\nNodo non trovato\n");
    }

    // Elimina un nodo per titolo
    delete(list, "Title1");
    printf("\nLista dopo l'eliminazione di 'Title1':\n");
    printList(list);

    // Libera la memoria della lista
    freeList(list);

    return 0;
}