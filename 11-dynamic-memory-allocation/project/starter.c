#include <stdio.h>
#include <stdlib.h>

// TODO: build your dynamic scoreboard here.
// See project/README.md for the full requirements.

int main(void) {
    int count;
    printf("How many players? ");
    scanf("%d", &count);

    // TODO: malloc an array of `count` ints for scores. Check for NULL.

    // TODO: read a starting score for each player.

    // TODO: print the scoreboard.

    // TODO: ask if the user wants to add more players. If yes, realloc
    // the array to fit the extra slots (into a temporary pointer first!),
    // read scores for the new players, and print the updated scoreboard.

    // TODO: free the array exactly once before the program exits.

    return 0;
}
