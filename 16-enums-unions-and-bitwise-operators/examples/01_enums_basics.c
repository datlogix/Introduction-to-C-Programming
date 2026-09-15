#include <stdio.h>

// An enum names a fixed set of related integer constants. Unless you say
// otherwise, members are auto-numbered starting at 0.
enum GameState { MENU, PLAYING, PAUSED, GAME_OVER };

// You can also assign your own values explicitly.
enum Direction { NORTH = 1, SOUTH = 2, EAST = 4, WEST = 8 };

int main(void) {
    printf("Auto-numbered from 0:\n");
    printf("MENU = %d\n", MENU);
    printf("PLAYING = %d\n", PLAYING);
    printf("PAUSED = %d\n", PAUSED);
    printf("GAME_OVER = %d\n", GAME_OVER);

    enum GameState state = PLAYING;
    printf("\ncurrent state, printed with %%d: %d\n", state);

    if (state == PLAYING) {
        printf("The game is currently playing.\n");
    }

    printf("\nExplicitly assigned values:\n");
    printf("NORTH = %d, SOUTH = %d, EAST = %d, WEST = %d\n", NORTH, SOUTH, EAST, WEST);

    return 0;
}
