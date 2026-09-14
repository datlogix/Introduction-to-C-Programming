#include <stdio.h>

int main(void) {
    int scores[5] = {90, 85, 77, 60, 100};

    // scores has 5 slots: valid indexes are 0, 1, 2, 3, 4.
    // scores[5] does NOT exist -- but C will NOT stop you from writing
    // scores[5] anyway. There is no automatic bounds checking in C, unlike
    // many other languages. Reading or writing past the end of an array is
    // called "undefined behavior": the compiler is allowed to do literally
    // anything -- print a garbage number, silently corrupt some OTHER
    // variable sitting nearby in memory, work fine on your laptop and crash
    // on a friend's, or crash immediately. It is NEVER a helpful error
    // message. This is one of the most important safety habits in C.
    //
    // The line below is commented out on purpose -- uncomment it locally to
    // see what happens on YOUR machine (it's genuinely unpredictable, so we
    // don't run it here):
    //
    //     scores[5] = 999;   // DANGER: writes past the end of the array
    //     printf("%d\n", scores[7]);   // DANGER: reads garbage memory

    // The fix is always the same: never trust an index blindly. Check it
    // against the array's real size before you use it.
    int size = 5;
    int index = 5; // pretend this came from user input or a calculation

    if (index >= 0 && index < size) {
        printf("scores[%d] = %d\n", index, scores[index]);
    } else {
        printf("Index %d is out of bounds for an array of size %d.\n",
               index, size);
    }

    // Off-by-one is the classic bounds mistake: looping with "i <= size"
    // instead of "i < size" walks one slot too far. Always double check
    // your loop condition against the array's actual size.
    for (int i = 0; i < size; i++) {
        printf("safe access scores[%d] = %d\n", i, scores[i]);
    }

    return 0;
}
