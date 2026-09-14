#include <stdio.h>

int main(void) {
    int score;
    char grade;

    printf("Enter your test score: ");
    scanf("%d", &score);

    // Notice the SPACE before %c on the next line: scanf(" %c", &grade).
    // Here's why it matters. When you typed your score and pressed Enter,
    // that Enter key left a '\n' (newline) character waiting in the input
    // buffer -- scanf("%d", ...) only consumed the number, not the
    // newline after it. Without the leading space, scanf("%c", &grade)
    // would immediately read that leftover '\n' as your "grade" instead
    // of waiting for you to type a letter. The space tells scanf: "skip
    // any whitespace (spaces, tabs, newlines) sitting in the buffer
    // before reading the next character." This is one of the most common
    // beginner bugs with scanf -- if a %c read seems to get skipped
    // entirely, this is almost always why.
    printf("Enter your grade letter: ");
    scanf(" %c", &grade);

    printf("Score: %d, Grade: %c\n", score, grade);

    return 0;
}
