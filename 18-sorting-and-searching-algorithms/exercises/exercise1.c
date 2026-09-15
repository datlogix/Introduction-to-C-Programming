#include <stdio.h>

/*
Exercise 1: Binary search as its own function.

Write:

    int binarySearch(int arr[], int size, int target)

It must:
  - Assume arr is already SORTED in ascending order (that's binary
    search's one precondition -- don't try to sort it yourself here).
  - Return the INDEX of target if it's found in arr.
  - Return -1 if target is not in arr.
  - Use the standard low/mid/high halving approach -- no linear scan.

main() below already calls binarySearch with test values (including a
target that doesn't exist, and targets at the very first and very last
index) and checks the results -- do not change main(). Just write the
function above it.
*/

// TODO: write binarySearch(int arr[], int size, int target) here

int main(void) {
    int sorted[] = {3, 7, 11, 19, 23, 28, 34, 41, 47, 52, 58, 63, 71, 79, 88};
    int size = 15;

    int tests[] = {3, 88, 41, 100, 1};
    int expected[] = {0, 14, 7, -1, -1};
    int numTests = 5;

    int allPassed = 1;
    for (int i = 0; i < numTests; i++) {
        int result = binarySearch(sorted, size, tests[i]);
        printf("binarySearch(sorted, 15, %3d) = %3d  (expected %3d)  %s\n",
               tests[i], result, expected[i],
               result == expected[i] ? "OK" : "FAIL");
        if (result != expected[i]) {
            allPassed = 0;
        }
    }

    printf("\n%s\n", allPassed ? "All tests passed!" : "Some tests failed -- check your binarySearch.");

    return 0;
}
