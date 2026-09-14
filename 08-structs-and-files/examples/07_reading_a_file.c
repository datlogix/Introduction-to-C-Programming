#include <stdio.h>

typedef struct {
    char name[30];
    int age;
    float gpa;
} Student;

int main(void) {
    // Open in "r" (read) mode. This assumes 06_writing_a_file.c has
    // already been run in this same folder to create students.txt --
    // run that one first if you see the error below.
    FILE *file = fopen("students.txt", "r");

    if (file == NULL) {
        printf("Error: could not open students.txt for reading.\n");
        printf("Did you run 06_writing_a_file.c first?\n");
        return 1;
    }

    Student class[10];
    int count = 0;

    // fscanf reads formatted data from a file the same way scanf (Module
    // 3) reads from the keyboard -- it returns how many items it
    // successfully matched, so we loop until a read comes up short
    // (which also happens naturally at the end of the file).
    while (fscanf(file, "%29s %d %f", class[count].name,
                  &class[count].age, &class[count].gpa) == 3) {
        count++;
    }

    fclose(file);

    printf("Loaded %d students from students.txt:\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d. %s is %d years old with a GPA of %.2f\n",
               i + 1, class[i].name, class[i].age, class[i].gpa);
    }

    // This is the whole trick behind "my program remembers things":
    // write struct data out with fprintf, read it back with fscanf into
    // a fresh array in a totally separate run of the program.
    return 0;
}
