#include <stdio.h>
#include <stdlib.h>

/*
Exercise 1: Dynamically sized average calculator.

1. Ask the user how many numbers they want to enter (use scanf).
2. Dynamically allocate an array of exactly that many ints with malloc
   (use the sizeof(int) * count pattern from the examples).
3. ALWAYS check the result of malloc for NULL before using it -- if it's
   NULL, print an error message and return 1 instead of continuing.
4. Fill the array by reading that many ints from the user with scanf.
5. Compute and print the average of the values (use a double for the
   average so it isn't truncated to a whole number).
6. free() the array before the program ends.

Sample run:
    How many numbers? 4
    Enter number 1: 10
    Enter number 2: 20
    Enter number 3: 30
    Enter number 4: 40
    Average: 25.00
*/

int main(void) {
    int count;
    printf("How many numbers? ");
    scanf("%d", &count);

    // TODO: dynamically allocate an array of `count` ints here.
    // int *numbers = ...

    // TODO: check the allocation for NULL before using it.

    // TODO: read `count` ints from the user into the array.

    // TODO: compute the sum, then the average (as a double), and print it
    // using a format like: printf("Average: %.2f\n", average);

    // TODO: free the array.

    return 0;
}
