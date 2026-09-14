#include <stdio.h>

int main(void) {
    // An array is a fixed number of values of the same type, stored back to
    // back in memory, all sharing one name. This declares an array that can
    // hold 5 ints, but its slots are NOT set yet -- they hold "garbage":
    // whatever bits happened to already be sitting in that memory.
    int scores[5];

    // You can declare AND initialize in one line instead:
    int prices[5] = {90, 85, 77, 60, 100};

    // Array indexing starts at 0, not 1. prices[0] is the FIRST element.
    // The LAST element is at index (size - 1), so here that's prices[4].
    printf("First price: %d\n", prices[0]);
    printf("Last price: %d\n", prices[4]);

    // Assigning into scores[] one slot at a time, using the same indexing.
    // Only after this do scores[0..4] hold values you can trust.
    scores[0] = 10;
    scores[1] = 20;
    scores[2] = 30;
    scores[3] = 40;
    scores[4] = 50;
    printf("Third score: %d\n", scores[2]);

    // Handy trick: if you give FEWER values than the array's size, C fills
    // every remaining slot with 0 -- it does NOT leave them as garbage.
    int reading[5] = {7};       // reading[0] is 7, reading[1..4] are all 0
    printf("reading[0] = %d, reading[4] = %d\n", reading[0], reading[4]);

    // A quick preview: real programs often need a grid, not just a row.
    // int grid[3][3]; is a 2D array (3 rows of 3 ints each) -- you'll use
    // these more once you're comfortable with plain 1D arrays like above.

    return 0;
}
