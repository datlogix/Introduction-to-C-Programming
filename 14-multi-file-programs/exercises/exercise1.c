#include <stdio.h>

/*
Exercise 1: Split this single file into a header + source pair.

Right now everything lives in one file, the way it did before this
module. Your job:

    1. Create a header file named "temputils.h" that contains:
       - An include guard (#ifndef / #define / #endif).
       - A #define for FREEZING_POINT_C (see below).
       - Function PROTOTYPES ONLY for celsiusToFahrenheit and
         describeTemperature (no function bodies in the header).

    2. Create a source file named "temputils.c" that:
       - #includes "temputils.h".
       - Contains the actual function BODIES for celsiusToFahrenheit
         and describeTemperature (copy them from below, then delete
         them from this file).

    3. Rewrite THIS file (rename it main.c, or just edit it in place)
       so it #includes "temputils.h" instead of defining the functions
       itself, and keeps only main().

    4. Compile all three files together and confirm the output is
       EXACTLY the same as it is right now:

           gcc main.c temputils.c -o program

When you're done, check your work: the program's output must match
the unsplit version exactly. Your file names and wording can differ, but
the split (declarations in the header, bodies in the source file, guard
in place) should hold. Ask your instructor for the reference split.
*/

#define FREEZING_POINT_C 0

double celsiusToFahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

const char *describeTemperature(double celsius) {
    if (celsius < FREEZING_POINT_C) {
        return "below freezing";
    } else if (celsius == FREEZING_POINT_C) {
        return "exactly freezing";
    } else {
        return "above freezing";
    }
}

int main(void) {
    double readings[] = {-5.0, 0.0, 20.0, 37.5};
    int count = 4;

    for (int i = 0; i < count; i++) {
        double c = readings[i];
        double f = celsiusToFahrenheit(c);
        printf("%.1fC = %.1fF (%s)\n", c, f, describeTemperature(c));
    }

    return 0;
}
