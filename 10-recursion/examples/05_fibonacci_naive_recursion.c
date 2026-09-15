#include <stdio.h>

int callCount = 0;

int fib(int n) {
    callCount++;
    if (n <= 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

int main(void) {
    for (int n = 0; n <= 20; n += 5) {
        callCount = 0;
        int result = fib(n);
        printf("fib(%2d) = %-6d  (took %d recursive calls)\n", n, result, callCount);
    }

    printf("\nNotice how fast 'calls' grows compared to 'n' -- that's the\n");
    printf("same work (e.g. fib(3)) being recomputed many times over.\n");
    return 0;
}
