#include <stdio.h>
#include <stdlib.h>

/*
malloc() and calloc() both hand you a block of heap memory, but they
differ in one important way:

- malloc(size) gives you `size` bytes of memory with whatever garbage
  values happened to already be sitting there. It does NOT zero it out.
- calloc(count, size) gives you room for `count` items of `size` bytes
  each, and guarantees every byte starts at 0.

Assuming malloc'd memory starts at zero is a classic beginner bug --
the values LOOK zeroed the first time you happen to run a program (the
memory might genuinely be clean), then mysteriously look like garbage
later, or on a different machine. Never rely on it.
*/

int main(void) {
    int size = 5;

    int *mallocArr = malloc(sizeof(int) * size);
    int *callocArr = calloc(size, sizeof(int)); // note the two-argument form

    if (mallocArr == NULL || callocArr == NULL) {
        printf("Allocation failed.\n");
        free(mallocArr);
        free(callocArr);
        return 1;
    }

    printf("malloc'd array (uninitialized -- contents are NOT guaranteed):\n");
    for (int i = 0; i < size; i++) {
        printf("  mallocArr[%d] = %d\n", i, mallocArr[i]);
    }

    printf("calloc'd array (guaranteed zeroed):\n");
    for (int i = 0; i < size; i++) {
        printf("  callocArr[%d] = %d\n", i, callocArr[i]);
    }

    printf("\nLesson: never assume mallocArr's values are 0 just because it\n");
    printf("looked that way above -- if you need zero-initialized memory,\n");
    printf("ask for it with calloc, don't hope for it from malloc.\n");

    free(mallocArr);
    free(callocArr);
    mallocArr = NULL;
    callocArr = NULL;

    return 0;
}
