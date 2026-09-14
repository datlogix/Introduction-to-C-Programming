#include <stdio.h>
#include <stddef.h>   // defines NULL

int main(void) {
    // A pointer that isn't ready to point at anything yet should be set to
    // NULL -- a special value meaning "this pointer points to nothing."
    int *p = NULL;

    printf("A fresh pointer, before pointing it anywhere, should be NULL.\n");

    // ALWAYS check before dereferencing a pointer you're not sure about.
    // Dereferencing NULL (or an uninitialized, "garbage" pointer that was
    // never set to anything) is undefined behavior -- it usually crashes
    // your program immediately (a "segmentation fault"), and even when it
    // doesn't crash, it can silently read or corrupt memory that isn't
    // yours.
    if (p != NULL) {
        printf("p points to: %d\n", *p);
    } else {
        printf("p is NULL -- skipping the dereference to avoid a crash.\n");
    }

    // Now point it at a real variable and check again.
    int age = 25;
    p = &age;

    if (p != NULL) {
        printf("p now points to a real variable: %d\n", *p);
    }

    // Uncomment the block below to see a crash for yourself (safely, in a
    // throwaway program) -- this is exactly the kind of bug the NULL check
    // above prevents:
    //
    // int *danger = NULL;
    // printf("%d\n", *danger);   // undefined behavior -- do NOT run this
    //                            // in real code without a NULL check first

    return 0;
}
