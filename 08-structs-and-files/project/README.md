# Module 8 Project — Persistent Contact Book

Remember the hook from the top of this module's README? You ran a program
that "remembered" your high score across two separate runs, just by
saving it to a file. You're building a bigger version of that same trick
now: a contact book that adds and lists contacts through a menu, and
never forgets a contact once you've added it -- even after you close the
program and open it again.

## Requirements

Your program must:

1. Define a `Contact` struct (use `typedef`) with at least: `name`,
   `phone`, and one more field of your choice (e.g. `email` or
   `category`).
2. Store contacts in an **array of structs** (a fixed-size array, e.g.
   `Contact contacts[50];`, is fine -- no dynamic memory needed for this
   module).
3. On startup, **load** any contacts already saved in a data file into
   that array, if the file exists.
4. Show a **menu loop** (reusing Module 4's control structures) with at
   least these options:
   - **Add** a new contact (read fields with `scanf`/`fgets`, store them
     in the array).
   - **View** all contacts (loop over the array and print each one).
   - **Save & exit** (write every contact in the array out to the data
     file with `fprintf`, then `fclose` it before quitting).
5. Use **at least one function that receives the contacts array by
   pointer** to either add to it or print it (mirroring
   `exercises/exercise1.c` and Module 7's pass-by-pointer lesson) --
   don't do everything inline in `main`.
6. **Always check `fopen`'s return value for `NULL`** before using it --
   on first run, the data file won't exist yet, and your program should
   handle that gracefully (start with zero contacts) instead of
   crashing.

## Ideas if you're stuck

- Can't decide on a third field? `email`, `category` (e.g. "family",
  "work"), or `notes` all work fine.
- Keep the file format simple: one contact per line, fields separated by
  spaces, read back with `fscanf` -- exactly like `examples/06` and
  `examples/07`.
- Not required, but fun stretch goals if you finish early: a "delete
  contact" option, searching by name, or counting contacts by category.

## Getting started

Open [`starter.c`](starter.c) and build from there. Compile and run
often -- don't write the whole menu before testing your first option.

```bash
gcc -Wall starter.c -o contacts
./contacts
```

**This project only proves itself across two runs.** Add a contact and
choose "Save & exit," then run `./contacts` again -- your contact should
already be there when you choose "View," before you've added anything in
this second run. That's the whole point: the data survived the program
closing.

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 8 project: persistent contact book"
git push
```

Next: **[Module 9 — Capstone Project](../../09-capstone-project/README.md)**.
