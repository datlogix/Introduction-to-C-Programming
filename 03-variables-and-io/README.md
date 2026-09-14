# Module 3 — Variables & Input/Output

## Hook: the instant mind reader

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>

int main(void) {
    int age;

    printf("Think of your age. Don't tell anyone. Just type it in: ");
    scanf("%d", &age);

    int birth_year_guess = 2026 - age;
    int days_alive_guess = age * 365;

    printf("\nI sense... you were born around the year %d.\n", birth_year_guess);
    printf("You have been alive for roughly %d days.\n", days_alive_guess);
    printf("I am basically a wizard.\n");

    return 0;
}
```

```bash
gcc mindreader.c -o mindreader
./mindreader
```

Type in your age and watch it "read your mind." There's no trick — just
a variable holding the number you typed, and two lines of arithmetic. By
the end of this module you'll understand every piece of this program:
how `age` stores what you typed, what that `&` before it is doing, and
how to build interactive programs like this from scratch. You'll build
a bigger version of it in the module project.

## What is a variable, really?

Every program so far has only ever printed text that was baked into the
code itself. That's not very useful — a real program needs to work with
information that changes: a score, a price, an age typed in by whoever
is running it. A **variable** is a named box in the computer's memory
that holds a value your program can read and change while it runs.

```
int age = 16;
 ^    ^    ^
 |    |    +-- the value stored in the box right now
 |    +-- the name you use to refer to the box
 +-- the type of value the box is allowed to hold (Module 2)
```

You've already used types (`int`, `float`, `double`, `char`) and literal
values in Module 2. A variable is what lets a value have a *name* you
can reuse, print, and update throughout a program instead of typing the
literal value over and over.

## Naming variables: rules and conventions

C enforces a small set of **rules** for names (the compiler will reject
anything that breaks them):

- Names can contain letters, digits, and underscores (`_`) only.
- A name **cannot start with a digit** (`1st_place` is illegal;
  `first_place` is fine).
- C is **case-sensitive** — `age`, `Age`, and `AGE` are three different
  names.
- You cannot use a **reserved word** as a name — words the language
  already uses for something else, like `int`, `float`, `return`, or
  `const` (more on `const` below).

Beyond what the compiler requires, good C code follows **conventions** —
habits the whole C community shares so anyone's code is easy to read:

- Use **meaningful names**. `s` tells you nothing; `average_score`
  tells you exactly what's stored there. You are writing code for the
  next human who reads it — often that human is you, in six months.
- Use **`snake_case`** for variable names: all lowercase, words joined
  by underscores (`number_of_students`, not `numberOfStudents` or
  `NumberOfStudents`). This is the idiomatic style in C, even though
  other languages prefer different conventions.

## Declaring, initializing, and re-assigning

**Declaring** a variable creates the box but doesn't necessarily put
anything meaningful in it yet:

```c
int score;
```

**Initializing** means giving it a value at the moment you declare it —
almost always the better habit:

```c
int score = 0;
```

You can also declare first and assign a value on a later line using
`=`:

```c
int score;
score = 0;
```

Once a variable already exists, using `=` again doesn't declare a new
variable — it **re-assigns** (overwrites) the value already stored
there:

```c
int age = 16;
age = age + 1;   // reads the current value (16), adds 1, stores 17 back
```

Notice `age = age + 1;` is not an equation in the mathematical sense —
`=` in C means "compute the right side, then store the result in the
variable on the left," not "these two things are equal."

## Why uninitialized variables are dangerous

Declaring a variable **without** initializing it leaves whatever bits
happened to already be sitting at that spot in memory — a **garbage
value**. It is not guaranteed to be `0`, or any predictable value at
all:

```c
int mystery;
printf("%d\n", mystery);   // could print anything -- don't do this
```

This is a classic source of bugs that are maddening to track down,
because the program might *seem* to work (garbage value happens to be
harmless) until it doesn't (garbage value happens to be huge, negative,
or otherwise breaks your logic) on a different run or a different
computer. The habit that avoids this entirely: **always initialize a
variable when you declare it**, unless you are about to immediately
read a value into it (as you'll do with `scanf` below).

## `const`: values that should never change

Some values in a program should be fixed for its entire run — a
mathematical constant, a maximum class size, a fixed price. Marking a
variable `const` tells the compiler to enforce that:

```c
const double PI = 3.14159;
const int MAX_STUDENTS = 30;
```

Try to assign a new value to a `const` variable anywhere later in the
program, and `gcc` will refuse to compile it. That's a feature, not an
annoyance — it turns "a value silently got changed somewhere it
shouldn't have" from a confusing runtime bug into an immediate, obvious
compiler error. Use `const` for any variable you can already tell should
never change after it's set.

## Reading user input with `scanf`

Every program until now has been a one-way conversation — it talks, you
listen. `scanf` (from `stdio.h`, the same header that gives you
`printf`) lets your program **read** input the user types.

```c
int age;
printf("Enter your age: ");
scanf("%d", &age);
```

A few things to notice:

- The **format specifier** works the same way it did for `printf` in
  Module 2 — `%d` for `int`, `%f` for `float`, `%c` for a single `char`.
- The **`&` before the variable name** is required. It means "the
  address of this variable" — it tells `scanf` exactly *where* in
  memory to store the value it reads, rather than handing it a copy of
  whatever's currently there. You'll fully understand why this works
  the way it does in Module 7 (Pointers). For now, the rule is simple:
  **always write `&` before the variable name in `scanf`** (for the
  types you know so far — this changes once you meet strings and
  arrays in Module 5).
- Always `printf` a prompt *before* calling `scanf`, so the user knows
  the program is waiting for them to type something.

Reading a `float` works the same way:

```c
float price;
printf("Enter a price: ");
scanf("%f", &price);
```

### `scanf` with `char` — and the leading-space bug

Reading a single character looks like it should be just as simple:

```c
char grade;
scanf("%c", &grade);
```

But there's a very common trap. Say your program first reads an `int`
with `scanf("%d", &score)`, then immediately tries to read a `char`:

```c
int score;
char grade;

scanf("%d", &score);
scanf("%c", &grade);   // BUG: this often doesn't wait for you to type anything
```

When you type a number and press Enter, `scanf("%d", ...)` reads the
digits but leaves the newline character (`\n`) from pressing Enter
sitting in the input buffer, untouched. The very next `scanf("%c", ...)`
immediately reads *that leftover newline* as if it were your answer —
your program appears to skip right past asking for the character.

The fix is a single space, written before `%c`:

```c
scanf(" %c", &grade);
```

That leading space tells `scanf`: "skip over any whitespace (spaces,
tabs, or leftover newlines) sitting in the buffer first, then read the
next real character." This one-character fix resolves one of the most
common and confusing beginner bugs with `scanf` — if a `%c` read seems
to get silently skipped, this is almost always why.

## Putting it together: read, compute, print

Every interactive program you'll write follows the same three-step
shape: **read input, compute something with it, print a result.**

```c
float num1, num2;

printf("Enter the first number: ");
scanf("%f", &num1);

printf("Enter the second number: ");
scanf("%f", &num2);

float sum = num1 + num2;
printf("%.2f + %.2f = %.2f\n", num1, num2, sum);
```

This is exactly the pattern behind the mind-reader hook at the top of
this module — read an age, compute a couple of values from it with
arithmetic, print sentences that reference the real numbers the user
typed. That's what makes it feel personal instead of generic.

## Common beginner mistakes

- Forgetting `&` before a variable name in `scanf` — the program will
  usually crash or behave unpredictably.
- Forgetting the leading space before `%c` in `scanf(" %c", ...)` when a
  numeric read came before it.
- Using the wrong format specifier for the variable's type (e.g.
  `scanf("%d", &price)` where `price` is a `float`) — this silently
  reads garbage instead of warning you.
- Declaring a variable without initializing it and then reading its
  value before ever assigning one.
- Trying to re-assign a `const` variable after it's been set.
- Using non-descriptive names (`x`, `a`, `temp1`) instead of names that
  say what the value actually represents.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one. Try feeding the `scanf` examples different input
   values.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 3: variables and input/output"
   git push
   ```

Next: **[Module 4 — Control Structures](../04-control-structures/README.md)**.
