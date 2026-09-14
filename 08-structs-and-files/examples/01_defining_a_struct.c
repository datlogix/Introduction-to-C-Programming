#include <stdio.h>
#include <string.h>

/*
Before structs: parallel arrays.

If you wanted to track 3 students' names, ages, and GPAs using only what
Module 5 taught you, you'd reach for three separate arrays, kept in sync
by hand:
*/

int main(void) {
    char names[3][30] = {"Ama", "Kwame", "Efua"};
    int ages[3] = {20, 22, 21};
    float gpas[3] = {3.8f, 3.2f, 3.9f};

    // To print "student 1", you have to remember to index all THREE
    // arrays with the same number every time. Nothing stops you from
    // sorting `ages` by mistake and leaving `names` untouched -- now
    // Ama's age might print next to Kwame's name, and the compiler
    // won't warn you at all.
    for (int i = 0; i < 3; i++) {
        printf("%s is %d years old with a GPA of %.1f\n",
               names[i], ages[i], gpas[i]);
    }

    // A struct fixes this by grouping related data into ONE type, so
    // "one student" is one value instead of three loosely related ones.
    struct Student {
        char name[30];
        int age;
        float gpa;
    };

    // Declaring a variable of this new type looks like any other
    // variable declaration, just with `struct Student` as the type.
    struct Student s1;
    strcpy(s1.name, "Ama");
    s1.age = 20;
    s1.gpa = 3.8f;

    printf("\nSame data, as a struct:\n");
    printf("%s is %d years old with a GPA of %.1f\n", s1.name, s1.age, s1.gpa);

    return 0;
}
