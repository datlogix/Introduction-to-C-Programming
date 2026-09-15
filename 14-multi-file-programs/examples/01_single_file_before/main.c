// The "before" version: one file, everything in it.
// This is small enough to read comfortably -- but imagine it's grown to
// 400 lines with a dozen more functions like these two. Finding
// "the cube function" means scrolling past everything else in the file.

#include <stdio.h>

#define SEPARATOR_WIDTH 20

int square(int n) {
    return n * n;
}

int cube(int n) {
    return n * n * n;
}

void printSeparator(void) {
    for (int i = 0; i < SEPARATOR_WIDTH; i++) {
        printf("-");
    }
    printf("\n");
}

void printReport(int n) {
    printf("Number: %d\n", n);
    printf("Square: %d\n", square(n));
    printf("Cube:   %d\n", cube(n));
    printSeparator();
}

int main(void) {
    printReport(4);
    printReport(7);
    return 0;
}
