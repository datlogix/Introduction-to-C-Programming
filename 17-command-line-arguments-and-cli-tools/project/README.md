# Module 17 Project — Mini Word-Count Tool

The hook at the top of this module showed `greet` doing two different
jobs from the exact same compiled program, driven only by what you typed
after its name. This project builds a small, genuinely useful version of
that idea: a `wc`-style word-count tool that reads a real file and
reports on it, entirely controlled by command-line arguments.

## Requirements

Your program must:

1. Take a **filename** as its first command-line argument (`argv[1]`).
   If no filename is given, print a usage message (showing how the
   program should be called) and return `1` — don't try to open a file
   that was never given.
2. Support three optional flags, in any order, after the filename:
   `--lines`, `--words`, and `--chars`.
3. If **none** of the three flags are given, print all three counts (the
   same way the real `wc` command behaves with no flags). If **one or
   more** flags are given, print only the counts that were requested.
4. Open the file with `fopen()` in `"r"` mode and **check the result for
   `NULL`** before using it (Module 8's rule) — print an error message
   and return `1` if the file can't be opened.
5. Count, in a single pass over the file with `fgetc()`:
   - **Characters** — every character read before `EOF`.
   - **Lines** — every `'\n'` encountered.
   - **Words** — every transition from "not inside a word" to "inside a
     word," the same counting technique as
     [`examples/03_a_real_cli_tool_word_counter.c`](../examples/03_a_real_cli_tool_word_counter.c).
6. `fclose()` the file once you're done reading it.
7. Label your output clearly, e.g. `Lines: 2`, `Words: 9`,
   `Characters: 44`.

## Ideas if you're stuck

- Build it in stages: get the filename-only version (counting
  everything, no flags) working and tested first, *then* add flag
  parsing on top of a working program.
- Three `int` flags (`showLines`, `showWords`, `showChars`), all
  starting at `0`, set to `1` by a `strcmp` loop over `argv[2..argc-1]`
  — exactly the pattern in
  [`examples/02_reading_named_flags.c`](../examples/02_reading_named_flags.c).
  After the loop, if all three are still `0`, set all three to `1`.
- One `while ((c = fgetc(file)) != EOF)` loop can update all three
  counters at once — you don't need three separate passes over the
  file.
- Create a small test file yourself before you start, e.g.:

  ```bash
  printf "the quick brown fox\njumps over the lazy dog\n" > sample.txt
  wc sample.txt
  ```

  Compare your program's output against the real `wc` command's — they
  should agree.

## Getting started

Open [`starter.c`](starter.c) — it has the requirements broken into
`TODO` comments in the order you'll likely want to tackle them. Compile
and test often, starting with a small file.

```bash
gcc starter.c -o wordcount
./wordcount sample.txt
./wordcount sample.txt --words
./wordcount sample.txt --lines --chars
./wordcount
```

That last invocation (no arguments at all) should print your usage
message, not crash.

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 17 project: mini word-count tool"
git push
```

Next: **[Module 18 — Sorting & Searching Algorithms](../../18-sorting-and-searching-algorithms/README.md)**.
