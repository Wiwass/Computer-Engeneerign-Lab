#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


void order(struct head*head,int type){

    if(head->size==0 || head->size==1){
        return;
    }

  //  if(type==0){
  //      #define parameter nome
  //  }
  //  else if(type==1){
  //      #define parameter area
  //  }


    int conta=0;
    struct city* current = head->first;
    struct city* min = head->first;
    struct city* base = head->first;
    struct city* prev = head->first;
    struct city* min_prev = head->first;

    while(current->next!=NULL){  //caso0
        if(current->popolazione<min->popolazione){
            min=current;
            min_prev=prev;
        }
        current=current->next;
    }
        current=base->next;
        base->next=min;
        min_prev->next=min->next;
        min->next=current;
        conta++;

        base=base->next;

    


    while(conta < head->size-1){ 
        while(current->next!=NULL){
            if(current->popolazione<min->popolazione){
                min=current;
                min_prev=prev;
            }
            current=current->next;
        }
        if(current->popolazione<min->popolazione){
            min=current;
            min_prev=prev;
        }
        current=base->next;  //scambio dei due valori
        base->next=min;
        min_prev->next=min->next;
        min->next=current;
        conta++;
    
        base=base->next;  //ricollocazione puntatori
        current=base->next;
        prev=base;
        min=base->next;
        min_prev=base;
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

int main(int argc, char* argv[]) 
{
    int conta=0;

    struct head* head=(struct head*)malloc(sizeof(struct head));
    head->size=0;
    head->first=NULL;

    while(conta++<10){
        char name[]="city";
        int popolazione=conta;
        int area=conta/2;
        add_city(name,popolazione,area,head);
    }

    print_city(head);
    order(head,0);
    print_city(head);

    return 0;
}
