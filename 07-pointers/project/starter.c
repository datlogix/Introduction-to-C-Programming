#include <stdio.h>

// TODO: write findMinAndMax(int arr[], int size, int *min, int *max)
// It should scan the array once and store results at *min and *max.


// TODO: write scaleArray(int arr[], int size, int factor)
// It should multiply every element of arr by factor, in place.


void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int scores[] = {42, 17, 99, 3, 56, 71, 8, 64};
    int size = 8;

    printf("Original array: ");
    printArray(scores, size);

    // TODO: declare min and max variables, call findMinAndMax, print results

    // TODO: call scaleArray with a factor of your choice

    printf("Scaled array:   ");
    printArray(scores, size);

    // TODO: print the memory addresses of scores[0], min, and max using %p

    return 0;
}
