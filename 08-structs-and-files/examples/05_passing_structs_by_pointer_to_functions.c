#include <stdio.h>

typedef struct {
    char name[30];
    int age;
    float gpa;
} Student;

// Module 7 taught you that passing a variable to a function normally
// passes a COPY -- changes inside the function don't escape it. That's
// still true for structs. This function receives a copy, so its change
// to `age` is thrown away when the function returns.
void birthdayByValue(Student s) {
    s.age = s.age + 1;
    printf("  inside birthdayByValue: age is now %d\n", s.age);
}

// To let a function actually modify the CALLER's struct, pass a POINTER
// to it instead -- exactly the pass-by-pointer pattern from Module 7,
// just with a struct as the pointed-to type.
void birthdayByPointer(Student *s) {
    s->age = s->age + 1;
    printf("  inside birthdayByPointer: age is now %d\n", s->age);
}

int main(void) {
    Student s1 = {"Ama", 20, 3.8f};

    printf("Before: %s is %d\n", s1.name, s1.age);

    birthdayByValue(s1);
    printf("After birthdayByValue: %s is still %d (unchanged)\n\n", s1.name, s1.age);

    birthdayByPointer(&s1);
    printf("After birthdayByPointer: %s is now %d (changed!)\n", s1.name, s1.age);

    // Rule of thumb: if a function needs to READ a struct, pass it by
    // value (or by const pointer, for large structs). If a function
    // needs to MODIFY the caller's struct, pass a pointer to it -- `&s1`
    // in, `Student *s` as the parameter, `s->member` inside.
    return 0;
}
