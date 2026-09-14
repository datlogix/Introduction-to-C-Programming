# Module 6 Project — Refactor the Number Guessing Game

Remember the hook at the top of this module's README? The receipt program
that did the exact same thing two ways — one messy, one clean? Now you're
doing that same move on a bigger, real program: your Module 4 Number
Guessing Game.

Open [`starter.c`](starter.c). It's a complete, correct, fully playable
guessing game — computer picks a secret number from 1 to 100, you guess
in a loop, it tells you too high / too low, and reports how many guesses
you needed once you win. Run it. It works.

The problem is `main()`. It reads input, validates it, compares it to the
secret number, *and* decides what to print — all tangled together in one
long function. Your job is to refactor it: same game, same behavior,
same output — cleaner code.

## Requirements

Your finished program must:

1. Have **at least three separate functions**, beyond `main()`:
   - One that gets a single valid guess from the player (it should keep
     re-prompting internally until the player enters a number from 1 to
     100 — `main()` should never see an invalid guess).
   - One that compares a guess to the secret number and reports how
     (too low / too high / correct) — without printing anything itself.
   - One that takes that comparison result and prints the matching
     message to the screen.
2. Keep `main()` short: it should mostly just call your functions in a
   loop and keep track of the guess count. It should **not** contain the
   `"Too low"` / `"Too high"` / range-validation `printf` calls directly
   — those belong inside your functions now.
3. Produce **exactly the same output text** as `starter.c` for the same
   sequence of guesses, including the out-of-range message and the final
   `"Correct! You guessed it in N tries."` line. (Try feeding both
   programs the same input and comparing — they should match.)
4. Use at least one **function prototype**, and give every function a
   name that says what it does.

## Ideas if you're stuck

Not sure how to split the logic? These signatures work well together:

```c
int getGuess(void);                  // prompts, validates, returns a guess 1-100
int checkGuess(int guess, int secret); // returns e.g. -1 (low), 0 (correct), 1 (high)
void printResult(int result);          // prints the message for that outcome
```

`main()` then becomes a short loop: call `getGuess()`, count it, call
`checkGuess()`, call `printResult()`, and stop once the result means
"correct" — printing your final "you win" line there.

## Getting started

Copy the game's logic out of `starter.c` piece by piece into functions —
don't rewrite it from memory. Compile and test after each small change,
comparing behavior against the original:

```bash
gcc starter.c -o starter_original
gcc refactored.c -o refactored   # after you've made your own copy/file
./starter_original
./refactored
```

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 6 project: refactor the guessing game"
git push
```
