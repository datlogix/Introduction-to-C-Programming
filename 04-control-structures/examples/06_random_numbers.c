#include <stdio.h>
#include <stdlib.h> // rand(), srand()
#include <time.h>   // time()

int main(void) {
    // Computers can't generate truly random numbers -- rand() actually
    // produces a long, fixed sequence of numbers that just LOOKS random.
    // That's good enough for games and simple programs like ours.
    //
    // srand() "seeds" that sequence -- without it, rand() gives you the
    // exact same numbers every single time you run the program. Seeding
    // with the current time (time(NULL), from <time.h>) means the seed
    // is different every run, so the numbers actually change.
    srand(time(NULL));

    // rand() alone returns a large number between 0 and RAND_MAX. To get
    // a number in a specific range, use % (modulo) to shrink it, then add
    // the minimum value you want.
    //
    //   rand() % 6       -> a number from 0 to 5
    //   rand() % 6 + 1    -> a number from 1 to 6 (a dice roll!)
    printf("-- rolling a die 5 times --\n");
    for (int i = 0; i < 5; i = i + 1) {
        int roll = rand() % 6 + 1;
        printf("Roll %d: %d\n", i + 1, roll);
    }

    // General formula for a random number between min and max (inclusive):
    //   rand() % (max - min + 1) + min
    int min = 1;
    int max = 100;
    int randomNumber = rand() % (max - min + 1) + min;
    printf("\nA random number between %d and %d: %d\n", min, max, randomNumber);

    return 0;
}
