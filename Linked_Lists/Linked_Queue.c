#include <stdio.h>

struct head{
	int size;
    struct node* front;
    struct node* tail;
};
struct node{
	int data;
	struct node* next;
};

struct head* queue(){
    struct head* head;
    head->front=NULL;
    head->tail=NULL;
    return head;
}

void enqueue(struct head* head,int x){
    if(head->size==0){
        struct node* new_node;
        new_node->data=x;
        new_node->next=head->tail;
        head->tail=new_node;
        head->front=new_node;
        head->size++;
        return;
    }
    struct node* new_node;
    new_node->data=x;
    new_node->next=head->tail;
    head->tail=new_node;
    head->size++;
    return;
}

int dequeue(struct head* head){
    if(head->size==0)
    	return INT_MIN;
	if(head->size==1){
        struct node* temp;
        temp=head->tail;
        head->tail=NULL;
        head->front=NULL;
        int out=temp->data;
        free(temp);
        head->size--;
        return out;
        
    }
	struct node* temp;
    temp=head->tail;
    head->front=head->front->next;
    int out=temp->data;
    head->size--;
    free(temp);
    return out;
}

int next_on(struct head* head){
    if(head->size==0)
    	return INT_MIN;
    return head->front->data;
    
}