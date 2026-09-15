# Module 15 Project — Bug Hunt

The module hook showed you a one-line crash with no clues, and then the
same crash again with gdb pointing straight at the guilty line in
seconds. This project scales that up: one small program, **three**
separate bugs, and the job of finding and fixing all of them the same
way -- with tools, not guesswork.

## Requirements

Your program must:

1. Start from [`bug_hunt.c`](bug_hunt.c) as provided. Do **not** rewrite
   it from scratch -- the bugs are specific and findable exactly as
   written.
2. Find and fix all **three** bugs:
   - A **segfault** -- the program crashes before reaching the end of
     `main()`. Use `gcc -g` and `gdb` to find the exact crashing line
     (`run`, then `bt` for a backtrace).
   - A **memory leak** -- one allocation is never freed. Use `valgrind`
     (or a manual audit of every `malloc`/`free` pair, if `valgrind`
     isn't available on your machine) to find it.
   - An **uninitialized value read** -- a variable is used before it's
     ever given a value, producing a nonsense result. `valgrind` flags
     this directly ("Use of uninitialised value"); `gcc -Wall` may also
     warn about it at compile time depending on the exact code shape --
     read your compiler warnings, they're free hints.
3. Fix the crash **first**. The program currently stops partway through
   `main()`, which means the tools can only tell you what happened
   *before* the crash. Once it runs to completion, you'll have a full,
   clean picture to check for the other two.
4. In your own `README.md` in this `project/` folder (rename or replace
   this one, or add a new file -- either is fine, just make it clear),
   document, for **each** of the three bugs:
   - What it was.
   - Which tool or technique found it (`gdb`, `valgrind`, or a manual
     audit -- and if you used a manual audit because `valgrind` wasn't
     available, say so).
   - The one- or two-line fix.
5. The fixed program must compile with `gcc -Wall -g` with **no
   warnings**, and run to completion printing a correct, sensible
   average and report.

## Ideas if you're stuck

- Work top to bottom, in the order the program actually executes:
  `createScoreArray` → `averageScore` → `printReport` →
  `announceWinner`. The crash is in the last function called, which is
  exactly why the first two bugs' bad output still gets printed before
  everything stops.
- For the segfault: `break main`, then `next` your way through `main()`
  one call at a time, watching which call never returns.
- For the leak: read every function that calls `malloc` and ask "where
  is this pointer's matching `free`?" If you can't find one anywhere in
  the program, that's your leak, no tool required to *confirm* it --
  though `valgrind` will tell you exactly which line allocated it.
- For the uninitialized read: look at every local variable declared
  without `= 0` (or another starting value) right away. Is it *always*
  written to before it's first read, on every possible path through the
  function?
- If `valgrind` isn't available to you, re-read Module 15's platform
  note in the main README for the manual-audit checklist to fall back
  on.

## Getting started

```bash
cd project
gcc -g -Wall bug_hunt.c -o bug_hunt
./bug_hunt
```

Run it once as-is first and watch what happens (and where it stops) --
that first crash is your starting clue, exactly like the module hook.

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 15 project: bug hunt"
git push
```

Next: **[Module 16 — Enums, Unions & Bitwise Operators](../../16-enums-unions-and-bitwise-operators/README.md)**.
