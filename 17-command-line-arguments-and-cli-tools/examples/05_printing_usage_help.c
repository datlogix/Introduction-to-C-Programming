#include <stdio.h>
#include <stdlib.h>

/*
Run this with exactly two numbers, and then with the wrong number of
arguments to see the usage message:

    ./printing_usage_help 3 5
    ./printing_usage_help
    ./printing_usage_help 3
*/

int main(int argc, char *argv[]) {
    // A usage message is the CLI equivalent of a helpful compiler
    // error: it tells the user exactly how the program expects to be
    // called instead of just crashing or silently doing nothing.
    if (argc != 3) {
        printf("Usage: %s <number1> <number2>\n", argv[0]);
        printf("Adds two whole numbers together.\n");
        return 1;
    }

    // atoi() converts a string of digits to an int, but quietly returns
    // 0 for text that isn't a valid number at all -- it can't tell you
    // "that wasn't a number" versus "that number really was 0." For
    // real error-checking, strtol() is the more robust tool, though its
    // full error-handling API is more than we need here.
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    printf("%d + %d = %d\n", a, b, a + b);
    return 0;
}
