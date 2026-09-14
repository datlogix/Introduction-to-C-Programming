# Module 5 — Arrays & Strings

## Hook: crack the secret message

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char secret[] = "Duudbv krog pdqb ydoxhv lq d urz!";
    int shift = 3;
    int len = strlen(secret);

    for (int i = 0; i < len; i++) {
        char c = secret[i];
        if (c >= 'a' && c <= 'z') {
            secret[i] = 'a' + (c - 'a' - shift + 26) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            secret[i] = 'A' + (c - 'A' - shift + 26) % 26;
        }
        // anything that isn't a letter (spaces, punctuation) is left alone
    }

    printf("Decoding secret message...\n");
    printf("%s\n", secret);

    return 0;
}
```

```bash
gcc hook.c -o hook
./hook
```

Gibberish goes in, an English sentence comes out. `secret` isn't a single
value like the `int`s and `char`s you've used so far — it's a whole *row*
of characters that the loop walks across one at a time, shifting each
letter three places back through the alphabet. By the end of this module
you'll understand exactly how `secret[i]` works, why `char secret[]` can
hold a whole sentence, and you'll build your own encoder/decoder in the
module project.

## What is an array?

Every variable you've used so far holds exactly one value: one `int`, one
`float`, one `char`. But plenty of real problems need a *bunch* of related
values — five quiz scores, thirty students' ages, a whole word. Declaring
30 separate variables (`score1`, `score2`, `score3`, ...) would be
miserable to write and impossible to loop over.

An **array** is a fixed number of values of the same type, stored back to
back in memory under one name:

```c
int scores[5];                          // 5 ints, not set yet
int prices[5] = {90, 85, 77, 60, 100};  // 5 ints, set immediately
```

`scores[5]` reserves 5 slots. `prices[5] = {...}` reserves 5 slots *and*
fills them in, left to right, in the order you list them.

## Indexing starts at 0

Each slot in an array has a position number called an **index**, and in C
indexing always starts at **0**, not 1. For an array of size 5, the valid
indexes are `0, 1, 2, 3, 4` — the last valid index is always `size - 1`,
never `size`.

```c
printf("%d\n", prices[0]); // 90  <- the FIRST element
printf("%d\n", prices[4]); // 100 <- the LAST element
```

This trips up almost every beginner at least once: reaching for
`prices[5]` expecting "the 5th price" and getting the price that doesn't
exist. `prices[5]` would be the **6th** slot of a 5-slot array — one past
the end. More on why that's dangerous below.

## Iterating with a for loop

A `for` loop is the natural match for "do something to every element":

```c
for (int i = 0; i < 5; i++) {
    printf("prices[%d] = %d\n", i, prices[i]);
}
```

`i` takes the values `0, 1, 2, 3, 4` — exactly the array's valid indexes —
and stops before `i` ever reaches `5`. This pattern (`i = 0`, `i < size`,
`i++`) is the standard way to visit every element of an array, and you'll
use it constantly: summing values, finding a maximum, searching for
something, printing everything out.

## Array bounds: C will not save you

Here's the single most important safety lesson in this module: **C does
not check array bounds for you.** Many languages throw a clear, helpful
error the instant you try to read or write past the end of an array. C
does not. If you write `scores[5]` on a 5-element array, the compiler
happily generates code for it — code that reads or writes whatever memory
happens to sit right after your array. This is called **undefined
behavior**, and the word "undefined" is doing a lot of work: it might
print a weird number, it might silently corrupt some *other* variable
elsewhere in your program, it might work fine today and crash tomorrow,
it might crash immediately. There is no guarantee, and no helpful error
message — the bug can show up far away from its actual cause, which makes
it one of the hardest kinds of bug to track down.

The discipline that prevents this: **always know your array's real size,
and never trust an index blindly.**

```c
int size = 5;
int index = get_some_index(); // from input, a calculation, wherever

if (index >= 0 && index < size) {
    printf("%d\n", scores[index]);
} else {
    printf("Index %d is out of bounds.\n", index);
}
```

The classic way this bites beginners is an off-by-one loop condition:
writing `i <= size` instead of `i < size` walks one slot too far on the
very last pass. Whenever a loop touches an array, double check the
condition against the array's actual size.

## C-strings: arrays of characters

You already know `char grade = 'A';` — a single character, single quotes.
A **string** in C is different: it's an *array* of `char`, written with
double quotes, and printed with `%s` instead of `%c`:

```c
char grade = 'A';          // ONE character
char name[20] = "Ama";     // a STRING — an array that can hold up to 19
                            // real characters (see why below)
printf("Grade: %c\n", grade);
printf("Name: %s\n", name);
```

Here's the part that catches everyone at first: C secretly stores one
extra, invisible character right after `"Ama"` — `'\0'`, the **null
terminator**. It marks "the real string data ends here." So `name[20]`
actually looks like this in memory:

```
name[0]='A'  name[1]='m'  name[2]='a'  name[3]='\0'  name[4..19]=unused
```

`printf("%s", ...)`, `strlen`, and every other string function scan
forward until they hit that `'\0'` and stop there — they have no other
way of knowing where your string ends. This is also why a `char name[20]`
can only ever hold a string of **19** real characters, not 20: one slot
is always reserved for the terminator. Forget to leave room for it (or
overwrite it), and every string function that touches that array walks
straight past your data into undefined behavior.

## Reading a line of text safely

Module 3 used `scanf("%d", ...)` and `scanf("%f", ...)` for numbers.
Reading text with `scanf("%s", ...)` has two serious problems: it stops
at the first space (so "Kofi Mensah" becomes just "Kofi"), and it has no
idea how big your array is — a long enough input overflows the buffer,
which is exactly the out-of-bounds danger from above.

`fgets` fixes both:

```c
char name[20];
printf("What is your name? ");
fgets(name, sizeof(name), stdin);
```

`sizeof(name)` tells `fgets` exactly how many bytes it's allowed to
write, so it can never overflow the array no matter what the user types.
The trade-off: `fgets` keeps the newline character from the Enter key at
the end of the string. It's usually not wanted, so it's common to strip
it off:

```c
name[strcspn(name, "\n")] = '\0';
```

`strcspn(name, "\n")` finds the index of the first `'\n'` in `name`;
writing `'\0'` there shortens the string right at that point.

## Useful `<string.h>` functions

| Function | What it does |
|---|---|
| `strlen(s)` | Number of real characters in `s` (not counting `'\0'`) |
| `strcpy(dest, src)` | Copies `src` into `dest` (`dest` must be big enough) |
| `strcmp(a, b)` | Returns `0` if `a` and `b` are exactly equal |
| `strcat(dest, src)` | Appends `src` onto the end of `dest` |

```c
char city[20] = "Kumasi";
printf("%zu\n", strlen(city));        // 6

char copy[20];
strcpy(copy, city);                   // copy now holds "Kumasi"

if (strcmp(copy, city) == 0) {        // true — same contents
    printf("They match!\n");
}

char greeting[40] = "Welcome to ";
strcat(greeting, city);               // greeting is now "Welcome to Kumasi"
```

Notice `strcmp`, not `==`. Comparing two strings with `==` compares where
they live in memory, not what characters they contain — it will almost
never do what you want. Always reach for `strcmp` instead.

## A preview: 2D arrays

Some problems need a grid instead of a single row — a tic-tac-toe board,
a seating chart, a spreadsheet of numbers. C lets you declare a **2D
array** for exactly that:

```c
int grid[3][3]; // 3 rows, each holding 3 ints
```

You won't need these yet — plain 1D arrays are enough for this module —
but it's worth knowing the idea exists for when a problem needs more than
one dimension.

One more preview, just so the name doesn't surprise you later: an array
name like `scores` is closely related to something called a **pointer**
— you'll see exactly what that means and how it works in Module 7.

## Common beginner mistakes

- Using index `size` instead of `size - 1` for the last element (off-by-
  one), or looping with `i <= size` instead of `i < size`.
- Reading or writing an index outside the array's bounds — C will not
  warn you; the bug can show up somewhere completely unrelated later on.
- Declaring a `char` array too small for the string plus its `'\0'` (e.g.
  `char name[3] = "Ama";` — that needs at least 4 slots, not 3).
- Using `scanf("%s", ...)` for user input instead of `fgets` — it splits
  on whitespace and has no protection against buffer overflow.
- Comparing strings with `==` instead of `strcmp`.
- Forgetting that `fgets` keeps the trailing newline, and being confused
  when a "matching" string comparison mysteriously fails.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 5: arrays and strings"
   git push
   ```

Next: **[Module 6 — Functions](../06-functions/README.md)**.
