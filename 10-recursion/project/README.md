# Module 10 Project — Recursive Fractal Pattern Printer

Nested shapes — a box within a box within a box — are one of the most
satisfying things to draw recursively, because the pattern really is
defined in terms of a smaller version of itself: "a nested square of
depth `n` is a border, with a nested square of depth `n - 1` inside it."

## Requirements

Your program must:

1. Ask the user for a **depth** (a positive integer) using `scanf`.
2. Use a **recursive function** — not a loop — to print a nested pattern
   that many layers deep. A nested-brackets pattern is the simplest
   version:

   ```
   Depth 4 might print:
   ( ( ( ( * ) ) ) )
   ```

3. Include a real **base case** (depth `0` or `1`) and a recursive case
   that makes visible progress toward it.
4. Handle depth `0` gracefully (print something sensible, don't crash).
5. Include at least one comment explaining *why* your base case is what
   it is.

## Ideas if you're stuck

- Nested brackets or parentheses, as above.
- A recursive "staircase" of indented asterisks, one more per level.
- A recursive countdown-and-count-back-up pattern, printing the number
  on the way in *and* on the way out (like
  [`examples/01_countdown_no_loop.c`](../examples/01_countdown_no_loop.c)).
- Concentric ASCII squares, if you want more of a challenge.

## Getting started

Open [`starter.c`](starter.c) and build inside `main()` and your own
recursive function. Compile and run often — test with a small depth (2
or 3) before trying something large.

```bash
gcc starter.c -o fractal
./fractal
```

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 10 project: recursive fractal pattern printer"
git push
```

Next: **[Module 11 — Dynamic Memory Allocation](../../11-dynamic-memory-allocation/README.md)**.
