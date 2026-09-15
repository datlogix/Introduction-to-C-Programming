# Module 14 Project — Personal Toolbox Library

The hook at the top of this module took one file and split it into
pieces you could hand to a teammate. This project asks you to build
something with that same shape from scratch: a small **library** of
general-purpose helper functions, declared in one header and implemented
in one source file, that `main.c` (or any future program of yours) can
pull in with a single `#include`.

## Requirements

Build a toolbox of exactly **five** functions: two math helpers, two
string helpers, and one more of either kind, your choice. A reasonable
set (feel free to substitute your own ideas for the fifth):

1. `int maxInt(int a, int b)` — returns whichever argument is larger.
2. `int clampInt(int value, int min, int max)` — restricts `value` to
   the range `[min, max]` (returns `min` if it's too small, `max` if
   it's too big, otherwise `value` unchanged).
3. `void toUpperCase(char *str)` — uppercases a string **in place**
   (modifies the array the caller passed in, like the string functions
   in Module 5 — no return value needed).
4. `int countChar(const char *str, char target)` — counts how many
   times `target` appears in `str`.
5. Your choice — a fifth helper of either kind. A palindrome checker, a
   string-reversing function, a `minInt`, an average-of-array function
   — anything genuinely reusable.

Your program must:

1. Declare all five functions in `toolbox.h`, protected by an **include
   guard**, with prototypes only — no function bodies in the header.
2. Define all five function bodies in `toolbox.c`, which `#include`s
   `toolbox.h`.
3. In `main.c`, `#include "toolbox.h"` and call **every** function at
   least once, `printf`-ing each result so someone can see your whole
   library work just by running the program — without ever opening
   `toolbox.c`.
4. Compile with a **Makefile** (`all:` target) rather than a hand-typed
   `gcc` command.
5. Use at least one `#define` constant *or* explain in a comment why
   your toolbox didn't need one — most small libraries end up needing
   at least one shared constant eventually.

## Ideas if you're stuck

- Struggling to think of a fifth function? Look back at Module 5
  (Arrays & Strings) for inspiration — a vowel counter, a string
  reverser, a simple "is this a palindrome" checker all fit this
  project well.
- `toUpperCase` and a string-reversing function both modify a `char`
  array through a pointer parameter, the same way functions in Module 7
  modified values through pointers — nothing new is required, just a
  loop and array indexing.
- Unsure what counts as a "good" helper function? A good rule: could a
  future you, working on a *completely different* program, drop
  `toolbox.h` and `toolbox.c` into it and find these functions useful
  immediately? If yes, it belongs in a toolbox.

## Getting started

Open [`toolbox.h`](toolbox.h), [`toolbox.c`](toolbox.c), and
[`main.c`](main.c) — each has TODO comments marking what to add. Build
up one function at a time: add its prototype to `toolbox.h`, its body to
`toolbox.c`, a call to it in `main.c`, then compile and test before
moving to the next one.

```bash
make
./toolbox
```

If you change the Makefile or add files, `make clean` removes the built
executable so you can rebuild from scratch.

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 14 project: personal toolbox library"
git push
```

Next: **[Module 15 — Debugging & Memory Safety](../../15-debugging-and-memory-safety/README.md)**.
