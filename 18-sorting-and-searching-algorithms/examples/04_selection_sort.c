#include <stdio.h>

// Selection sort: for each position (starting at index 0), find the
// MINIMUM value in the remaining unsorted part of the array and swap it
// into that position. After pass i, the first i+1 elements are the i+1
// smallest values, fully sorted.
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
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
    int values[] = {29, 10, 14, 37, 13};
    int size = 5;

    printf("Before: ");
    printArray(values, size);

    selectionSort(values, size);

    printf("After:  ");
    printArray(values, size);

    return 0;
}
