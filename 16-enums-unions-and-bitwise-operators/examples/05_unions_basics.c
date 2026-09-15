#include <stdio.h>

enum ValueType { TYPE_INT, TYPE_FLOAT };

// A "tagged union": the tag (type) records which member is currently
// meaningful. This is exactly how real-world code uses unions safely.
typedef struct {
    enum ValueType type;
    union {
        int i;
        float f;
    } data;
} Variant;

int main(void) {
    Variant v1;
    v1.type = TYPE_INT;
    v1.data.i = 42;

    Variant v2;
    v2.type = TYPE_FLOAT;
    v2.data.f = 3.14f;

    printf("sizeof(union data) = %zu bytes -- big enough for the LARGER\n", sizeof(v1.data));
    printf("member only; int and float SHARE that memory, not each get their own.\n\n");

    // Safe: check the tag before reading.
    if (v1.type == TYPE_INT) {
        printf("v1 holds an int: %d\n", v1.data.i);
    }
    if (v2.type == TYPE_FLOAT) {
        printf("v2 holds a float: %.2f\n", v2.data.f);
    }

    // Unsafe: writing one member and reading a DIFFERENT one. This is
    // legal C -- it compiles and runs -- but it is almost always a bug.
    // The raw bytes get REINTERPRETED, not converted.
    union {
        int i;
        float f;
    } confused;
    confused.i = 42;
    printf("\nWrote an int (42), read it back as a float: %f\n", confused.f);
    printf("(NOT 42.0 -- same bits, different meaning applied to them)\n");

    return 0;
}
