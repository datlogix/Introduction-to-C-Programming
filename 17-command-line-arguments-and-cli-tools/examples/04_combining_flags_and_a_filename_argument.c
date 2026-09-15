#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Create a small multi-line text file first, e.g.:

    printf "one\ntwo\nthree\nfour\nfive\nsix\n" > sample.txt

Then run:

    ./combining_flags_and_a_filename_argument sample.txt --lines 3
    ./combining_flags_and_a_filename_argument sample.txt

Prints the first N lines of the file. --lines takes the number of lines
as its own argument; without --lines, it defaults to 5.
*/

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename> [--lines N]\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int numLines = 5; // default when --lines isn't given

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--lines") == 0) {
            // --lines needs a number right after it. Check argc BEFORE
            // reading argv[i + 1] -- otherwise, if --lines is the very
            // last argument, we'd read past the end of argv.
            if (i + 1 >= argc) {
                printf("Error: --lines needs a number after it.\n");
                return 1;
            }
            // Arguments always arrive as strings -- atoi() converts a
            // digit string like "3" into the actual int 3.
            numLines = atoi(argv[i + 1]);
            i++; // skip the number we just consumed
        } else {
            printf("Unknown option: %s\n", argv[i]);
        }
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: could not open file \"%s\".\n", filename);
        return 1;
    }

    char line[256];
    int printed = 0;
    while (printed < numLines && fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        printed++;
    }

    fclose(file);
    return 0;
}
