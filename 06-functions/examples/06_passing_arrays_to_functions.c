// You can pass an array to a function just like any other value -- the
// function receives the array's size separately, since C doesn't track
// it automatically once the array is inside the function.
//
// Important: unlike a normal int or double, when you pass an array to a
// function, the function can change the ORIGINAL array back in main --
// not just its own local copy. You'll fully understand exactly why in
// Module 7. For now, just know: arrays behave differently here.

#include <stdio.h>

int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

double average(int arr[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += arr[i];
    }
    return (double) total / size;
}

// This function modifies the caller's actual array -- proof that arrays
// aren't copied when passed to a function the way plain numbers are.
void doubleAllValues(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = arr[i] * 2;
    }
}

int main(void) {
    int scores[5] = {12, 45, 7, 89, 34};

    printf("Max score: %d\n", findMax(scores, 5));
    printf("Average score: %.1f\n", average(scores, 5));

    doubleAllValues(scores, 5);
    printf("After doubleAllValues, scores[0] = %d (it really changed!)\n", scores[0]);

    return 0;
}
