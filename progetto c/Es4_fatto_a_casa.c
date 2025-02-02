#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// le date nell'output sono tra parntesi tonde per rendere più leggibile l'output soprattutto qunado si rappresentano intervalli di tempo che finiscono BC e quindi presentano un trattino davanti

typedef struct {
    int start;
    int end;
} interval;

typedef struct {
    char* eventName;
    interval period;
} event;

struct node {
    event data;
    struct node* left;
    struct node* right;
};

// Funzione per creare un nuovo nodo
struct node* createNode(char* eventName, int start, int end) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data.eventName = strdup(eventName);  // Alloca memoria per la stringa
    newNode->data.period.start = start;           //
    newNode->data.period.end = end;               //assegno i valori al nodo
    newNode->left = newNode->right = NULL;        //
    return newNode;
}

// Funzione per inserire un nodo nel BST
struct node* insert(struct node* root, char* eventName, int start, int end) {
    if (root == NULL)
        return createNode(eventName, start, end);

    if (start < root->data.period.start) // prendo come riferimento per l'ordinamento l'anno di inizio dell'evento
        root->left = insert(root->left, eventName, start, end);
    else
        root->right = insert(root->right, eventName, start, end);

    return root;
}

// Visita inorder per stampare in ordine ascendente
void inorderAscending(struct node* root) {
    if (root != NULL) {
        inorderAscending(root->left);
        printf("%s: (%d)", root->data.eventName, root->data.period.start);
        if (root->data.period.end != root->data.period.start)
            printf("-(%d)", root->data.period.end);
        printf("\n");
        inorderAscending(root->right);
    }
}

// Visita inorder inversa per stampare in ordine discendente
void inorderDescending(struct node* root) {
    if (root != NULL) {
        inorderDescending(root->right);
        printf("%s: (%d)", root->data.eventName, root->data.period.start);
        if (root->data.period.end != root->data.period.start)
            printf("-(%d)", root->data.period.end);
        printf("\n");
        inorderDescending(root->left);
    }
}

// Funzione per calcolare l'altezza del BST
int getHeight(struct node* root) {
    if (root == NULL)
        return -1;
    
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong input\n");
        return 1;
    }

    char* filename=argv[1];
    //filename="historicalEvents.csv";

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Errore nell'apertura del file\n");
        return 1;
    }

    struct node* root = NULL;
    char line[256];
    char eventName[200];
    int startYear, endYear;

    // Lettura del file e costruzione del BST
    while (fgets(line, sizeof(line), file)) {
        char* period = strchr(line, ';');
        if (period == NULL) continue;  // Salta la riga se non c'è il punto e virgola
        
        *period = '\0';  // Sostituisce il punto e virgola con il terminatore di stringa
        strcpy(eventName, line); // Copia il nome dell'evento
        period++;  // Avanza il puntatore alla parte successiva della stringa

        if (strchr(period, '#')) {  // Se c'è il cancelletto, allora c'è un intervallo
            sscanf(period, "%d#%d", &startYear, &endYear);
        } else {
            sscanf(period, "%d", &startYear);  // Altrimenti c'è un solo anno
            endYear = startYear;
        }

        root = insert(root, eventName, startYear, endYear); // Inserisce l'evento nel BST
    }

    fclose(file);  // Chiude il file


    // i nomi delle funzioni sono abbasta autoesplicativi
    printf("\nEventi in ordine ascendente per anno di inizio:\n");
    inorderAscending(root);

    printf("\nEventi in ordine discendente per anno di inizio:\n");
    inorderDescending(root);

    printf("\nAltezza del BST: %d\n", getHeight(root));

    return 0;
}