#include <stdio.h>

typedef struct {
    char name[30];
    int age;
    float gpa;
} Student;

int main(void) {
    Student s1 = {"Ama", 20, 3.8f};

    // Recall Module 7: `&` gets the address of a variable, and a pointer
    // variable stores that address.
    Student *p = &s1;

    // To get from a POINTER TO a struct back to a member, Module 7's
    // dereference operator `*` still works -- but you must parenthesize
    // it, because `.` binds tighter than `*`:
    printf("(*p).name  = %s\n", (*p).name);
    printf("(*p).age   = %d\n", (*p).age);

    // Writing `(*p).age` everywhere is clunky, so C gives you a
    // dedicated operator for exactly this: `->` (the arrow operator).
    // `p->age` means EXACTLY the same thing as `(*p).age`.
    printf("p->age     = %d\n", p->age);
    printf("p->name    = %s\n", p->name);

    // You can also assign through the pointer, either way:
    (*p).gpa = 3.85f;
    printf("after (*p).gpa = 3.85f  -> p->gpa is %.2f\n", p->gpa);

    p->age = 21;
    printf("after p->age = 21       -> s1.age is %d (same variable!)\n", s1.age);

    // `p` and `s1` are not two copies -- `p` just points AT `s1`, so
    // changes through `p` really do change `s1`. In practice, always
    // prefer `->` over `(*p).` -- it's what every C programmer expects
    // to read.
    return 0;
}
