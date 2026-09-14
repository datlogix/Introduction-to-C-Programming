#include <stdio.h>
#include <string.h>

int main(void) {
    // In Module 3 you used scanf("%d", ...) and scanf("%f", ...) to read
    // numbers. Reading a STRING with scanf("%s", ...) is risky:
    //   1. It stops at the first space, so "Kofi Mensah" becomes just
    //      "Kofi" -- the rest gets left for the next read.
    //   2. It has no idea how big your array is, so a long enough input
    //      can overflow the buffer -- writing past the end of the array,
    //      exactly the danger from the last example.
    //
    // fgets() fixes both problems: it reads a whole line, and you tell it
    // exactly how many bytes it's allowed to write.
    char name[20];

    printf("What is your name? ");
    fgets(name, sizeof(name), stdin);
    // sizeof(name) is 20 here -- fgets will never write more than that,
    // no matter how much the user types. This is the safe habit to build.

    // fgets keeps the newline character the user typed (from pressing
    // Enter) at the end of the string, unlike scanf. That newline is
    // usually not what you want, so it's common to strip it off:
    name[strcspn(name, "\n")] = '\0';
    // strcspn(name, "\n") returns the index of the first '\n' in name.
    // Overwriting that spot with '\0' shortens the string right there,
    // cutting the newline off.

    printf("Hello, %s! That's %zu characters.\n", name, strlen(name));

    return 0;
}
