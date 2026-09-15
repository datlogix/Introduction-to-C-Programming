#include <stdio.h>
#include <stdlib.h>

/*
Module 15 Project: Bug Hunt.

This program has THREE separate, distinct bugs hiding in it:
  - one that crashes it (a segfault),
  - one that leaks memory,
  - and one that reads an uninitialized value.

It compiles cleanly. It even prints output before anything visibly goes
wrong. See the project README for your task -- diagnose all three using
gdb and/or valgrind (or a careful manual audit), fix them, and document
how you found each one.

Do not just read the code and guess at the fixes -- the point of this
project is practicing the tools, not spotting bugs by eye.
*/

int *createScoreArray(int count) {
    int *scores = malloc(sizeof(int) * count);
    if (scores == NULL) {
        return NULL;
    }
    for (int i = 0; i < count; i++) {
        scores[i] = (i + 1) * 10;
    }
    return scores;
}

double averageScore(int *scores, int count) {
    int total;
    for (int i = 0; i < count; i++) {
        total += scores[i];
    }
    return (double)total / count;
}

void printReport(int *scores, int count) {
    int *summaryBuffer = malloc(sizeof(int) * count);
    if (summaryBuffer == NULL) {
        return;
    }

    for (int i = 0; i < count; i++) {
        summaryBuffer[i] = scores[i];
    }

    printf("Score report:\n");
    for (int i = 0; i < count; i++) {
        printf("  Player %d: %d\n", i + 1, summaryBuffer[i]);
    }
}

void announceWinner(int *scores, int count) {
    int *topScorePtr = NULL;

    for (int i = 0; i < count; i++) {
        if (scores[i] > 25) {
            // (supposed to record the top score's address here)
        }
    }

    printf("Top score this round: %d\n", *topScorePtr);
}

int main(void) {
    // Line-buffer stdout so every printed line shows up immediately,
    // even if the program crashes moments later -- otherwise a crash
    // can silently swallow output that was still sitting in a buffer.
    setvbuf(stdout, NULL, _IOLBF, 0);

    int count = 4;
    int *scores = createScoreArray(count);
    if (scores == NULL) {
        printf("Allocation failed.\n");
        return 1;
    }

    double avg = averageScore(scores, count);
    printf("Average score: %.2f\n", avg);

    printReport(scores, count);

    announceWinner(scores, count);

    free(scores);
    return 0;
}
