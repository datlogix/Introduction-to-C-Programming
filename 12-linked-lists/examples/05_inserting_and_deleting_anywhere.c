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

Node *insertAtHead(Node *head, int value) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return head;
    }
    newNode->value = value;
    newNode->next = head;
    return newNode;
}

// Insert `value` immediately after the first node holding `afterValue`.
// To insert in the middle, you have to walk to the node just BEFORE
// where the new node belongs, then relink pointers around it.
Node *insertAfter(Node *head, int afterValue, int value) {
    Node *current = head;
    while (current != NULL && current->value != afterValue) {
        current = current->next;
    }

    if (current == NULL) {
        printf("insertAfter: %d not found, list unchanged\n", afterValue);
        return head;
    }

    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return head;
    }
    newNode->value = value;
    newNode->next = current->next;   // new node points to what used to be next
    current->next = newNode;          // the node before it now points to new node
    return head;   // head didn't change -- we inserted in the middle
}

// Delete the first node holding `value`. Need the pointer to the
// PREVIOUS node so we can relink around the node being removed.
Node *deleteValue(Node *head, int value) {
    if (head == NULL) {
        return head;   // empty list, nothing to do
    }

    // Special case: deleting the head itself -- head must change.
    if (head->value == value) {
        Node *doomed = head;
        head = head->next;
        free(doomed);
        return head;
    }

    Node *previous = head;
    Node *current = head->next;
    while (current != NULL && current->value != value) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("deleteValue: %d not found, list unchanged\n", value);
        return head;
    }

    previous->next = current->next;   // skip over the node being removed
    free(current);
    return head;
}

void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *head = NULL;
    head = insertAtHead(head, 30);
    head = insertAtHead(head, 20);
    head = insertAtHead(head, 10);
    printf("Start:            ");
    printList(head);   // 10 -> 20 -> 30 -> NULL

    head = insertAfter(head, 20, 25);
    printf("After insert 25:  ");
    printList(head);   // 10 -> 20 -> 25 -> 30 -> NULL

    head = deleteValue(head, 10);
    printf("After delete 10:  ");
    printList(head);   // 20 -> 25 -> 30 -> NULL (head changed!)

    head = deleteValue(head, 25);
    printf("After delete 25:  ");
    printList(head);   // 20 -> 30 -> NULL

    freeList(head);
    return 0;
}
