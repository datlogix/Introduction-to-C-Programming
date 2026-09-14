#include <stdio.h>

/*
Exercise 1: Three small functions.

Write three separate functions and call all of them from main():

    1. int isEven(int number)
       Returns 1 if `number` is even, 0 otherwise.

    2. int maxOfThree(int a, int b, int c)
       Returns the largest of the three arguments.

    3. int factorial(int n)
       Returns n! (n * (n-1) * (n-2) * ... * 1). Assume n is 0 or a
       positive integer. factorial(0) should return 1.

main() below already calls all three with test values and prints the
results -- do not change main(). Just write the functions above it
(you'll need prototypes, or define them above main -- your choice).
*/

// TODO: write a prototype (or full definition) for isEven here

// TODO: write a prototype (or full definition) for maxOfThree here

// TODO: write a prototype (or full definition) for factorial here

int main(void) {
    printf("isEven(4) = %d (expected 1)\n", isEven(4));
    printf("isEven(7) = %d (expected 0)\n", isEven(7));

    printf("maxOfThree(3, 9, 5) = %d (expected 9)\n", maxOfThree(3, 9, 5));
    printf("maxOfThree(10, 2, 8) = %d (expected 10)\n", maxOfThree(10, 2, 8));

    printf("factorial(0) = %d (expected 1)\n", factorial(0));
    printf("factorial(5) = %d (expected 120)\n", factorial(5));

    return 0;
}

// TODO: if you didn't write full definitions above, write them down here.
