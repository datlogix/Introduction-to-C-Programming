// Why functions? Same output, two very different mains.
//
// Run this file once. Notice the "BEFORE" block and the "AFTER" block print
// the exact same receipt lines — but the AFTER block does it with two short
// function calls instead of eight lines of copy-pasted math.

#include <stdio.h>

// A function definition: it must exist before main() can call it, unless we
// give main a prototype first (you'll see that trick in the next example).
void printReceiptLine(char itemName[], double unitPrice, int quantity) {
    double subtotal = unitPrice * quantity;
    double tax = subtotal * 0.15;
    double total = subtotal + tax;
    printf("%-8s: %d x $%.2f = $%.2f (tax $%.2f) => total $%.2f\n",
           itemName, quantity, unitPrice, subtotal, tax, total);
}

int main(void) {
    printf("--- BEFORE: logic copy-pasted for every item ---\n");

    // Coffee
    double price1 = 4.50;
    int qty1 = 3;
    double subtotal1 = price1 * qty1;
    double tax1 = subtotal1 * 0.15;
    double total1 = subtotal1 + tax1;
    printf("%-8s: %d x $%.2f = $%.2f (tax $%.2f) => total $%.2f\n",
           "Coffee", qty1, price1, subtotal1, tax1, total1);

    // Muffin -- same five lines again, just different numbers.
    double price2 = 2.25;
    int qty2 = 5;
    double subtotal2 = price2 * qty2;
    double tax2 = subtotal2 * 0.15;
    double total2 = subtotal2 + tax2;
    printf("%-8s: %d x $%.2f = $%.2f (tax $%.2f) => total $%.2f\n",
           "Muffin", qty2, price2, subtotal2, tax2, total2);

    printf("\n--- AFTER: same math, written once, called twice ---\n");
    printReceiptLine("Coffee", 4.50, 3);
    printReceiptLine("Muffin", 2.25, 5);

    printf("\nSame numbers. Same output. Half the file, and if the tax rate\n");
    printf("ever changes, you now fix it in exactly one place.\n");

    return 0;
}
