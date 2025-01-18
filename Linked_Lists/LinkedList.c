#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct head {
    int size;
    struct city* first;
};

struct city {
    char* name;
    int popolazione;
    int area;
    struct city* next;
};


void order_area(struct head* head) {
    if (head->size == 0 || head->size == 1) {
        return;
    }

    struct city* i;
    struct city* j;
    int temp_popolazione;
    int temp_area;
    char* temp_name;

    for (i = head->first; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->area > j->area) {
                // Scambia popolazione
                temp_popolazione = i->popolazione;
                i->popolazione = j->popolazione;
                j->popolazione = temp_popolazione;

                // Scambia area
                temp_area = i->area;
                i->area = j->area;
                j->area = temp_area;

                // Scambia nome
                temp_name = i->name;
                i->name = j->name;
                j->name = temp_name;
            }
        }
    }
}

void order_population(struct head* head) {
    if (head->size == 0 || head->size == 1) {
        return;
    }

    struct city* i;
    struct city* j;
    int temp_popolazione;
    int temp_area;
    char* temp_name;

    for (i = head->first; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->popolazione > j->popolazione) {
                // Scambia popolazione
                temp_popolazione = i->popolazione;
                i->popolazione = j->popolazione;
                j->popolazione = temp_popolazione;

                // Scambia area
                temp_area = i->area;
                i->area = j->area;
                j->area = temp_area;

                // Scambia nome
                temp_name = i->name;
                i->name = j->name;
                j->name = temp_name;
            }
        }
    }
}


void biggest_city(struct head*head){
    struct city* current = head->first;
    struct city* ptr=head->first;
    while(current->next!=NULL){
        if(ptr->popolazione<current->popolazione)
            ptr=current; 
    }
    if(ptr->popolazione<current->popolazione)
            ptr=current;

    printf("%s / %d / %d\n",ptr->name, ptr->popolazione, ptr->area);
    return;
}

void print_city(struct head* head){
    struct city* current=head->first;
    while(current->next!=NULL){
        printf("%s / %d / %d\n",current->name, current->popolazione, current->area);
        current=current->next;
    }
    printf("%s / %d / %d\n",current->name, current->popolazione, current->area);
}

void remove_city(char* name, struct head* head){
    struct city* current=head->first;

    while(current->next!=NULL){
        if(current->next->name==name){
          	struct city* ptr=current->next;
            current->next=current->next->next;
            free(ptr);
            head->size--;
            return;
        }
        current=current->next;
    }
    return;

}


void add_city(char* name, int popolazione, int area, struct head* head) {
    if (head->size == 0) {
        struct city *new_city = (struct city*)malloc(sizeof(struct city));
        new_city->name = (char*)malloc(sizeof(char)*strlen(name)+1);
        strcpy(new_city->name, name);
        new_city->popolazione = popolazione;
        new_city->area = area;
        new_city->next = NULL;
        head->first = new_city;
        head->size++;
        return;
    }
    struct city* current = head->first;
    while (current->next != NULL) {
        current = current->next;
    }
    struct city *new_city = (struct city*)malloc(sizeof(struct city));
    new_city->name = (char*)malloc(sizeof(char)*strlen(name)+1);
    strcpy(new_city->name, name);
    new_city->popolazione = popolazione;
    new_city->area = area;
    new_city->next = NULL;
    current->next = new_city;
    head->size++;
    return;
}

int random_population() {
    return rand() % 1000 + 1; // Genera un numero casuale tra 1 e 1000
}

char* random_city_name() {
    static char name[10];
    int len = rand() % 5 + 5; // Lunghezza del nome tra 5 e 9 caratteri
    for (int i = 0; i < len; i++) {
        name[i] = 'a' + rand() % 26;
    }
    name[len] = '\0';
    return name;
}

int random_area() {
    return rand() % 500 + 1; // Genera un numero casuale tra 1 e 500
}

int main(int argc, char* argv[]) 
{
    int conta=0;

    struct head* head=(struct head*)malloc(sizeof(struct head));
    head->size=0;
    head->first=NULL;

    srand(time(NULL)); // Inizializza il generatore di numeri casuali

    while(conta++<10){
        char* name = random_city_name(); // Usa la funzione per generare un nome di città casuale
        int popolazione = random_population(); // Usa la funzione per generare una popolazione casuale
        int area = random_area(); // Usa la funzione per generare un'area casuale
        add_city(name, popolazione, area, head);
    }

    
    print_city(head);
    order_area(head);
    printf("\n");
    print_city(head);
    printf("\n");
    order_population(head);
    printf("\n");
    print_city(head);

    return 0;
}
