# Module 6 — Functions

## Hook: the same receipt, two very different mains

Compile and run both of these — don't read ahead first.

**Version A:**

```c
#include <stdio.h>

int main(void) {
    double price1 = 4.50;
    int qty1 = 3;
    double subtotal1 = price1 * qty1;
    double tax1 = subtotal1 * 0.15;
    double total1 = subtotal1 + tax1;
    printf("Coffee: %d x $%.2f = $%.2f (tax $%.2f) => total $%.2f\n",
           qty1, price1, subtotal1, tax1, total1);

    double price2 = 2.25;
    int qty2 = 5;
    double subtotal2 = price2 * qty2;
    double tax2 = subtotal2 * 0.15;
    double total2 = subtotal2 + tax2;
    printf("Muffin: %d x $%.2f = $%.2f (tax $%.2f) => total $%.2f\n",
           qty2, price2, subtotal2, tax2, total2);

    return 0;
}
```

**Version B:**

```c
#include <stdio.h>

void printReceiptLine(char itemName[], double unitPrice, int quantity) {
    double subtotal = unitPrice * quantity;
    double tax = subtotal * 0.15;
    double total = subtotal + tax;
    printf("%s: %d x $%.2f = $%.2f (tax $%.2f) => total $%.2f\n",
           itemName, quantity, unitPrice, subtotal, tax, total);
}

int main(void) {
    printReceiptLine("Coffee", 4.50, 3);
    printReceiptLine("Muffin", 2.25, 5);
    return 0;
}
```

```bash
gcc versionA.c -o versionA && ./versionA
gcc versionB.c -o versionB && ./versionB
```

Same numbers in, same receipt lines out — byte for byte. Version B is
less than half the length, and if the tax rate ever changes, you fix it
in exactly **one** place instead of hunting down every copy-pasted block.
That's the entire pitch for this module: a **function** is a named,
reusable chunk of code you write once and use as many times as you like.
By the end of this module you'll refactor a much bigger program the same
way. You can see this exact comparison, with a bit more detail, in
[`examples/01_why_functions_before_and_after.c`](examples/01_why_functions_before_and_after.c).

## Why functions?

Think back to your Module 4 Number Guessing Game project: the computer
picks a random number, and `main()` loops — reading a guess, checking
whether it's in range, comparing it to the secret number, and printing
"too high," "too low," or "correct." For a first version, all of that
living inside one `main()` is fine.

But picture growing that game a little: add a limit on the number of
guesses, add a "play again?" option, add a difficulty setting that
changes the range. Every new feature means `main()` gets a few lines
longer and a bit more tangled — the input-reading code, the validation
code, the comparison code, and the printing code all interleaved. Six
months from now (or six minutes from now, debugging it), it's hard to
answer a simple question like "where exactly do we decide the player
won?" because that logic is mixed in with everything else.

Functions fix this by giving each *job* a name and a boundary. "Get a
valid guess from the player" becomes a function. "Check the guess"
becomes a function. `main()` shrinks down to reading like a to-do list:
get a guess, check it, print the result, repeat. You'll do exactly this
refactor to your own guessing game in this module's project.

Breaking a program into functions gives you three things at once:

- **Reusability** — write the logic once, call it from anywhere, as many
  times as you like (that's the receipt hook, above).
- **Readability** — a well-named function tells you what a block of code
  does without you having to read its body. `checkGuess(guess, secret)`
  is self-explanatory; twelve lines of `if`/`else` inline in `main()`
  aren't, at a glance.
- **Testability** — you can try a function on its own, with known inputs,
  and check it gives the right output, without running your whole
  program end to end.

## Declaring and calling a function

A function has three parts: a **header** (what it's called, what it
takes in, what it gives back), a **body** (the code that runs), and,
separately, every place you **call** it.

```c
void printStarRow(int count) {
    for (int i = 0; i < count; i++) {
        printf("*");
    }
    printf("\n");
}

int main(void) {
    printStarRow(3);
    printStarRow(8);
    return 0;
}
```

Reading the header left to right: `void` is the **return type** (this
function doesn't send any value back — more on that soon), `printStarRow`
is the **name**, and `(int count)` is the **parameter list** — the inputs
this function expects. Every time you write `printStarRow(3);`, you're
**calling** the function, and `3` flows into `count` for that one run.

See [`examples/02_declaring_and_calling.c`](examples/02_declaring_and_calling.c).

## Prototypes: telling the compiler what's coming

C reads your file from top to bottom, once. If `main()` calls a function
that hasn't been defined *yet* — because its full definition is further
down the file — the compiler has no idea it exists and refuses to
compile.

A **prototype** (also called a **declaration**) solves this. It's the
function's header line, on its own, ending in a semicolon, with no body:

```c
void describeTemperature(int celsius); // prototype

int main(void) {
    describeTemperature(35); // compiler already knows this exists
    return 0;
}

void describeTemperature(int celsius) { // full definition, further down
    if (celsius >= 30) {
        printf("%d C: that's hot.\n", celsius);
    } else {
        printf("%d C: that's not so hot.\n", celsius);
    }
}
```

The prototype is a promise: "a function with this exact name, these
parameter types, and this return type exists somewhere in this file."
The compiler holds you to it — if the real definition doesn't match, or
never shows up, you'll get an error at link time. This is exactly why
you'll often see a block of prototypes near the top of a C file, above
`main()`: it lets you write `main()` first, reading top-to-bottom like a
summary of the program, with the messy implementation details below it.

See [`examples/03_prototypes.c`](examples/03_prototypes.c).

## Parameters, arguments, and return values

These two words get mixed up constantly, so pin them down now:

- A **parameter** is the named placeholder in the function's own header —
  it's part of how the function is *written*.
- An **argument** is the actual value you hand over at the *call site*.

```c
int add(int a, int b) {  // a and b are PARAMETERS
    return a + b;
}

int total = add(3, 4);   // 3 and 4 are ARGUMENTS
```

A function can send a result back to its caller with `return`. The type
before the function's name promises what type that will be:

```c
int isEven(int number) {
    if (number % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}
```

`return` immediately exits the function with that value — any code after
a `return` in the same path never runs. You can use the returned value
directly (`printf("%d\n", isEven(7));`) or store it in a variable first.

See [`examples/04_parameters_and_return_values.c`](examples/04_parameters_and_return_values.c).

## `void` functions

Not every function needs to hand a value back. A function whose job is
just to *do* something — print a banner, update the screen, play a sound
— declares `void` as its return type, meaning "nothing comes back." You
already met one above: `printStarRow`. A `void` function can still use a
bare `return;` (no value) to exit early, but it's optional.

## Scope: where a variable lives

A variable declared inside a function only exists **inside that
function**, for as long as that function is running. This is called its
**scope**. Once the function returns, its local variables are gone —
nothing outside can see them, read them, or accidentally clash with a
variable of the same name in a different function.

```c
void printWelcomeBanner(char userName[]) {
    int line = 1;             // exists only inside this function
    printf("%d) Welcome, %s!\n", line, userName);
}

int main(void) {
    printWelcomeBanner("Ama");
    // printf("%d\n", line);  // ERROR: `line` doesn't exist out here
    return 0;
}
```

A **global variable** — declared outside every function — is the
opposite: every function can read and change it. It compiles, and
sometimes you'll see it in other people's code, but avoid it as a
beginner. When any function anywhere can silently change a shared
variable, tracking down *which* function caused a wrong value becomes a
real headache as programs grow. Passing values in as parameters and
getting results back with `return` keeps each function's effects
visible and contained.

See [`examples/05_void_functions_and_scope.c`](examples/05_void_functions_and_scope.c).

## Passing an array to a function

You can pass an array to a function just like any other value — you just
also pass its size as a separate argument, since C doesn't track an
array's length for you once it's inside the function:

```c
int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
```

Here's the part that's genuinely different from every other type you've
passed to a function so far: **when you pass an array, the function can
modify the original array back in `main()`** — not just its own private
copy. An `int` or `double` argument gets copied in, and changes inside
the function stay inside the function. Arrays don't work that way. You'll
find out exactly *why* in Module 7 — for now, just know arrays are the
exception, and treat any function that takes an array as a function that
might change it.

See [`examples/06_passing_arrays_to_functions.c`](examples/06_passing_arrays_to_functions.c).

## Refactoring: turning a mess into functions

**Refactoring** means changing how code is organized without changing
what it does. It's the single most practical skill in this module. The
process is always the same:

1. Find a self-contained piece of logic — something you could describe
   in one short sentence ("this part checks if the guess is too high or
   too low").
2. Give that sentence a function name (`checkGuess`).
3. Move the code into a new function with that name, turning the values
   it depended on into parameters, and whatever it produced into a
   `return` value (or a `printf`, if its whole job is printing).
4. Replace the original code with a call to your new function.
5. **Recompile and test immediately.** Refactoring should never change
   behavior — if the output changes, you introduced a bug, not an
   improvement.

That's exactly what you did conceptually in the hook at the top of this
module (turning duplicated receipt math into `printReceiptLine`), and
it's exactly what this module's project asks you to do to your whole
Number Guessing Game.

## Common beginner mistakes

- Forgetting a function's **prototype** when it's defined below `main()`
  — the compiler will complain about an undeclared or implicitly
  declared function, often pointing at the *call*, not the missing
  prototype.
- Mixing up **parameters** and **arguments** in conversation — harmless
  day to day, but know the difference when reading error messages.
- Writing `void` on a function and then trying to use its result:
  `int x = printStarRow(3);` won't compile — a `void` function has no
  value to give back.
- Forgetting `return` in a non-`void` function, or returning the wrong
  type. The compiler will often warn you, but always double check.
- Trying to use a local variable outside the function it was declared
  in — remember, its scope ends at the function's closing `}`.
- Forgetting to pass an array's size as its own parameter, or assuming a
  function *won't* change the array you passed it, when it does.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 6: functions"
   git push
   ```

Next: **[Module 7 — Pointers](../07-pointers/README.md)**.
