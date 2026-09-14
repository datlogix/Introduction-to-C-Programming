// Module 6 Project starter: the Module 4 Number Guessing Game, exactly as
// a beginner might first write it -- one long main(), everything inline.
// It works correctly. Your job is NOT to change what it does, but HOW
// it's organized: see project/README.md for the refactoring requirements.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int) time(NULL));
    int secretNumber = rand() % 100 + 1;
    int guess;
    int numberOfGuesses = 0;
    int hasWon = 0;

    printf("I'm thinking of a number between 1 and 100.\n");

    while (hasWon == 0) {
        printf("Enter your guess: ");
        scanf("%d", &guess);

        if (guess < 1 || guess > 100) {
            printf("Please enter a number between 1 and 100.\n");
            continue;
        }

        numberOfGuesses = numberOfGuesses + 1;

        if (guess < secretNumber) {
            printf("Too low! Try again.\n");
        } else if (guess > secretNumber) {
            printf("Too high! Try again.\n");
        } else {
            printf("Correct! You guessed it in %d tries.\n", numberOfGuesses);
            hasWon = 1;
        }
    }

    return 0;
}
