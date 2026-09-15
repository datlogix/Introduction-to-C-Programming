#include <stdio.h>
#include <stdlib.h>

/*
A MEMORY LEAK happens when you malloc/calloc/realloc a block and lose
every pointer to it before calling free -- the memory stays reserved for
the rest of the program's run, but nothing can ever reach it again to
give it back. A leak doesn't crash your program immediately (which is
what makes it dangerous) -- it just quietly wastes more and more memory
the longer the program runs.

We demonstrate this SAFELY: leaking a bounded, tiny amount of memory a
few times (a handful of ints) is harmless and won't crash anything, so
you can watch the broken version run and then compare it to the fixed
version. This is not something you'd want to do in a long-running or
real program -- it's here purely so you can see the shape of the bug.

--- BROKEN (leaks memory every call -- shown for comparison, not run) ---

void leakyAllocate(void) {
    int *data = malloc(sizeof(int) * 10);
    if (data == NULL) {
        return;
    }
    data[0] = 42;
    // BUG: no free(data) here. When this function returns, the local
    // variable `data` (the only pointer to that block) disappears, but
    // the block itself is still marked "in use" on the heap forever.
    // Call this function 1,000 times and you've leaked 1,000 blocks with
    // no way to ever get any of them back.
}

--- FIXED ---
*/

void allocateAndFree(void) {
    int *data = malloc(sizeof(int) * 10);
    if (data == NULL) {
        return;
    }
    data[0] = 42;

    // ... use data here ...

    free(data); // matching free before the pointer goes out of scope
}

int main(void) {
    // Call the fixed version a few times -- each call allocates AND frees,
    // so no memory is leaked no matter how many times we call it.
    for (int i = 0; i < 5; i++) {
        allocateAndFree();
    }

    printf("Allocated and freed memory 5 times -- nothing leaked.\n");
    printf("Compare this to the commented-out leakyAllocate() above:\n");
    printf("that version would lose a block every single call.\n");

    return 0;
}
