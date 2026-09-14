#include <stdio.h>

int main(void) {
    int wholeScore = 7;
    float bonus = 2.5f;

    // Implicit conversion: C automatically "promotes" the int to a float
    // before adding, because one of the operands is already a float.
    float total = wholeScore + bonus;
    printf("Implicit conversion: %d + %.1f = %f\n", wholeScore, bonus, total);

    int a = 7;
    int b = 2;

    // Without a cast, this is still integer division -- the answer truncates.
    printf("No cast:   %d / %d = %d\n", a, b, a / b);

    // (float) explicitly converts `a` to a float before the division runs,
    // so we get the real decimal answer instead of a truncated one.
    printf("With cast: (float)%d / %d = %f\n", a, b, (float)a / b);

    return 0;
}
