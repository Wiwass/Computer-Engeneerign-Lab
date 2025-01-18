#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

// Struttura per rappresentare una riga del file CSV
struct CSVRow {
    char** fields; // Array di stringhe, ogni stringa rappresenta un campo della riga
    int fieldCount; // Numero di campi nella riga
};

/**
 * Funzione per leggere una riga dal file CSV
 * @param file: puntatore al file CSV aperto
 * @return: puntatore alla struttura CSVRow che rappresenta la riga letta, NULL se fine del file
 */
struct CSVRow* readCSVRow(FILE* file) {
    char line[MAX_LINE_LENGTH];
    if (fgets(line, sizeof(line), file) == NULL) {
        return NULL;
    }

    struct CSVRow* row = (struct CSVRow*)malloc(sizeof(struct CSVRow));
    row->fields = (char**)malloc(MAX_FIELD_LENGTH * sizeof(char*));
    row->fieldCount = 0;

    char* token = strtok(line, ",");
    while (token != NULL) {
        row->fields[row->fieldCount] = strdup(token);
        row->fieldCount++;
        token = strtok(NULL, ",");
    }

    return row;
}

/**
 * Funzione per liberare la memoria di una riga del file CSV
 * @param row: puntatore alla struttura CSVRow da liberare
 */
void freeCSVRow(struct CSVRow* row) {
    for (int i = 0; i < row->fieldCount; i++) {
        free(row->fields[i]);
    }
    free(row->fields);
    free(row);
}

/**
 * Funzione per leggere tutte le righe dal file CSV
 * @param filename: nome del file CSV da leggere
 * @param rowCount: puntatore a un intero dove verrà memorizzato il numero di righe lette
 * @return: array di puntatori a strutture CSVRow che rappresentano le righe lette
 */
struct CSVRow** readCSVFile(const char* filename, int* rowCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return NULL;
    }

    struct CSVRow** rows = (struct CSVRow**)malloc(MAX_LINE_LENGTH * sizeof(struct CSVRow*));
    *rowCount = 0;

    struct CSVRow* row;
    while ((row = readCSVRow(file)) != NULL) {
        rows[*rowCount] = row;
        (*rowCount)++;
    }

    fclose(file);
    return rows;
}

/**
 * Funzione per liberare la memoria di tutte le righe del file CSV
 * @param rows: array di puntatori a strutture CSVRow da liberare
 * @param rowCount: numero di righe da liberare
 */
void freeCSVFile(struct CSVRow** rows, int rowCount) {
    for (int i = 0; i < rowCount; i++) {
        freeCSVRow(rows[i]);
    }
    free(rows);
}

int main() {
    const char* filename = "example.csv"; // Nome del file CSV da leggere
    int rowCount;

    // Leggi tutte le righe dal file CSV
    struct CSVRow** rows = readCSVFile(filename, &rowCount);
    if (rows == NULL) {
        printf("Errore nella lettura del file CSV.\n");
        return 1;
    }

    // Stampa tutte le righe lette dal file CSV
    printf("Contenuto del file CSV:\n");
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < rows[i]->fieldCount; j++) {
            printf("%s", rows[i]->fields[j]);
            if (j < rows[i]->fieldCount - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }

    // Libera la memoria di tutte le righe lette dal file CSV
    freeCSVFile(rows, rowCount);

    return 0;
}


