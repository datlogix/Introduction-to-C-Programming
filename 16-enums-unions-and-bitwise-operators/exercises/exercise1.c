#include <stdio.h>

/*
Exercise 1: An enum-based traffic light.

1. Define: enum TrafficLight { RED, YELLOW, GREEN };

2. Write: void printLightName(enum TrafficLight light);
   Prints the name of the light ("RED", "YELLOW", or "GREEN") followed by
   a newline. No other output.

3. Write: enum TrafficLight nextLight(enum TrafficLight light);
   Returns the light that comes next in the standard cycle:
   RED -> GREEN -> YELLOW -> RED -> ...

main() below already exercises both functions -- do not change main().
Just write the enum and the two functions above it.
*/

// TODO: define enum TrafficLight here

// TODO: write printLightName here

// TODO: write nextLight here

int main(void) {
    enum TrafficLight light = RED;

    for (int i = 0; i < 5; i++) {
        printLightName(light);
        light = nextLight(light);
    }

    return 0;
}
