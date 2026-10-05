# Introduction to C Programming

Welcome! This course takes you from **never having written a line of
code** to **designing your own leak-free, multi-file data structures**,
tracked in Git and submitted through GitHub Classroom. No prior
programming experience is assumed.

The course comes in two parts:

- **Part 1 — Modules 0–9.** Zero to a working, file-backed C program:
  syntax, types, control flow, arrays and strings, functions, pointers,
  structs, and a team capstone.
- **Part 2 — Modules 10–19.** The actual dividing line between "I can
  write C" and "I've written some C once": recursion, dynamic memory,
  linked lists and the structures built on them, multi-file program
  organization, debugging tools, and a second, harder capstone.

Part 2 assumes Part 1 is finished — Module 10 does not re-explain
anything from Modules 0–9.

## Built to work with or without a lecturer in the room

Every lesson is written so you can teach yourself from it directly — the
*why* always comes before the *how*, every claim is backed by code you
actually run, and nothing assumes a lecturer will fill in a gap out loud.
If you have an instructor, they'll add depth, war stories, and live
debugging. If you don't, you can still get every concept from the page.

## Every module starts with a hook

Before any theory, every module opens with a **Hook** — a short, genuinely
fun demo or puzzle you run *first*, before you understand how it works.
Curiosity ("wait, why did that happen?") is the entire teaching strategy —
it's a far stronger reason to keep going than "you'll need this later."
By the end of each module you'll understand exactly how your own hook
worked.

## How this course is built

Every module (after Setup) follows the same shape:

1. **`README.md`** — the lesson. A hook first, then concepts explained in
   plain language, with common beginner mistakes called out explicitly.
2. **`examples/`** — small, runnable `.c` files that demonstrate exactly
   one idea at a time. Compile and run every single one yourself. Reading
   code you didn't type teaches you far less than watching your own build
   succeed (or fail) at the terminal.
3. **`exercises/`** — practice problems with starter files containing
   `TODO` markers. Reference solutions aren't included in this repo — your
   instructor shares them after the deadline, so give each exercise a real
   attempt (at least 15 minutes) and use your compiler output and
   debugging to check your own work.
4. **`project/`** — a small, fun program that only uses what you've
   learned *so far*. This is the payoff for the module — something you'd
   actually want to show a friend.

## Roadmap

### Part 1

| # | Module | You will be able to... |
|---|--------|------------------------|
| 0 | [Setup: Tools, Git & GitHub Classroom](00-setup/README.md) | Install a compiler, use VS Code, and submit work through GitHub Classroom |
| 1 | [Basics of Programming](01-basics-of-programming/README.md) | Explain how a C program becomes a running program, and write/compile your first one |
| 2 | [Data Types & Operators](02-data-types-and-operators/README.md) | Choose the right type for a piece of data and compute with it correctly |
| 3 | [Variables & Input/Output](03-variables-and-io/README.md) | Store data, name it well, and write programs that talk back to the user |
| 4 | [Control Structures](04-control-structures/README.md) | Make decisions (`if`/`switch`) and repeat work (loops) |
| 5 | [Arrays & Strings](05-arrays-and-strings/README.md) | Store and process collections of values and text |
| 6 | [Functions](06-functions/README.md) | Break a program into reusable, named, testable pieces |
| 7 | [Pointers](07-pointers/README.md) | Work directly with memory addresses — the idea that makes C, C |
| 8 | [Structs & File I/O](08-structs-and-files/README.md) | Design your own data records and make programs remember things after they close |
| 9 | [Capstone Project](09-capstone-project/README.md) | Combine everything into one real program, built in a team and submitted via GitHub Classroom |

### Part 2

| # | Module | You will be able to... |
|---|--------|------------------------|
| 10 | [Recursion](10-recursion/README.md) | Write a function that calls itself correctly, and trace its call stack by hand |
| 11 | [Dynamic Memory Allocation](11-dynamic-memory-allocation/README.md) | Use `malloc`/`calloc`/`realloc`/`free` and stop being limited to fixed-size arrays |
| 12 | [Linked Lists](12-linked-lists/README.md) | Build a growable data structure from structs, pointers, and dynamic memory |
| 13 | [Stacks & Queues](13-stacks-and-queues/README.md) | Implement LIFO/FIFO structures and recognize where each applies |
| 14 | [Multi-File Programs](14-multi-file-programs/README.md) | Split a program across `.h`/`.c` files with include guards, and compile them together |
| 15 | [Debugging & Memory Safety](15-debugging-and-memory-safety/README.md) | Use `gdb` and `valgrind` to find a crash's real cause and catch memory leaks |
| 16 | [Enums, Unions & Bitwise Operators](16-enums-unions-and-bitwise-operators/README.md) | Model fixed states cleanly and manipulate individual bits |
| 17 | [Command-Line Arguments & CLI Tools](17-command-line-arguments-and-cli-tools/README.md) | Read `argc`/`argv` and build a real terminal tool, not just a menu loop |
| 18 | [Sorting & Searching Algorithms](18-sorting-and-searching-algorithms/README.md) | Implement classic sorts and searches, with an intuition for why some are faster |
| 19 | [Part 2 Capstone Project](19-part-2-capstone-project/README.md) | Build a leak-free, multi-file program on a dynamic data structure, submitted via GitHub Classroom |

## Ground rules for how we'll work

- **Type the code yourself.** Copy-pasting defeats the purpose — your
  fingers and your mistakes are how the syntax sticks.
- **Read every compiler error fully**, top to bottom, before asking for
  help. The first error in a long list is usually the real one; everything
  after it is often noise caused by that first mistake.
- **Compile often.** Write 3–5 lines, then compile. Don't write 100 lines
  and try to debug them all at once.
- **Commit often.** After finishing an example, exercise, or project step,
  commit it. Module 0 shows you exactly how. Small, frequent commits are a
  professional habit you're building from day one — and they're also your
  evidence of steady progress once the capstone is a team project.

## How work gets submitted

Every exercise, module project, and both capstones are submitted through
**GitHub Classroom**, not by email or file upload:

- Individual modules (0–8, 10–18): you accept a per-student assignment
  link once (Module 0 walks through this), which gives you your own
  private repo. Commit and push your work there as you go — the last
  commit before a deadline is what gets graded.
- The capstones (Module 9, Module 19): each is a **group assignment** —
  GitHub Classroom creates one shared repo per team. See
  [Module 9](09-capstone-project/README.md) and
  [Module 19](19-part-2-capstone-project/README.md) for exactly how
  teams are formed and how many people are on yours.

## Prerequisites

None, other than curiosity and a willingness to make (and fix) mistakes.
Mistakes are not a sign you're bad at this — they're the main way anyone
learns to program. Start with [Module 0: Setup](00-setup/README.md).

Douglas Ayitey
