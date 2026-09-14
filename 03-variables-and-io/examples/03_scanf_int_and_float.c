#include <stdio.h>

int main(void) {
    int age;
    float price;

    // scanf reads input the user types and stores it in a variable.
    // The & before the variable name means "the address of this
    // variable" -- it tells scanf WHERE in memory to put the value it
    // reads. You'll fully understand why it works that way in Module 7
    // (Pointers). For now: always write & before the variable name in
    // scanf, except when the variable is a string (Module 5).
    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Enter the price of your favorite snack: ");
    scanf("%f", &price);

    printf("You are %d years old and your snack costs %.2f.\n", age, price);

    return 0;
}
