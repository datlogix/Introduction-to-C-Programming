#include <stdio.h>

int main(void) {
    int age = 25;
    int *p = &age;

    printf("Before: age = %d\n", age);

    // *p on the LEFT side of an assignment means "go to the address p
    // points to, and store this new value there." Since p points to age,
    // this changes age itself -- even though we never wrote "age = 100"
    // directly.
    *p = 100;

    printf("After:  age = %d\n", age);

    // p itself never changed -- it still points to age's address. What
    // changed is the value SITTING at that address. This is the whole
    // superpower of pointers: they let you reach out and change a variable
    // indirectly, through its address, instead of by using its name.
    printf("p still points to the same address: %p\n", (void *)p);

    return 0;
}
