# Module 13 — Stacks & Queues

## Hook: building your own Ctrl+Z

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    const char *action;
    struct Node *next;
} Node;

Node* push(Node *top, const char *action) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("malloc failed -- history unchanged.\n");
        return top;
    }
    newNode->action = action;
    newNode->next = top;
    return newNode;
}

Node* pop(Node *top) {
    if (top == NULL) {
        printf("Nothing left to undo.\n");
        return NULL;
    }
    printf("Undoing: %s\n", top->action);
    Node *oldTop = top;
    top = top->next;
    free(oldTop);
    return top;
}

int main(void) {
    Node *history = NULL;

    history = push(history, "Typed 'Hello'");
    printf("Did: Typed 'Hello'\n");
    history = push(history, "Typed ', world!'");
    printf("Did: Typed ', world!'\n");
    history = push(history, "Deleted a paragraph");
    printf("Did: Deleted a paragraph\n");

    printf("\nPressing Ctrl+Z three times:\n");
    history = pop(history);
    history = pop(history);
    history = pop(history);

    return 0;
}
```

```bash
gcc hook.c -o hook
./hook
```

Three actions go in, and three actions come back out in exactly the
**reverse** order — the last thing you did is the first thing undone.
That's not a coincidence; it's the entire idea behind this module,
already working. By the end of this module you'll understand exactly
why `push`/`pop` naturally produce that reversal, you'll meet its
opposite (a structure where the *first* thing in is the first thing
out), and you'll build a small interactive text editor with real undo
in this module's project. See
[`examples/04_undo_simulation_with_a_stack.c`](examples/04_undo_simulation_with_a_stack.c)
for this exact program.

## LIFO vs. FIFO: two disciplines for ordering data

A **stack** and a **queue** are both just linked lists (Module 12) —
the *only* difference is a rule about which end you're allowed to add
to and remove from:

- A **stack** is **LIFO** — **L**ast **I**n, **F**irst **O**ut. Whatever
  you added most recently is the first thing that comes back out. Think
  of a stack of plates: you add to the top, and you take from the top.
  That's exactly what the hook just demonstrated — `push` added to one
  end, and `pop` removed from that *same* end, which is why the order
  came back reversed.
- A **queue** is **FIFO** — **F**irst **I**n, **F**irst **O**ut.
  Whatever you added *first* is the first thing that comes back out.
  Think of a line at a checkout counter: you join at the back, and
  you're served from the front. Add at one end, remove from the
  *other* end, and the order comes back the same as it went in.

Everything else in this module is really just: how do you build each of
these on top of a linked list, and why does a queue need a little more
bookkeeping than a stack does?

## Implementing a stack with a linked list

A stack needs exactly two operations: **push** (add a new item) and
**pop** (remove and return the most recently added item). If you did
Module 12's insert-at-head exercise, you've already written half of
this — pushing onto a stack IS inserting a new node at the head of a
linked list:

```c
typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* push(Node *top, int value) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("malloc failed -- stack unchanged.\n");
        return top;
    }
    newNode->value = value;
    newNode->next = top;
    return newNode;
}
```

We call the head pointer `top` here instead of `head` — same pointer,
different name, because stack terminology talks about the "top" of the
stack rather than the "front" of a list. `pop` is remove-the-head, with
one rule that matters more here than it ever did for a plain linked
list: **always check for an empty stack before popping.**

```c
Node* pop(Node *top, int *poppedValue) {
    if (top == NULL) {              // ALWAYS check this first
        printf("Stack is empty -- cannot pop.\n");
        return NULL;
    }
    Node *oldTop = top;
    *poppedValue = top->value;
    top = top->next;
    free(oldTop);
    return top;
}
```

Skipping that check means dereferencing `top->value` when `top` is
`NULL` — an instant crash. Because `push` and `pop` only ever touch the
head, neither one has to walk the list, so both run in constant time no
matter how large the stack gets. See
[`examples/01_stack_push_and_pop.c`](examples/01_stack_push_and_pop.c).

## A simpler alternative: array-based stacks

A linked-list stack can grow without limit — every `push` just mallocs
one more node. But sometimes you know in advance you'll never need more
than, say, 100 items, and in that case a plain array is a simpler
alternative: no `malloc`, no `free`, no pointers to chase, just an
array and an integer tracking the index of the top element (`-1` means
empty).

The tradeoff is the mirror image of the linked-list version: **simpler
code, but a fixed maximum size decided at compile time** — push past
that limit and you have to explicitly refuse, instead of just
allocating another node. Neither approach is "better" in general; pick
the one that matches what you actually know about your data ahead of
time. See
[`examples/02_array_based_stack_alternative.c`](examples/02_array_based_stack_alternative.c).

## Implementing a queue with a linked list

A queue needs **enqueue** (add to the back of the line) and
**dequeue** (remove from the front). This is where a queue genuinely
needs more than a stack does: enqueue adds at the **tail**, dequeue
removes from the **head** — two different ends.

If you only tracked a head pointer, `enqueue` would have to walk the
*entire* list every single time, just to find the last node to attach
the new one to — that's an O(n) operation that gets slower as the queue
grows, for something that should be instant. The fix is to track a
**tail pointer too**, updated on every enqueue, so you always know
exactly where the last node is without looking:

```c
typedef struct {
    Node *head;   // front of the line -- dequeue removes from here
    Node *tail;   // back of the line -- enqueue adds here
} Queue;

void enqueue(Queue *q, int value) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("malloc failed -- queue unchanged.\n");
        return;
    }
    newNode->value = value;
    newNode->next = NULL;

    if (q->tail == NULL) {          // queue was empty
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
}
```

Because enqueue and dequeue each need to update *two* pointers at once
(head and tail), we pass a **pointer to the whole `Queue` struct**
(Module 7/8's `->` operator) instead of returning a new value the way
`push` did for the single-pointer stack. `dequeue` has the same
empty-check discipline as `pop` — plus one extra rule:

```c
int dequeue(Queue *q, int *value) {
    if (q->head == NULL) {          // ALWAYS check this first
        printf("Queue is empty -- cannot dequeue.\n");
        return 0;
    }
    Node *oldHead = q->head;
    *value = oldHead->value;
    q->head = oldHead->next;

    if (q->head == NULL) {          // that was the last node --
        q->tail = NULL;             // the tail must be reset too
    }

    free(oldHead);
    return 1;
}
```

That last `if` matters: after removing the only node in the queue,
`head` correctly becomes `NULL` on its own, but `tail` does **not** —
it's still pointing at the node you just freed unless you reset it
yourself. Forgetting this leaves `tail` **dangling** (pointing at freed
memory), and the next `enqueue` would write through it and corrupt the
heap. See
[`examples/03_queue_enqueue_and_dequeue.c`](examples/03_queue_enqueue_and_dequeue.c).

## Real-world use cases

- **Stacks power undo history.** Every "undo" button you've ever used —
  in a text editor, an image editor, your browser's back button — is
  LIFO by nature: the most recent action is always the first one
  reversed. See
  [`examples/04_undo_simulation_with_a_stack.c`](examples/04_undo_simulation_with_a_stack.c),
  which is the hook above.
- **Queues power task and print queues.** When several jobs are
  requested and handled one at a time, fairness usually means FIFO:
  whoever asked first gets served first. See
  [`examples/05_task_queue_simulation.c`](examples/05_task_queue_simulation.c),
  a small print-queue simulation.

## Common beginner mistakes

- **Popping or dequeuing without checking for empty first** — the
  single most common bug in this module. `top == NULL` or
  `q->head == NULL` must be checked *before* touching `->value`.
- **Mixing up which end a queue operates on** — enqueue at the tail,
  dequeue at the head. Doing both at the same end turns your "queue"
  into a stack by accident.
- **Forgetting to reset `tail` to `NULL`** when `dequeue` removes the
  last node, leaving it dangling and corrupting the next `enqueue`.
- **Forgetting to `free` a popped/dequeued node** — same rule as Module
  11 and 12: every node that came from `malloc` needs exactly one
  matching `free`, whether it leaves the structure through pop,
  dequeue, or a full cleanup loop at the end of the program.
- **Assuming a stack and a queue are "the same thing with different
  names."** The node struct is identical; the *rule about which end you
  touch* is the entire difference, and it's what makes one LIFO and the
  other FIFO.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 13: stacks and queues"
   git push
   ```

Next: **[Module 14 — Multi-File Programs](../14-multi-file-programs/README.md)**.
