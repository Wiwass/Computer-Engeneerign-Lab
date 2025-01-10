// stackLetters.c : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 

// A structure to represent a stack 
struct StackNode {
    char data;
    struct StackNode* next;
};

int isEmpty(struct StackNode* head)
{
    return(!head);
}

struct StackNode* createNode(char value)
{
	struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
	if (newNode == NULL) {
		printf("Memory allocation failed\n");
	}
	else {
		newNode->data = value;
		newNode->next = NULL;
	}
	return(newNode);
}

void push(struct StackNode** head, struct StackNode* newNode)
{
    newNode->next = *head;
    *head = newNode;
    printf("%c pushed to stack\n", newNode->data);
}

char pop(struct StackNode** head)
{
    if (isEmpty(*head))
		return('\0');
    struct StackNode* tmp = *head;
    *head = (*head)->next;
    char popped = tmp->data;
    free(tmp);

    return(popped);
}

char top(struct StackNode* head)
{
    if (isEmpty(head))
		return('\0');
	return(head->data);
}

void tail_insert(struct StackNode** ptr, struct StackNode* newNode)
{
	struct StackNode* tmp;
	tmp = *ptr;
	if (tmp == NULL)
	{
		*ptr = newNode;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newNode;
	}
}

int main(int argc, char* argv[]) {
	char val;
	struct StackNode* myList = NULL;

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
			struct StackNode* tmp = createNode(val);
			if (tmp != NULL)
			{
				//tail_insert(&myList, tmp);
				push(&myList, tmp);
			}
		}
		//else
			//continue;
	} while (val != '\n');
	fclose(fr);
	printf("Printing letters in the stack:\t");
	do
	{
		val = pop(&myList);
		if (val != '\0')
		{
			printf("%c", val);
		}
	} while (val != '\0');
}
