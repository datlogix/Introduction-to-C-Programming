#include <stdio.h>

/*
This program compiles cleanly and even runs for a moment before it
crashes -- that's exactly the kind of bug this module teaches you to
hunt down instead of guessing at.

    gcc -g 01_segfault_and_gdb_backtrace.c -o segfault_demo
    ./segfault_demo

Run it once as-is: you'll see "Segmentation fault" and nothing else --
no line number, no variable values, nothing to go on. Then read the
README's gdb walkthrough for this exact file, which finds the crashing
line in seconds.
*/

void printScore(int *score) {
    printf("Score: %d\n", *score); // crashes here -- score is NULL
}

int main(void) {
    int *currentScore = NULL; // supposed to point at a real score, but nothing ever set it

    printScore(currentScore);

    printf("This line never runs -- the crash above stops the program first.\n");
    return 0;
}
