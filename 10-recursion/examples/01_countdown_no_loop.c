#include <stdio.h>

void countdown(int n) {
    if (n == 0) {
        printf("Liftoff!\n");
        return;
    }
    printf("%d... (entering call with n=%d)\n", n, n);
    countdown(n - 1);
    printf("...back out of the call where n=%d\n", n);
}

int main(void) {
    countdown(3);
    return 0;
}
