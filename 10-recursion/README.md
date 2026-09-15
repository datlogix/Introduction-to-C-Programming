# Module 10 — Recursion

*Part 2 begins here.* Modules 10–19 assume you've finished Part 1
(Modules 0–9) — everything from `printf` through pointers, structs, and
file I/O is fair game and won't be re-explained.

## Hook: a countdown with no loop anywhere in sight

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>

void countdown(int n) {
    if (n == 0) {
        printf("Liftoff!\n");
        return;
    }
    printf("%d...\n", n);
    countdown(n - 1);
}

int main(void) {
    countdown(5);
    return 0;
}
```

```bash
gcc hook.c -o hook
./hook
```

`5... 4... 3... 2... 1... Liftoff!` — six lines of output, and there is no
`for`, no `while`, no `do-while` anywhere in this file. `countdown` is
doing something new: **calling itself**. By the end of this module you'll
understand exactly how a function can repeat work without a loop, and
you'll build a small recursive ASCII-art generator in this module's
project.

## What is recursion?

A **recursive function** is a function that calls itself, working on a
smaller version of the same problem each time, until it reaches a version
small enough to answer directly. Every recursive function needs exactly
two parts:

- **The base case** — the smallest version of the problem, answered
  directly, with no further recursive call. In the hook, that's
  `n == 0`: just print `"Liftoff!"` and stop.
- **The recursive case** — do a small piece of work, then call the same
  function again on a problem that's *closer* to the base case. In the
  hook, that's "print `n`, then countdown from `n - 1`."

Miss the base case, or write a recursive case that never actually gets
closer to it, and the function calls itself forever — see [Common
beginner mistakes](#common-beginner-mistakes) below.

## Tracing the call stack

Every function call — recursive or not — gets its own private copy of its
parameters and local variables, stored in a **stack frame**. Normal
function calls (Module 6) use exactly one frame at a time. Recursion is
different: each recursive call adds a *new* frame on top of the last one,
and none of those frames go away until the calls start **returning**, one
at a time, from the innermost call outward.

Trace `countdown(3)` by hand:

```
countdown(3) called
  prints "3..."
  calls countdown(2)
    countdown(2) called
      prints "2..."
      calls countdown(1)
        countdown(1) called
          prints "1..."
          calls countdown(0)
            countdown(0) called -- base case! prints "Liftoff!", returns
          countdown(1) resumes after its call, has nothing left to do, returns
        countdown(2) resumes, has nothing left to do, returns
      countdown(3) resumes, has nothing left to do, returns
```

Four separate stack frames existed briefly, all at once, each remembering
its *own* value of `n` — that's why `n - 1` in each call doesn't disturb
any other call's `n`. See
[`examples/01_countdown_no_loop.c`](examples/01_countdown_no_loop.c) —
it's the hook with a print statement added on the way back out, so you
can watch the unwinding happen.

## A classic example: factorial

`factorial(n)` (written `n!`) is `n × (n-1) × (n-2) × ... × 1`, and it
translates almost word-for-word into a recursive definition: "`n!` is `n`
times `(n-1)!` — unless `n` is `0`, in which case the answer is just `1`."

```c
int factorial(int n) {
    if (n == 0) {           // base case
        return 1;
    }
    return n * factorial(n - 1);   // recursive case
}
```

Every recursive call here waits for the call *below* it to return before
it can finish its own multiplication — `factorial(4)` can't produce a
final answer until `factorial(3)` returns, which can't finish until
`factorial(2)` returns, and so on down to the base case. See
[`examples/02_factorial_recursive.c`](examples/02_factorial_recursive.c).

## Recursion over an array: sum of elements

Recursion isn't limited to counting down a single number — it works over
arrays too, by recursing on "everything except the first element":

```c
int sumArray(int arr[], int size) {
    if (size == 0) {         // base case: an empty array sums to 0
        return 0;
    }
    return arr[0] + sumArray(arr + 1, size - 1);
}
```

`arr + 1` is pointer arithmetic from Module 7 — it points one element
further into the array, so each recursive call sees one fewer element,
moving steadily toward the base case. See
[`examples/03_sum_of_array_recursive.c`](examples/03_sum_of_array_recursive.c).

## Recursive vs. iterative: two ways to solve the same problem

Anything you can write recursively, you can also write with a loop —
`factorial` is a good side-by-side:

```c
int factorialIterative(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result = result * i;
    }
    return result;
}
```

Neither version is "more correct." Loops are usually a little more
memory-efficient (one stack frame instead of many) and can be easier to
follow for simple counting. Recursion tends to shine when a problem is
*naturally* defined in terms of a smaller version of itself — as you'll
see clearly in Module 12 (Linked Lists), where walking a chain of nodes
maps onto recursion almost perfectly. For now, the honest beginner rule:
**if a loop solves it cleanly, use the loop — reach for recursion when
the problem genuinely describes itself in smaller pieces.** See
[`examples/04_recursive_vs_iterative.c`](examples/04_recursive_vs_iterative.c).

## A cautionary tale: naive Fibonacci

Not every recursive solution is a *good* one. The Fibonacci sequence
(`0, 1, 1, 2, 3, 5, 8, 13, ...`, each number the sum of the two before it)
has an obvious-looking recursive definition:

```c
int fib(int n) {
    if (n <= 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}
```

This is correct — and, past roughly `n = 35`, painfully slow. Trace it by
hand for `fib(5)` and you'll notice `fib(3)` gets computed **twice**,
`fib(2)` three times, and it only gets worse as `n` grows — the same
work is repeated over and over instead of reused. This isn't a reason to
distrust recursion; it's a reason to notice when a recursive definition
is quietly doing far more work than it looks like on paper. See
[`examples/05_fibonacci_naive_recursion.c`](examples/05_fibonacci_naive_recursion.c),
which prints a call counter so you can watch the blowup happen.

## What happens without a base case

See [`examples/06_missing_base_case_infinite_recursion.c`](examples/06_missing_base_case_infinite_recursion.c)
for the full story — in short: a recursive function with no base case
(or a recursive case that never actually reaches it) calls itself
forever. Each call adds another stack frame, and stack frames aren't
infinite — eventually the program crashes with a **stack overflow**. That
file shows the broken version *safely disabled* behind a comment (running
it for real crashes the program on purpose, which isn't worth doing more
than once), alongside the corrected version with a real base case, so you
can see exactly what separates them.

## Common beginner mistakes

- **No base case at all**, or a base case that's never actually reached
  — guaranteed infinite recursion and a crash.
- A recursive case that doesn't make **measurable progress** toward the
  base case (e.g. calling `countdown(n)` instead of `countdown(n - 1)` —
  identical arguments forever).
- Forgetting to `return` the recursive call's result when the function
  needs to hand a value back (`factorial(n - 1);` instead of
  `return n * factorial(n - 1);` silently discards the computation).
- Assuming recursion is always "cleaner" — sometimes it quietly repeats
  huge amounts of work, as naive Fibonacci shows.
- Off-by-one base cases (`n == 1` instead of `n == 0`, or vice versa) —
  trace a small example by hand before trusting a base case is right.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one — including the safely-disabled infinite recursion in
   `06`, so you understand the danger without actually crashing anything
   you care about.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 10: recursion"
   git push
   ```

Next: **[Module 11 — Dynamic Memory Allocation](../11-dynamic-memory-allocation/README.md)**.
