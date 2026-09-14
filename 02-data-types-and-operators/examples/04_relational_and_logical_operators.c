#include <stdio.h>

int main(void) {
    int age = 20;

    // Relational operators compare two values and produce 1 (true)
    // or 0 (false) -- in C, there is no separate "boolean" type for this.
    printf("age == 20 -> %d\n", age == 20);
    printf("age != 20 -> %d\n", age != 20);
    printf("age > 18  -> %d\n", age > 18);
    printf("age < 18  -> %d\n", age < 18);
    printf("age >= 20 -> %d\n", age >= 20);
    printf("age <= 19 -> %d\n", age <= 19);

    // Logical operators combine 0/1 results: && (and), || (or), ! (not).
    printf("(age > 18) && (age < 65) -> %d\n", (age > 18) && (age < 65));
    printf("(age < 18) || (age > 65) -> %d\n", (age < 18) || (age > 65));
    printf("!(age == 20)             -> %d\n", !(age == 20));

    // We're just printing what these operators produce for now --
    // using them to actually make decisions is Module 4's job.
    return 0;
}
