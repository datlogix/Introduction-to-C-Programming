#include <stdio.h>

// Each flag claims one bit. Powers of two guarantee the bits never overlap.
#define FLAG_READ    (1 << 0)  // 1  -- 00000001
#define FLAG_WRITE   (1 << 1)  // 2  -- 00000010
#define FLAG_EXECUTE (1 << 2)  // 4  -- 00000100

int main(void) {
    int permissions = 0;
    printf("start:            %d\n", permissions);

    // Set a flag: OR it in. Any bit already on stays on.
    permissions |= FLAG_READ;
    printf("after +READ:      %d\n", permissions);

    permissions |= FLAG_EXECUTE;
    printf("after +EXECUTE:   %d\n", permissions);

    // Check a flag: AND with the flag, see if anything survived.
    if (permissions & FLAG_READ) {
        printf("READ is set.\n");
    }
    if (!(permissions & FLAG_WRITE)) {
        printf("WRITE is NOT set.\n");
    }

    // Clear a flag: AND with the flag's bits flipped off (~FLAG_READ).
    permissions &= ~FLAG_READ;
    printf("after -READ:      %d\n", permissions);

    if (!(permissions & FLAG_READ)) {
        printf("READ is now cleared.\n");
    }
    if (permissions & FLAG_EXECUTE) {
        printf("EXECUTE is still set -- clearing READ didn't touch it.\n");
    }

    return 0;
}
