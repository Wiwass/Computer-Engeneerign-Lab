#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

// separare usando terminatori stringhe

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, " ");
            tok && *tok;
            tok = strtok(NULL, " \n"))
    {
        if (num-- <= 0)
            return tok;
    }
    return NULL;
}

int main(){
	
	FILE* stream = fopen("sequence2.txt", "r");
	int array[100];
	char* temp;

    char line[1024];
    fgets(line, 1024, stream);
 
    char* tmp = strdup(line);

	
	for(int i=0; i<100; i++){
        char* tmp_copy = strdup(tmp); // Crea una copia della stringa originale
        temp=(char*)getfield(tmp_copy, i); // Passa la copia alla funzione getfield
        if(atoi(temp) == 0){
            array[i] = 0;
            free(tmp_copy); // Libera la memoria allocata per la copia
            break;
        }
        array[i] = atoi(temp);
        free(tmp_copy); // Libera la memoria allocata per la copia
    }

    
	int pari[100];
	int dispari[100];
	int conta_pari=0;
	int conta_dispari=0;
	
	for(int i=0;i<100;i++){
		
		if(array[i]==0){break;}
		
		if(array[i]%2==0){pari[conta_pari]=array[i]
			;conta_pari++;
			}
		if(array[i]%2!=0){
			dispari[conta_dispari]=array[i];
			conta_dispari++;
			}
		
	}
	
	int conta=conta_dispari+conta_pari;
	printf("%d\n",conta);
	printf("numero di pari:%d\n",conta_pari);
	printf("numero di dispari:%d\n",conta_dispari);
	
	//array sorting di pari e dispari;
	
	
	qsort(pari, conta_pari, sizeof(int), compare);
	qsort(dispari, conta_dispari, sizeof(int), compare);
	
	for(int i=0;i<conta_pari;i++){
		printf("%d ",pari[i]);
	}
	
	printf("\n");
	
	for(int i=0;i<conta_dispari;i++){
		printf("%d ",dispari[i]);
	}
	printf("\n");
	
	}
