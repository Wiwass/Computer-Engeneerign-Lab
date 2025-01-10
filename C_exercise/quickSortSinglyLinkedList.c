// quickSortSLL.c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Utility function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Utility function to print the linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Function to partition the list and return the pivot node
struct Node* partition(struct Node* head, struct Node* end, struct Node** newHead, struct Node** newEnd) {
    struct Node* pivot = end;
    struct Node* prev = NULL, * cur = head, * tail = pivot;

    // Nodes smaller than the pivot will be moved to the front
    while (cur != pivot) {
        if (cur->data < pivot->data) {
            // Move node to the new head
            if ((*newHead) == NULL) {
                (*newHead) = cur;
            }
            prev = cur;
            cur = cur->next;
        }
        else {
            // Move node to the end of the list
            if (prev) {
                prev->next = cur->next;
            }
            struct Node* temp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    // If the new head hasn't been updated, it is the pivot
    if ((*newHead) == NULL) {
        (*newHead) = pivot;
    }

    // Update the new end to the current tail
    (*newEnd) = tail;

    return pivot;
}

// The main quick sort function
struct Node* quickSortRecur(struct Node* head, struct Node* end) {
    // Base case: zero or one node
    if (!head || head == end) {
        return head;
    }

    struct Node* newHead = NULL, * newEnd = NULL;

    // Partition the list and get the pivot node
    struct Node* pivot = partition(head, end, &newHead, &newEnd);

    // If the pivot is the smallest element, no need to recur for the left side
    if (newHead != pivot) {
        // Recur for the left of the pivot
        struct Node* temp = newHead;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = NULL;

        // Sort the left part and attach to the pivot
        newHead = quickSortRecur(newHead, temp);

        // Find the tail of the sorted left side and link it to the pivot
        temp = newHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = pivot;
    }

    // Recur for the right of the pivot
    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

// Utility function to find the tail of the linked list
struct Node* getTail(struct Node* head) {
    while (head != NULL && head->next != NULL) {
        head = head->next;
    }
    return head;
}

// Function to sort the linked list using quick sort
void quickSort(struct Node** headRef) {
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
}

// Example usage
int main() {
    struct Node* head = createNode(80);
    head->next = createNode(30);
    head->next->next = createNode(20);
    head->next->next->next = createNode(50);
    head->next->next->next->next = createNode(10);
    head->next->next->next->next->next = createNode(40);

    printf("Original list:\n");
    printList(head);

    quickSort(&head);

    printf("Sorted list:\n");
    printList(head);

    return 0;
}
