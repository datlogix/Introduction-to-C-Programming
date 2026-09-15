#include <stdio.h>
#include <stdlib.h>

/*
This program runs to completion and prints correct-looking output --
nothing crashes, nothing looks wrong. But it leaks memory every time
printReport() runs. A leak like this is invisible without a tool (or a
very careful read), which is exactly why valgrind exists.

    gcc -g 02_memory_leak_and_valgrind.c -o leak_demo
    valgrind ./leak_demo

See the README for a full walkthrough of the "definitely lost" report
this produces.
*/

void printReport(int *scores, int count) {
    int *summaryBuffer = malloc(sizeof(int) * count); // never freed -- see below
    if (summaryBuffer == NULL) {
        return;
    }

    for (int i = 0; i < count; i++) {
        summaryBuffer[i] = scores[i] * 2;
    }

    printf("Doubled scores:\n");
    for (int i = 0; i < count; i++) {
        printf("  %d\n", summaryBuffer[i]);
    }
    // BUG: summaryBuffer is malloc'd above but never free'd. Once this
    // function returns, the only pointer to that block is gone -- the
    // memory is unreachable for the rest of the program's run.
}

int main(void) {
    int scores[4] = {10, 20, 30, 40};

    printReport(scores, 4);

    printf("Report printed -- but we just leaked memory doing it.\n");
    return 0;
}
