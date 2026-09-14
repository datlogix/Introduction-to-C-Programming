#include <stdio.h>

// From Module 6, this is how you've been writing array parameters:
int sumArray(int arr[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += arr[i];
    }
    return total;
}

// This does EXACTLY the same thing. When an array is passed to a function,
// it "decays" into a pointer to its first element -- so arr[] and *arr are
// two spellings of the same parameter here. This is why the array you pass
// to a function in C can always be modified by that function: you're not
// handing over a copy of the whole array, you're handing over the address
// of its first element.
int sumArrayPointerVersion(int *arr, int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += arr[i];       // arr[i] still works, even though arr is a pointer
        // total += *(arr + i); does the exact same thing -- arr[i] is just
        // friendlier notation for "the value at address arr, i slots along"
    }
    return total;
}

int main(void) {
    int scores[] = {10, 20, 30, 40, 50};
    int size = 5;

    // Proof: the array name itself, with no & needed, already behaves like
    // an address -- it's the address of scores[0].
    printf("scores itself (decays to a pointer): %p\n", (void *)scores);
    printf("&scores[0] (address of first element): %p\n", (void *)&scores[0]);
    printf("These are the same address.\n\n");

    printf("sumArray:                %d\n", sumArray(scores, size));
    printf("sumArrayPointerVersion:  %d\n", sumArrayPointerVersion(scores, size));

    return 0;
}
