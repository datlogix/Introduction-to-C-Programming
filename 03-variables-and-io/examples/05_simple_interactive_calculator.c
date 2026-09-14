#include <stdio.h>

int main(void) {
    float num1, num2;

    printf("Enter the first number: ");
    scanf("%f", &num1);

    printf("Enter the second number: ");
    scanf("%f", &num2);

    // Read the input, compute something, print a result -- the pattern
    // behind every interactive program you'll ever write.
    float sum = num1 + num2;
    float difference = num1 - num2;
    float product = num1 * num2;
    float quotient = num1 / num2;

    printf("\n%.2f + %.2f = %.2f\n", num1, num2, sum);
    printf("%.2f - %.2f = %.2f\n", num1, num2, difference);
    printf("%.2f * %.2f = %.2f\n", num1, num2, product);
    printf("%.2f / %.2f = %.2f\n", num1, num2, quotient);

    return 0;
}
