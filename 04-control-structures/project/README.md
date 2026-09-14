# Module 4 Project — Number Guessing Game

The computer picks a secret number between 1 and 100 using `rand()`. You
guess it, and after every guess the program tells you whether to guess
higher or lower. When you get it right, it tells you how many guesses it
took. This is the classic project for control structures because it uses
almost everything from this module at once: a loop that repeats an
unknown number of times, `if`/`else` to compare the guess, and `rand()` to
pick the secret number.

## Requirements

Your program must:

1. Pick a secret number between 1 and 100 (inclusive) using `rand()`,
   seeded with `srand(time(NULL))` so it's different every run.
2. Use a loop (`while` or `do-while`) that keeps asking the player to
   guess until they get it right.
3. Read each guess with `scanf`.
4. After each guess, print exactly one of:
   - `"Higher!"` if the guess is too low,
   - `"Lower!"` if the guess is too high,
   - a success message if the guess is correct.
5. Count how many guesses the player took, and print that count once the
   game ends, e.g. `"You got it in 6 guesses."`

## Ideas if you're stuck

- Add a guess limit (e.g. 10 tries) — use `break` to end the game early
  if the player runs out, and tell them the number they missed.
- Wrap the whole game in an outer loop that asks "Play again? (1 = yes,
  0 = no)" after each round, so the player can keep playing without
  restarting the program.
- Print how far off the last guess was (e.g. `"Lower! (you're within 5)"`)
  once you're comfortable with the basic version.

## Getting started

Open [`starter.c`](starter.c) and build inside `main()`, following the
TODO comments in order. Compile and run often — test after adding just
the random number, then again after adding the loop, rather than writing
the whole thing before testing anything.

```bash
gcc starter.c -o guess
./guess
```

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 4 project: number guessing game"
git push
```
