#include <stdio.h>

int main(void) {
    int age = 25;
    float price = 9.99f;
    char grade = 'A';

    // Every variable you've ever created lives somewhere in your computer's
    // memory (RAM). "&variableName" means "the address where this variable
    // is stored" -- not its value. %p is the format specifier for printing
    // an address.
    printf("age lives at address:   %p\n", (void *)&age);
    printf("price lives at address: %p\n", (void *)&price);
    printf("grade lives at address: %p\n", (void *)&grade);

    // The addresses will look like strange hex numbers (e.g. 0x7ffee3a1c9ac).
    // You'll never need to memorize or predict them -- what matters is that
    // they EXIST, they're usually different for each variable, and a
    // pointer is simply a variable that stores one of these addresses.
    printf("\nCompare: the VALUE of age is still just %d\n", age);

    return 0;
}
