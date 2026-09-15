#include <stdio.h>
#include <stdlib.h>

/*
A stack, built on a linked list. This is exactly Module 12's
insert-at-head pattern, wearing different names: pushing a value onto a
stack IS inserting a new node at the head. Popping is removing the head
node and handing back its value.

The stack only ever touches ONE end of the list -- the head, which we
call the "top" here -- so, just like insert-at-head, push and pop don't
need to walk the list at all. Both are O(1).
*/

typedef struct Node {
    int value;
    struct Node *next;
} Node;

// Push: insert a new node at the top (head) of the stack. Returns the
// new top, exactly like Module 12's insertAtHead returned the new head.
Node* push(Node *top, int value) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("malloc failed -- stack unchanged.\n");
        return top;
    }
    newNode->value = value;
    newNode->next = top;
    return newNode;
}

// Pop: remove the top node, hand its value back through *poppedValue,
// free the node, and return the new top. ALWAYS check for an empty
// stack (top == NULL) before popping -- there is nothing to remove.
Node* pop(Node *top, int *poppedValue) {
    if (top == NULL) {
        printf("Stack is empty -- cannot pop.\n");
        return NULL;
    }
    Node *oldTop = top;
    *poppedValue = top->value;
    top = top->next;
    free(oldTop);
    return top;
}

int main(void) {
    Node *stack = NULL;   // an empty stack is just a NULL top pointer

    printf("Pushing 10, 20, 30 (in that order)...\n");
    stack = push(stack, 10);
    stack = push(stack, 20);
    stack = push(stack, 30);

    printf("\nPopping everything -- watch the LIFO order:\n");
    int value;
    stack = pop(stack, &value);
    printf("popped: %d\n", value);
    stack = pop(stack, &value);
    printf("popped: %d\n", value);
    stack = pop(stack, &value);
    printf("popped: %d\n", value);

    // The stack is empty now (stack == NULL). Popping again is safe --
    // it's caught by the empty check instead of crashing.
    printf("\nPopping an empty stack:\n");
    stack = pop(stack, &value);

    return 0;
}
