# Module 13 Project — Text Editor Undo Stack

The hook simulated a fixed, pre-written sequence of edits and undid
three of them. This project makes it interactive: you'll build a tiny
text editor that types one word at a time from user input, keeps every
typed word on a stack, and supports a real `undo` command that pops the
most recently typed word off — exactly like Ctrl+Z.

## Requirements

Your program must:

1. Define a stack node holding one word (a fixed-size `char` array, e.g.
   `char word[50]`) and a `next` pointer — the same node shape used
   throughout this module's examples, just with a word instead of an
   `int`.
2. Read tokens one at a time from the user with `scanf("%s", ...)` in a
   loop, stopping when the token is `"quit"`.
3. If the token is `"undo"`: pop the most recently typed word off the
   stack and print what was undone. **Check for an empty stack before
   popping** — undoing with nothing typed yet must not crash.
4. If the token is anything else, treat it as a typed word: push it onto
   the stack and print a confirmation.
5. After every push or undo, print the current state of the document —
   every word still on the stack, in the order they were **originally
   typed** (oldest first), not stack order (which is newest-on-top).
   This needs a little thought: the stack itself only gives you easy
   access newest-first. See "Ideas if you're stuck" below.
6. When the user types `"quit"`, free every remaining node before the
   program exits — no leaked memory.

## Ideas if you're stuck

- Printing oldest-first from a structure that's naturally newest-first
  is exactly the kind of problem Module 10 (Recursion) solves well:
  write a recursive print function that calls itself on `top->next`
  *first*, and only prints `top->data` (or `top->word`) on the way back
  out — the same "print after the recursive call" trick as
  `examples/01_countdown_no_loop.c` from that module. The bottom of the
  stack (typed first) ends up printed first.
- Try it on paper with 3 words before you trust the code: push `"the"`,
  `"quick"`, `"fox"` — the stack has `fox -> quick -> the -> NULL`, but
  the document should print as `the quick fox`.
- A sample interaction:

  ```
  > the
  Typed: the
  Document: the

  > quick
  Typed: quick
  Document: the quick

  > undo
  Undid: quick
  Document: the

  > quit
  ```

## Getting started

Open [`starter.c`](starter.c) and build inside the TODOs. Compile and
run often — test with two or three words and one undo before trying a
longer session.

```bash
gcc starter.c -o editor
./editor
```

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 13 project: text editor undo stack"
git push
```

Next: **[Module 14 — Multi-File Programs](../../14-multi-file-programs/README.md)**.
