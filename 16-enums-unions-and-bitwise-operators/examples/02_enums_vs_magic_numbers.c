#include <stdio.h>

enum GameState { MENU, PLAYING, PAUSED, GAME_OVER };

// The "before" version: works, but only readable if you've memorized
// which number means what. Nothing here tells you PLAYING is 1.
void describeStateMagicNumber(int state) {
    if (state == 0) {
        printf("[magic number] In the menu.\n");
    } else if (state == 1) {
        printf("[magic number] Playing the game.\n");
    } else if (state == 2) {
        printf("[magic number] Paused.\n");
    } else if (state == 3) {
        printf("[magic number] Game over.\n");
    }
}

// The "after" version: self-documenting. You can read the comparisons
// out loud and they make sense without knowing any numbers at all.
void describeStateEnum(enum GameState state) {
    if (state == MENU) {
        printf("[enum] In the menu.\n");
    } else if (state == PLAYING) {
        printf("[enum] Playing the game.\n");
    } else if (state == PAUSED) {
        printf("[enum] Paused.\n");
    } else if (state == GAME_OVER) {
        printf("[enum] Game over.\n");
    }
}

int main(void) {
    describeStateMagicNumber(1);
    describeStateEnum(PLAYING);

    // Enums are really just ints under the hood -- that's their convenience
    // (ordinary integer comparisons, easy to print) AND their limitation:
    // the compiler won't stop you from putting a nonsense value in one.
    enum GameState sneaky = 99;
    printf("\nA plain int assigned into an enum variable -- compiles fine: %d\n", sneaky);

    return 0;
}
