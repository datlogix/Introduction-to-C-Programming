#include <stdio.h>
#include <string.h>

// TODO: build your Mini Word-Count Tool below. See project/README.md
// for the full requirements.

int main(int argc, char *argv[]) {
    // TODO: check argc and print a usage message (then return 1) if no
    // filename was given, e.g.:
    //   Usage: ./wordcount <filename> [--lines] [--words] [--chars]

    // TODO: loop over argv[2..argc-1] to see which of --lines, --words,
    // and --chars were requested. If none were given, count all three.

    // TODO: open argv[1] with fopen() in "r" mode, and check the result
    // for NULL before using it (Module 8's rule).

    // TODO: read through the file ONE character at a time with fgetc(),
    // counting lines, words, and characters as you go:
    //   - characters: count every character fgetc() returns before EOF.
    //   - lines: count every '\n' you see.
    //   - words: count transitions from "not inside a word" to "inside
    //     a word", the same way examples/03 does it.

    // TODO: fclose() the file, then print only the counts that were
    // requested (or all three if no flags were given).

    return 0;
}
