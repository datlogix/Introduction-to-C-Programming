# Module 11 Project — Dynamic Scoreboard

The module hook asked "how many scores do you want to enter?" and then
allocated exactly that many slots instead of guessing a fixed array size.
This project extends that same idea into something closer to a real
program: a scoreboard that starts out sized for however many players you
have right now, and can **grow** with `realloc` if more players show up
later -- all without wasting memory up front or running out.

## Requirements

Your program must:

1. Ask the user how many players to start with (a positive integer) using
   `scanf`.
2. `malloc` exactly that many `int` score slots (use the
   `sizeof(int) * count` pattern from the examples), and check the result
   for `NULL` before using it.
3. Let the user enter a starting score for each player.
4. Print all current players and their scores, clearly labeled (e.g.
   `Player 1: 50`).
5. Ask the user if they want to add more players. If yes, ask how many
   more, then use `realloc` to grow the array by that many slots --
   **capture `realloc`'s return value in a temporary pointer, check it for
   `NULL`, and only then update your real pointer** (exactly like
   [`examples/04_realloc_growing_an_array.c`](../examples/04_realloc_growing_an_array.c)).
   Let the user enter scores for the new players too.
6. Print the full, updated scoreboard again.
7. `free()` the array exactly once before the program exits, no matter
   how many times it was grown -- there should be no memory leaks and no
   double frees.

## Ideas if you're stuck

- Keep two variables: how many slots you've allocated (`capacity`) and how
  many are actually filled (`count`) -- they're the same thing here since
  every slot gets a score immediately, but naming them separately makes
  the growth step easier to reason about.
- Write the "print the scoreboard" logic as its own loop you can call
  twice (once before growing, once after) instead of duplicating it.
- Test with a small number first (2 players, then add 1) before trying
  something bigger.
- If `realloc` ever fails in your testing, your program should still be
  able to free the *original* block and exit cleanly -- it must not lose
  the only pointer to memory that's still valid.

## Getting started

Open [`starter.c`](starter.c) and build out `main()`. Compile and run
often.

```bash
gcc starter.c -o scoreboard
./scoreboard
```

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 11 project: dynamic scoreboard"
git push
```

Next: **[Module 12 — Linked Lists](../../12-linked-lists/README.md)**.
