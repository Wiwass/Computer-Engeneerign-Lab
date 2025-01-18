#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

// Struttura per rappresentare una riga del file CSV
struct CSVRow {
    char** fields;
    int fieldCount;
};

// Funzione per leggere una riga dal file CSV
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

// Funzione per liberare la memoria di una riga del file CSV
void freeCSVRow(struct CSVRow* row) {
    for (int i = 0; i < row->fieldCount; i++) {
        free(row->fields[i]);
    }
    free(row->fields);
    free(row);
}

// Funzione per leggere tutte le righe dal file CSV
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

// Funzione per liberare la memoria di tutte le righe del file CSV
void freeCSVFile(struct CSVRow** rows, int rowCount) {
    for (int i = 0; i < rowCount; i++) {
        freeCSVRow(rows[i]);
    }
    free(rows);
}

// Funzione per stampare una riga del file CSV
void printCSVRow(struct CSVRow* row) {
    for (int i = 0; i < row->fieldCount; i++) {
        printf("%s", row->fields[i]);
        if (i < row->fieldCount - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

// Funzione per stampare tutte le righe del file CSV
void printCSVFile(struct CSVRow** rows, int rowCount) {
    for (int i = 0; i < rowCount; i++) {
        printCSVRow(rows[i]);
    }
}
