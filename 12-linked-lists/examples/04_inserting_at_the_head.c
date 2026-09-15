#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

// Inserting at the head is the cheapest possible insertion: no
// shifting, no walking the list -- just two pointer assignments.
// It returns the new head, because the head has changed.
Node *insertAtHead(Node *head, int value) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("malloc failed\n");
        return head;   // insertion failed; list is unchanged
    }

    newNode->value = value;
    newNode->next = head;   // new node points at the OLD head first...
    return newNode;          // ...then becomes the new head
}

void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;   // save next before freeing!
        free(current);
        current = next;
    }
}

int main(void) {
    Node *head = NULL;   // start from an empty list

    head = insertAtHead(head, 30);
    head = insertAtHead(head, 20);
    head = insertAtHead(head, 10);

    printf("List after three head-inserts: ");
    printList(head);   // expect: 10 -> 20 -> 30 -> NULL

    freeList(head);
    return 0;
}
