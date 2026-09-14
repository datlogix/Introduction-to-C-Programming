#include <stdio.h>

int main(void) {
    printf("Oops\n")
    return 0;
}

/*
Try compiling this file as-is:

    gcc 04_broken_missing_semicolon.c -o broken

Read the error message gcc gives you. It will point near the `return`
line, but the real mistake is the missing semicolon on the line ABOVE it.
Fix it, recompile, and confirm you get a clean build with no errors.
*/
