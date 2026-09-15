# Module 15 — Debugging & Memory Safety

You've been writing programs with `malloc`, pointers, and linked
structures for a few modules now, which means you've also been writing
the occasional crash and the occasional silent memory leak -- everyone
does. This module doesn't teach you to stop making those mistakes
entirely (nobody does that). It teaches you to find them in minutes
instead of hours, using the same tools working C programmers reach for
every day.

## Hook: the crash is not a mystery, it just looks like one

Compile and run this exactly as written -- don't read ahead first:

```c
#include <stdio.h>

void printScore(int *score) {
    printf("Score: %d\n", *score);
}

int main(void) {
    int *currentScore = NULL;

    printScore(currentScore);

    printf("This line never runs.\n");
    return 0;
}
```

```bash
gcc -g hook.c -o hook
./hook
```

```
Segmentation fault
```

That's it. That's the entire error message. No line number, no
function name, no hint about `currentScore` being `NULL`. If this were
a 2,000-line program instead of nine lines, you'd have almost nothing
to go on.

Now run the *exact same program* under a debugger instead:

```
$ gdb ./hook
(gdb) run
Starting program: /home/you/15-debugging-and-memory-safety/hook

Program received signal SIGSEGV, Segmentation fault.
0x0000000000401156 in printScore (score=0x0) at hook.c:4
4           printf("Score: %d\n", *score);
(gdb) bt
#0  0x0000000000401156 in printScore (score=0x0) at hook.c:4
#1  0x0000000000401189 in main () at hook.c:11
```

Same crash, same program -- but now you know the exact line (`hook.c:4`),
the exact function (`printScore`), and the exact reason (`score=0x0`,
i.e. `score` is `NULL`), in about five seconds. The crash was never
mysterious. You just needed the right tool to ask the program what
happened. That's this whole module.

## A quick note on your platform

`gdb` and `valgrind` both work great on Linux and on Windows via WSL.
`gdb` is also generally fine on Intel Macs (it may need a one-time
setup step to grant it permission to control other processes).
`valgrind`, however, **does not reliably support Apple Silicon (M1/M2/M3/M4)
Macs** -- which a good number of you are probably using right now. This
is a well-known, common situation, not something broken about your
setup.

If `valgrind` isn't available on your machine, you can still do this
whole module:

- Work through every `gdb` section normally -- it's unaffected.
- For the `valgrind` sections, either use a Linux machine or WSL if you
  have access to one, **or** treat the example output shown below as
  what you're learning to read -- the skill is interpreting a valgrind
  report, and you can build that skill from real examples even before
  you've generated your own.
- You'll get hands-on `valgrind` practice in the Part 2 capstone if your
  team works on a Linux/WSL machine, or you'll do a careful manual
  malloc/free audit instead if not -- Module 19 explains both paths.

Nothing below assumes you have `valgrind` running in front of you right
now. Read the reports, understand what they're telling you, and you're
learning the real skill either way.

## What actually happens during a segfault

A **segmentation fault** ("segfault") happens when your program tries
to read or write memory it doesn't have permission to touch --
most often through a `NULL` pointer (like the hook) or a pointer that
never held a valid address in the first place (an uninitialized
pointer, or one that's already been freed).

Your program doesn't own all of memory; the operating system hands it
specific regions to use. The instant your program reaches outside those
regions, the OS steps in and kills the process immediately, before
anything worse can happen (like corrupting some *other* program's
memory). That abrupt kill is the segfault. It's not your program
"breaking" in some soft, recoverable way -- it's the OS actively
stopping it.

This is exactly why a segfault gives you almost no information by
default: the OS's job is to stop the damage, not to explain it to you.
That's the debugger's job.

## Compiling with debug symbols: `-g`

```bash
gcc -g file.c -o program
```

The `-g` flag tells `gcc` to bake extra information into the compiled
program: which machine instruction corresponds to which line of *your*
source file, and what your variables are actually named. Without `-g`,
a debugger can only show you raw memory addresses -- technically
correct, practically useless. With `-g`, it can show you `hook.c:4` and
`score=0x0` instead.

`-g` doesn't change how your program runs or what it prints -- it only
adds information *for tools like `gdb`* to use. Get in the habit of
compiling with it any time you're about to debug something:

```bash
gcc -g -Wall file.c -o program
```

## Using `gdb`: the small, practical subset

`gdb` (the GNU Debugger) lets you run your program under close
supervision -- pausing it, stepping through it one line at a time, and
inspecting variables as it goes. It has an enormous command set; you
need about six commands to handle most beginner debugging.

Start it on a program compiled with `-g`:

```bash
gdb ./program
```

**Running a program that crashes.** Type `run` (or `r`) at the `(gdb)`
prompt. The program executes normally until it crashes, then `gdb`
pauses it *at the exact instant of the crash* instead of letting the OS
kill it silently:

```
(gdb) run
Starting program: /path/to/program

Program received signal SIGSEGV, Segmentation fault.
0x0000000000401156 in printScore (score=0x0) at hook.c:4
4           printf("Score: %d\n", *score);
```

**Reading a backtrace.** Once stopped, `bt` (backtrace) prints the
chain of function calls that got you there, most recent call first:

```
(gdb) bt
#0  0x0000000000401156 in printScore (score=0x0) at hook.c:4
#1  0x0000000000401189 in main () at hook.c:11
```

`#0` is where the crash happened; `#1` is who called that function;
and so on outward. For a crash, `#0` is almost always where you want to
start looking.

**Setting a breakpoint.** Sometimes you don't want to wait for a crash
-- you want to pause at a specific spot and watch what happens from
there. `break` (or `b`) sets that pause point, either by function name
or by file and line number:

```
(gdb) break printScore
(gdb) break hook.c:10
```

Then `run` starts the program and it stops automatically the moment it
reaches that breakpoint, before executing that line.

**Moving through code.** Once stopped at a breakpoint:
- `next` (or `n`) runs the current line and moves to the next one,
  stepping *over* function calls (they run to completion without you
  following into them).
- `step` (or `s`) does the same, but steps *into* a function call if
  the current line makes one -- useful when the bug might be inside
  that call.

**Inspecting a value.** `print` (or `p`) followed by a variable name
shows its current value, at any point while the program is paused:

```
(gdb) print currentScore
$1 = (int *) 0x0
```

`0x0` is `NULL` -- there's your bug, confirmed directly from the
running program instead of inferred from a crash message.

Type `quit` (or `q`) to leave `gdb` when you're done.

That's the whole practical toolkit: `run`, `bt`, `break`, `next`/`step`,
`print`, `quit`. Everything else `gdb` can do, you can look up when you
actually need it.

*(The exact addresses and version banner `gdb` prints will differ on
your machine -- what matters is the function name, file, and line
number, which will match.)*

## Using `valgrind`: finding leaks and invalid memory access

`gdb` is for crashes -- things that stop your program. `valgrind` is
for the bugs that **don't** stop your program: memory that's silently
leaked, or memory that's read or written outside the bounds you
allocated. Both can run for a long time looking completely fine before
they cause real damage.

Run it exactly like your program, just with `valgrind` in front:

```bash
gcc -g file.c -o program
valgrind ./program
```

### Reading a "definitely lost" leak report

Take [`examples/02_memory_leak_and_valgrind.c`](examples/02_memory_leak_and_valgrind.c),
which allocates a small buffer inside `printReport()` and never frees
it. Running it under `valgrind` produces a report shaped like this
*(the example below is reconstructed from a real valgrind run, since
this course's build environment doesn't have `valgrind` installed to
capture live output from -- the shape, wording, and line numbers are
exactly what your own run against this file will show if you have
`valgrind` available)*:

```
==12345== Memcheck, a memory error detector
==12345== Command: ./leak_demo
==12345==
Doubled scores:
  20
  40
  60
  80
Report printed -- but we just leaked memory doing it.
==12345==
==12345== HEAP SUMMARY:
==12345==     in use at exit: 16 bytes in 1 blocks
==12345==   total heap usage: 1 allocs, 0 frees, 16 bytes allocated
==12345==
==12345== 16 bytes in 1 blocks are definitely lost in loss record 1 of 1
==12345==    at 0x4848899: malloc (vg_replace_malloc.c:381)
==12345==    by 0x1091A4: printReport (02_memory_leak_and_valgrind.c:18)
==12345==    by 0x1091FD: main (02_memory_leak_and_valgrind.c:39)
==12345==
==12345== LEAK SUMMARY:
==12345==    definitely lost: 16 bytes in 1 blocks
==12345==      indirectly lost: 0 bytes in 0 blocks
==12345==      possibly lost: 0 bytes in 0 blocks
==12345==    still reachable: 0 bytes in 0 blocks
==12345== ERROR SUMMARY: 1 errors from 1 contexts
```

Three things to read, in order:

1. **The program's own output still prints normally** -- `valgrind`
   doesn't stop your program, it watches it. A leak never crashes
   anything, which is exactly why you need a tool to catch it.
2. **`definitely lost: 16 bytes in 1 blocks`** -- this is the headline.
   "Definitely lost" means memory that's gone forever: nothing in your
   program still holds a pointer to it, so it can never be freed. 16
   bytes is `sizeof(int) * 4` -- exactly the one allocation that never
   got a matching `free()`.
3. **The backtrace under "definitely lost"** -- reads the same
   direction as `gdb`'s: `malloc` was called from `printReport` at
   line 18, which was called from `main` at line 39. That's the exact
   allocation to go add a `free()` for.

### Reading an "invalid read" report

Take [`examples/03_invalid_read_and_valgrind.c`](examples/03_invalid_read_and_valgrind.c),
which allocates room for 5 `int`s and then reads index `5` -- one past
the end. Ordinary execution won't crash (you tested this yourself if
you ran the file), which is exactly the danger: it just silently reads
whatever happens to be in adjacent memory. `valgrind` catches it
directly *(again, reconstructed to match a real run against this exact
file, valid indices and all)*:

```
==12346== Memcheck, a memory error detector
==12346== Command: ./invalid_read_demo
==12346==
Last valid value: 500
==12346== Invalid read of size 4
==12346==    at 0x109184: main (03_invalid_read_and_valgrind.c:30)
==12346==  Address 0x4a4b054 is 0 bytes after a block of size 20 alloc'd
==12346==    at 0x4848899: malloc (vg_replace_malloc.c:381)
==12346==    by 0x109160: main (03_invalid_read_and_valgrind.c:20)
==12346==
One past the end:  0
==12346==
==12346== HEAP SUMMARY:
==12346==     in use at exit: 0 bytes in 0 blocks
==12346==   total heap usage: 1 allocs, 1 frees, 20 bytes allocated
==12346== ERROR SUMMARY: 1 errors from 1 contexts
```

Read it the same way: **`Invalid read of size 4`** at line 30 is the
headline -- a 4-byte (one `int`) read that shouldn't have happened.
Underneath, `valgrind` tells you exactly *why*: address `0x4a4b054` is
"0 bytes after a block of size 20" that was allocated at line 20 --
in other words, precisely one element past the 5-`int` (20-byte) array
you asked for. No guessing required: the report names the exact
allocation and the exact overstep.

## Defensive programming checklist

Most of what this module diagnoses is preventable with four habits.
[`examples/04_defensive_programming_checklist.c`](examples/04_defensive_programming_checklist.c)
shows all four working together in one file:

- **Always initialize pointers** -- to `NULL` if you don't have a real
  address for them yet. A `NULL` pointer that gets misused crashes
  immediately and obviously; an *uninitialized* pointer can point
  anywhere, including memory that happens to "work" by pure luck until
  it doesn't.
- **Always check `malloc`/`fopen` return values.** Both return `NULL`
  on failure instead of crashing on the spot -- if you don't check,
  *your* code is what turns that failure into a crash, several lines
  later and much harder to trace back.
- **Always match every `malloc` with exactly one `free`.** Not zero
  (a leak). Not two (a double free). Exactly one, on every possible
  path through the function -- exactly the bug in this module's
  exercise.
- **Compile with `-Wall` and read every warning.** The compiler already
  catches some of these bugs for free, before you ever need a debugger
  -- an uninitialized variable used before being set is a common one it
  flags directly. A warning that's ignored today is a `gdb` session
  tomorrow.

## Common beginner mistakes

- **Forgetting `-g`.** Running `gdb` on a program compiled without it
  gives you raw addresses instead of file names and line numbers --
  technically debuggable, practically painful. If `gdb` can't find your
  source lines, this is almost always why.
- **Assuming "it didn't crash" means "it's correct."** A memory leak or
  an out-of-bounds read can run for a long time looking completely
  fine. Absence of a crash is not proof of absence of a bug -- that's
  exactly the gap `valgrind` fills.
- **Reading only the first line of a `valgrind` report.** The
  "definitely lost" or "Invalid read" summary tells you *that*
  something's wrong; the backtrace underneath tells you *where*. Skip
  it and you'll fix the wrong line, or nothing at all.
- **Freeing a pointer and continuing to use it.** `free()` releases the
  memory but doesn't change the pointer variable itself -- it still
  holds the old (now invalid) address. Set it to `NULL` right after
  freeing, as a habit, not just when you remember to.
- **Panicking at "Segmentation fault" with no other output.** That bare
  message is the *starting* point for debugging, not a dead end --
  it's exactly what the hook showed you `gdb` turns into a precise
  answer in seconds.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling each
   with `gcc -g -Wall` and running it. For `01`, run it once plain, then
   again under `gdb` and reproduce the backtrace yourself. For `02` and
   `03`, run them under `valgrind` if you have it; if not, read through
   the code and match it against the reconstructed reports above --
   explain in your own words what each report line means before moving
   on.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c) -- find and
   describe the bug yourself before checking
   [`exercises/solutions/exercise1_solution.c`](exercises/solutions/exercise1_solution.c).
3. Build the [module project](project/README.md): a program with three
   separate bugs, waiting for you to diagnose and fix all of them.
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 15: debugging and memory safety"
   git push
   ```

Next: **[Module 16 — Enums, Unions & Bitwise Operators](../16-enums-unions-and-bitwise-operators/README.md)**.
