#include <stdio.h>

int main(void) {
    int dayNumber = 6; // Saturday

    // This switch is missing its break statements on purpose. Compile and
    // run this file exactly as written first, and see if the output
    // surprises you.
    switch (dayNumber) {
        case 6:
            printf("Saturday: weekend movie night.\n");
        case 7:
            printf("Sunday: weekend movie night.\n");
        default:
            printf("Some other day: no movie night.\n");
    }

    /*
    What happened? All three lines printed, even though dayNumber is only
    6. Without break, a switch doesn't stop after a matching case -- it
    "falls through" and keeps running every case AFTER the match too, all
    the way to the end (or until it hits a break).

    Fix it: add `break;` after each case's printf (the way 02_switch.c
    does) and recompile. You should then see ONLY the Saturday line.

    This is one of the most common beginner switch bugs -- when a switch
    seems to print "too much," missing break statements are almost always
    the reason.
    */

    return 0;
}
