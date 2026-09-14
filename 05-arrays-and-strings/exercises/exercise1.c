#include <stdio.h>

/*
Exercise 1: Find the highest score.

The array `scores` below already has 6 values in it. Complete main() so
the program finds and prints the HIGHEST value in the array.

Steps:
    1. Start by assuming the first element (scores[0]) is the highest
       so far -- store it in a variable called `highest`.
    2. Use a for loop to check every OTHER element (index 1 through the
       last valid index). Any time you find one bigger than `highest`,
       update `highest` to that value.
    3. After the loop, print the result in exactly this format:
       "Highest score: 97"  (using whatever the real highest value is)

Do not change the `scores` array or its size.
*/

int main(void) {
    int scores[6] = {72, 88, 95, 60, 97, 81};
    int size = 6;

    // TODO: declare `highest` and set it to scores[0]

    // TODO: loop through scores[1] .. scores[size - 1], updating `highest`
    //       whenever you find a bigger value

    // TODO: printf("Highest score: %d\n", highest);

    return 0;
}
