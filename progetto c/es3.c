#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 20
#define MAX_TEAM 40
#define MAX_ROW 80
#define MAX_TOURNAMENT 20
#define MAX_MANIFACTURE 7

struct driver{
		char title[MAX_NAME+1];
		char house[MAX_TEAM+1];
		int value;
		struct driver* next;
	
};
struct house{
	char title[MAX_TEAM+1];
	int value;
	struct house* next;

};
struct mani{
	char title[MAX_MANIFACTURE+1];
	int value;
	struct mani* next;
};

struct DList {
    struct driver* head;
    int size;
};

struct HList {
    struct house* head;
    int size;
};

struct MList {
    struct mani* head;
    int size;
};

// Inizializzazione
struct DList* initDList() {
    struct DList* list = (struct DList*)malloc(sizeof(struct DList));
    list->head = NULL;
    list->size = 0;
    return list;
}


struct HList* inithList() {
    struct HList* list = (struct HList*)malloc(sizeof(struct HList));
    list->head = NULL;
    list->size = 0;
    return list;
}

struct MList* initmList() {
    struct MList* list = (struct MList*)malloc(sizeof(struct MList));
    list->head = NULL;
    list->size = 0;
    return list;
}

// Ricerca
struct driver* searchDByTitle(struct DList* list, const char* title) {
    struct driver* current = list->head;
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) return current;
        current = current->next;
    }
    return NULL;
}


struct house* searchHByTitle(struct HList* list, const char* title) {
    struct house* current = list->head;
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) return current;
        current = current->next;
    }
    return NULL;
}

struct mani* searchMByTitle(struct MList* list, const char* title) {
    struct mani* current = list->head;
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) return current;
        current = current->next;
    }
    return NULL;
}

// Inserimento
void Dinsert(struct DList* list, int value, const char* title, const char* house) {
    if(searchDByTitle(list, title) != NULL){
        return;
    }
    struct driver* newNode = (struct driver*)malloc(sizeof(struct driver));
    newNode->value = value;
    strcpy(newNode->title,title);
    strcpy(newNode->house,house);
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}


void Hinsert(struct HList* list, int value, const char* title) {
    if(searchHByTitle(list, title) != NULL){
        return;
    }
    struct house* newNode = (struct house*)malloc(sizeof(struct house));
    newNode->value = value;
    strcpy(newNode->title,title);
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

void Minsert(struct MList* list, int value, const char* title) {
    if(searchMByTitle(list, title) != NULL){
        return;
    }
    struct mani* newNode = (struct mani*)malloc(sizeof(struct mani));
    newNode->value = value;
    strcpy(newNode->title,title);
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}



// Stampa
void printDList(struct DList* list) {
    struct driver* current = list->head;
    while (current != NULL) {
        printf("Value: %d, Title: %s\n", current->value, current->title);
        current = current->next;
    }
}


void printHList(struct HList* list) {
    struct house* current = list->head;
    while (current != NULL) {
        printf("Value: %d, Title: %s\n", current->value, current->title);
        current = current->next;
    }
}

void printMList(struct MList* list) {
    struct mani* current = list->head;
    while (current != NULL) {
        printf("Value: %d, Title: %s\n", current->value, current->title);
        current = current->next;
    }
}


// Sorting
void sortDByValue(struct DList* list) {
    if (list->size < 2) return;

    struct driver* i;
    struct driver* j;
    int temp_value;
    char temp_title[MAX_NAME+1];
    char temp_house[MAX_TEAM+1];

    for (i = list->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->value > j->value) {
                // Scambia value
                temp_value = i->value;
                i->value = j->value;
                j->value = temp_value;

                // Scambia title
                strcpy(temp_title,i->title);
                strcpy(i->title,j->title);
                strcpy(j->title,temp_title);

                // Scambia house
                strcpy(temp_house,i->house);
                strcpy(i->house,j->house);
                strcpy(j->house,temp_house);
            }
        }
    }
}

void sortHByValue(struct HList* list) {
    if (list->size < 2) return;

    struct house* i;
    struct house* j;
    int temp_value;
    char temp_title[MAX_TEAM+1];

    for (i = list->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->value > j->value) {
                // Scambia value
                temp_value = i->value;
                i->value = j->value;
                j->value = temp_value;

                // Scambia title
                strcpy(temp_title,i->title);
                strcpy(i->title,j->title);
                strcpy(j->title,temp_title);
            }
        }
    }
}

void sortMByValue(struct MList* list) {
    if (list->size < 2) return;

    struct mani* i;
    struct mani* j;
    int temp_value;
    char temp_title[MAX_MANIFACTURE+1];

    for (i = list->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->value > j->value) {
                // Scambia value
                temp_value = i->value;
                i->value = j->value;
                j->value = temp_value;

                // Scambia title
                strcpy(temp_title,i->title);
                strcpy(i->title,j->title);
                strcpy(j->title,temp_title);
            }
        }
    }
}

int main(){
    struct DList* drivers = initDList();
    struct HList* houses = inithList();
    struct MList* manifactures = initmList();

    int conta=0;
    char name[MAX_NAME+1];
    char team[MAX_TEAM+1];
    char manifattura[MAX_MANIFACTURE+1];
    char value[20];
    struct driver* d;
    struct house* h;
    struct mani* m;
    int points;


    char buf[1024]; //creazione di un buffer di 1024 caratteri
    char filename[20]; // Inizializza correttamente il puntatore filename
    int races=1;
    while(races<21){

    sprintf(filename, "motogp%d.csv", races);

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Impossibile aprire il file\n");
        return 1;
    }

    
    while (fgets(buf, 1024, fp)) {
        char *campo = strtok(buf, ";"); //divido la riga in campi separati da virgola, o un qualunque altro carattere separatore
        conta=0;
        while(campo) {
            if(conta==0){
                strcpy(name,campo);
            }
            if(conta==2){
                strcpy(team,campo);
            }
            if(conta==3){
				strcpy(manifattura,campo);
			}
            if(conta==4){
                strcpy(value,campo);
                d=searchDByTitle(drivers,name);
                h=searchHByTitle(houses,team);
                m=searchMByTitle(manifactures,manifattura);
                points=atoi(value);
				if(m==NULL){
					
					Minsert(manifactures,points,manifattura);
					m=searchMByTitle(manifactures,manifattura);
				}
				
                if(d==NULL){
                    Dinsert(drivers,points,name,team);
                    d=searchDByTitle(drivers,name);
                }
                
                if(h==NULL){
                    Hinsert(houses,points,team);
                    h=searchHByTitle(houses,team);
                }
                else{
                    d->value+=points;
                    h->value+=points;
                    m->value+=points;
                }
                //printDList(drivers);
                //printHList(houses);
                         
            }
            conta++;
            campo = strtok(NULL, ";"); //continua a dividere la riga in campi separati da virgola, o un qualunque altro carattere separatore
        }
        
    }
	
	printf("after race %d:\n",races);
	
	sortDByValue(drivers);
    sortHByValue(houses);
    sortMByValue(manifactures);
    
    printf("lista piloti:\n");
    printDList(drivers);
    printf("\n");
    printf("lista team:\n");
    printHList(houses);
    printf("\n");
    printf("lista manifatture:\n");
    printMList(manifactures);
    printf("\n");
    printf("-----------------------------");
    
    fclose(fp);
    races++;
}

    
return 0;


}
