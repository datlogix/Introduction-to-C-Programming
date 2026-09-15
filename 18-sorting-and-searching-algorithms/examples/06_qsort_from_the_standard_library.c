#include <stdio.h>
#include <stdlib.h>

// The C standard library already ships a general-purpose sort: qsort,
// declared in <stdlib.h>. You don't hand it comparison/swap logic for
// your specific data -- you hand it a small COMPARATOR function, and it
// does the rest. Treat this signature as a pattern to copy correctly,
// not something to derive from scratch:
//
//   int compare(const void *a, const void *b) {
//       return (*(int *)a) - (*(int *)b);
//   }
//
// - both parameters are generic "pointer to anything" (void *), because
//   qsort works for any data type, not just int
// - cast each one back to what it actually points to (here, int *) and
//   dereference it to get the real values to compare
// - return negative if a should come before b, positive if a should come
//   after b, and 0 if they're equal -- subtraction does exactly that for
//   plain integers
int compareInts(const void *a, const void *b) {
    return (*(int *)a) - (*(int *)b);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int values[] = {40, 10, 100, 90, 20, 25};
    int size = 6;

    printf("Before: ");
    printArray(values, size);

    // qsort(array, number_of_elements, size_of_one_element, comparator)
    qsort(values, size, sizeof(int), compareInts);

    printf("After:  ");
    printArray(values, size);

    return 0;
}
