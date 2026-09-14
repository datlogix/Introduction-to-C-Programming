# Module 4 — Control Structures

## Hook: Rock, Paper, Scissors vs. the computer

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(NULL));

    int playerChoice;
    printf("Rock (0), Paper (1), or Scissors (2)? ");
    scanf("%d", &playerChoice);

    int computerChoice = rand() % 3;

    printf("You chose:      ");
    if (playerChoice == 0) {
        printf("Rock\n");
    } else if (playerChoice == 1) {
        printf("Paper\n");
    } else {
        printf("Scissors\n");
    }

    printf("Computer chose: ");
    if (computerChoice == 0) {
        printf("Rock\n");
    } else if (computerChoice == 1) {
        printf("Paper\n");
    } else {
        printf("Scissors\n");
    }

    if (playerChoice == computerChoice) {
        printf("It's a tie!\n");
    } else if ((playerChoice == 0 && computerChoice == 2) ||
               (playerChoice == 1 && computerChoice == 0) ||
               (playerChoice == 2 && computerChoice == 1)) {
        printf("You win!\n");
    } else {
        printf("Computer wins!\n");
    }

    return 0;
}
```

```bash
gcc rps.c -o rps
./rps
```

Run it a few times and try all three choices. Two things in there are new:
`if` / `else if` / `else`, which decide which lines of code actually run,
and `rand()`, which gets you a random number. You've already met the
building blocks these depend on — Module 2's `==`, `&&`, and `||` are
exactly what's deciding the winner above. By the end of this module
you'll understand every line of this, and you'll build a full Number
Guessing Game using the same ideas in this module's project.

## Why control structures?

Every program you've written so far runs top to bottom, once, no
exceptions — line 1, then line 2, then line 3, done. That's fine for a
fortune teller, but real programs need to **make decisions** ("if the
guess is too high, say so") and **repeat work** ("keep asking until the
player gets it right"). `if`, `switch`, `while`, `do-while`, and `for`
are how C does both. They're called **control structures** because they
control which statements run, and how many times.

## if / else if / else

An `if` runs a block of code only when its condition is true. Recall
from Module 2 that relational operators (`==`, `!=`, `<`, `>`, `<=`,
`>=`) and logical operators (`&&`, `||`, `!`) produce `1` (true) or `0`
(false) — that value is exactly what `if` checks.

```c
int temperature = 28;

if (temperature >= 30) {
    printf("It's hot outside.\n");
} else if (temperature >= 20) {
    printf("It's a mild day.\n");
} else {
    printf("It's cold.\n");
}
```

C checks each condition **top to bottom** and runs the first block whose
condition is true — then it skips every other branch, even if a later
condition would also be true. `else if` lets you chain as many
conditions as you need; the final `else` (optional) catches everything
that didn't match any condition above it. Combine conditions with `&&`
("and", both must be true) and `||` ("or", at least one must be true) —
see [`examples/01_if_else.c`](examples/01_if_else.c).

## switch statements

When you're comparing **one variable** against several **exact values**,
a `switch` is often cleaner than a long `if`/`else if` chain:

```c
int dayNumber = 3;

switch (dayNumber) {
    case 1:
        printf("Monday\n");
        break;
    case 2:
        printf("Tuesday\n");
        break;
    case 3:
        printf("Wednesday\n");
        break;
    default:
        printf("Not a valid day number.\n");
        break;
}
```

`switch` jumps straight to the matching `case` and starts running code
from there. `break` is what makes it **stop** and jump out of the switch
— without it, execution keeps going into the next case too, whether it
matches or not. This is called **falling through**, and forgetting
`break` is one of the most common beginner switch bugs. See
[`examples/07_switch_fallthrough_demo.c`](examples/07_switch_fallthrough_demo.c)
to watch it happen, then fix it. Always include a `default` case too —
it's your safety net for values that don't match anything, the same job
a final `else` does for `if`.

Note: `switch` can only compare against exact constant values — it can't
do ranges or `&&`/`||` conditions. For those, you still need `if`/`else`.

## while loops

A `while` loop repeats its body for as long as its condition stays true.
The condition is checked **before** every run — including the first —
so if it starts out false, the body never runs at all.

```c
int countdown = 5;
while (countdown > 0) {
    printf("%d...\n", countdown);
    countdown = countdown - 1;
}
printf("Liftoff!\n");
```

Use a `while` loop when you're repeating **until something happens**, and
you don't know in advance how many times that will take — like asking
the player to guess a number until they get it right.

## do-while loops

`do-while` is almost the same, except it checks its condition **after**
running the body — so the body always runs **at least once**, no matter
what the condition is:

```c
int attempts = 10;
do {
    printf("This runs even though attempts is already 10.\n");
    attempts = attempts + 1;
} while (attempts < 3);
```

This matters anywhere you need to do something once before you can even
check the condition — like asking for a player's first guess before you
have anything to compare it to. See
[`examples/03_while_and_do_while.c`](examples/03_while_and_do_while.c)
for a side-by-side comparison.

## for loops

A `for` loop packs three things onto one line, separated by `;`:

```c
for (int i = 1; i <= 10; i = i + 1) {
    printf("%d\n", i);
}
```

1. **initialization** — `int i = 1;` runs once, before the loop starts.
2. **condition** — `i <= 10` is checked before every run; the loop stops
   the moment it's false.
3. **increment** — `i = i + 1` runs after every run of the body.

Use a `for` loop when you know **in advance** how many times you want to
repeat something (print a multiplication table, roll a die 5 times).
Use a `while` loop instead when the number of repetitions depends on
something that happens *during* the loop. Anything you can write as a
`for` loop, you could also write as a `while` loop with the
initialization before it and the increment as the last line of the body
— `for` just keeps those three pieces together so they're harder to
forget.

## break and continue

Both work inside any loop (`while`, `do-while`, or `for`):

- **`break`** immediately exits the loop entirely — no more checks, no
  more iterations.
- **`continue`** skips the *rest* of the current iteration only, then
  jumps straight to the next check of the condition — the loop keeps
  going.

```c
for (int i = 1; i <= 15; i = i + 1) {
    if (i % 3 == 0) {
        continue; // skip multiples of 3, keep looping
    }
    if (i > 10) {
        break; // stop the loop completely once i passes 10
    }
    printf("%d\n", i);
}
```

## Nesting control structures

Control structures can live inside each other — most commonly, an `if`
inside a loop, to check something about each value as the loop produces
it:

```c
for (int i = 1; i <= 10; i = i + 1) {
    if (i % 2 == 0) {
        printf("%d is even\n", i);
    } else {
        printf("%d is odd\n", i);
    }
}
```

Each nested level is usually indented one more level than the one
around it — that indentation is for humans (C ignores whitespace, as you
saw in Module 1), but it's what makes nested code readable at a glance.

## Random numbers with rand() and srand()

Computers can't generate truly random numbers — `rand()` (from
`<stdlib.h>`) actually produces a long, fixed sequence of numbers that
just *looks* random. That's good enough for games and simple programs
like ours.

`srand()` "seeds" that sequence — without calling it, `rand()` gives you
the exact same numbers every single time you run the program. Seeding
with the current time, `srand(time(NULL))` (`time()` comes from
`<time.h>`), makes the seed different each run, so the numbers actually
change:

```c
#include <stdlib.h>
#include <time.h>

srand(time(NULL)); // call this once, near the start of main
int roll = rand() % 6 + 1; // a number from 1 to 6
```

`rand()` alone returns a number between `0` and a very large maximum.
`% 6` shrinks it down to `0`–`5`, and `+ 1` shifts it up to `1`–`6`. The
general pattern for a random number between `min` and `max` (inclusive)
is:

```c
rand() % (max - min + 1) + min
```

See [`examples/06_random_numbers.c`](examples/06_random_numbers.c).

## Common beginner mistakes

- Using `=` (assignment) instead of `==` (comparison) inside an `if`
  condition — `if (x = 5)` compiles, assigns `5` to `x`, and is always
  true, which is almost never what you meant.
- Forgetting `break` in a `switch` case, causing it to fall through into
  the next case.
- Writing a `while` loop whose condition never becomes false because you
  forgot to update the variable it depends on — an **infinite loop**. If
  your program seems frozen, this is almost always why (`Ctrl+C` stops
  it).
- Off-by-one errors in a `for` loop condition — `i < 10` runs 10 times
  (`0`–`9`), `i <= 10` runs 11 times (`0`–`10`). Decide which one you
  actually want and double check it.
- Calling `srand()` more than once, or inside a loop — call it **once**,
  near the top of `main`, before any calls to `rand()`.
- Confusing `break` and `continue` — `break` leaves the loop for good;
  `continue` just skips to the next round of it.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one — including the intentionally broken
   `07_switch_fallthrough_demo.c`, so you see the bug before fixing it.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 4: control structures"
   git push
   ```

Next: **[Module 5 — Arrays & Strings](../05-arrays-and-strings/README.md)**.
