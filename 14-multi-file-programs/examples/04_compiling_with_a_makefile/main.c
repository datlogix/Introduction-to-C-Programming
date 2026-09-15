#include <stdio.h>
#include "stats.h"

int main(void) {
    int scores[] = {88, 95, 72, 100, 67};
    int count = 5;

    printf("Max: %d\n", maxOf(scores[0], scores[1]));
    printf("Min: %d\n", minOf(scores[0], scores[1]));
    printf("Average: %.2f\n", average(scores, count));

    return 0;
}
