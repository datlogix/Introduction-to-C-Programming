#include <stdio.h>

int main(void) {
    // Back in Module 2/3 you met a single character, like this:
    char grade = 'A';           // single quotes, ONE character, no \0
    printf("Grade: %c\n", grade);

    // A "string" in C is just an array of chars, printed with %s instead
    // of %c. Double quotes, and it can hold many characters:
    char name[20] = "Ama";

    // "Ama" is 3 letters, but C secretly stores a 4th, invisible character
    // right after them: '\0', the NULL TERMINATOR. It marks "the string
    // ends here" and is what printf/strlen/etc. look for. Without it,
    // functions that expect a string would keep reading past your data
    // into whatever memory comes next -- more undefined behavior.
    //
    // So name[20] actually looks like this in memory:
    //   name[0]='A' name[1]='m' name[2]='a' name[3]='\0' name[4..19]=unused
    printf("Name: %s\n", name);
    printf("name[0] = %c, name[3] is the invisible null terminator\n",
           name[0]);

    // The array is sized 20, but the STRING inside it is only "Ama" (3
    // characters). Everything from the null terminator onward is unused
    // space, reserved in case you want to store a longer name later.
    // %s will only ever print up to the first '\0' it finds.

    // Careful: an array like char name[20] can NEVER hold a string longer
    // than 19 real characters -- you must always leave room for the '\0'.

    return 0;
}
