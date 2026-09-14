#include <stdio.h>
#include <string.h>

// Writing `struct Student` every single time you declare a variable gets
// tedious fast. `typedef` lets you give the type a shorter name to use
// from now on. This is PURELY a naming convenience -- it changes nothing
// about how the struct works or how much memory it uses.
typedef struct {
    char name[30];
    int age;
    float gpa;
} Student;

// Now `Student` can be used on its own, exactly like `int` or `float`.

int main(void) {
    Student s1;                      // instead of: struct Student s1;
    strcpy(s1.name, "Kwame");
    s1.age = 22;
    s1.gpa = 3.2f;

    // The `.` (dot operator) reads or writes a member of a struct
    // variable. You already used it above to set the fields; here it is
    // again to read them back out.
    printf("%s is %d years old with a GPA of %.1f\n", s1.name, s1.age, s1.gpa);

    // Struct variables can also be initialized all at once, in the same
    // order the members were declared:
    Student s2 = {"Efua", 21, 3.9f};
    printf("%s is %d years old with a GPA of %.1f\n", s2.name, s2.age, s2.gpa);

    // You can update a single member later, just like a normal variable.
    s2.gpa = 4.0f;
    printf("%s's GPA is now %.1f\n", s2.name, s2.gpa);

    return 0;
}
