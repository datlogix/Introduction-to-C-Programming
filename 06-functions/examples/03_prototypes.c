// A function PROTOTYPE (also called a declaration) tells the compiler
// "a function with this name, these parameters, and this return type
// exists somewhere in this file" -- without giving the full body yet.
//
// This lets main() call describeTemperature() even though its full
// DEFINITION doesn't appear until further down the file. Without the
// prototype below, this file would fail to compile: the compiler reads
// top to bottom, and by the time it reaches main(), it wouldn't have
// seen describeTemperature() yet.

#include <stdio.h>

void describeTemperature(int celsius); // prototype -- note the semicolon

int main(void) {
    describeTemperature(35);
    describeTemperature(10);
    describeTemperature(-5);

    return 0;
}

// The full definition -- notice the header line matches the prototype
// exactly, just without the trailing semicolon, and with a body attached.
void describeTemperature(int celsius) {
    if (celsius >= 30) {
        printf("%d C: that's hot.\n", celsius);
    } else if (celsius >= 15) {
        printf("%d C: that's mild.\n", celsius);
    } else {
        printf("%d C: that's cold.\n", celsius);
    }
}
