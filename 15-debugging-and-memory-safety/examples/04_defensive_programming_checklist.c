#include <stdio.h>
#include <stdlib.h>

/*
This file isn't about a new bug -- it's the checklist from the README,
written as working code. Every habit below exists to prevent one of the
bugs from examples 01-03 before it ever happens, instead of debugging it
after the fact. Compile with -Wall (as always) and confirm it's clean.
*/

int main(void) {
    // 1. Initialize pointers -- to NULL if they don't have a real
    // address yet. A NULL pointer crashes immediately and obviously if
    // you forget to check it later; an uninitialized pointer can point
    // ANYWHERE, including memory that happens to "work" by accident.
    int *data = NULL;

    // 2. Always check malloc's return value before using it.
    data = malloc(sizeof(int) * 5);
    if (data == NULL) {
        fprintf(stderr, "malloc failed -- out of memory.\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        data[i] = i * i;
    }

    // 2b. The same discipline applies to fopen -- it returns NULL on
    // failure (missing file, no permission, disk full, ...) instead of
    // crashing, so ALWAYS check before reading/writing through it.
    FILE *log = fopen("scores.log", "w");
    if (log == NULL) {
        fprintf(stderr, "Could not open scores.log -- continuing without logging.\n");
    } else {
        for (int i = 0; i < 5; i++) {
            fprintf(log, "%d\n", data[i]);
        }
        fclose(log);
    }

    for (int i = 0; i < 5; i++) {
        printf("data[%d] = %d\n", i, data[i]);
    }

    // 3. Match every malloc with exactly one free -- and set the
    // pointer to NULL right after, so a stray later use is an obvious,
    // immediate NULL-dereference crash instead of silent corruption.
    free(data);
    data = NULL;

    printf("Done -- allocated once, freed exactly once, no leaks.\n");
    return 0;
}
