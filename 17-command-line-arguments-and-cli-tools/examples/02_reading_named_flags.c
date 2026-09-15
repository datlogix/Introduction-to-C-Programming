#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
This is the "greet" tool from this module's README hook. Run it with
different arguments and compare:

    ./reading_named_flags Ama
    ./reading_named_flags Kwame --shout

Same compiled program, zero code changes, different behavior -- driven
entirely from outside itself by the arguments you type.
*/

int main(int argc, char *argv[]) {
    // Always check argc BEFORE indexing into argv -- argv[1] doesn't
    // exist if the user typed no arguments at all (Module 5's
    // array-bounds lesson applies here too).
    if (argc < 2) {
        printf("Usage: %s <name> [--shout]\n", argv[0]);
        return 1;
    }

    char *name = argv[1];
    int shout = 0;

    // Look at every argument AFTER the name for a recognized flag.
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--shout") == 0) {
            shout = 1;
        } else {
            printf("Unknown option: %s\n", argv[i]);
        }
    }

    if (shout) {
        printf("HELLO, ");
        for (int i = 0; name[i] != '\0'; i++) {
            putchar(toupper(name[i]));
        }
        printf("!!!\n");
    } else {
        printf("Hello, %s!\n", name);
    }

    // Real-world C programs usually parse flags like --shout with the
    // standard library's getopt() / getopt_long() instead of a
    // hand-rolled strcmp loop -- worth looking up once this feels
    // comfortable, but not necessary to get started.

    return 0;
}
