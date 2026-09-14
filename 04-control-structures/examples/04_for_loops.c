#include <stdio.h>

int main(void) {
    // A for loop packs three things into one line, separated by ; :
    //   1. initialization -- runs once, before the loop starts
    //   2. condition      -- checked before every run, loop stops when false
    //   3. increment      -- runs after every run of the body
    //
    // Use a for loop when you know in advance how many times you want to
    // repeat something -- like "print the 3 times table" below. Use a
    // while loop instead when you're repeating until something happens,
    // and you don't know in advance how many times that will take.
    int number = 3;
    printf("-- %d times table --\n", number);
    for (int i = 1; i <= 10; i = i + 1) {
        printf("%d x %d = %d\n", number, i, number * i);
    }

    // A control structure (if) can live inside another (for) -- this is
    // called nesting. Here we check each number as we generate it.
    printf("\n-- even or odd, 1 to 10 --\n");
    for (int i = 1; i <= 10; i = i + 1) {
        if (i % 2 == 0) {
            printf("%d is even\n", i);
        } else {
            printf("%d is odd\n", i);
        }
    }

    return 0;
}
