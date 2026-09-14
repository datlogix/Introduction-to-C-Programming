#include <stdio.h>

int main(void) {
    // break immediately exits the loop it's in -- no more checks, no more
    // iterations, execution jumps straight to the first line after the loop.
    printf("-- break: stop as soon as the running total passes 50 --\n");
    int total = 0;
    for (int i = 1; i <= 100; i = i + 1) {
        total = total + i;
        if (total > 50) {
            printf("Stopping at i = %d, total = %d\n", i, total);
            break;
        }
    }

    // continue skips the REST of the current iteration only and jumps
    // straight to the next check of the condition -- the loop keeps going.
    printf("\n-- continue: skip multiples of 3 from 1 to 15 --\n");
    for (int i = 1; i <= 15; i = i + 1) {
        if (i % 3 == 0) {
            continue; // skip printing this one, but keep looping
        }
        printf("%d\n", i);
    }

    return 0;
}
