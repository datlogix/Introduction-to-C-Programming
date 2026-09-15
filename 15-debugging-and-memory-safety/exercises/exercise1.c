#include <stdio.h>
#include <stdlib.h>

/*
Exercise 1: Debug this program.

It's supposed to dynamically allocate an array, let the user search it
for a target number, and clean up before exiting. It compiles cleanly
and appears to "work" no matter what you search for -- but it has ONE
real bug.

Your job: don't just read it and guess. Actually use gdb and/or
valgrind (or, if neither is available on your machine, a careful
line-by-line audit -- see the README's platform note) to find it. Then
write one or two sentences as a comment at the bottom of this file
describing what tool/technique found it and what the bug was, before
you look at the solution.

Hint: trace every path out of main() after findTarget() returns. Does
memory get freed on ALL of them, or just some?
*/

int *buildArray(int count) {
    int *arr = malloc(sizeof(int) * count);
    if (arr == NULL) {
        return NULL;
    }
    for (int i = 0; i < count; i++) {
        arr[i] = i * 3;
    }
    return arr;
}

int findTarget(int *arr, int count, int target) {
    for (int i = 0; i < count; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int main(void) {
    int count = 5;
    int *numbers = buildArray(count);
    if (numbers == NULL) {
        return 1;
    }

    int target;
    printf("Enter a number to search for: ");
    scanf("%d", &target);

    int index = findTarget(numbers, count, target);
    if (index >= 0) {
        printf("Found %d at index %d.\n", target, index);
        return 0;
    }

    printf("%d not found.\n", target);
    free(numbers);
    return 0;
}

// TODO: describe the bug and how you found it here.
