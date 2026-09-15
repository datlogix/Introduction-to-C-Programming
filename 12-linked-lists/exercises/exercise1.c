#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

/*
Exercise 1: Two small functions over a linked list.

Write two separate functions and call both from main():

    1. int countNodes(Node *head)
       Returns how many nodes are in the list. An empty list (head is
       NULL) has 0 nodes.
       Hint: walk the list with a "current" pointer, incrementing a
       counter each time you move to current->next.

    2. int contains(Node *head, int value)
       Returns 1 if any node in the list holds `value`, or 0 if not
       (including when the list is empty).
       Hint: same walking pattern as countNodes, but you're checking
       current->value against `value` instead of counting.

main() below already builds a test list and calls both functions --
do not change main(). Just write the functions above it.
*/

// TODO: write countNodes(Node *head) here

// TODO: write contains(Node *head, int value) here

int main(void) {
    // Build a small test list: 5 -> 10 -> 15 -> 20 -> NULL
    Node *n4 = malloc(sizeof(Node));
    Node *n3 = malloc(sizeof(Node));
    Node *n2 = malloc(sizeof(Node));
    Node *n1 = malloc(sizeof(Node));
    if (n1 == NULL || n2 == NULL || n3 == NULL || n4 == NULL) {
        printf("malloc failed\n");
        return 1;
    }

    n1->value = 5;  n1->next = n2;
    n2->value = 10; n2->next = n3;
    n3->value = 15; n3->next = n4;
    n4->value = 20; n4->next = NULL;
    Node *head = n1;

    printf("countNodes(head) = %d (expected 4)\n", countNodes(head));
    printf("contains(head, 15) = %d (expected 1)\n", contains(head, 15));
    printf("contains(head, 99) = %d (expected 0)\n", contains(head, 99));

    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    return 0;
}
