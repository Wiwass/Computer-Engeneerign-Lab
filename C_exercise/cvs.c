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
