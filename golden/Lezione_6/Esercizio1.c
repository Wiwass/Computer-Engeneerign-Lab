#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 20
#define MAX_TEAM 40
#define MAX_ROW 80
#define MAX_TOURNAMENT 22

struct driver{
		char name[MAX_NAME+1];
		char team[MAX_TEAM+1];
		int points;
		struct driver* next;
	
};
struct house{
	char name[MAX_TEAM+1];
	int points;
	struct house* next;

};

struct driver* createPilotNode(char* pilotName, char* team, int score){ //creazione di un nuovo pilota
	struct driver* new_pilot = (struct driver*)malloc(sizeof(struct driver));
	new_pilot->name=strcpy(pilotName);
	new_pilot->team=strcpy(team);
	new_pilot->points=score;
	
	return new_pilot;
	}
	
struct house createTeamNode(char* team, int score){ // creazione di un nuovo team
	driver new_team* = (house*)malloc(sizeof(house));
	new_pilot->name=team;
	new_pilot->points=score;
	}
	
void addPointsToPilot(struct driver* pilot,int score){
	pilot->points=pilot->points+score;
	return;
	}
void addPointsToHouse(struct house* team,int score){
	team->points=team->points+score;
	}
	
	
	
// prima linked list che gestisce i piloti

struct drivers_list{
	struct driver* first;
	int size;
	};

struct drivers_list* creaDrivers_list(){
	struct drivers_list* new_list = (struct drivers_list*)malloc(sizeof(struct drivers_list));
	new_list->first=NULL;
	new_list->size=0;
	}
	
void add_driver(struct drivers_list* list,struct driver* new_driver){
	struct driver* current=list->first;
	if(list->size==0){
		list->first=new_driver;
		list->size++;
		return;
		}
		
	while(current->next!=NULL){current=current->next;}
	current->next=new_driver;
	list->size++;
	return;
	}
	
void update_driver(struct drivers_list* list, char* name, int score){
	struct driver* current=list->first;
	while(current->next!=NULL){
		if(current->name==name){addPointsToPilot(current,score); return;}
		}
	return;
	}
	
// seconda linked list che gestisce le casate

struct house_list{
	struct house* first;
	int size;
	};

struct house_list* creaHouse_list(){
	struct house_list* new_list = (struct house_list*)malloc(sizeof(struct house_list));
	new_list->first=NULL;
	new_list->size=0;
	
	return new_list;
	}
	
void add_house(struct house_list* list,struct house* new_house){
	struct house* current=list->first;
	if(list->size==0){
		list->first=new_house;
		list->size++;
		return;
		}
		
	while(current->next!=NULL){
		if(current->name==new_house->name){
			update_house(list,new_house->name,new_house->score);
			return;
		}
		current=current->next;
		}
	
	if(current->name==new_house->name){
			update_house(list,new_house->name,new_house->score);
			return;
		}
		
	current->next=new_house;
	list->size++;
	return;
	}
	
void update_house(struct house_list* list, char* name, int score){
	struct house* current=list->first;
	while(current->next!=NULL){
		if(current->name==name){addPointsToHouse(current,score); return;}
		}
	return;
	}
	
// separare usando terminatori stringhe

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ";");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

// sistema di input

int main(void)
{
	char temp_name[MAX_NAME+1];
	char temp_house_name[MAX_TEAM+1];
	int score;
	
	struct drivers_list* dlist = creaDrivers_list();
	struct house_list* hlist = creaHouse_list();
	
    FILE* stream = fopen("input", "r");

    char line[1024];
    while (fgets(line, 1024, stream))
    {	
		char* tmp = strdup(line);
		temp_name=getfield(tmp, 1);
		temp_house=getfield(tmp, 2);
		score=(int)getfield(tmp, 3);
		add_driver(dlist,createPilotNode(temp_name,temp_house_name,score));
		add_house(hlist,createTeamNode(temp_house,score));  
        free(tmp);
    }
    for(int i=0;i<22;i++)
    {
	char input;
	FILE* stream = fopen(input,"r");
		char* tmp = strdup(line);
		temp_name=getfield(tmp, 1);
		temp_house=getfield(tmp, 2);
		score=(int)getfield(tmp, 3);
		add_driver(dlist,createPilotNode(temp_name,temp_house_name,score));
		add_house(hlist,createTeamNode(temp_house,score));  
        free(tmp);
		}
    return 0;
}
