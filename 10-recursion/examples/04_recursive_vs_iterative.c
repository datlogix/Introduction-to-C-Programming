#include <stdio.h>

int factorialRecursive(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorialRecursive(n - 1);
}

int factorialIterative(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result = result * i;
    }
    return result;
}

int main(void) {
    for (int i = 0; i <= 6; i++) {
        printf("%d! -- recursive: %d, iterative: %d\n",
               i, factorialRecursive(i), factorialIterative(i));
    }
    return 0;
}
