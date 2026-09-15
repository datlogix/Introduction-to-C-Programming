# Module 12 Project — Grocery List Manager

The hook chained a handful of nodes together by hand and followed them
like clues in a treasure hunt. A real linked list needs the same
chain, but built and rearranged *while the program runs* — items get
added, items get bought and removed, and the list has to stay correctly
linked through all of it. That's exactly what a grocery list needs.

## Requirements

Your program must:

1. Define an `Item` struct (a node) holding a name (`char[30]` or
   similar), a quantity (`int`), and a `struct Item *next` pointer.
2. Implement `addItem` — allocates a new node and inserts it into the
   list (inserting at the head is simplest and is fine).
3. Implement `removeItem` — finds the first item matching a given name,
   unlinks it from the list, and frees it. Handle removing the head
   correctly, and handle "name not found" without crashing.
4. Implement `printList` — walks the list and prints every item's name
   and quantity. Print something sensible for an empty list.
5. In `main()`, build a grocery list of at least 4 items, print it,
   remove at least one item (including a case that removes the current
   head), and print the list again to show the change.
6. Before the program exits, **free every remaining node** — no leaks.
   Use the "save `next` before freeing" pattern from
   [`examples/06_freeing_the_whole_list.c`](../examples/06_freeing_the_whole_list.c).

## Ideas if you're stuck

- Copy the shape of `insertAtHead` and `deleteValue` from
  [`examples/05_inserting_and_deleting_anywhere.c`](../examples/05_inserting_and_deleting_anywhere.c)
  — `addItem`/`removeItem` are almost the same functions with a struct
  swapped in for a plain `int`.
- Use `strncpy(item->name, name, sizeof(item->name) - 1);` and
  manually set the last byte to `'\0'` when copying a name into a
  fixed-size `char` array, so a too-long name can't overflow it.
- If you want a challenge: add an `updateQuantity(head, name, newQty)`
  function that walks the list and edits a matching node's quantity in
  place, without allocating or freeing anything.

## Getting started

Open [`starter.c`](starter.c) — the `Item` struct and function
prototypes' TODOs are laid out for you. Compile and test often, and
test removal for a name at the head, in the middle, at the end, and a
name that isn't in the list at all.

```bash
gcc starter.c -o grocery
./grocery
```

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 12 project: grocery list manager"
git push
```

Next: **[Module 13 — Stacks & Queues](../../13-stacks-and-queues/README.md)**.
