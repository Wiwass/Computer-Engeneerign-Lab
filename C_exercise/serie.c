/* serie.cpp
Write the first 30 elements of a series defined as follows:
the first three elements are worth 1, the subsequent ones (i>=4) are worth the sum of the elements i-1 and i-3
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    #define MAXSIZE 30
    int num[MAXSIZE];
    for (int i = 0; i < MAXSIZE; i++)
        num[i] = 0;
    num[0] = num[1] = num[2] = 1;
    for (int i = 3; i < MAXSIZE; i++)
    {
        num[i] = num[i - 1] + num[i - 3];
    }
    printf("Serie is:\n");
    for (int i = 0; i < MAXSIZE; i++)
    {
        printf("%5d\n", num[i]);
    }
    exit(0);
}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

// Suggerimenti per iniziare: 
//   1. Usare la finestra Esplora soluzioni per aggiungere/gestire i file
//   2. Usare la finestra Team Explorer per connettersi al controllo del codice sorgente
//   3. Usare la finestra di output per visualizzare l'output di compilazione e altri messaggi
//   4. Usare la finestra Elenco errori per visualizzare gli errori
//   5. Passare a Progetto > Aggiungi nuovo elemento per creare nuovi file di codice oppure a Progetto > Aggiungi elemento esistente per aggiungere file di codice esistenti al progetto
//   6. Per aprire di nuovo questo progetto in futuro, passare a File > Apri > Progetto e selezionare il file con estensione sln
