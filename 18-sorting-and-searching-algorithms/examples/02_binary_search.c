#include <stdio.h>

// Binary search: repeatedly halve the search space by comparing the
// target to the middle element. ONLY works on a SORTED array -- see the
// README for what happens if you break that rule.
//
// Hand trace for target = 71 in the 15-element array below:
//   low=0  high=14 mid=7  arr[7]=42  42 < 71  -> search the right half
//   low=8  high=14 mid=11 arr[11]=63 63 < 71  -> search the right half
//   low=12 high=14 mid=13 arr[13]=78 78 > 71  -> search the left half
//   low=12 high=12 mid=12 arr[12]=71 found!
// Four comparisons to find one value out of fifteen -- and the gap only
// gets more dramatic as the array grows, because every step throws away
// HALF of whatever was still left.
int binarySearch(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;   // avoids overflow vs (low+high)/2
        printf("  checking low=%d high=%d mid=%d arr[mid]=%d\n", low, high, mid, arr[mid]);

        if (arr[mid] == target) {
            return mid;              // found it
        } else if (arr[mid] < target) {
            low = mid + 1;           // target must be in the right half
        } else {
            high = mid - 1;          // target must be in the left half
        }
    }

    return -1;   // low crossed high -- target isn't in the array
}

int main(void) {
    int sorted[] = {2, 5, 8, 12, 16, 23, 38, 42, 45, 51, 59, 63, 71, 78, 90};
    int size = 15;

    printf("Searching for 71:\n");
    int index = binarySearch(sorted, size, 71);
    printf("-> found at index %d\n\n", index);

    printf("Searching for 100 (not present):\n");
    index = binarySearch(sorted, size, 100);
    printf("-> result: %d (not found)\n", index);

    return 0;
}
