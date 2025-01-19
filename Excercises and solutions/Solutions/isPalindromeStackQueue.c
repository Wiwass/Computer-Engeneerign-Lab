// isPalindromeStackQueue.c

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for linked list
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// Stack structure
typedef struct Stack {
    Node* top;
} Stack;

// Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Stack operations
int push(Stack* stack, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL)
    {
        newNode->data = data;
        newNode->next = stack->top;
        stack->top = newNode;
        return(0);
    }
    else
        return(-1);
}

char pop(Stack* stack) {
    if (stack->top == NULL) return '\0';
    Node* temp = stack->top;
    char data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

// Queue operations
int enqueue(Queue* queue, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL)
    {
        newNode->data = data;
        newNode->next = NULL;
        if (queue->rear == NULL) {
            queue->front = queue->rear = newNode;
        }
        else {
            queue->rear->next = newNode;
            queue->rear = newNode;
        }
        return(0);
    }
    else
        return(-1);
}

char dequeue(Queue* queue) {
    if (queue->front == NULL) return '\0';
    Node* temp = queue->front;
    char data = temp->data;
    queue->front = temp->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

// Function to check if a string is a palindrome
int isPalindrome(char* str) {
    Stack stack = { NULL };
    Queue queue = { NULL, NULL };

    // Push and enqueue each character
    for (int i = 0; str[i] != '\0'; i++) {
        if (push(&stack, str[i]) != 0)
        {
            printf("perror inserting character in the stack");
            return(0);
        }
        if (enqueue(&queue, str[i]) != 0)
        {
            printf("perror inserting character in the queue");
            return(0);
        }
    }

    // Compare stack and queue elements
    while (stack.top != NULL && queue.front != NULL) {
        if (pop(&stack) != dequeue(&queue)) {
            return(0); // Not a palindrome
        }
    }
    return(1); // Palindrome
}

int main() {
    char str[100];
    printf("Enter a string: ");
    unsigned int i = 0;
    do
    {
        if (scanf("%c", &str[i]) != 1)
        {
            perror("Error reading char value");
            return(1);
        }
        if (str[i] == '\n')
        {
            str[i] = '\0';
            break;
        }
        else
        {
            i++;
        }
    } while (i < 99);

    if (isPalindrome(str)) {
        printf("Palindrome");
    }
    else {
        printf("Not a Palindrome");
    }

    return(0);
}