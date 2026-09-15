// The "after" version: same program, split into pieces. main.c now only
// has to know WHAT printReport() does (from mathreport.h), not HOW.
//
// "mathreport.h" -- double quotes, because it's OUR file, sitting right
// here in this project directory. The compiler looks in the project
// directory first for quoted includes.
// <stdio.h>      -- angle brackets, because it's a SYSTEM header that
// ships with the compiler; the compiler looks in its standard library
// locations for angle-bracket includes.
#include <stdio.h>
#include "mathreport.h"

int main(void) {
    printReport(4);
    printReport(7);
    return 0;
}
