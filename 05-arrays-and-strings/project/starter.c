#include <stdio.h>
#include <string.h>

int main(void) {
    char message[100];
    char choice[10];
    int shift;

    // TODO 1: Ask the user "Encode or decode? (e/d): " and read their
    //         answer with fgets(choice, sizeof(choice), stdin), same as
    //         reading any other line. You'll check choice[0] later.

    // TODO 2: Ask for the message: "Enter your message: " and read it with
    //         fgets(message, sizeof(message), stdin). Don't forget to strip
    //         the trailing newline with strcspn, like in example 05.

    // TODO 3: Ask for the shift amount: "Enter shift amount (1-25): " and
    //         read it with scanf("%d", &shift).

    // TODO 4: Loop over every character in `message`. For each letter:
    //           - if decoding, shift it BACKWARD by `shift`
    //           - if encoding, shift it FORWARD by `shift`
    //         Handle uppercase and lowercase separately (like the hook!),
    //         and leave anything that isn't a letter (spaces, punctuation,
    //         numbers) completely unchanged.

    // TODO 5: Print the result, e.g. printf("Result: %s\n", message);

    return 0;
}
