#include <stdio.h>

int main(void) {
    // while checks its condition BEFORE every run of the loop body --
    // including the very first time. If the condition starts out false,
    // the body never runs at all.
    printf("-- while loop: countdown --\n");
    int countdown = 5;
    while (countdown > 0) {
        printf("%d...\n", countdown);
        countdown = countdown - 1; // without this, the loop never ends!
    }
    printf("Liftoff!\n\n");

    // do-while checks its condition AFTER running the body -- so the
    // body always runs at least once, no matter what the condition is.
    printf("-- do-while loop: runs once no matter what --\n");
    int attempts = 10;
    do {
        printf("This prints even though attempts (%d) is already >= 3.\n", attempts);
        attempts = attempts + 1;
    } while (attempts < 3);

    // Compare: the same condition with a plain while never runs at all.
    printf("\n-- the same condition with a plain while --\n");
    int attempts2 = 10;
    while (attempts2 < 3) {
        printf("You will never see this line.\n");
        attempts2 = attempts2 + 1;
    }
    printf("(nothing printed above -- the condition was false from the start)\n");

    return 0;
}
