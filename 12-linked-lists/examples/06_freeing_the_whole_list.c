#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *insertAtHead(Node *head, int value) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return head;
    }
    newNode->value = value;
    newNode->next = head;
    return newNode;
}

// THE WRONG WAY (do not do this -- shown only in a comment, never run):
//
//     Node *current = head;
//     while (current != NULL) {
//         free(current);
//         current = current->next;   // BUG: current was just freed!
//     }                              // reading current->next here reads
//                                     // freed memory -- undefined behavior,
//                                     // and often a crash.
//
// THE FIX: save the next pointer BEFORE freeing the current node, so
// you never have to read through freed memory to keep walking.
void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;   // save it first
        free(current);                 // now it's safe to free current
        current = next;                // advance using the saved pointer
    }
}

int main(void) {
    Node *head = NULL;
    head = insertAtHead(head, 3);
    head = insertAtHead(head, 2);
    head = insertAtHead(head, 1);

    printf("Freeing a 3-node list node by node...\n");
    freeList(head);
    printf("Done -- every node returned to the system, nothing leaked.\n");

    // Danger: if you ever do "head = someNewNode;" without freeing the
    // list head used to point to first, every node in the old list
    // becomes unreachable -- there's no other pointer left anywhere in
    // the program that remembers where they were. That memory is gone
    // for good until the program exits. Always free (or otherwise keep
    // a handle on) a list before overwriting its head pointer.

    return 0;
}
