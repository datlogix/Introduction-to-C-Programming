# Module 2 — Data Types & Operators

## Hook: why did math just break?

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>

int main(void) {
    printf("Splitting 7 slices of pizza among 2 people: %d slices each\n", 7 / 2);

    unsigned char tinyBox = 255;
    tinyBox = tinyBox + 1;
    printf("One more than 255 in a box that only holds 0-255: %d\n", tinyBox);

    return 0;
}
```

```bash
gcc hook.c -o hook
./hook
```

You should see `3` slices each (not `3.5` — did someone eat half a slice?),
and then `0` where you'd expect `256`. Neither of these is a bug in your
program. Both are C doing *exactly* what it was told, using the rules for
**data types** and **operators** you're about to learn. By the end of this
module you'll know precisely why 7 divided by 2 lost its remainder, and
why a number can "wrap around" back to zero — and you'll use both facts on
purpose in this module's project.

## Why data types exist

Every piece of data in a C program lives in memory as a fixed-size box of
bits. A **data type** tells the compiler two things: how big that box is,
and how to interpret the bits inside it. Get the type wrong for what
you're storing, and you get wrong (but silent!) answers — like the hook
just showed you. This is different from what you're used to if you've
ever used a calculator or spreadsheet, where numbers "just work." In C,
you choose the box size up front.

## The basic types

```c
#include <stdio.h>

int main(void) {
    int wholeNumber = 42;
    float singlePrecision = 3.14f;
    double doublePrecision = 3.14159265358979;
    char letter = 'A';

    printf("%d\n", wholeNumber);
    printf("%f\n", singlePrecision);
    printf("%f\n", doublePrecision);
    printf("%c\n", letter);

    return 0;
}
```

- **`int`** — whole numbers, positive or negative, no decimal point:
  `42`, `-7`, `0`.
- **`float`** — numbers with a decimal point, stored with limited
  precision (about 6-7 reliable digits). Written with an `f` suffix in
  code, e.g. `3.14f`.
- **`double`** — also decimal numbers, but roughly twice the storage of
  `float` and about twice the precision. This is C's *default* choice for
  decimal numbers when you're not tight on memory — prefer it over
  `float` unless you have a specific reason not to.
- **`char`** — a single character, written in **single** quotes:
  `'A'`, `'7'`, `'$'`. Under the hood it's just a small integer (each
  character has a numeric code), which is why arithmetic on `char`
  values is legal, if unusual, in C.

You'll also see `short` and `long` mentioned in other people's code —
they're `int` variants with smaller or larger ranges. As a beginner
you'll rarely need them; stick to `int`, `float`, `double`, and `char`
for now.

This line is new too: `int wholeNumber = 42;` **declares** a variable
(reserves a labeled box of memory of that type) and **initializes** it
(puts a value in the box) in one step. We're using variables here purely
as a way to hold values so we can inspect types and operators — Module 3
goes much deeper on naming them well, `const`, and reading values in from
the user with `scanf`.

### Picking the right format specifier

`printf` needs to be told what type you're handing it, using a **format
specifier** inside the string:

| Type     | Specifier |
|----------|-----------|
| `int`    | `%d`      |
| `float`/`double` | `%f` |
| `char`   | `%c`      |

Get this wrong (e.g. `%d` for a `float`) and you'll get garbage output —
the compiler often won't stop you, so double-check it yourself. There's
also `%s` for printing strings of text, but strings are a Module 5 topic
— you won't need it yet.

## `sizeof` — how big is that box, really?

`sizeof` tells you exactly how many bytes a type (or a variable) occupies
in memory:

```c
printf("%zu\n", sizeof(int));
printf("%zu\n", sizeof(wholeNumber));
```

Note the format specifier: `sizeof` produces a special unsigned type, and
`%zu` is the correct specifier for it — not `%d`. On a typical machine
you'll see `int` and `float` at 4 bytes, `double` at 8 bytes, and `char`
at exactly 1 byte (by definition — `char` is always 1 byte in C). This is
also the mechanism behind the hook: `unsigned char` only has 1 byte to
work with, giving it 256 possible values (0-255). Add 1 past the top of
its range and there's nowhere for the extra bit to go — it silently
**wraps around** back to 0.

## Arithmetic operators — and the integer division trap

C gives you the five arithmetic operators you'd expect: `+ - * / %`.
The first three behave the way you'd guess. The last two need care.

```c
int apples = 7;
int friends = 2;

printf("%d\n", apples / friends);       // 3 -- NOT 3.5
printf("%d\n", apples % friends);       // 1 -- the remainder
```

**When both operands of `/` are integers, C performs integer division:
the decimal portion is discarded entirely, not rounded.** `7 / 2` is `3`,
full stop. This is exactly what the hook demonstrated, and it is
*probably the single most common source of silently-wrong output* for
beginners in C. To get a true decimal answer, at least one operand must
be a `float` or `double` — which brings us to conversion and casting.

`%` (modulo) gives you the remainder left over from integer division:
`7 % 2` is `1`, because 7 divided by 2 is 3 remainder 1. It only works on
integer types.

## Type conversion and casting

**Implicit conversion** happens automatically when an expression mixes
types — C "promotes" the smaller/less-precise type up to match:

```c
int wholeScore = 7;
float bonus = 2.5f;
float total = wholeScore + bonus;   // wholeScore is promoted to float first
```

This is convenient, but it doesn't save you from the integer division
trap above — that trap only happens *before* any promotion, when
**both** operands are already integers. To fix it, you need an **explicit
cast**: write the target type in parentheses right before the value you
want converted.

```c
int a = 7;
int b = 2;

printf("%d\n", a / b);           // 3  -- integer division
printf("%f\n", (float)a / b);    // 3.500000 -- a is converted to float FIRST
```

`(float)a` converts just `a` to a `float` *before* the division runs.
Since one operand is now a `float`, the whole division becomes float
division. This one technique — casting one operand before dividing — is
the fix for the hook's first surprise, and you'll use it constantly.

## Relational and logical operators

**Relational operators** compare two values and produce `1` (true) or
`0` (false) — C has no separate boolean type for this:

```c
int age = 20;

printf("%d\n", age == 20);   // 1  (equal to)
printf("%d\n", age != 20);   // 0  (not equal to)
printf("%d\n", age > 18);    // 1  (greater than)
printf("%d\n", age < 18);    // 0  (less than)
printf("%d\n", age >= 20);   // 1  (greater than or equal to)
printf("%d\n", age <= 19);   // 0  (less than or equal to)
```

Watch out: `==` (comparison) and `=` (assignment) are different
operators that look almost identical — mixing them up is a classic bug
you'll meet again in Module 4.

**Logical operators** combine `0`/`1` results: `&&` (and — true only if
both sides are true), `||` (or — true if either side is true), and `!`
(not — flips true to false and vice versa):

```c
printf("%d\n", (age > 18) && (age < 65));   // 1 -- both true
printf("%d\n", (age < 18) || (age > 65));   // 0 -- both false
printf("%d\n", !(age == 20));               // 0 -- flips 1 to 0
```

Right now we're just printing what these operators produce. Using them
to actually branch your program's behavior (`if` statements) is Module
4's job — for now, just get comfortable with the fact that a comparison
*is* a value in C: `0` or `1`, ready to be printed, stored, or combined
with others.

## Operator precedence

Just like in math class, `*` and `/` run before `+` and `-`:

```c
printf("%d\n", 2 + 3 * 4);     // 14, not 20
printf("%d\n", (2 + 3) * 4);   // 20 -- parentheses run first
```

You don't need to memorize a full precedence table right now. The
practical rule: **when you're not 100% sure how an expression will be
evaluated, add parentheses.** It costs nothing, makes your intent obvious
to anyone reading the code, and removes all doubt.

## Common beginner mistakes

- Assuming `int / int` gives a decimal answer. It doesn't — `7 / 2` is
  `3`. Cast at least one operand to `float` or `double` if you need a
  real decimal result.
- Using the wrong `printf` format specifier for a type (e.g. `%d` for a
  `float`) — this often doesn't error, it just prints garbage.
- Using `%d` for the result of `sizeof` instead of `%zu`.
- Confusing `=` (assignment) with `==` (comparison).
- Forgetting single quotes for `char` literals (`'A'`, not `"A"` —
  double quotes are for strings, which are a different, later topic).
- Casting the *wrong* operand or casting too late — `(float)(a / b)`
  still does integer division first and only converts the already-wrong
  answer; you must cast **before** the division happens, e.g.
  `(float)a / b`.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one. Predict the output before you run it, then check.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 2: data types and operators"
   git push
   ```

Next: **[Module 3 — Variables & Input/Output](../03-variables-and-io/README.md)**.
