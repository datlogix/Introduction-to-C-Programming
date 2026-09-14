# Module 1 — Basics of Programming

## Hook: the world's smallest fortune teller

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>

int main(void) {
    printf("You will encounter a strange creature today.\n");
    printf("It has six legs, compound eyes, and excellent opinions.\n");
    printf("Its name is: ");
    printf("your cat.\n");
    return 0;
}
```

```bash
gcc fortune.c -o fortune
./fortune
```

Four `printf` calls, one program, one joke that lands because of the line
break placement. By the end of this module you'll understand exactly why
that third `printf` doesn't start a new line, and you'll build your own
version of this in the module project.

## What is a program, really?

A computer only understands one language: electrical signals interpreted
as numbers — **machine code**. Nobody writes programs directly in machine
code anymore. Instead, we write in a **language humans can read** (like
C), and a program called a **compiler** translates it into machine code
for us.

```
you write          compiler translates          computer runs
hello.c      --->      (gcc)            --->        hello
(C source)                                       (machine code)
```

This is exactly what you did in Module 0 when you ran
`gcc hook.c -o hook`. Every C program you ever write follows this same
pipeline: **source code → compiler → executable → run**.

C is a **compiled language**. Contrast this with languages like Python,
which are **interpreted** — run line-by-line by another program every
time, with no separate "build" step. This is why compiled programs tend
to run faster (all the translation work happens once, ahead of time) but
have an extra step (you must recompile after every change).

## Anatomy of a C program

Look at the smallest complete, useful C program:

```c
#include <stdio.h>

int main(void) {
    printf("Hello, C!\n");
    return 0;
}
```

Let's take it apart line by line.

### `#include <stdio.h>`

C's core language is small — even printing to the screen isn't built in.
Instead, functionality lives in **libraries** you pull in with
`#include`. `stdio.h` ("standard input/output header") gives you
`printf` (for printing) and `scanf` (for reading input, coming in
Module 3). This line must come before you use anything from that
library.

### `int main(void) { ... }`

Every C program has exactly one `main` function — it's the **entry
point**: the first code that runs when your program starts. `int` means
main reports back a whole number when it finishes (see `return 0` below).
`void` between the parentheses means "this version of main takes no
inputs" — you'll see a different form of `main` if you ever handle
command-line arguments, but this is the one you'll use for now. The `{`
and `}` mark where main's body begins and ends — everything a function
does lives between its braces.

### `printf("Hello, C!\n");`

- `printf` — "print formatted" — a function from `stdio.h` that writes
  text to the screen.
- `"Hello, C!\n"` — a **string literal**: literal text, always in double
  quotes. `\n` is a single special character meaning "newline" — it's
  what moves output to the next line. Without it, the next `printf` would
  continue on the *same* line (exactly what the hook program exploited).
- `;` — a **semicolon** ends every statement in C. Forget one and the
  compiler will complain — usually about the *next* line, which confuses
  beginners. If an error message makes no sense, check the line *above*
  it for a missing semicolon first.

### `return 0;`

Tells whoever ran the program "I finished successfully." `0`
conventionally means success; any other number signals some kind of
error occurred. You won't use this deliberately much yet, but it must be
there in `main`.

## Statements, whitespace, and comments

- A **statement** is one instruction, ending in `;`. C doesn't care about
  line breaks or indentation the way Python does — they're purely for
  humans to read the code. *Always* indent consistently anyway; VS Code's
  C/C++ extension does this for you automatically.
- **Comments** are notes for humans that the compiler ignores entirely:

  ```c
  // A single-line comment — everything after // on this line is ignored.

  /* A multi-line comment.
     Everything between /* and */ is ignored, across as many lines as you like. */
  ```

  Use comments to explain *why* something is done a non-obvious way — not
  to restate what the code already says.

## Compiling and running — the two ways you'll use in this course

**Terminal (do this to really understand it):**

```bash
gcc myfile.c -o myfile
./myfile
```

**VS Code Code Runner (fast iteration once you're comfortable):** open the
`.c` file and click the ▶ button in the top-right corner, or press
`Ctrl+Alt+N`.

Both do the same thing. Use the terminal version whenever you want to be
sure you understand exactly what's happening — it's also what you'll use
on any computer that doesn't have VS Code.

## Errors are normal — read them, don't fear them

Try compiling this broken version (missing semicolon):

```c
#include <stdio.h>

int main(void) {
    printf("Oops\n")
    return 0;
}
```

`gcc` will report something like:
`error: expected ';' before 'return'`

That's the compiler pointing almost exactly at the mistake. Reading
compiler errors is a skill — you'll get fast at it. The habit that
matters most right now: **fix the first error first, then recompile.**
One missing semicolon can produce five confusing-looking errors below it;
they usually all disappear once you fix the real one.

## Common beginner mistakes

- Forgetting the semicolon at the end of a statement.
- Mismatched `{` and `}` — VS Code highlights the matching brace when your
  cursor is next to one; use it.
- Forgetting `#include <stdio.h>` and then using `printf` — some
  compilers will still let this slide with a warning, but always include
  it; never rely on it being implicit.
- Forgetting `\n` and being confused why two `printf` calls' output ran
  together on one line.
- Typos in `printf` (e.g. `Printf`, `PRINTF`) — C is **case-sensitive**.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work (see Module 0 §6 if you need a refresher):

   ```bash
   git add .
   git commit -m "Complete Module 1: basics of programming"
   git push
   ```

Next: **[Module 2 — Data Types & Operators](../02-data-types-and-operators/README.md)**.
