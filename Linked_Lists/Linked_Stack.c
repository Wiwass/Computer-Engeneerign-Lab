struct node{
int data;
struct node* next;
};

struct head{
struct node* top;
struct node* tail;
int size;
};


void create_node(int x){
	struct node nodo=(node*)malloc(sizeof(node));
	nodo->data=x;
	nodo->next=NULL;
	return;
}


void crea_stack(){
				struct head head;
				head->top=NULL;
				head->tail=NULL;
				head->size=0;
				return;
}


void add(struct head* head,struct node* new_node){
				if(size==0){
					head->top=new_node;
					new_node->next=NULL;
					head->tail=new_node;
					head->size++;
				}
				else{
					struct node* temp = head->top;
					head->top=new_node;
					new_node->next=temp;
					head->size++;
				}
}


int pop(struct head* head){
	if(size==0)
		return(INT_MIN);
	if(size==1){
		int temp=head->top->data;
		head->top=NULL;
		head->tail=NULL;
		head->size--;
		return temp;
	}
	int temp=head->top->data;
	head->top=head->top->next;
	head->size--;
	return temp;
}


int top(struct head* head){
	if(size==0)
		return INT_MIN;
	
	return head->top->data;
}






