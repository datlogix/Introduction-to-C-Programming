#include <stdio.h>
#include <stdlib.h>

/*
The basic malloc/free pattern: ask for exactly the memory you need, use
it, then give it back. This is the same idea as the module hook, stripped
down to the essentials.
*/

int main(void) {
    int count;
    printf("How many numbers do you want to store? ");
    scanf("%d", &count);

    // malloc(size) asks the heap for `size` bytes and returns a pointer
    // to the start of that block -- or NULL if the request couldn't be
    // satisfied. `sizeof(int) * count` is the idiomatic way to size a
    // request: "enough room for `count` ints," however big an int is on
    // this machine.
    int *numbers = malloc(sizeof(int) * count);

    // ALWAYS check the result before using it. Skipping this check and
    // then writing through a NULL pointer crashes your program.
    if (numbers == NULL) {
        printf("malloc failed -- could not allocate memory for %d numbers.\n", count);
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &numbers[i]);
    }

    printf("You entered:");
    for (int i = 0; i < count; i++) {
        printf(" %d", numbers[i]);
    }
    printf("\n");

    // Every malloc needs exactly one matching free. This block came from
    // one malloc call, so it gets exactly one free call.
    free(numbers);
    numbers = NULL;

    return 0;
}
