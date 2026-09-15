# Module 11 — Dynamic Memory Allocation

## Hook: an array with no size guess anywhere in it

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int count;
    printf("How many scores do you want to enter? ");
    scanf("%d", &count);

    int *scores = malloc(sizeof(int) * count);  // exactly `count` slots -- not a guess
    if (scores == NULL) {
        printf("malloc failed.\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("Score %d: ", i + 1);
        scanf("%d", &scores[i]);
    }

    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += scores[i];
    }
    printf("You entered %d scores, totaling %d.\n", count, sum);

    free(scores);
    return 0;
}
```

```bash
gcc hook.c -o hook
./hook
```

Run it and enter `3` when asked, followed by 3 scores — it works. Now run
it again and enter `300`, followed by 300 scores — it *still* works, with
the exact same source code, no recompiling with a bigger number baked in.
Back in Module 5 you had to pick an array size up front, like
`int scores[100]`, and just hope it was big enough. This program has no
such guess anywhere in it: it asks the heap for *exactly* the number of
slots it needs, at the moment it finds out how many that is. By the end
of this module you'll understand exactly how `malloc` does that, and
you'll build a scoreboard that can even grow *after* it's already
allocated.

## Where variables actually live: stack vs. heap

Every "normal" variable you've written so far — including fixed-size
arrays like `int scores[100]` — lives on the **stack**: the same
per-function-call storage from Module 10's stack frames. Stack memory is
fast and fully automatic — it appears when a function starts and
disappears the instant that function returns — but its size has to be
known at compile time, which is exactly why `int scores[100]` needs a
fixed number in the brackets.

The **heap** is a separate, much larger pool of memory that isn't tied to
any function call. Memory on the heap is allocated on request, *while
your program is running*, and it stays reserved until you explicitly give
it back — nothing frees it automatically just because a function
returned. That trade means more responsibility (you must remember to free
it — more on that below) in exchange for a size that isn't locked in at
compile time. See
[`examples/01_stack_vs_heap_intro.c`](examples/01_stack_vs_heap_intro.c).

## Why fixed-size arrays fall short

`int scores[100]` forces a decision before you have any information: if
only 3 students show up, 97 slots sit there wasted; if 150 show up, the
array is simply too small and you're out of luck without editing the
source and recompiling. Dynamic memory allocation lets you make that
decision **at runtime**, based on real information like a `scanf` result
— exactly what the hook just did.

## `malloc`: asking the heap for memory

```c
int *numbers = malloc(sizeof(int) * count);
```

`malloc(size)` asks the heap for a block of `size` **bytes** and returns
a pointer to the start of that block. Two details matter every time you
call it:

- **Always combine it with `sizeof`.** `malloc(count)` would only ask for
  `count` *bytes*, not `count` ints — `malloc(sizeof(int) * count)` asks
  for enough bytes to hold `count` ints, whatever an `int`'s actual size
  happens to be on this machine. Read this pattern as "enough room for
  `count` of this type."
- **Always check the result for `NULL` before using it.** If the heap
  can't satisfy the request (memory really can run out), `malloc` returns
  `NULL` instead of crashing outright. Using that `NULL` pointer as if it
  pointed to real memory — writing through it — is what actually crashes
  the program, and it does so with a much more confusing error than a
  clean, deliberate check would have given you.

```c
if (numbers == NULL) {
    printf("Allocation failed.\n");
    return 1;
}
```

See [`examples/02_malloc_and_free_basics.c`](examples/02_malloc_and_free_basics.c),
which is the hook's pattern with the `free` half added in.

## `calloc`: malloc that zero-initializes

```c
int *counts = calloc(count, sizeof(int));
```

`calloc(count, size)` does almost the same job as `malloc`, with two
differences: it takes the item count and item size as two separate
arguments, and — this is the important part — **it guarantees every byte
of the block starts at zero.** `malloc` makes no such promise; the memory
it hands you contains whatever garbage values were already sitting there.
Assuming a freshly malloc'd array starts at zero is a classic bug: it can
look zeroed the first few times you run a program and then silently
contain garbage later, or on a different machine. If you need
zero-initialized memory, ask for it with `calloc` — don't hope for it
from `malloc`. See
[`examples/03_calloc_vs_malloc.c`](examples/03_calloc_vs_malloc.c).

## `realloc`: growing (or shrinking) a block you already have

```c
int *temp = realloc(scores, sizeof(int) * newSize);
if (temp == NULL) {
    // scores is STILL valid here -- realloc left it untouched on failure
    free(scores);
    return 1;
}
scores = temp;
```

`realloc(pointer, newSize)` resizes a block you previously got from
`malloc`, `calloc`, or `realloc` itself. It has two gotchas that cause
real bugs if you miss them:

- **It can move the block.** If the memory right after your current block
  isn't free, `realloc` allocates a new block elsewhere, copies your old
  data into it, and returns a pointer to the *new* location. You must
  capture that return value — continuing to use the old pointer afterward
  reads or writes memory that may no longer belong to you.
- **On failure it returns `NULL` — and leaves the original block alone.**
  If you write `scores = realloc(scores, newSize);` and it fails, you've
  just overwritten your only pointer to the original block with `NULL`.
  That original memory is still allocated and still has your data in it,
  but you can no longer reach it to use it *or* to free it — a leak.
  Always `realloc` into a temporary pointer, check the temporary for
  `NULL`, and only then assign it back to your real pointer.

See [`examples/04_realloc_growing_an_array.c`](examples/04_realloc_growing_an_array.c).

## `free`: giving memory back

```c
free(numbers);
numbers = NULL;
```

Heap memory is never returned automatically — you ask for it with
`malloc`/`calloc`/`realloc`, and you're on the hook for giving it back
with `free`. The rule is simple to state and easy to violate in a bigger
program: **every successful `malloc`, `calloc`, or `realloc` needs
exactly one matching `free`.** Not zero (that's a leak, next section).
Not two (that's a double free, below). Exactly one.

Setting the pointer to `NULL` immediately after freeing it isn't required
by the language, but it's a habit worth building now: it turns two
dangerous, silent bugs into a harmless no-op and an obvious crash,
covered next.

## Memory leaks

A **memory leak** happens when you allocate a block and lose every
pointer to it before calling `free` — usually because a function returns
without freeing something it allocated, or a pointer gets overwritten
before the block it pointed to was freed. The memory stays reserved for
the rest of the program's run; nothing can ever reach it again to give it
back. A leak doesn't crash your program on the spot, which is exactly
what makes it dangerous — it quietly wastes more memory the longer a
program runs, especially one that allocates repeatedly in a loop or
across many function calls.

[`examples/05_memory_leak_demonstration.c`](examples/05_memory_leak_demonstration.c)
shows the broken pattern (a function that mallocs and never frees) safely
disabled in a comment, next to the fixed version that actually runs.

## Dangling pointers and double frees

Two more dangers, both **undefined behavior** — not a clean, predictable
error, but anything from silently wrong output to a crash to nothing
visibly wrong at all until much later:

- A **dangling pointer** is a pointer whose memory has already been
  freed. `free(ptr)` releases the memory `ptr` points to, but it does
  *not* change `ptr` itself — the variable still holds that old address.
  Dereferencing it afterward (reading or writing through it) is a
  **use-after-free**: that memory may already have been handed to
  something else entirely.
- A **double free** is calling `free` twice on the same block. The heap's
  internal bookkeeping isn't designed to be told "here's this memory
  back" twice, and doing so corrupts that bookkeeping — undefined
  behavior again, and often not until much later in the program's run.

The fix for both is the habit from the previous section: **set a pointer
to `NULL` immediately after freeing it.** `free(NULL)` is explicitly
defined to do nothing, so an accidental second `free` becomes harmless,
and dereferencing a `NULL` pointer crashes immediately and obviously
instead of silently corrupting memory somewhere else. (A later module —
Module 15 — introduces tools that can catch leaks and invalid memory
access automatically; for now, the discipline in this module is what
keeps you safe.)

See [`examples/06_dangling_pointer_and_double_free.c`](examples/06_dangling_pointer_and_double_free.c).

## Common beginner mistakes

- **Forgetting to check `malloc`/`calloc`/`realloc` for `NULL`** before
  using the result — the single most common bug in this module.
- **Assuming `malloc`'d memory starts at zero.** It doesn't; use `calloc`
  if you need that guarantee.
- **Losing the original pointer on `realloc` failure** by writing
  `ptr = realloc(ptr, newSize);` directly instead of through a temporary
  pointer — this leaks the original block if `realloc` ever fails.
- **Mismatched allocation and freeing** — freeing something twice, never
  freeing it at all, or freeing a pointer that was never returned by
  `malloc`/`calloc`/`realloc` in the first place.
- **Using a pointer after freeing it** without setting it to `NULL` first
  — a dangling pointer that looks like it might still work, until it
  doesn't.
- **Forgetting the `sizeof(type) * count` pattern** and allocating the
  wrong number of *bytes* instead of the wrong number of *items*.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one — including the safely-disabled leak and
   dangling-pointer bugs in `05` and `06`, so you understand the danger
   without actually corrupting anything.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 11: dynamic memory allocation"
   git push
   ```

Next: **[Module 12 — Linked Lists](../12-linked-lists/README.md)**.
