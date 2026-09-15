#include <stdio.h>

// Prints an 8-bit value as its binary digits, most significant bit first.
void printBinary8(unsigned char value) {
    for (int bit = 7; bit >= 0; bit--) {
        printf("%d", (value >> bit) & 1);
    }
}

int main(void) {
    unsigned char a = 12;  // binary 00001100
    unsigned char b = 10;  // binary 00001010

    printf("a      = "); printBinary8(a); printf(" (%d)\n", a);
    printf("b      = "); printBinary8(b); printf(" (%d)\n\n", b);

    unsigned char andResult = a & b;
    printf("a & b  = "); printBinary8(andResult);
    printf(" (%d)  -- 1 only where BOTH bits are 1\n", andResult);

    unsigned char orResult = a | b;
    printf("a | b  = "); printBinary8(orResult);
    printf(" (%d)  -- 1 where EITHER bit is 1\n", orResult);

    unsigned char xorResult = a ^ b;
    printf("a ^ b  = "); printBinary8(xorResult);
    printf(" (%d)  -- 1 where the bits DIFFER\n", xorResult);

    unsigned char notA = ~a;
    printf("~a     = "); printBinary8(notA);
    printf(" (%d)  -- every bit flipped\n", notA);

    unsigned char leftShift = a << 2;
    printf("a << 2 = "); printBinary8(leftShift);
    printf(" (%d)  -- bits move left, zeros fill in on the right (a * 4)\n", leftShift);

    unsigned char rightShift = a >> 2;
    printf("a >> 2 = "); printBinary8(rightShift);
    printf(" (%d)  -- bits move right (a / 4, remainder discarded)\n", rightShift);

    return 0;
}
