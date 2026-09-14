#include <stdio.h>

int main(void) {
    // 'const' means "this value is not allowed to change after this line."
    // The compiler will enforce it for you -- that's the whole point.
    const double PI = 3.14159;
    const int MAX_STUDENTS = 30;

    double radius = 4.0;
    double area = PI * radius * radius;

    printf("Circle area: %.2f\n", area);
    printf("Classroom capacity: %d\n", MAX_STUDENTS);

    // Try uncommenting the line below and recompiling. gcc will refuse,
    // with an error like "assignment of read-only variable 'PI'". That
    // refusal is a feature: it catches a whole category of bugs where a
    // value that should be fixed (a mathematical constant, a maximum
    // capacity, a fixed price) accidentally gets changed somewhere deep
    // in a large program.
    // PI = 3.0;

    return 0;
}
