#include <stdio.h>

// A "node" is a struct that holds some data PLUS a pointer to another
// node of the SAME type. That self-reference is what lets nodes chain
// together into a list.
//
// Notice: inside the struct body, the type name "Node" doesn't exist
// yet -- the typedef isn't finished until the closing "} Node;" below.
// So the pointer field has to spell out "struct Node *next", not
// "Node *next". This is a naming quirk every C programmer hits once.
typedef struct Node {
    int value;
    struct Node *next;   // NOT "Node *next" -- see comment above
} Node;

int main(void) {
    // A single, unconnected node -- next is NULL because there's
    // nothing after it yet.
    Node single;
    single.value = 42;
    single.next = NULL;

    printf("A lone node holding %d, next = %p\n", single.value, (void *)single.next);
    return 0;
}
