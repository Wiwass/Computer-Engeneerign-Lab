// queueLetters.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#define _CRT_SECURE_NO_WARNINGS

#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 

// A structure to represent a node 
struct qNode {
	char data;
	struct qNode* next;
};

struct queue {
	struct qNode* front, * rear;
};

int isEmpty(struct qNode* head)
{
	return(!head);
}

// A utility function to create a new LL node.
struct qNode* createNode(char value)
{
	struct qNode* tmp = (struct qNode*)malloc(sizeof(struct qNode));
	if (tmp == NULL) {
		printf("Memory allocation failed\n");
	}
	else {
		tmp->data = value;
		tmp->next = NULL;
	}
	return(tmp);
}

// A utility function to create an empty queue
struct queue* createQueue()
{
	struct queue* q = (struct queue*)malloc(sizeof(struct queue));
	if (q != NULL)
		q->front = q->rear = NULL;
	return(q);
}

// The function to add a data value to q
int enQueue(struct queue* q, char value)
{
	// Create a new LL node
	struct qNode* tmp = createNode(value);
	if (tmp != NULL)
	{
		// If queue is empty, then new node is front and rear both
		if (q->rear == NULL) {
			q->front = q->rear = tmp;
			return(0);
		}
		// Add the new node at the end of queue and change rear
		q->rear->next = tmp;
		q->rear = tmp;
		return(0);
	}
	else
	{
		return(-1);
	}
}

// Function to dequeue a key from given queue q
struct qNode* deQueue(struct queue* q)
{
	// If queue is empty, return NULL.
	if (q->front == NULL)
		return(NULL);
	// Store previous front and move front one node ahead
	struct qNode* tmp = q->front;
	q->front = q->front->next;
	// If front becomes NULL, then change rear also as NULL
	if (q->front == NULL)
		q->rear = NULL;
	return(tmp);
}


int main(int argc, char* argv[]) {
	char val;
	struct queue* q = createQueue();

	if (argc != 2)
	{
		printf("Bad arguments: usage %s filename_to_be_read\n", argv[0]);
		return(1);
	}
	FILE* fr = fopen(argv[1], "r");
	if (fr == NULL)
	{
		perror("error opening file passed as argument\n");
		return(2);
	}

	do
	{
		if (fscanf(fr, "%c", &val) != 1)
		{
			perror("Error reading char value");
			return(3);
		}
		if (val == '\n')
		{
			break;
		}
		else //if (val != ' ')
		{
			struct qNode* tmp = createNode(val);
			if (tmp != NULL)
			{
				if (enQueue(q, val) != 0)
				{
					perror("Error enque char value");
					return(4);
				}
			}
		}
		//else
			//continue;
	} while (val != '\n');
	fclose(fr);
	printf("Printing letters in the queue:\t");
	struct qNode* tmp = NULL;
	do
	{
		tmp = deQueue(q);
		if (tmp != NULL)
		{
			printf("%c", tmp->data);
			free(tmp);
		}
	} while (tmp != NULL);

	return(0);
}