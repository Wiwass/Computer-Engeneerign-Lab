#include <stdio.h>
#include <stdlib.h>



struct head2{
	int size;
	struct node* top;
	struct node* tail;
};

struct node{
	char data;
	struct node* next;
};


struct head2* create_stack(){
	struct head2* head = (struct head2*)malloc(sizeof(struct head2));
	head->top=NULL;
	head->tail=NULL;
	head->size=0;
	return head; 
	
	}

struct node* create_node(char x){
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data=x;
	new_node->next=NULL;
	return new_node;
	}
	
char pop(struct head2* head){
	if(head->size==0)
		return '\0';
	if(head->size==1){
		char temp=head->top->data;
		head->top=NULL;
		head->tail=NULL;
		head->size--;
		return temp;
	}
	
	char temp=head->top->data;
	head->top=head->top->next;
	head->size--;
	return temp;	
}

void add(struct head2* head,struct node* new_node){
	if(head->size==0){
		head->top=new_node;
		new_node->next=NULL;
		head->tail=new_node;
		head->size++;
		}
	else{
		struct node* temp= head->top;
		head->top=new_node;
		new_node->next=temp;
		head->size++;	
		}
	return;
	}
	
int main(){
		struct head2* head = create_stack();
		add(head,create_node('a'));
		add(head,create_node('b'));
		add(head,create_node('c'));
		add(head,create_node('d'));
		
		printf("%c \n",pop(head));
		printf("%c \n",pop(head));
		printf("%c \n",pop(head));
		printf("%c \n",pop(head));
		
		
	
}
