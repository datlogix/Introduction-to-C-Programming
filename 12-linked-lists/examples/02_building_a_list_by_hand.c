#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

int main(void) {
    // Build a 3-node list completely by hand: allocate each node
    // separately, then wire them together with -> assignments.
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

    // Link them: node1 -> node2 -> node3 -> NULL
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;   // node3 is the last node -- nothing after it

    // head is the ONLY thing that remembers where the list starts.
    Node *head = node1;

    printf("head->value = %d\n", head->value);
    printf("head->next->value = %d\n", head->next->value);
    printf("head->next->next->value = %d\n", head->next->next->value);
    printf("head->next->next->next = %p (should be NULL)\n",
           (void *)head->next->next->next);

    free(node1);
    free(node2);
    free(node3);
    return 0;
}
