#include <stdio.h>

int sumArray(int arr[], int size) {
    if (size == 0) {
        return 0;
    }
    return arr[0] + sumArray(arr + 1, size - 1);
}

int main(void) {
    int scores[] = {90, 85, 77, 60, 100};
    int count = 5;

    printf("Sum: %d\n", sumArray(scores, count));
    return 0;
}
