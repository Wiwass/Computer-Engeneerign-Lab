#include <stdio.h>
#include <stdlib.h>

struct head{
	int size;
	struct node* front;
	struct node* tail;
};

struct head2{
	int size;
	struct node* top;
	struct node* tail;
};

struct node{
	char data;
	struct node* next;
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

	
	
//	--------------------------------------------------------------------
	
	


struct head2* create_stack(){
	struct head2* head = (struct head2*)malloc(sizeof(struct head2));
	head->top=NULL;
	head->tail=NULL;
	head->size=0;
	return head; 
	
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
		struct head* head = create_queue();
		enqueue(head,create_node('a'));
		enqueue(head,create_node('b'));
		enqueue(head,create_node('b'));
		enqueue(head,create_node('a'));
		
		
		struct head2* head2 = create_stack();
		add(head2,create_node('a'));
		add(head2,create_node('b'));
		add(head2,create_node('b'));
		add(head2,create_node('a'));
		
		for(int i=0;i<4;i++){
			if(dequeue(head)!=pop(head2)){
				printf("NON Palindromo"); 
				return 0;
				}
			}
		
		printf("Palindromo \n");
	
}
