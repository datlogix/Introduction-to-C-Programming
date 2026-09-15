#include <stdio.h>

#define MAX_PLAYERS 10

// TODO: write a sorting function here, e.g.
//   void insertionSort(int arr[], int size)
// (bubble, selection, and insertion sort are all fine choices -- see
// the module README/examples for all three if you want a reminder).

// TODO: write your own binarySearch(int arr[], int size, int target)
// here, returning the found index or -1 (you already built this in
// exercises/exercise1.c -- reuse it).

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int scores[MAX_PLAYERS];
    int numPlayers;

    printf("How many players? (max %d) ", MAX_PLAYERS);
    scanf("%d", &numPlayers);

    for (int i = 0; i < numPlayers; i++) {
        printf("Enter score for player %d: ", i + 1);
        scanf("%d", &scores[i]);
    }

    printf("\nUnsorted scores: ");
    printArray(scores, numPlayers);

    // TODO: sort scores[0..numPlayers-1] with your sorting function.

    printf("Sorted leaderboard (lowest to highest): ");
    printArray(scores, numPlayers);

    int target;
    printf("\nLook up a score to find its rank: ");
    scanf("%d", &target);

    // TODO: binary-search scores for target and report its position.
    // Remember: index 0 in the sorted array is the LOWEST score, so
    // you'll probably want to turn the index into a rank (e.g.
    // "1st place" = the highest score = the LAST index).

    return 0;
}
