# Module 7 Project — Pointer Playground

Remember the swap hook from the top of this module's README? `swapBroken`
couldn't touch the caller's variables, but `swapWorks` could -- because it
had their addresses. You're about to use that same trick for something
genuinely useful: **returning two answers from one function call.**

In C, a function can only `return` a single value. But what if you need an
array's smallest AND largest value at the same time? Without pointers,
you'd have to scan the array twice (once per answer) or fake it with
global variables. With pointers, one function can fill in both answers in
a single pass -- by writing directly into the caller's variables through
their addresses.

## Requirements

Your program must:

1. Declare an array of at least **8 integers**, with values you choose
   (not all the same value).
2. Write a function
   ```c
   void findMinAndMax(int arr[], int size, int *min, int *max);
   ```
   that scans the array **once** and stores the smallest value at `*min`
   and the largest value at `*max`.
3. Write a function
   ```c
   void scaleArray(int arr[], int size, int factor);
   ```
   that multiplies every element of the array by `factor`, modifying the
   original array in place (this works for the same reason `sumArray`
   worked in the examples -- the array decays to a pointer, so the
   function is already working on the real data, not a copy).
4. In `main()`:
   - Print the array before scaling.
   - Call `findMinAndMax` and print both results, labeled.
   - Call `scaleArray` with a factor of your choice, then print the array
     again to prove it actually changed.
   - Print the **memory address** of the array's first element (using
     `%p`) and the address of your `min` and `max` variables, to build
     intuition that these are all just numbers pointing at real locations
     in memory.
5. Include at least one comment explaining *why* pointers were necessary
   for `findMinAndMax` specifically (i.e. what you'd lose without them).

## Ideas if you're stuck

- Use test scores, temperatures, or game high scores as your array's
  theme -- pick something where "find the min and max" is a natural
  thing to want.
- Add a third pointer output parameter, `int *sum`, that also totals the
  array in the same pass.
- Print a small "before vs after" table once you've scaled the array.

## Getting started

Open [`starter.c`](starter.c) and build from there. Compile and run often.

```bash
gcc starter.c -o playground
./playground
```

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 7 project: pointer playground"
git push
```

Next: **[Module 8 — Structs & File I/O](../../08-structs-and-files/README.md)**.
