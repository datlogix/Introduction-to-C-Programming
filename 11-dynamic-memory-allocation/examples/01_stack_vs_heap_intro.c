#include <stdio.h>
#include <stdlib.h>

/*
This file is a small, concrete illustration of stack vs. heap -- not a
deep dive into memory layout, just enough to see the difference.

- `stackValue` below is a normal local variable. It lives on the STACK,
  in the stack frame for main() (Module 10 covered stack frames). It's
  created automatically when main() starts and destroyed automatically
  when main() returns. You never manage it yourself.
- `heapValue` is a pointer to an int that we asked for explicitly with
  malloc(). That int lives on the HEAP -- a separate region of memory
  that stays allocated until YOU free it, no matter what functions come
  and go. Nothing frees it for you.
*/

int main(void) {
    int stackValue = 42;                       // lives on the stack
    int *heapValue = malloc(sizeof(int));       // lives on the heap

    if (heapValue == NULL) {                    // ALWAYS check malloc's result
        printf("malloc failed -- out of memory.\n");
        return 1;
    }

    *heapValue = 99;

    printf("stackValue = %d (address on the stack: %p)\n", stackValue, (void *)&stackValue);
    printf("*heapValue = %d (address on the heap:  %p)\n", *heapValue, (void *)heapValue);

    // The two addresses printed above are typically far apart -- the
    // stack and the heap are different regions of your program's memory.
    // The exact addresses don't matter; what matters is that heapValue
    // points to memory YOU are now responsible for.

    free(heapValue);   // give the heap memory back -- required, nothing does this automatically
    heapValue = NULL;  // good habit: a freed pointer shouldn't keep pointing at that memory

    return 0;
}
