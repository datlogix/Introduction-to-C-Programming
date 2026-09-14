#include <stdio.h>

typedef struct {
    char name[30];
    int age;
    float gpa;
} Student;

int main(void) {
    Student class[3] = {
        {"Ama",   20, 3.8f},
        {"Kwame", 22, 3.2f},
        {"Efua",  21, 3.9f}
    };

    // fopen(filename, mode) opens a file and gives you back a FILE*
    // ("file pointer") to use with every other file function. The mode
    // string says what you intend to do:
    //   "w" - write.  Creates the file if it doesn't exist, or ERASES
    //         its old contents if it does. Use when starting fresh.
    //   "r" - read.   Fails if the file doesn't exist.
    //   "a" - append. Like "w", but adds to the END of an existing file
    //         instead of erasing it.
    FILE *file = fopen("students.txt", "w");

    // fopen can fail -- wrong permissions, a full disk, a bad path. When
    // it fails, it returns NULL instead of a real FILE*. ALWAYS check
    // for this before using the result; using a NULL FILE* crashes your
    // program.
    if (file == NULL) {
        printf("Error: could not open students.txt for writing.\n");
        return 1;
    }

    // fprintf works exactly like printf, except the first argument says
    // WHERE to send the formatted text -- here, our open file instead of
    // the screen.
    for (int i = 0; i < 3; i++) {
        fprintf(file, "%s %d %.2f\n", class[i].name, class[i].age, class[i].gpa);
    }

    // fclose flushes any text still waiting to be written and releases
    // the file. Skipping this is a classic bug: output can sit in a
    // memory buffer and never actually reach the disk until the file is
    // closed (or the program ends), so a program that crashes before
    // closing its files can lose data it thinks it already saved.
    fclose(file);

    printf("Saved %d students to students.txt\n", 3);
    return 0;
}
