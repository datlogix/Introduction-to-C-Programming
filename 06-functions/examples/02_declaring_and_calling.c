// The basic shape of a function: a header, a body, and a call.
//
//     return_type name(parameter_list) {
//         ... body ...
//     }
//
// This function is defined ABOVE main(), so main() already knows about it
// by the time it's called -- no extra step needed yet.

#include <stdio.h>

void printStarRow(int count) {
    for (int i = 0; i < count; i++) {
        printf("*");
    }
    printf("\n");
}

int main(void) {
    printf("Calling the same function three times with different input:\n");
    printStarRow(3);
    printStarRow(8);
    printStarRow(1);

    return 0;
}
