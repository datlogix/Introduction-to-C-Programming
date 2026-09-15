#include <stdio.h>

/*
The linked-list stack in 01 can grow forever, one malloc() per push --
unlimited capacity, at the cost of a little memory and time overhead per
node. If you know in advance you'll never need more than, say, 100
items, a plain array is a simpler alternative: no malloc, no free, no
pointers to chase -- just an array and an integer tracking the index of
the top element.

The tradeoff is exactly the mirror image of the linked-list version:
simpler code, but a FIXED maximum size decided at compile time. Push
past that limit and you have to explicitly refuse (a "stack overflow"
check), instead of the linked-list version just mallocing another node.
*/

#define MAX_SIZE 5

int main(void) {
    int stack[MAX_SIZE];
    int top = -1;   // -1 means "empty" -- no valid index yet

    // --- push ---
    for (int i = 1; i <= 3; i++) {
        int value = i * 10;
        if (top == MAX_SIZE - 1) {
            printf("Stack is full -- cannot push %d.\n", value);
            continue;
        }
        top++;
        stack[top] = value;
        printf("pushed: %d\n", value);
    }

    // --- pop everything ---
    printf("\nPopping everything -- still LIFO order:\n");
    while (top != -1) {
        int value = stack[top];
        top--;
        printf("popped: %d\n", value);
    }

    // --- pop from empty ---
    if (top == -1) {
        printf("\nStack is empty -- cannot pop.\n");
    }

    return 0;
}
