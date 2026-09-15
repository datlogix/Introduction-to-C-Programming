# Module 18 Project — Leaderboard Sorter

The hook at the top of this module's README showed the payoff of a
sorted array: binary search finding one value out of a thousand in just
10 comparisons instead of 1,000. This project puts that whole pipeline
in your own hands — take a messy, unsorted list of player scores, sort
it yourself, and then use binary search to instantly look up where any
given score ranks.

## Requirements

Your program must:

1. Ask the user how many players there are, then read that many scores
   with `scanf` into an array (a small fixed-size array, e.g. 10 players
   max, is fine).
2. Sort the scores using a **sorting function you write yourself** —
   bubble sort, selection sort, or insertion sort, your choice (a couple
   of ideas below if you want to mix it up).
3. Print the sorted leaderboard.
4. Ask the user for a score to look up, then find it with a
   **binary search function you write yourself** (reuse your
   `binarySearch` from `exercises/exercise1.c` — this is exactly what
   it's for).
5. Report the player's **rank** based on the index binary search
   returns (e.g. the highest score is rank #1 — remember your sort
   puts the *lowest* score at index 0, so rank and index run in
   opposite directions).
6. Handle a looked-up score that isn't in the leaderboard gracefully —
   print a clear message, don't crash and don't print a fake rank.

## Ideas if you're stuck

- Start with insertion sort if you want the simplest one to adapt —
  it's short, and [`examples/05_insertion_sort.c`](../examples/05_insertion_sort.c)
  is a complete reference.
- Not sure how to turn an index into a rank? If there are `n` players
  and a score is found at index `i` (0 = lowest), its rank is
  `n - i` (the highest score, at index `n - 1`, is rank `1`).
- Want a bonus challenge? Also print each player's *name* alongside
  their score by sorting a second array of strings in parallel with the
  scores array (swap both arrays together, at the same indexes, every
  time your sort swaps two scores).

## Getting started

Open [`starter.c`](starter.c) — it already handles reading the players
and their scores, and prompts for a score to look up. Fill in the
`TODO`s: your sort function, your `binarySearch` function, and the calls
that wire them into `main()`. Compile and run often, testing with a
small number of players (3 or 4) before trying more.

```bash
gcc starter.c -o leaderboard
./leaderboard
```

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 18 project: leaderboard sorter"
git push
```

Next: **[Module 19 — Part 2 Capstone Project](../../19-part-2-capstone-project/README.md)**.
