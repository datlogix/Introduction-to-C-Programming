#include <stdio.h>
#include <stdlib.h>

/*
A queue is also built on a linked list -- but unlike a stack, it needs
BOTH ends of the list: new items join at the TAIL (enqueue), and items
leave from the HEAD (dequeue). That's what makes it FIFO instead of
LIFO.

A single Node* isn't enough to do this efficiently. If we only tracked
the head, enqueue would have to walk the entire list every single time
just to find the last node to attach to -- O(n) instead of O(1), and it
gets slower as the queue grows. So a queue is usually represented as a
small struct holding BOTH a head pointer and a tail pointer, kept in
sync on every enqueue and dequeue.

Because two pointers need to change together, we pass a POINTER to the
Queue struct into enqueue/dequeue (Module 7/8) instead of returning a
new value, the way push/pop did for the single-pointer stack.
*/

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;   // the front of the line -- dequeue removes from here
    Node *tail;   // the back of the line -- enqueue adds here
} Queue;

// Enqueue: attach a new node after the current tail, then move the
// tail pointer to point at it. Special case: an empty queue has no
// tail to attach to, so the new node becomes both head and tail.
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

// Dequeue: remove the head node, hand its value back through *value,
// and move the head pointer forward. ALWAYS check for an empty queue
// (head == NULL) first. If removing the last node empties the queue,
// the tail must be reset to NULL too -- forgetting this leaves tail
// pointing at freed memory.
int dequeue(Queue *q, int *value) {
    if (q->head == NULL) {
        printf("Queue is empty -- cannot dequeue.\n");
        return 0;
    }

    Node *oldHead = q->head;
    *value = oldHead->value;
    q->head = oldHead->next;

    if (q->head == NULL) {   // that was the last node
        q->tail = NULL;
    }

    free(oldHead);
    return 1;
}

int main(void) {
    Queue q;
    q.head = NULL;
    q.tail = NULL;

    printf("Enqueuing 10, 20, 30 (in that order)...\n");
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    printf("\nDequeuing everything -- watch the FIFO order:\n");
    int value;
    while (dequeue(&q, &value)) {
        printf("dequeued: %d\n", value);
    }

    // The queue is empty now (head == NULL and tail == NULL). Dequeuing
    // again is safe -- it's caught by the empty check.
    printf("\nDequeuing an empty queue:\n");
    dequeue(&q, &value);

    return 0;
}
