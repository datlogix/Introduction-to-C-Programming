#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

/*
Exercise 1: isEmpty and peek for a linked-list-based stack.

push() and pop() are already written below -- study them, then write:

    1. int isEmpty(Node *top)
       Returns 1 (true) if the stack is empty, 0 (false) otherwise.

    2. int peek(Node *top, int *value)
       If the stack is NOT empty: stores the top node's value into
       *value and returns 1.
       If the stack IS empty: returns 0 and leaves *value untouched.
       Unlike pop(), peek() must NOT remove or free anything -- it only
       looks at the top and reports back.

main() below already builds a small stack and calls both functions --
do not change main(). Just write the two functions above it.
*/

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

Node* pop(Node *top, int *poppedValue) {
    if (top == NULL) {
        return NULL;
    }
    Node *oldTop = top;
    *poppedValue = top->value;
    top = top->next;
    free(oldTop);
    return top;
}

// TODO: write isEmpty(Node *top) here

// TODO: write peek(Node *top, int *value) here

int main(void) {
    Node *stack = NULL;

    printf("isEmpty on a brand-new stack: %d (expected 1)\n", isEmpty(stack));

    stack = push(stack, 10);
    stack = push(stack, 20);
    stack = push(stack, 30);

    printf("isEmpty after 3 pushes: %d (expected 0)\n", isEmpty(stack));

    int topValue;
    if (peek(stack, &topValue)) {
        printf("peek() sees: %d (expected 30)\n", topValue);
    }
    printf("peek() should not remove anything -- popping 3 more values:\n");

    int value;
    stack = pop(stack, &value);
    printf("popped: %d (expected 30)\n", value);
    stack = pop(stack, &value);
    printf("popped: %d (expected 20)\n", value);
    stack = pop(stack, &value);
    printf("popped: %d (expected 10)\n", value);

    printf("isEmpty after popping everything: %d (expected 1)\n", isEmpty(stack));

    int unused;
    printf("peek() on an empty stack: %d (expected 0)\n", peek(stack, &unused));

    return 0;
}
