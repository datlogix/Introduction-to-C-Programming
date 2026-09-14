#include <stdio.h>

int main(void) {
    int apples = 7;
    int friends = 2;

    // Two ints divided with / gives you INTEGER division: the decimal
    // part is thrown away completely, not rounded.
    printf("%d / %d as int division   = %d\n", apples, friends, apples / friends);

    // Casting one operand to float forces "real" division.
    printf("%d / %d as float division = %f\n", apples, friends, (float)apples / friends);

    // % gives you the remainder left over from integer division.
    printf("%d %% %d (remainder)       = %d\n", apples, friends, apples % friends);

    return 0;
}
