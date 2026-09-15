#include "stats.h"

int maxOf(int a, int b) {
    return (a > b) ? a : b;
}

int minOf(int a, int b) {
    return (a < b) ? a : b;
}

double average(int arr[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += arr[i];
    }
    return (double)total / size;
}
