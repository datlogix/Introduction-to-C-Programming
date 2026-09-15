#include <stdio.h>
#include <string.h>

/*
Exercise 1: String reverser.

Write a CLI tool that reverses whatever single string is passed as its
one command-line argument.

    ./reverse hello     ->  olleh
    ./reverse           ->  usage message (no argument given)

Requirements:
1. If no argument is given (argc < 2), print a usage message showing
   how the program should be called (e.g. "Usage: ./reverse <word>"),
   and return 1.
2. Otherwise, print the characters of argv[1] in reverse order, followed
   by a newline.

Hint: strlen(argv[1]) gives you the string's length; loop backwards from
its last character (index length - 1) down to index 0, printing each
character with putchar().
*/

int main(int argc, char *argv[]) {
    // TODO: check argc and print a usage message (then return 1) if no
    // argument was given.

    // TODO: reverse and print argv[1], followed by a newline.

    return 0;
}
