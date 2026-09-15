// Source file: the actual function bodies. mathreport.c is the only
// file that needs to know *how* square() or printReport() work --
// everyone else just needs mathreport.h.
#include <stdio.h>
#include "mathreport.h"

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
