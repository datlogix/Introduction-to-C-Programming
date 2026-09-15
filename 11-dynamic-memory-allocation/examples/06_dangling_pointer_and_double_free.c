#include <stdio.h>
#include <stdlib.h>

/*
Two closely related dangers, both undefined behavior (not a clean,
predictable error -- anything from garbage output to a crash to nothing
visibly wrong at all, which is what makes them so dangerous):

- DANGLING POINTER / USE-AFTER-FREE: once you free(ptr), the memory
  ptr points to is no longer yours. ptr itself still holds the old
  address (freeing a pointer does NOT change the pointer variable), but
  reading or writing through it now is undefined behavior -- that memory
  may already have been handed to something else.
- DOUBLE FREE: calling free() twice on the same block. The heap's
  internal bookkeeping isn't designed to be told "give this back" twice,
  and doing so corrupts that bookkeeping -- undefined behavior again.

Both bugs below are shown safely disabled -- reading through freed
memory or freeing something twice is exactly the kind of "might work,
might not, might corrupt something else entirely" behavior that isn't
worth triggering for real. The fix for both is the same simple habit:
set a pointer to NULL immediately after freeing it. free(NULL) is
explicitly safe and does nothing, so a second accidental free becomes
harmless, and using a NULL pointer crashes immediately and obviously
instead of silently corrupting memory.

--- BROKEN (do not uncomment -- undefined behavior) ---

int *ptr = malloc(sizeof(int));
*ptr = 5;
free(ptr);
printf("%d\n", *ptr);  // BUG: use-after-free -- ptr is dangling now
free(ptr);              // BUG: double free -- already freed once above

--- FIXED ---
*/

int main(void) {
    int *ptr = malloc(sizeof(int));
    if (ptr == NULL) {
        return 1;
    }

    *ptr = 5;
    printf("Before freeing: *ptr = %d\n", *ptr);

    free(ptr);
    ptr = NULL; // the fix: nothing can accidentally dereference or re-free the old address

    // Because ptr is now NULL, both of these mistakes become impossible
    // to make silently:
    if (ptr != NULL) {
        printf("This never runs -- ptr is NULL, so we can't use-after-free.\n");
    }

    free(ptr); // safe: free(NULL) is explicitly a no-op, not a double free

    printf("Freed once, set to NULL, and a second free(ptr) was harmless.\n");

    return 0;
}
