#include <stdio.h>

/*
Exercise 1: Grade classifier.

A test score from 0-100 maps to a letter grade like this:
    90-100  -> 'A'
    80-89   -> 'B'
    70-79   -> 'C'
    60-69   -> 'D'
    below 60 -> 'F'

Complete main() below so the program:
    1. Reads an integer score (0-100) from the user with scanf.
    2. Uses an if / else if / else chain to decide the letter grade.
    3. Prints exactly one line: "Grade: X" where X is the letter.

Test your program with scores like 95, 82, 71, 60, and 40 -- one for
each branch -- to make sure every path works before moving on.
*/

int main(void) {
    int score;

    printf("Enter a test score (0-100): ");
    // TODO: read the score into `score` with scanf

    // TODO: if/else-if/else chain that decides the letter grade
    // TODO: print "Grade: X" using the letter you decided above

    return 0;
}
