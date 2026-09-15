# Module 17 — Command-Line Arguments & CLI Tools

## Hook: one program, two completely different behaviors

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <name> [--shout]\n", argv[0]);
        return 1;
    }

    char *name = argv[1];
    int shout = 0;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--shout") == 0) {
            shout = 1;
        }
    }

    if (shout) {
        printf("HELLO, ");
        for (int i = 0; name[i] != '\0'; i++) {
            putchar(toupper(name[i]));
        }
        printf("!!!\n");
    } else {
        printf("Hello, %s!\n", name);
    }

    return 0;
}
```

```bash
gcc hook.c -o greet
./greet Ama
./greet Kwame --shout
```

`./greet Ama` prints `Hello, Ama!`. `./greet Kwame --shout` prints
`HELLO, KWAME!!!` — same compiled program, zero code changes, entirely
different behavior. The difference wasn't a new build; it was
information handed to the program **from outside itself**, at the
moment it started. By the end of this module you'll understand exactly
how `main` receives that information, and you'll build a small `wc`-style
tool of your own in the module project.

## A new shape of `main`

Every program you've written until now has started with:

```c
int main(void)
```

`void` means "takes no inputs." There's a second, equally standard form:

```c
int main(int argc, char *argv[])
```

This `main` *does* take inputs — the words typed after the program's
name on the command line. `argc` ("argument count") is a whole number
telling you how many of those words there are. `argv` ("argument
vector") is an array of C-strings, one per word. Both are filled in
automatically by the operating system before your program's first line
even runs — you don't request them, they're just there.

## `argv[0]` is the program's own name

This trips up nearly everyone the first time: `argv[0]` is **not** the
first argument the user typed — it's the name (or path) the program was
run as. The first *real* argument is `argv[1]`.

Run `./greet Ama` and the array looks like this:

```
argc = 2
argv[0] = "./greet"     <- the program's own name, always
argv[1] = "Ama"         <- the first thing the user actually typed
```

Run `./greet Kwame --shout` (three words, including the program name)
and `argc` becomes `3`, with `argv[2] = "--shout"`. See
[`examples/01_argc_and_argv_basics.c`](examples/01_argc_and_argv_basics.c)
— run it with a few different sets of arguments and watch `argc` and
every slot of `argv` print out.

## Always check `argc` before indexing `argv`

`argv` is an array, and Module 5's rule about arrays never went away:
reading an index that wasn't actually filled in reads **past the end of
the array** — undefined behavior, not a clean error message. If a
program blindly reads `argv[1]` and the user ran it with zero
arguments, `argv[1]` doesn't exist.

```c
// DANGEROUS: assumes argv[1] exists
printf("Hello, %s!\n", argv[1]);

// SAFE: check argc first
if (argc < 2) {
    printf("Usage: %s <name>\n", argv[0]);
    return 1;
}
printf("Hello, %s!\n", argv[1]);
```

Every example and exercise in this module checks `argc` before it
touches `argv[1]` or beyond — get in the habit now.

## Reading named flags by hand

A **flag** is an argument that turns a behavior on or off, usually
starting with `--` (e.g. `--shout`). There's no special language feature
for this — you just loop over `argv` and compare each entry against the
flag strings you're expecting, using `strcmp` (Module 5):

```c
int shout = 0;
for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "--shout") == 0) {
        shout = 1;
    }
}
```

This is exactly what the hook's `greet` program does — see
[`examples/02_reading_named_flags.c`](examples/02_reading_named_flags.c)
for the full version. It's worth knowing that real-world C programs
usually parse flags like this with the standard library's `getopt()` /
`getopt_long()` instead of a hand-rolled loop — it handles things like
`-x` vs `--long-name` and combined short flags for you. It's not
necessary for anything in this module, but worth looking up once
`strcmp`-based parsing feels comfortable.

## Arguments are always strings — converting to numbers

No matter what the user types, `argv[i]` is a C-string. Typing
`./program 42` does **not** hand your program the number `42` — it hands
it the two characters `'4'` and `'2'`. To actually do arithmetic with
it, convert it first:

```c
int count = atoi(argv[1]);   // "42" -> 42
```

`atoi` ("ASCII to integer") is the quick tool for this. Its downside:
given text that isn't a valid number at all (like `"abc"`), it quietly
returns `0` — it can't tell you "that wasn't a number" versus "that
number really was 0." For real error-checking, `strtol` is the more
robust tool (it can report exactly where parsing failed), though its
full error-handling interface is more than this module needs — `atoi`
is enough for now. See
[`examples/04_combining_flags_and_a_filename_argument.c`](examples/04_combining_flags_and_a_filename_argument.c)
and
[`examples/05_printing_usage_help.c`](examples/05_printing_usage_help.c).

## The shape of a real Unix-style CLI tool

Every program in this course so far has followed the same interactive
loop: print a menu, `scanf` a choice, act on it, repeat until the user
picks "quit." That's a perfectly reasonable shape for a program a human
sits in front of — but it's not how most real command-line tools work.
Commands like `wc`, `grep`, and `ls` follow a different, simpler shape:

```
read input (from arguments and/or a file) -> do ONE job -> print output -> exit
```

No menu. No "run again? (y/n)." The tool is meant to be driven **from
outside itself** — by a human typing different arguments each time, by
a script that calls it in a pipeline, or by another program entirely.
Everything the tool needs to know is handed to it as arguments (and
maybe a file) when it starts, and it's gone the moment it finishes.
[`examples/03_a_real_cli_tool_word_counter.c`](examples/03_a_real_cli_tool_word_counter.c)
reads a file named on the command line, counts its words, prints one
number, and exits — the whole thing in one pass, no interaction at all.

## Printing a usage message

When a CLI tool is called wrong — missing arguments, a bad flag — the
helpful response isn't a crash or silent wrong output. It's a short
**usage message** showing exactly how the program expects to be called,
the CLI equivalent of a helpful compiler error:

```c
if (argc != 3) {
    printf("Usage: %s <number1> <number2>\n", argv[0]);
    return 1;
}
```

Using `argv[0]` (rather than hardcoding the program's name) means the
message is always accurate even if the compiled file gets renamed.
Returning a non-`0` value (Module 1) also signals to whatever *called*
your program — a script, another tool — that something went wrong,
which matters a great deal once programs start calling other programs.

## Common beginner mistakes

- Assuming `argv[1]` is the first argument the user typed — it's
  `argv[0]` that's the program's own name; `argv[1]` is the first real
  one.
- Reading `argv[i]` without checking `argc` first — an out-of-bounds
  array read, not a clean error.
- Forgetting that every `argv[i]` is a **string**, even when it looks
  like a number — `argv[1] + argv[2]` doesn't add two numbers, it adds
  two pointers. Convert with `atoi`/`strtol` first.
- Writing `if (argv[i] == "--shout")` instead of
  `if (strcmp(argv[i], "--shout") == 0)` — Module 5's rule about
  comparing C-strings with `strcmp`, not `==`, still applies here.
- Consuming a flag's value argument (like the `N` after `--lines`)
  without checking there's actually another argument left to read.
- Building an interactive menu loop when the assignment asked for a CLI
  tool — re-read the requirements; "do one job and exit" is the point.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one **with real command-line arguments** — these
   programs don't do anything interesting run with no arguments at all
   (except printing their usage message).
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 17: command-line arguments and CLI tools"
   git push
   ```

Next: **[Module 18 — Sorting & Searching Algorithms](../18-sorting-and-searching-algorithms/README.md)**.
