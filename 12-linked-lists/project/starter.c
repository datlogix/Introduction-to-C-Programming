#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 30

// Each grocery item is one node: a name, a quantity, and a pointer to
// the next item on the list.
typedef struct Item {
    char name[NAME_LENGTH];
    int quantity;
    struct Item *next;
} Item;

// TODO: Item *addItem(Item *head, const char *name, int quantity)
//   Allocate a new Item, fill in its fields (use strncpy or snprintf
//   for the name so you can't overflow the array), and insert it --
//   at the head is simplest. Return the (possibly new) head.

// TODO: Item *removeItem(Item *head, const char *name)
//   Find the first item whose name matches, unlink it from the list,
//   free it, and return the (possibly new) head. If no item matches,
//   return head unchanged. Don't forget the special case of removing
//   the head itself.

// TODO: void printList(Item *head)
//   Walk the list and print every item's name and quantity.

// TODO: void freeList(Item *head)
//   Walk the list and free every node. Save the next pointer before
//   freeing each node!

int main(void) {
    Item *head = NULL;

    // TODO: use addItem/removeItem/printList/freeList to build a small
    // grocery list, print it, remove something, and print it again.
    // Free the whole list before the program exits.

    return 0;
}
