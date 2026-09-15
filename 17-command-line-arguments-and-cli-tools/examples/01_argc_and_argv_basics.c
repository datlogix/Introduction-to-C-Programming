#include <stdio.h>

/*
Run this with a few different sets of arguments and compare the output --
no changes to the code between runs, only what you type after the
program name:

    ./argc_and_argv_basics
    ./argc_and_argv_basics hello
    ./argc_and_argv_basics hello world 123
*/

int main(int argc, char *argv[]) {
    printf("argc = %d\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = \"%s\"\n", i, argv[i]);
    }

    printf("\nargv[0] is always the program's own name/path -- \"%s\" here.\n", argv[0]);
    printf("The first REAL argument the user typed, if any, is argv[1].\n");
    printf("argc counts argv[0] too, so \"%d real argument(s) were given.\"\n", argc - 1);

    return 0;
}
