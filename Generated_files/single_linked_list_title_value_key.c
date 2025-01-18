#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int key; // Chiave univoca del nodo
    int value; // Valore associato al nodo
    char* title; // Titolo associato al nodo
    struct Node* next; // Puntatore al nodo successivo
};

struct List {
    struct Node* head; // Puntatore al primo nodo della lista
    int size; // Numero di nodi nella lista
};

/**
 * Funzione per inizializzare una nuova lista
 * @return: puntatore alla nuova lista inizializzata
 */
struct List* initList() {
    struct List* list = (struct List*)malloc(sizeof(struct List));
    list->head = NULL;
    list->size = 0;
    return list;
}

/**
 * Funzione per inserire un nuovo nodo nella lista
 * @param list: puntatore alla lista
 * @param key: chiave del nuovo nodo
 * @param value: valore del nuovo nodo
 * @param title: titolo del nuovo nodo
 */
void insert(struct List* list, int key, int value, const char* title) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->title = strdup(title);
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

/**
 * Funzione per cercare un nodo nella lista per titolo
 * @param list: puntatore alla lista
 * @param title: titolo da cercare
 * @return: puntatore al nodo trovato, NULL se non trovato
 */
struct Node* searchByTitle(struct List* list, const char* title) {
    struct Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) return current;
        current = current->next;
    }
    return NULL;
}

/**
 * Funzione per eliminare un nodo dalla lista per titolo
 * @param list: puntatore alla lista
 * @param title: titolo del nodo da eliminare
 * @return: 1 se il nodo è stato eliminato, 0 se non trovato
 */
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

/**
 * Funzione per stampare tutti i nodi della lista
 * @param list: puntatore alla lista
 */
void printList(struct List* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("Key: %d, Value: %d, Title: %s\n", current->key, current->value, current->title);
        current = current->next;
    }
}

/**
 * Funzione per liberare la memoria di tutti i nodi della lista
 * @param list: puntatore alla lista
 */
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

/**
 * Funzione per ottenere la dimensione della lista
 * @param list: puntatore alla lista
 * @return: numero di nodi nella lista
 */
int size(struct List* list) {
    return list->size;
}

/**
 * Funzione per verificare se la lista è vuota
 * @param list: puntatore alla lista
 * @return: 1 se la lista è vuota, 0 altrimenti
 */
int isEmpty(struct List* list) {
    return list->size == 0;
}

/**
 * Funzione per ordinare i nodi della lista per valore
 * @param list: puntatore alla lista
 */
void sortByValue(struct List* list) {
    if (list->size < 2) return;

    struct Node* i;
    struct Node* j;
    int temp_key;
    int temp_value;
    char* temp_title;

    for (i = list->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->value > j->value) {
                // Scambia key
                temp_key = i->key;
                i->key = j->key;
                j->key = temp_key;

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

/**
 * Funzione per ordinare i nodi della lista per titolo
 * @param list: puntatore alla lista
 */
void sortByTitle(struct List* list) {
    if (list->size < 2) return;

    struct Node* i;
    struct Node* j;
    int temp_key;
    int temp_value;
    char* temp_title;

    for (i = list->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->title, j->title) > 0) {
                // Scambia key
                temp_key = i->key;
                i->key = j->key;
                j->key = temp_key;

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
