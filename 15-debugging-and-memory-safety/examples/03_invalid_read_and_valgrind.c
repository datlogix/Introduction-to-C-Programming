#include <stdio.h>
#include <stdlib.h>

/*
This program allocates space for exactly 5 ints, fills all 5 correctly,
then reads one element PAST the end of the block. On most systems this
won't crash -- it'll just print some meaningless leftover number and
keep going, which is exactly what makes this class of bug so dangerous:
it can run for years in production without anyone noticing, silently
reading (or, far worse, writing) memory that belongs to something else.

    gcc -g 03_invalid_read_and_valgrind.c -o invalid_read_demo
    valgrind ./invalid_read_demo

See the README for a full walkthrough of the "Invalid read of size 4"
report this produces.
*/

int main(void) {
    int *values = malloc(sizeof(int) * 5);
    if (values == NULL) {
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        values[i] = (i + 1) * 100;
    }

    printf("Last valid value: %d\n", values[4]);
    printf("One past the end:  %d\n", values[5]); // BUG: index 5 doesn't exist -- valid indices are 0-4

    free(values);
    return 0;
}
