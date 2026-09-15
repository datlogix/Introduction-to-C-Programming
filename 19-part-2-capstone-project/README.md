# Module 19 — Part 2 Capstone Project

Part 1's capstone proved you could combine variables, control flow,
arrays, functions, pointers, structs, and file I/O into one real program.
This capstone raises the bar: your data now has to **grow**, your
program has to be **organized across files**, and at least one part of
it has to **recurse** — the actual dividing line between a beginner and
an intermediate C programmer.

## 1. Two ways to start

You have a genuine choice for this capstone:

- **Option A — Level up your Part 1 capstone.** Take the project you (or
  your team) built for [Module 9](../09-capstone-project/README.md) and
  rebuild its core data storage as a linked list instead of a fixed-size
  array, split the code across `.h`/`.c` files, and add a real recursive
  function somewhere it belongs. This is a great option if you're proud
  of what you already built and want to make it genuinely better rather
  than start over.
- **Option B — Pick a new project** from the menu in §4 below.

Either way, the requirements in §3 apply in full.

## 2. Teams and GitHub Classroom

Team formation works exactly like Module 9: your instructor announces
the class size, which sets pairs (2:1, ≤20 students), groups of four
(4:1, >20 students), or an approved solo "daring" track (1:1 — same core
requirements, plus every stretch goal). If your class is continuing
straight from Part 1, you may keep the same team, or your instructor may
have you re-form them — check before Sprint 0. Team formation and repo
setup happen through a GitHub Classroom Group Assignment exactly as
described in [Module 9 §2](../09-capstone-project/README.md#2-forming-your-team-in-github-classroom).

## 3. Requirements for every project (Option A or B)

- **A dynamically-growing data structure**, built with `malloc`/`free`
  (Module 11) — a linked list, stack, or queue (Modules 12–13). A
  fixed-size array standing in for "the list" does not satisfy this.
- **No memory leaks.** Every `malloc` needs exactly one matching `free`.
  Document in your README how you verified this — `valgrind` if your
  platform supports it (Module 15), or a careful manual audit of every
  allocation if not.
- **At least one genuinely recursive function**, used because the
  problem calls for it — not bolted on to satisfy this checklist.
- **Code organized across multiple `.c`/`.h` files** with include guards
  (Module 14) — not one giant `main.c`.
- **Everything Part 1 already required still applies**: structs, file
  I/O so your data survives a restart, functions with clear jobs,
  pointers used with intention, a clean `gcc -Wall` build, and a project
  README a stranger could build and run unaided.
- A menu-driven **or** command-line-argument-driven interface (Module 17)
  — pick whichever fits your project better, and say which you chose and
  why in your README.

## 4. Project menu (if you're not leveling up your Part 1 project)

1. **Task Manager** — a linked list of dynamically allocated tasks:
   add, complete, delete, reorder, saved to a file. *Stretch:* sort by
   priority (Module 18), an undo stack (Module 13) for the last change.
2. **Library System v2** — Module 9's library idea, rebuilt on a linked
   list catalog instead of a fixed array, so it can hold any number of
   books. *Stretch:* binary search (Module 18) over a sorted snapshot.
3. **Music Playlist Manager** — a linked list of songs: add, remove,
   reorder, shuffle, save/load. *Stretch:* an undo stack for the last
   edit.
4. **Undo/Redo Simulator** — two stacks (undo and redo) of dynamically
   allocated action records, simulating a text editor's edit history.
   *Stretch:* persist the history to a file.
5. **Command-Line Notes Tool** — a real CLI utility (Module 17,
   `argc`/`argv`-driven, no interactive menu) that appends, lists, and
   deletes notes stored in a linked list synced to a file, organized
   across multiple files. *Stretch:* search notes by keyword.
6. **Maze Solver** — recursive backtracking (Module 10) through a small
   grid maze, finding and printing a path. *Stretch:* load the maze from
   a file.
7. **Polynomial Calculator** — represent a polynomial as a linked list of
   `(coefficient, exponent)` nodes; add two polynomials together and
   print the result. *Stretch:* multiply two polynomials.

Have your own idea? Propose it to your instructor — as long as it
satisfies every requirement in §3, it's fair game.

## 5. Suggested timeline

| Sprint | Focus | Git evidence expected |
|---|---|---|
| Sprint 0 | Team formed, project chosen, the dynamic data structure designed on paper, header file layout planned | An initial commit with your struct/node definitions and a `.h` file skeleton |
| Sprint 1 | The dynamic structure works in memory (create/insert/delete/traverse), no persistence yet | Several small commits, each compiling cleanly |
| Sprint 2 | File I/O persistence, and the code actually split across `.c`/`.h` files | A commit where you can close and reopen the program without losing data |
| Sprint 3 | Recursion integrated meaningfully, interface polish, edge cases | Commits addressing specific bugs/edge cases you found |
| Final | Leak-free (documented), `-Wall`-clean build, finished README, last push before deadline | Your final commit *is* your submission |

## 6. How this gets assessed

- **Correctness** — does it do what it claims, including edge cases
  (an empty list, a full free-and-reload cycle, bad input)?
- **Memory discipline** — every `malloc` freed, no leaks, no
  use-after-free.
- **Meaningful use of recursion, linked structures, and multi-file
  organization** — used appropriately, not bolted on.
- **Code organization** — logically split across functions and files,
  consistent style, comments where the *why* isn't obvious.
- **Git history and documentation** — regular, meaningful commits from
  every team member under their own name, and a README a stranger could
  build and run unaided.

## Try it yourself

1. Confirm your team (or solo status) in GitHub Classroom.
2. Decide: level up your Part 1 project, or pick a new one from §4.
3. Design your core data structure on paper before writing code.
4. Work through the sprints in §5, committing and pushing regularly.
5. Submit by pushing your final commit before the deadline.

You've now built two real, working programs — one straightforward, one
that manages its own memory correctly. That second one is the actual
skill that separates "I can write C" from "I've written some C once."
