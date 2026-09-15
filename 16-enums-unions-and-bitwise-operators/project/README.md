# Module 16 Project — Permission Flags System

The hook packed eight independent yes/no permissions into a single `int`
and flipped exactly one of them with `|=`. Now you'll build out the full
toolkit around that idea: a small set of functions that grant, revoke,
check, and print a user's permissions, all backed by one `int` and the
bitwise patterns from this module.

## Requirements

Your program must:

1. Define at least four flag constants — `READ`, `WRITE`, `EXECUTE`,
   `DELETE` (or a permission set of your own choosing) — each a distinct
   power of two, using `#define` and either literal values (`1`, `2`,
   `4`, `8`) or `1 << n`.
2. Store a single user's permissions in one `int` variable.
3. Write `void grantPermission(int *permissions, int flag);` — turns one
   flag **on** using `|=`, without disturbing any other flag.
4. Write `void revokePermission(int *permissions, int flag);` — turns one
   flag **off** using `&= ~`, without disturbing any other flag.
5. Write `int hasPermission(int permissions, int flag);` — returns
   nonzero if `flag` is set, `0` otherwise, using `&`.
6. Write `void printPermissions(int permissions);` — prints a
   human-readable summary of every flag and whether it's currently set,
   e.g. `READ: yes` / `WRITE: no` on its own line for each flag.
7. In `main`, demonstrate the whole system: start from `0`, grant a few
   permissions, check some with `hasPermission`, revoke one, and print
   the summary before and after the revoke — so it's visible that
   revoking one flag left every other flag untouched, exactly like the
   hook.

## Ideas if you're stuck

- Start with exactly the four flags in the requirements before adding
  more — get grant/revoke/check/print working end to end first.
- `grantPermission` and `revokePermission` take a **pointer** to the
  permissions variable (`int *permissions`) so they can modify the
  caller's variable directly — this is the same pattern Module 7 taught
  you for any function that needs to change a variable back in `main`.
- If you want a challenge, add a fifth flag (e.g. `SHARE`, like the hook)
  and a function that grants *several* flags at once by OR-ing them
  together before passing them in: `grantPermission(&perms, READ | WRITE);`
  works today's `|=` code without any changes, since OR-ing two already-OR'd
  flags together still just turns more distinct bits on.

## Getting started

Open [`starter.c`](starter.c) and fill in the flags and functions. Compile
and run often.

```bash
gcc starter.c -o permissions
./permissions
```

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 16 project: permission flags system"
git push
```

Next: **[Module 17 — Command-Line Arguments & CLI Tools](../../17-command-line-arguments-and-cli-tools/README.md)**.
