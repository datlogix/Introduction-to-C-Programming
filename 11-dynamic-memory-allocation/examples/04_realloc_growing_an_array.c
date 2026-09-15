#include <stdio.h>
#include <stdlib.h>

/*
realloc(pointer, newSize) resizes a block of memory you previously got
from malloc/calloc/realloc. Two things make it easy to get wrong:

1. realloc is allowed to MOVE the block to a brand-new address (if it
   can't grow it in place) and copies the old contents over for you. It
   returns the pointer to wherever the (possibly new) block now lives --
   you MUST capture that return value. Keep using the old pointer and
   you're reading/writing memory that may no longer be valid.
2. If realloc fails, it returns NULL and leaves the ORIGINAL block
   completely untouched. If you overwrite your only pointer to that
   block with the NULL result, you've just leaked the original memory --
   you can no longer reach it to free it. Always realloc into a
   temporary pointer first, check it, THEN update your real pointer.
*/

int main(void) {
    int initialSize = 3;
    int *scores = malloc(sizeof(int) * initialSize);

    if (scores == NULL) {
        printf("Initial allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < initialSize; i++) {
        scores[i] = (i + 1) * 10; // 10, 20, 30
    }

    printf("Before growing:");
    for (int i = 0; i < initialSize; i++) {
        printf(" %d", scores[i]);
    }
    printf("\n");

    // Grow the block from 3 ints to 6 ints.
    int newSize = 6;

    // WRONG pattern (don't do this): scores = realloc(scores, sizeof(int) * newSize);
    // If realloc fails, that line overwrites `scores` with NULL and the
    // original block is now unreachable -- a leak, with no way to free it.

    int *temp = realloc(scores, sizeof(int) * newSize);
    if (temp == NULL) {
        printf("realloc failed -- original data is still safe in `scores`.\n");
        free(scores); // we can still free the original block
        return 1;
    }
    scores = temp; // only now do we update our real pointer

    for (int i = initialSize; i < newSize; i++) {
        scores[i] = (i + 1) * 10; // 40, 50, 60
    }

    printf("After growing: ");
    for (int i = 0; i < newSize; i++) {
        printf(" %d", scores[i]);
    }
    printf("\n");

    free(scores);
    scores = NULL;

    return 0;
}
