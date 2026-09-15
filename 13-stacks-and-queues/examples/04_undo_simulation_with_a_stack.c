#include <stdio.h>
#include <stdlib.h>

/*
This is the module's hook, with one addition: pop() itself prints what
it's undoing, so the connection between "pop" and "undo" is as direct
as possible. Every text editor's Ctrl+Z is, underneath, a stack exactly
like this one -- the most recently performed action is always the first
one undone.
*/

typedef struct Node {
    const char *action;
    struct Node *next;
} Node;

Node* push(Node *top, const char *action) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("malloc failed -- history unchanged.\n");
        return top;
    }
    newNode->action = action;
    newNode->next = top;
    return newNode;
}

Node* pop(Node *top) {
    if (top == NULL) {
        printf("Nothing left to undo.\n");
        return NULL;
    }
    printf("Undoing: %s\n", top->action);
    Node *oldTop = top;
    top = top->next;
    free(oldTop);
    return top;
}

int main(void) {
    Node *history = NULL;   // empty undo history

    const char *actions[] = {
        "Typed 'Hello'",
        "Typed ', world!'",
        "Deleted a paragraph"
    };
    int numActions = 3;

    for (int i = 0; i < numActions; i++) {
        history = push(history, actions[i]);
        printf("Did: %s\n", actions[i]);
    }

    printf("\nPressing Ctrl+Z three times:\n");
    history = pop(history);
    history = pop(history);
    history = pop(history);

    // A fourth undo -- nothing left, handled gracefully.
    printf("\nPressing Ctrl+Z a fourth time:\n");
    history = pop(history);

    return 0;
}
