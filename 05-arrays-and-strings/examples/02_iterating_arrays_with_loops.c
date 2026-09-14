#include <stdio.h>

int main(void) {
    int scores[5] = {90, 85, 77, 60, 100};

    // Typing scores[0], scores[1], scores[2]... by hand doesn't scale.
    // A for loop lets the index "i" walk across every slot instead.
    // NOTICE: the loop runs while i < 5, so i takes the values 0,1,2,3,4 --
    // exactly the 5 valid indexes of a 5-element array. It never reaches 5.
    printf("All scores:\n");
    for (int i = 0; i < 5; i++) {
        printf("  scores[%d] = %d\n", i, scores[i]);
    }

    // The same idea lets you compute things about the whole array, like a
    // running total and an average.
    int total = 0;
    for (int i = 0; i < 5; i++) {
        total = total + scores[i];
    }
    double average = total / 5.0; // 5.0, not 5, so we get a decimal result
    printf("Total: %d\n", total);
    printf("Average: %.2f\n", average);

    // Finding the biggest value: start by assuming the first element is the
    // biggest, then let every other element challenge that assumption.
    int highest = scores[0];
    for (int i = 1; i < 5; i++) {
        if (scores[i] > highest) {
            highest = scores[i];
        }
    }
    printf("Highest score: %d\n", highest);

    return 0;
}
