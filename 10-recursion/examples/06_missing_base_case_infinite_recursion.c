#include <stdio.h>

/*
This file is about the single most common recursion bug: a missing (or
unreachable) base case. Running the broken version for real crashes the
program on purpose -- with a "stack overflow" -- once every stack frame
your program is allowed has been used up. That's not worth doing more
than once, so the broken version stays commented out below. Read it,
understand why it never stops, then compile and run the FIXED version
that actually runs.

--- BROKEN (do not uncomment and run -- this crashes on purpose) ---

void countdownBroken(int n) {
    printf("%d...\n", n);
    countdownBroken(n);   // BUG: calls itself with the SAME n every time.
                          // There is no base case, and n never gets any
                          // closer to one. Every call adds another stack
                          // frame; eventually there's no room left and
                          // the program crashes with a stack overflow.
}

--- FIXED ---
*/

void countdownFixed(int n) {
    if (n == 0) {                 // base case -- this is what was missing
        printf("Liftoff!\n");
        return;
    }
    printf("%d...\n", n);
    countdownFixed(n - 1);        // n gets measurably closer to the base case
}

int main(void) {
    countdownFixed(5);
    return 0;
}
