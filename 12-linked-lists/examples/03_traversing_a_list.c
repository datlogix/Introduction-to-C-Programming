#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

int main(void) {
    Node *node1 = malloc(sizeof(Node));
    Node *node2 = malloc(sizeof(Node));
    Node *node3 = malloc(sizeof(Node));
    if (node1 == NULL || node2 == NULL || node3 == NULL) {
        printf("malloc failed\n");
        return 1;
    }

    node1->value = 10;
    node2->value = 20;
    node3->value = 30;
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;

    Node *head = node1;

    // Traversal: walk the list with a separate pointer, "current",
    // so we never lose track of head. Stop when current becomes NULL
    // -- that's how we know we've walked off the end of the list.
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");

    free(node1);
    free(node2);
    free(node3);
    return 0;
}
