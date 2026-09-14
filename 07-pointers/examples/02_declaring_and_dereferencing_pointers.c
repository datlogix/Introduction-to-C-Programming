#include <stdio.h>

int main(void) {
    int age = 25;

    // "int *p" declares p as a pointer to an int -- a variable whose job is
    // to hold the ADDRESS of an int, not an int value itself. Read it as
    // "p is a pointer to int."
    int *p = &age;

    // Careful: the * above is part of the DECLARATION -- it tells the
    // compiler "this variable is a pointer," it is not dereferencing
    // anything yet.
    printf("age is:            %d\n", age);
    printf("&age (address) is: %p\n", (void *)&age);
    printf("p (address) is:    %p\n", (void *)p);

    // Now use * in a different way: as the DEREFERENCE operator. Written in
    // front of an already-declared pointer, *p means "go to the address p
    // is holding, and give me the value stored there."
    printf("*p (dereferenced) is: %d\n", *p);

    // This is the classic beginner trap: the SAME symbol * means two
    // different things depending on where it appears.
    //   int *p;   <- here * means "p is a pointer" (declaration)
    //   *p        <- here * means "the value p points to" (dereference)
    // There is no way to tell them apart except by context: are you
    // declaring a new variable, or using one that already exists?

    return 0;
}
