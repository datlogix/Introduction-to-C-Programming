#include <stdio.h>

// Receives a COPY of whatever int is passed in. Changing x here only
// changes that local copy -- the original variable back in main() never
// finds out.
void addTenBroken(int x) {
    x = x + 10;
    printf("  inside addTenBroken: x is now %d\n", x);
}

// Receives a POINTER instead -- the ADDRESS of an int, not a copy of its
// value. Dereferencing that pointer (*x) reaches all the way back to the
// original variable in main() and changes it for real.
void addTenWorks(int *x) {
    *x = *x + 10;
    printf("  inside addTenWorks: *x is now %d\n", *x);
}

int main(void) {
    int number = 5;

    printf("number starts at %d\n\n", number);

    printf("Calling addTenBroken(number)...\n");
    addTenBroken(number);
    printf("Back in main: number is still %d (unchanged!)\n\n", number);

    printf("Calling addTenWorks(&number)...\n");
    addTenWorks(&number);
    printf("Back in main: number is now %d (it worked!)\n", number);

    // This is the real reason C has pointers: it's the ONLY tool the
    // language gives you for letting a function reach back and modify a
    // variable that belongs to its caller. Some other languages call this
    // "pass by reference" and hide the mechanism from you -- in C, you do
    // it yourself, explicitly, with &  and *.

    return 0;
}
