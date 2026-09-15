# Module 12 — Linked Lists

## Hook: a treasure hunt made of pointers

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char clue[40];
    struct Node *next;
} Node;

int main(void) {
    // Build the treasure hunt by hand: four clues, each one pointing
    // to the next.
    Node *stop1 = malloc(sizeof(Node));
    Node *stop2 = malloc(sizeof(Node));
    Node *stop3 = malloc(sizeof(Node));
    Node *stop4 = malloc(sizeof(Node));

    snprintf(stop1->clue, sizeof(stop1->clue), "Look under the old oak tree");
    snprintf(stop2->clue, sizeof(stop2->clue), "Check behind the waterfall");
    snprintf(stop3->clue, sizeof(stop3->clue), "Search the lighthouse steps");
    snprintf(stop4->clue, sizeof(stop4->clue), "You found the treasure!");

    stop1->next = stop2;
    stop2->next = stop3;
    stop3->next = stop4;
    stop4->next = NULL;   // the last clue points nowhere -- hunt over

    Node *start = stop1;   // "start" is the only thing that remembers stop1

    Node *current = start;
    while (current != NULL) {
        printf("%s\n", current->clue);
        current = current->next;
    }

    free(stop1);
    free(stop2);
    free(stop3);
    free(stop4);
    return 0;
}
```

```bash
gcc hook.c -o hook
./hook
```

Four separate blocks of memory, allocated one at a time, each holding a
clue **and directions to the next one** — nothing but pointers holds
this chain together. `start` doesn't know about `stop2`, `stop3`, or
`stop4` directly; it only knows `stop1`, and `stop1` knows where
`stop2` is, and so on. Follow the chain far enough and you reach
`stop4`, whose `next` is `NULL` — the treasure, and the end of the
hunt. That chain is a **linked list**, and by the end of this module
you'll be adding stops to it, removing them, and cleaning the whole
thing up without losing a single node.

## Why not just use a bigger array?

Module 11 gave you `realloc` — an array that can grow. That solves
"I don't know how many elements I'll need," but it doesn't solve
everything. Picture removing the 3rd element out of 10,000 from an
array: elements 4 through 10,000 all have to physically shift one slot
to the left to close the gap. Insert something in the middle and
everything after it has to shift the other way to make room. For
**frequent insertions and deletions in the middle**, that shifting adds
up fast.

A linked list solves this differently: instead of one big contiguous
block, each element is its own small chunk of memory, and elements
point to their neighbors instead of sitting next to them. Removing an
element in the middle becomes "change where two pointers point" —
nothing shifts. The trade-off: you lose the array's instant
`arr[500]`-style access — to reach the 500th node you have to walk
there one `next` at a time. Arrays and linked lists are good at
opposite things; you'll pick whichever one fits the job.

## What is a node?

A **node** is a struct that holds data **plus a pointer to another node
of the same type**. That pointer-to-its-own-type is called a
**self-referential struct**, and it's the one new idea this whole
module is built on:

```c
typedef struct Node {
    int value;
    struct Node *next;   // a pointer to another Node
} Node;
```

Read that `next` line carefully — it says `struct Node *next`, not
`Node *next`. This trips up almost everyone the first time. The
`typedef` on the first line says "once this whole declaration is
finished, you may call this type `Node`" — but that name doesn't exist
*yet* while you're still in the middle of defining the struct's own
body. C already has a name you can use at that point, though: `struct
Node`, from `typedef struct Node {`. So inside the braces, before the
typedef is complete, you must write `struct Node *next` — after the
closing `} Node;`, everywhere else in your code, you can go back to
using the short name `Node`. See
[`examples/01_what_is_a_node.c`](examples/01_what_is_a_node.c).

## Building a list by hand

A list is just nodes, `malloc`'d one at a time and linked together with
plain assignments:

```c
Node *node1 = malloc(sizeof(Node));
Node *node2 = malloc(sizeof(Node));
Node *node3 = malloc(sizeof(Node));

node1->value = 10;
node2->value = 20;
node3->value = 30;

node1->next = node2;   // node1 points to node2
node2->next = node3;   // node2 points to node3
node3->next = NULL;    // node3 is last -- nothing after it

Node *head = node1;    // head remembers where the list starts
```

`head` is the only variable in this whole program that remembers where
`node1` lives. Everything else — `node2`, `node3`, the rest of the
list — is only reachable **by following `next` pointers starting from
head**. Hold onto that idea; it matters a lot later in this module.
See [`examples/02_building_a_list_by_hand.c`](examples/02_building_a_list_by_hand.c).

## Traversal: walking the list

To do anything with a list — print it, search it, count it — you walk
it with a separate pointer, conventionally called `current`, so you
never lose track of `head`:

```c
Node *current = head;
while (current != NULL) {
    printf("%d -> ", current->value);
    current = current->next;
}
printf("NULL\n");
```

`current` starts at `head` and moves one node at a time
(`current = current->next`) until it falls off the end of the list —
which is exactly when it becomes `NULL`. That `while (current != NULL)`
check is the heartbeat of almost every linked list function you'll
write. See [`examples/03_traversing_a_list.c`](examples/03_traversing_a_list.c).

## Inserting at the head

The cheapest possible insertion: point the new node at the current
head, then make the new node the head.

```c
Node *insertAtHead(Node *head, int value) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return head;   // allocation failed -- list unchanged
    }
    newNode->value = value;
    newNode->next = head;   // new node points at the OLD head first...
    return newNode;          // ...then becomes the new head
}
```

Order matters: `newNode->next = head;` has to happen **before**
`head` is overwritten, or you'd lose the rest of the list. That's why
the function returns the new head instead of modifying `head` in
place — the caller has to remember to do `head = insertAtHead(head, ...)`.
See [`examples/04_inserting_at_the_head.c`](examples/04_inserting_at_the_head.c).

## Inserting and deleting anywhere else

Inserting or deleting in the *middle* means walking to the node just
**before** the spot you care about, then relinking pointers around it.

Inserting after a target node:

```c
newNode->next = current->next;   // new node points to what used to be next
current->next = newNode;          // the node before it now points to new node
```

Deleting a node (not the head) needs a `previous` pointer alongside
`current`, so you can skip over the node being removed:

```c
previous->next = current->next;   // skip over the node being removed
free(current);
```

Deleting the **head** is a special case, because there's no `previous`
node to relink — you have to update `head` itself instead:

```c
if (head->value == value) {
    Node *doomed = head;
    head = head->next;
    free(doomed);
    return head;
}
```

See [`examples/05_inserting_and_deleting_anywhere.c`](examples/05_inserting_and_deleting_anywhere.c)
for both operations working together on the same list, insertions and
deletions verified against the expected list contents at each step.

## Freeing the whole list

Every node was `malloc`'d individually, so every node has to be `free`'d
individually — Module 11's rule about matching every `malloc` still
applies here, just once per node instead of once total. The tempting
but broken approach:

```c
// BROKEN -- do not do this:
Node *current = head;
while (current != NULL) {
    free(current);
    current = current->next;   // current was JUST freed -- reading
}                               // current->next here is undefined
                                // behavior, often a crash
```

The fix is one line of reordering: **save `next` before you free the
current node**, so you're never reading through memory you just
returned to the system.

```c
Node *current = head;
while (current != NULL) {
    Node *next = current->next;   // save it first
    free(current);                 // now safe to free current
    current = next;                // advance using the SAVED pointer
}
```

See [`examples/06_freeing_the_whole_list.c`](examples/06_freeing_the_whole_list.c).

## Don't lose the head

`head` is the single pointer your whole program uses to reach every
node in the list. If you ever overwrite it without freeing (or
otherwise saving) the list it used to point to —

```c
head = someBrandNewNode;   // the old list is now unreachable!
```

— every node the old `head` used to lead to is still sitting in memory,
still allocated, but there is no longer any pointer anywhere in your
program that remembers where any of them are. That's a **memory
leak**, and it's permanent for the life of the program: you can't
`free` what you can no longer reach. Always free (or deliberately hand
off to another pointer) a list's nodes before its `head` pointer gets
reassigned to something else.

## Common beginner mistakes

- Writing `Node *next;` instead of `struct Node *next;` inside the
  struct body — the typedef name doesn't exist yet at that point.
- Freeing a node and then reading `current->next` afterward — always
  save `next` into a local variable *before* calling `free`.
- Forgetting that insertion/deletion functions must **return** the
  (possibly new) head, and forgetting to write `head = theFunction(...)`
  at the call site — without it, changes to the head are silently lost.
- Overwriting `head` (or any pointer that's the only reference to part
  of a list) without freeing what it used to point to — an instant,
  unrecoverable leak.
- Deleting or inserting in the middle without keeping a `previous`
  pointer — you need the node *before* the target to relink around it.
- Forgetting the `NULL` check after `malloc` — a failed allocation
  returns `NULL`, and dereferencing it crashes the program (Module 11).

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 12: linked lists"
   git push
   ```

Next: **[Module 13 — Stacks & Queues](../13-stacks-and-queues/README.md)**.
