// A `void` function does something (prints, changes something, etc.)
// but hands nothing back to the caller. It has no `return value;` --
// at most a bare `return;` to exit early.
//
// This file also demonstrates SCOPE: a variable declared inside a
// function only exists inside that function. Nobody outside can see it.

#include <stdio.h>

void printWelcomeBanner(char userName[]) {
    // `line` only exists while printWelcomeBanner is running.
    int line = 1;
    printf("%d) Welcome, %s!\n", line, userName);
    line++;
    printf("%d) We hope you enjoy the course.\n", line);
    // `line` disappears the moment this function returns.
}

// A global variable: declared outside every function, visible to all of
// them. It compiles and works, but avoid this as a beginner -- any
// function can silently change it, which makes bugs very hard to track
// down as a program grows. Prefer parameters and return values instead.
int totalGreetings = 0;

void countGreeting(void) {
    totalGreetings++; // reads and modifies the global directly
}

int main(void) {
    printWelcomeBanner("Ama");

    // Uncommenting the next line would NOT compile: `line` belongs to
    // printWelcomeBanner and doesn't exist out here.
    // printf("%d\n", line);

    countGreeting();
    countGreeting();
    countGreeting();
    printf("Total greetings counted: %d\n", totalGreetings);

    return 0;
}
