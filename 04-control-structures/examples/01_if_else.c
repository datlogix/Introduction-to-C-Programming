#include <stdio.h>

int main(void) {
    int temperature = 28;

    // The relational and logical operators from Module 2 (>, <, >=, <=,
    // &&, ||) produce 0 (false) or 1 (true) -- an if statement runs its
    // block only when the condition inside () is true (non-zero).
    if (temperature >= 30) {
        printf("It's hot outside.\n");
    } else if (temperature >= 20) {
        printf("It's a mild day.\n");
    } else if (temperature >= 10) {
        printf("It's a bit cold.\n");
    } else {
        printf("It's freezing!\n");
    }

    // C checks each condition top to bottom and runs the FIRST one that's
    // true, then skips the rest -- it never checks more than one branch.
    int age = 16;
    int hasPermissionSlip = 1; // 1 = true, 0 = false (Module 2)

    // Combine conditions with && ("and") to require both to be true.
    if (age >= 18) {
        printf("You can enter without a permission slip.\n");
    } else if (age >= 13 && hasPermissionSlip) {
        printf("You can enter with your permission slip.\n");
    } else {
        printf("Sorry, you can't enter yet.\n");
    }

    return 0;
}
