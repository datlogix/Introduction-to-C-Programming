#include <stdio.h>

typedef struct {
    char name[30];
    int age;
    float gpa;
} Student;

int main(void) {
    // Just like an array of int or an array of char, you can have an
    // array of a struct type. Each slot is one full Student -- a name,
    // an age, AND a gpa, always kept together.
    Student class[3] = {
        {"Ama",   20, 3.8f},
        {"Kwame", 22, 3.2f},
        {"Efua",  21, 3.9f}
    };

    // Looping over an array of structs looks just like Module 5's array
    // loops -- you just reach one member deeper with `.` each time.
    float total = 0.0f;
    for (int i = 0; i < 3; i++) {
        printf("%d. %s (age %d) - GPA %.1f\n",
               i + 1, class[i].name, class[i].age, class[i].gpa);
        total += class[i].gpa;
    }

    printf("Average GPA: %.2f\n", total / 3);

    // Compare this file to 01_defining_a_struct.c: one array (`class`)
    // now does the job of three separate, error-prone parallel arrays.
    return 0;
}
