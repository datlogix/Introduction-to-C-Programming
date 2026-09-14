#include <stdio.h>

int main(void) {
    int dayNumber = 3;

    // switch compares dayNumber against each case, top to bottom, and
    // jumps straight to the one that matches. It's often cleaner than a
    // long if/else-if chain when you're comparing ONE variable against
    // several exact values (switch can't do ranges or && / || conditions
    // -- for those you still need if/else).
    switch (dayNumber) {
        case 1:
            printf("Monday\n");
            break;
        case 2:
            printf("Tuesday\n");
            break;
        case 3:
            printf("Wednesday\n");
            break;
        case 4:
            printf("Thursday\n");
            break;
        case 5:
            printf("Friday\n");
            break;
        case 6:
            printf("Saturday\n");
            break;
        case 7:
            printf("Sunday\n");
            break;
        default:
            // default runs when none of the cases match -- always include
            // one, the same way you'd include a final `else`.
            printf("Not a valid day number.\n");
            break;
    }

    // break is what stops execution from "falling through" into the next
    // case. See 07_switch_fallthrough_demo.c for what happens if you
    // forget it -- it's one of the most common beginner switch bugs.
    char grade = 'B';

    switch (grade) {
        case 'A':
            printf("Excellent!\n");
            break;
        case 'B':
            printf("Good job.\n");
            break;
        case 'C':
            printf("You passed.\n");
            break;
        default:
            printf("Keep practicing.\n");
            break;
    }

    return 0;
}
