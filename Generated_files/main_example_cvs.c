#include <stdio.h>
#include "tools_cvs_read.c" // Includi il file con le funzioni per leggere i file CSV

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
    printCSVFile(rows, rowCount);

    // Libera la memoria di tutte le righe lette dal file CSV
    freeCSVFile(rows, rowCount);

    return 0;
}
