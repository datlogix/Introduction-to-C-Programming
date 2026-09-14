// Parameters are the named inputs a function is written to expect.
// Arguments are the actual values you hand it when you call it.
//
// A function can also send a value back to whoever called it, using
// `return`. The type before the function name (e.g. `int`, `double`)
// promises what type of value will come back.

#include <stdio.h>

// Two parameters (a and b). Returns their sum as an int.
int add(int a, int b) {
    int sum = a + b;
    return sum; // sends `sum` back to the caller
}

// One parameter. Returns 1 (true-ish) or 0 (false-ish) -- C has no
// separate boolean type in the version we're using, so int does the job.
int isEven(int number) {
    if (number % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Two parameters, both double. Returns a double.
double rectangleArea(double width, double height) {
    return width * height; // you can return an expression directly
}

int main(void) {
    int total = add(3, 4); // 3 and 4 are the ARGUMENTS for parameters a and b
    printf("add(3, 4) = %d\n", total);

    int result = isEven(7);
    printf("isEven(7) = %d\n", result);

    double area = rectangleArea(2.5, 4.0);
    printf("rectangleArea(2.5, 4.0) = %.2f\n", area);

    // You don't have to store the return value -- you can use it directly.
    printf("add(10, 20) = %d\n", add(10, 20));

    return 0;
}
