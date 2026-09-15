#include <stdio.h>

/*
Create a small text file first, e.g.:

    echo "the quick brown fox jumps over the lazy dog" > sample.txt

Then run:

    ./a_real_cli_tool_word_counter sample.txt

Prints the number of whitespace-separated words in the file, then exits
immediately -- no menu, no "press any key," no "run again? (y/n)" like
every interactive program earlier in this course. Read input, do ONE
job, print output, exit.
*/

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: could not open file \"%s\".\n", argv[1]);
        return 1;
    }

    int wordCount = 0;
    int insideWord = 0;
    int c;

    while ((c = fgetc(file)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            insideWord = 0;
        } else if (!insideWord) {
            insideWord = 1;
            wordCount++;
        }
    }

    fclose(file);

    printf("%d\n", wordCount);
    return 0;
}
