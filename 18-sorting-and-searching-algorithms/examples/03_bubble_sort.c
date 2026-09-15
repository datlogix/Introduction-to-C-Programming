#include <stdio.h>

// Bubble sort: repeatedly walk the array comparing ADJACENT pairs and
// swapping them if they're out of order. Each full pass pushes the
// largest remaining value one step closer to the end -- like a bubble
// rising to the top.
void bubbleSort(int arr[], int size) {
    for (int pass = 0; pass < size - 1; pass++) {
        for (int i = 0; i < size - 1 - pass; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int values[] = {64, 34, 25, 12, 22, 11, 90};
    int size = 7;

    printf("Before: ");
    printArray(values, size);

    bubbleSort(values, size);

    printf("After:  ");
    printArray(values, size);

    return 0;
}
