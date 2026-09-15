#include <stdio.h>

// Linear search: check every element in order until the target is found
// (or we run out of elements). Works on ANY array -- sorted or not.
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;   // found it -- return the index immediately
        }
    }
    return -1;          // walked the whole array, never matched
}

int main(void) {
    int scores[] = {77, 60, 90, 85, 100, 42, 68};
    int size = 7;

    int targets[] = {90, 68, 999};
    int numTargets = 3;

    for (int t = 0; t < numTargets; t++) {
        int target = targets[t];
        int index = linearSearch(scores, size, target);
        if (index != -1) {
            printf("Found %d at index %d\n", target, index);
        } else {
            printf("%d is not in the array\n", target);
        }
    }

    return 0;
}
