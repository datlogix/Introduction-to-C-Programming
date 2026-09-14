#include <stdio.h>

/*
Exercise 1: Doubling and Min/Max, for real this time.

Part A: doubleValue
    Write a function:
        void doubleValue(int *n)
    that doubles the value the caller's variable holds, THROUGH the
    pointer (using *n), the same way addTenWorks() did in the examples.

Part B: findMinAndMax
    In Module 6, a function could only ever `return` ONE value. Here,
    write a function:
        void findMinAndMax(int arr[], int size, int *min, int *max)
    that scans the array once and stores the smallest value at the
    address `min` points to, and the largest value at the address `max`
    points to. This is a genuinely common use of pointers: it's how C
    functions "return" more than one result.

Test both functions from main() -- code is already there to call them and
print the results. Do not change main().
*/

void doubleValue(int *n) {
    // TODO: set the value n points to, to double what it currently is
}

void findMinAndMax(int arr[], int size, int *min, int *max) {
    // TODO: initialize *min and *max to arr[0] first, then loop through
    // the rest of the array, updating *min and *max as you find smaller
    // or larger values
}

int main(void) {
    int number = 21;
    printf("number before doubleValue: %d\n", number);
    doubleValue(&number);
    printf("number after doubleValue:  %d\n", number);

    int scores[] = {42, 17, 99, 3, 56, 71};
    int size = 6;
    int smallest;
    int largest;

    findMinAndMax(scores, size, &smallest, &largest);
    printf("\nSmallest score: %d\n", smallest);
    printf("Largest score:  %d\n", largest);

    return 0;
}
