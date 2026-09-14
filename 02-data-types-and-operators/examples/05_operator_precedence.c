#include <stdio.h>

int main(void) {
    // Just like in math class: * and / run before + and -.
    printf("2 + 3 * 4   = %d (multiplication happens first)\n", 2 + 3 * 4);
    printf("(2 + 3) * 4 = %d (parentheses override the default order)\n", (2 + 3) * 4);

    printf("10 - 4 / 2   = %d (division happens first)\n", 10 - 4 / 2);
    printf("(10 - 4) / 2 = %d\n", (10 - 4) / 2);

    // When you're not 100% sure how an expression will be evaluated,
    // add parentheses. It costs nothing and removes all doubt.
    return 0;
}
