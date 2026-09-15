# Module 14 — Multi-File Programs (& the Preprocessor)

## Hook: the same program, in two pieces

Compile and run both of these exactly as written — don't read ahead
first.

**Version 1 — one file, everything in it:**
[`examples/01_single_file_before/main.c`](examples/01_single_file_before/main.c)

```bash
gcc examples/01_single_file_before/main.c -o before
./before
```

**Version 2 — the exact same program, split into pieces:**
[`examples/02_split_into_header_and_source/`](examples/02_split_into_header_and_source/)
contains `main.c`, `mathreport.c`, and `mathreport.h`.

```bash
gcc examples/02_split_into_header_and_source/main.c \
    examples/02_split_into_header_and_source/mathreport.c \
    -o after
./after
```

Same output, both times, character for character. The only thing that
changed is *where* the code lives: one `gcc` command that now lists two
`.c` files instead of one, a new `.h` file describing what's available,
and a `main.c` that's shrunk down to just "what does this program do,"
with "how" moved somewhere else. That's the whole subject of this
module: **splitting a program across files without changing what it
does** — so it's something you could hand to a teammate to work on
independently, or just find again in six months without scrolling.

## Why one file stops scaling

Every program you've written so far has fit in a single `.c` file
comfortably. That stops being true as programs grow. Picture a 400-line
`.c` file: a few structs, a dozen functions for validating input,
computing statistics, formatting output, saving to a file — all of it
scrolling past in one window. Now imagine you need to fix one bug in
"the function that formats a report." You know it's *in there somewhere*
between line 40 and line 380. That search — scrolling, `Ctrl+F`-ing,
losing your place — is the actual, physical cost of a program outgrowing
one file. It also means:

- Two people can't easily work on the same program at once — you're
  both editing the same file and fighting over the same lines.
- Code you wrote for one program (a temperature converter, say) can't be
  reused in another program without copy-pasting the whole file and
  deleting what you don't need.
- Everything recompiles every time, even if you only changed one small
  function.

The fix isn't a new language feature — it's organization. **Header
files** and **source files**, working together, are how C code gets
organized once it outgrows a single file.

## Splitting a program: headers declare, source files define

A C program split across files always follows the same shape:

- A **header file** (`.h`) holds **declarations**: function prototypes,
  struct definitions, and `#define` constants. It's the *menu* — what
  this piece of code offers, with no detail about how any of it works.
- A **source file** (`.c`) holds **definitions**: the actual function
  bodies. It's the *kitchen* — how the menu items actually get made.

Look at [`examples/02_split_into_header_and_source/mathreport.h`](examples/02_split_into_header_and_source/mathreport.h):

```c
#ifndef MATHREPORT_H
#define MATHREPORT_H

#define SEPARATOR_WIDTH 20

int square(int n);
int cube(int n);
void printSeparator(void);
void printReport(int n);

#endif
```

Every line is a *promise*, not an implementation — "somewhere, a
function called `square` exists that takes an `int` and returns an
`int`." The actual bodies live in
[`mathreport.c`](examples/02_split_into_header_and_source/mathreport.c),
which `#include`s the header and then defines every function it
promised. Any file that wants to use `square()` just needs
`#include "mathreport.h"` — it doesn't need to see, or even care about,
how `square` is implemented.

## `#include "..."` vs. `#include <...>`

You've used `#include <stdio.h>` since Module 1. Now compare it with
`#include "mathreport.h"` in
[`examples/02_split_into_header_and_source/main.c`](examples/02_split_into_header_and_source/main.c):

- **Angle brackets** (`<stdio.h>`) — for **system/standard library**
  headers that shipped with your compiler. The compiler looks in its own
  standard install locations.
- **Double quotes** (`"mathreport.h"`) — for **your own local files**.
  The compiler looks in your project directory first (starting next to
  the file doing the including), and only falls back to the system
  locations if it doesn't find a match there.

Practically: if you wrote the header yourself and it lives in your
project, use double quotes. If it's part of the C standard library, use
angle brackets. Mixing them up (`#include <mathreport.h>`) usually
produces a "file not found" error, because the compiler never thinks to
look in your project folder.

## Include guards: why every header needs one

Try this on purpose. [`examples/03_include_guards_demo/no_guards/`](examples/03_include_guards_demo/no_guards/)
has a `point.h` with **no** include guard, included by both `main.c`
*and* `shape.h` — and `main.c` includes `shape.h` too. Compile it:

```bash
gcc examples/03_include_guards_demo/no_guards/main.c \
    examples/03_include_guards_demo/no_guards/point.c \
    examples/03_include_guards_demo/no_guards/shape.c \
    -o broken
```

That fails with something like `error: redefinition of 'struct Point'`.
Here's why: `#include` is a **preprocessor** directive — before the
compiler ever looks at your code, the preprocessor literally copy-pastes
the entire contents of the included file in, textually, replacing the
`#include` line. `main.c` includes `point.h` directly *and* includes
`shape.h`, which **also** includes `point.h` internally. Once the
preprocessor is done, `main.c`'s expanded text contains the entire
`struct Point` definition **twice** — and the compiler, quite
reasonably, refuses to accept the same struct defined twice in one file.

The fix is an **include guard**, wrapped around everything in a header:

```c
#ifndef POINT_H
#define POINT_H

// ... the header's actual contents ...

#endif
```

The first time `point.h` gets pulled into a file, `POINT_H` isn't
defined yet, so the preprocessor defines it and keeps the contents.
Every *later* `#include "point.h"` in that same file finds `POINT_H`
already defined and skips straight past everything to `#endif` — the
struct only ever gets pasted in once. See
[`examples/03_include_guards_demo/with_guards/`](examples/03_include_guards_demo/with_guards/),
which is the identical program with only that one fix, and compiles and
runs cleanly:

```bash
gcc examples/03_include_guards_demo/with_guards/main.c \
    examples/03_include_guards_demo/with_guards/point.c \
    examples/03_include_guards_demo/with_guards/shape.c \
    -o fixed
./fixed
```

**Every header you write from now on should have an include guard.**
The convention is simple and consistent: `#ifndef` using the filename in
capitals with underscores, matching `#define` right below it, `#endif`
as the very last line.

## `#define` vs. `const`

You met `const` back in Module 3, and you've now used `#define` for
`SEPARATOR_WIDTH` and the include-guard names above. They can look
similar but work completely differently:

```c
#define MAX_STUDENTS 30   // preprocessor: pure text substitution,
                          // happens BEFORE compilation even starts

const int maxStudents = 30;   // compiler: a real, typed variable that
                               // happens to be read-only
```

`#define` isn't a variable at all — the preprocessor just replaces every
later appearance of `MAX_STUDENTS` with the literal text `30`, the same
mechanical find-and-replace it uses to expand `#include`. `const int` is
a genuine variable, with a type the compiler checks, that simply can't
be reassigned after it's initialized.

For a beginner, the practical rule: **prefer `const` for values** — you
get type checking and it behaves like every other variable you already
know. Reach for `#define` mainly for two things this module actually
needs it for: include-guard names (which must be pure preprocessor
text, not a real variable) and small constants you want shared
identically across several files via a header, like `SEPARATOR_WIDTH`
above.

## Compiling multiple `.c` files together

`gcc` needs to know about **every** `.c` file that contributes code to
your program — headers are never listed on the command line, only
`.c` files:

```bash
gcc main.c helpers.c -o program
```

Miss one (say you only typed `gcc main.c -o program` when `main.c` calls
a function defined in `helpers.c`) and you'll get a **linker error**
like `undefined reference to 'someFunction'` — the compiler understood
*that* the function exists (it saw the prototype in the header you
included), but nothing ever supplied its actual body, because
`helpers.c` was never compiled in. The fix is almost always the same:
check your `gcc` command lists every `.c` file the program needs.

## A minimal Makefile

Retyping a long `gcc` command with several `.c` files every time you
test a change gets old fast. A **Makefile** fixes that by giving the
command a name. See
[`examples/04_compiling_with_a_makefile/Makefile`](examples/04_compiling_with_a_makefile/Makefile):

```makefile
all:
	gcc main.c stats.c -o program

clean:
	rm -f program
```

`all` and `clean` are **targets** — names for a recipe. Typing `make` in
that folder runs the recipe under the first target (`all`) by default;
`make clean` runs the recipe under `clean`. The one rule that trips
everyone up once: **the indented line under a target must start with a
real tab character**, not spaces — most editors handle this
automatically inside a file literally named `Makefile`, but it's worth
knowing if `make` ever complains about a "missing separator."

```bash
cd examples/04_compiling_with_a_makefile
make
./program
```

This is intentionally the smallest useful Makefile, not a real build
system — enough to stop retyping one command, nothing more.

## Common beginner mistakes

- **Forgetting the include guard** — see [Include guards](#include-guards-why-every-header-needs-one)
  above; this is the single most common multi-file bug.
- **Putting a function body in a header instead of just a prototype** —
  works by accident in a tiny one-file-includes-it-once program, then
  breaks the moment two `.c` files both include that header: each `.c`
  file gets its own copy of the function, and the linker refuses to
  build with the same function defined twice.
- **Defining a variable (not just a prototype) in a header** — the same
  problem as above, one level worse: `int total = 0;` sitting directly
  in a header, included by two different `.c` files, gives *each* `.c`
  file its own separate copy of `total`. The linker then reports
  `total` as multiply defined and refuses to build. Declarations
  (prototypes) belong in headers; the actual variable belongs in exactly
  one `.c` file.
- **Mixing up `"..."` and `<...>`** in `#include` — your own files use
  double quotes; standard library headers use angle brackets.
- **Forgetting to list every `.c` file** on the `gcc` command line, then
  being confused by an `undefined reference` linker error.
- **A Makefile recipe line indented with spaces instead of a tab** —
  `make` requires a literal tab character before every recipe line.

## Try it yourself

1. Work through every folder in [`examples/`](examples/), compiling and
   running each one — including deliberately reproducing (and then
   fixing) the duplicate-definition error in `03_include_guards_demo/`.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c) — split a
   single-file program into a header and source pair yourself.
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 14: multi-file programs"
   git push
   ```

Next: **[Module 15 — Debugging & Memory Safety](../15-debugging-and-memory-safety/README.md)**.
