#include <stdio.h>

/*
Exercise 1: Two small recursive functions.

Write two separate recursive functions and call both from main():

    1. int power(int base, int exp)
       Returns base raised to exp (base^exp). Assume exp is 0 or a
       positive integer. power(x, 0) should return 1 for any x.
       Hint: base^exp == base * base^(exp - 1).

    2. int reverseSum(int arr[], int size)
       Returns the sum of all elements in arr, computed by recursing on
       the LAST element instead of the first (the opposite direction
       from examples/03_sum_of_array_recursive.c).
       Hint: the base case is still size == 0; the recursive case adds
       arr[size - 1] to the sum of the remaining size - 1 elements.

main() below already calls both with test values and prints the
results -- do not change main(). Just write the functions above it.
*/

// TODO: write power(int base, int exp) here

// TODO: write reverseSum(int arr[], int size) here

int main(void) {
    printf("power(2, 5) = %d (expected 32)\n", power(2, 5));
    printf("power(3, 0) = %d (expected 1)\n", power(3, 0));
    printf("power(5, 3) = %d (expected 125)\n", power(5, 3));

    int values[] = {4, 8, 15, 16, 23, 42};
    printf("reverseSum(values, 6) = %d (expected 108)\n", reverseSum(values, 6));

    return 0;
}
