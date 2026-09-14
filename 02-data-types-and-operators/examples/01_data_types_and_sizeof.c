#include <stdio.h>

int main(void) {
    int wholeNumber = 42;
    float singlePrecision = 3.14f;
    double doublePrecision = 3.14159265358979;
    char letter = 'A';

    printf("int:    %d (uses %zu bytes)\n", wholeNumber, sizeof(wholeNumber));
    printf("float:  %f (uses %zu bytes)\n", singlePrecision, sizeof(singlePrecision));
    printf("double: %f (uses %zu bytes)\n", doublePrecision, sizeof(doublePrecision));
    printf("char:   %c (uses %zu bytes)\n", letter, sizeof(letter));

    // short and long exist too, but as a beginner you'll rarely need them --
    // int, float, double, and char cover almost everything you'll write.
    printf("short takes %zu bytes, long takes %zu bytes\n", sizeof(short), sizeof(long));

    return 0;
}
