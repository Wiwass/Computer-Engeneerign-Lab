#include <stdio.h>
#include <stdlib.h>

struct node{
	char data;
	struct node* next;
};

struct head{
	int size;
	struct node* front;
	struct node* tail;
};

struct head* create_queue(){
	struct head* head = (struct head*)malloc(sizeof(struct head));
	head->front=NULL;
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
	
void enqueue(struct head* head,struct node* new_node){
	if(head->size==0){
		head->tail=new_node;
		head->front=new_node;
		head->size++;
		}
	head->tail->next=new_node;
	head->tail=new_node;
	head->size++;
	return;
	}
char dequeue(struct head* head){
	if(head->size==0)
		return '\0';
		
	struct node* temp = head->front;
	char out=temp->data;
	head->front=head->front->next;
	free(temp);
	head->size--;
	return out;
	}

int main(){
		struct head* head = create_queue();
		enqueue(head,create_node('a'));
		enqueue(head,create_node('b'));
		enqueue(head,create_node('c'));
		enqueue(head,create_node('d'));
		printf("%c \n",dequeue(head));
		printf("%c \n",dequeue(head));
		printf("%c \n",dequeue(head));
		printf("%c \n",dequeue(head));
		
		
		
	
}
