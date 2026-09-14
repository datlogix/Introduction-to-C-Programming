#include <stdio.h>

// This is a single-line comment. The compiler ignores this entire line.

/* This is a multi-line comment.
   It can span as many lines as you like,
   and the compiler ignores all of it too. */

int main(void) {
    // Comments explain WHY, not WHAT. This one is a bad example on purpose:
    printf("Hello!\n"); // prints "Hello!" -- useless, the code already says this

    // A good comment explains a non-obvious reason, e.g.:
    // We print a trailing space here because the grading script expects
    // "Score: " with a space before the number gets appended later.
    printf("Score: ");
    printf("100\n");

    return 0;
}
