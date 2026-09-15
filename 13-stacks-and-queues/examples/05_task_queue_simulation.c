#include <stdio.h>
#include <stdlib.h>

/*
The mirror image of the undo stack: a print/task queue. Jobs are handled
in the order they were REQUESTED, not the order they happen to finish
being thought about -- first in, first out. This is the same Queue from
03_queue_enqueue_and_dequeue.c, just holding job names instead of ints.
*/

typedef struct Node {
    const char *job;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Queue;

void enqueue(Queue *q, const char *job) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("malloc failed -- queue unchanged.\n");
        return;
    }
    newNode->job = job;
    newNode->next = NULL;

    if (q->tail == NULL) {
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

int dequeue(Queue *q, const char **job) {
    if (q->head == NULL) {
        return 0;
    }
    Node *oldHead = q->head;
    *job = oldHead->job;
    q->head = oldHead->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    free(oldHead);
    return 1;
}

int main(void) {
    Queue printQueue;
    printQueue.head = NULL;
    printQueue.tail = NULL;

    printf("Three people send documents to the printer:\n");
    enqueue(&printQueue, "Doug's essay.pdf");
    printf("  queued: Doug's essay.pdf\n");
    enqueue(&printQueue, "Ama's timetable.pdf");
    printf("  queued: Ama's timetable.pdf\n");
    enqueue(&printQueue, "Kofi's poster.pdf");
    printf("  queued: Kofi's poster.pdf\n");

    printf("\nThe printer works through the queue, in request order:\n");
    const char *job;
    while (dequeue(&printQueue, &job)) {
        printf("  now printing: %s\n", job);
    }

    printf("\nPrint queue is empty:\n");
    if (!dequeue(&printQueue, &job)) {
        printf("  nothing left to print.\n");
    }

    return 0;
}
