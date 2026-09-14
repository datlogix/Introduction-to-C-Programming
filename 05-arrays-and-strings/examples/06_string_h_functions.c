#include <stdio.h>
#include <string.h>

int main(void) {
    // <string.h> gives you ready-made functions for common string tasks,
    // so you don't have to write your own loops for every one of these.

    // strlen: how many real characters are in the string (NOT counting
    // the invisible '\0' at the end).
    char city[20] = "Kumasi";
    printf("strlen(\"%s\") = %zu\n", city, strlen(city));

    // strcpy: copies one string into another array. The destination array
    // must be big enough to hold the source string PLUS its '\0'.
    char copy[20];
    strcpy(copy, city);
    printf("copy = %s\n", copy);

    // strcmp: compares two strings. It returns 0 if they are EXACTLY
    // equal -- you cannot compare C-strings with == like numbers, that
    // would just compare where they live in memory, not their contents.
    char guess[20] = "Kumasi";
    if (strcmp(guess, city) == 0) {
        printf("\"%s\" matches \"%s\"\n", guess, city);
    } else {
        printf("\"%s\" does NOT match \"%s\"\n", guess, city);
    }

    // strcmp also tells you alphabetical order: a negative result means
    // the first string comes before the second, positive means after.
    char other[20] = "Accra";
    int result = strcmp(other, city); // "Accra" vs "Kumasi"
    printf("strcmp(\"%s\", \"%s\") = %d (negative means \"%s\" comes first)\n",
           other, city, result, other);

    // strcat: appends one string onto the END of another, right before
    // where the first string's '\0' used to be. The destination array
    // must have enough spare room for the extra characters plus '\0'.
    char greeting[40] = "Welcome to ";
    strcat(greeting, city);
    printf("%s\n", greeting);

    return 0;
}
