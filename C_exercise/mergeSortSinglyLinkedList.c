// mergeSortSLL.cpp
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void splitList(struct Node* source, struct Node** frontRef, struct Node** backRef) {
    struct Node* slow;
    struct Node* fast;
    slow = source;
    fast = source->next;
    // Move fast two nodes and slow one node
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // Split the list into two halves
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}


// Merge two sorted linked lists into a single sorted list.
struct Node* sortedMerge(struct Node* a, struct Node* b) {
    struct Node* result = NULL;

    // Base cases
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    // Pick either a or b and recurse
    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }

    return result;
}

void mergeSort(struct Node** headRef) {
    struct Node* head = *headRef;
    struct Node* a;
    struct Node* b;
    // Base case: if the list is empty or has a single element
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    // Split the list into two halves
    splitList(head, &a, &b);

    // Recursively sort the two halves
    mergeSort(&a);
    mergeSort(&b);

    // Merge the sorted halves
    *headRef = sortedMerge(a, b);
}


// Create a new node:
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
// Print the linked list :
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// main Example Program
int main() {
    struct Node* head = createNode(4);
    head->next = createNode(2);
    head->next->next = createNode(5);
    head->next->next->next = createNode(3);
    head->next->next->next->next = createNode(1);

    printf("Original List:\n");
    printList(head);

    mergeSort(&head);

    printf("Sorted List:\n");
    printList(head);

    return 0;
}
