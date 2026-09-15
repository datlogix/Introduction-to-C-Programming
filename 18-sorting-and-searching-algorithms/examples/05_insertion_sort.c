#include <stdio.h>

// Insertion sort: build up a sorted portion at the front of the array,
// one element at a time. Each new element gets shifted left into the
// spot where it belongs -- exactly like sorting a hand of playing cards
// as you pick them up one by one.
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];      // the card we just "picked up"
        int j = i - 1;

        // shift every sorted element bigger than key one slot to the right
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;      // drop key into its correct spot
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int values[] = {9, 5, 1, 4, 3, 8};
    int size = 6;

    printf("Before: ");
    printArray(values, size);

    insertionSort(values, size);

    printf("After:  ");
    printArray(values, size);

    return 0;
}
