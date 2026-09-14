#include <stdio.h>

int main(void) {
    // You can declare a variable first and assign it a value later.
    int score;
    score = 0;
    printf("Starting score: %d\n", score);

    // Or declare and initialize in a single step -- prefer this style
    // whenever you already know the starting value.
    int age = 16;
    printf("Age: %d\n", age);

    // Re-assignment: once a variable exists, '=' just updates its value.
    // This is NOT the same as declaring it again.
    age = age + 1;
    printf("Age next year: %d\n", age);

    // Meaningful, snake_case names (all lowercase, words joined by
    // underscores) are the idiomatic C style. Compare how much easier
    // these are to understand than "int n = 24; double s = 78.5;".
    int number_of_students = 24;
    double average_score = 78.5;
    printf("%d students, average score %.1f\n", number_of_students, average_score);

    // DANGER: a variable that is declared but never given a value holds
    // whatever leftover bits were already sitting at that memory address --
    // a "garbage value". It could be 0, it could be 2 billion, it could be
    // different every time you run the program. Never trust an
    // uninitialized variable.
    int mystery;
    printf("Uninitialized mystery value: %d (unpredictable! do not rely on this)\n", mystery);

    return 0;
}
