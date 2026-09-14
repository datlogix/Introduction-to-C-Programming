# Introduction to C Programming — A Beginner's Course

Welcome! This course takes you from **never having written a line of
code** to **building a multi-file C project with pointers, structs, and
file I/O, tracked in Git and submitted through GitHub Classroom.** No
prior programming experience is assumed.

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
   `TODO` markers. A `solutions/` folder sits next to them — try for at
   least 15 minutes before you look.
4. **`project/`** — a small, fun program that only uses what you've
   learned *so far*. This is the payoff for the module — something you'd
   actually want to show a friend.

## Roadmap

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

Every exercise, module project, and the capstone are submitted through
**GitHub Classroom**, not by email or file upload:

- Individual modules (0–8): you accept a per-student assignment link once
  (Module 0 walks through this), which gives you your own private repo.
  Commit and push your work there as you go — the last commit before a
  deadline is what gets graded.
- The capstone (Module 9): a **group assignment** — GitHub Classroom
  creates one shared repo per team. See
  [Module 9](09-capstone-project/README.md) for exactly how teams are
  formed and how many people are on yours.

## Prerequisites

None, other than curiosity and a willingness to make (and fix) mistakes.
Mistakes are not a sign you're bad at this — they're the main way anyone
learns to program. Start with [Module 0: Setup](00-setup/README.md).
