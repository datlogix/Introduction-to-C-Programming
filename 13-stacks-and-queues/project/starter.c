#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: define your stack node here.
// typedef struct Node {
//     char word[50];
//     struct Node *next;
// } Node;

// TODO: write push(Node *top, const char *word) here.
// Remember to malloc a new node, copy the word in with strcpy, point it
// at the old top, and return the new top.

// TODO: write pop(Node *top, char *poppedWord) here.
// Check for an empty stack (top == NULL) before touching anything.

// TODO: write a function to print the current document, oldest word
// first. See project/README.md's "Ideas if you're stuck" for the
// recursive approach.

int main(void) {
    // TODO: Node *document = NULL;

    printf("Type words one at a time. Type 'undo' to undo the last word,\n");
    printf("or 'quit' to stop.\n\n");

    char token[50];
    while (scanf("%s", token) == 1) {
        if (strcmp(token, "quit") == 0) {
            break;
        }

        if (strcmp(token, "undo") == 0) {
            // TODO: pop the stack (checking for empty first), print
            // what was undone, then print the document.
        } else {
            // TODO: push `token` onto the stack, print a confirmation,
            // then print the document.
        }
    }

    // TODO: free every remaining node before exiting.

    return 0;
}
