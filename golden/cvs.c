#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp = fopen("data.csv", "r");
    if (!fp) {
        printf("Impossibile aprire il file\n");
        return 1;
    }

    char buf[1024]; //creazione di un buffer di 1024 caratteri
    while (fgets(buf, 1024, fp)) {
        char *campo = strtok(buf, ","); //divido la riga in campi separati da virgola, o un qualunque altro carattere separatore
        while(campo) {
            printf("%s\n", campo);
            campo = strtok(NULL, ","); //continua a dividere la riga in campi separati da virgola, o un qualunque altro carattere separatore
        }
    }

    fclose(fp);
    return 0;
}

int stringToInt(const char* str) {
    // Verifica input valido
    if (str == NULL) {
        printf("Errore: stringa vuota\n");
        return -1;
    }

    // Variabili per gestire la conversione
    char* endPtr;
    long result = strtol(str, &endPtr, 10);

    // Verifica errori di conversione
    if (*endPtr != '\0' && *endPtr != '\n') {
        printf("Errore: conversione non valida per '%s'\n", str);
        return -1;
    }

    // Verifica range valido per int
    if (result > INT_MAX || result < INT_MIN) {
        printf("Errore: numero fuori range\n");
        return -1;
    }

    return (int)result;
}

/**
 * Funzione per convertire un intero in una stringa in base 10
 * @param value: intero da convertire
 * @param str: buffer di destinazione per la stringa convertita
 * @return: puntatore alla stringa convertita
 */
char* intToString(int value, char* str) {
    sprintf(str, "%d", value);
    return str;
}