# Module 7 — Pointers

## Hook: the magic swap that isn't

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>

void swapBroken(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    printf("  inside swapBroken: a = %d, b = %d\n", a, b);
}

int main(void) {
    int x = 3;
    int y = 7;

    printf("Before: x = %d, y = %d\n", x, y);
    swapBroken(x, y);
    printf("After:  x = %d, y = %d\n", x, y);

    return 0;
}
```

```bash
gcc swap.c -o swap
./swap
```

Look closely at the output. Inside `swapBroken`, `a` and `b` swap just
fine — but back in `main`, `x` and `y` are completely unchanged. The
function did exactly what you told it to. So why didn't it work?

The answer is coming in this module, and once you have it, you'll fix
this with a real, working swap using nothing but the tools below. This is
also the exact question that's been waiting since Module 6: why could a
function change the contents of an array you passed it, but never change
a plain `int`, `float`, or `char` the same way? Same answer.

## What is a memory address, really?

Every variable you create has to physically live somewhere while your
program runs — in **RAM (random-access memory)**. You can think of RAM as
an enormous row of numbered mailboxes; when you write `int age = 25;`,
the compiler picks a free mailbox, labels it `age` (just for your
convenience while reading the code), and stores `25` inside it. The
*number* of that mailbox is called its **address**.

You've already been using addresses without necessarily thinking of them
that way — every time you wrote `scanf("%d", &age);` back in Module 3,
that `&` meant "don't give scanf the value of age, give it the *address*
of age, so scanf can reach in and store what the user typed directly into
that mailbox." That's the whole mystery behind `&` finally explained.

You can print any variable's address yourself, using `&` and the `%p`
format specifier:

```c
int age = 25;
printf("age lives at address: %p\n", (void *)&age);
```

The address itself will look like a strange string of hex digits (e.g.
`0x7ffee3a1c9ac`). You will never need to memorize or predict what it
says — what matters is that it exists, and that a **pointer** is simply a
variable built to store one.

## Declaring a pointer

A pointer is a variable, just like any other — except instead of holding
a number or a character, it holds an *address*. You declare one with a
`*` between the type and the name:

```c
int *p;
```

Read this as "`p` is a pointer to `int`" — meaning: whatever address `p`
holds, it promises that address contains an `int`. This matters, because
the computer needs to know how many bytes to read starting from that
address; a pointer to `int` and a pointer to `char` read different
amounts of memory when you use them.

## The dual meaning of `*` — the single biggest beginner trap

Here is the part that trips up almost everyone at first: the `*` symbol
means **two completely different things** depending on where it shows up,
and C gives you no visual hint about which one you're looking at.

```c
int *p = &age;   // (1) declaration:  * means "p is a pointer"
*p = 100;        // (2) dereference:  * means "the value at the address p holds"
```

- In line (1), `*` is part of *declaring* `p`'s type. It only appears
  once, at the moment you introduce the variable.
- In line (2), `*` is the **dereference operator**. Applied to a pointer
  that already exists, `*p` means "go to the address stored in `p`, and
  give me (or let me set) the value that lives there."

The rule of thumb: if you're introducing a brand-new variable name right
after a type, `*` is part of the declaration. Anywhere else, `*` is
asking to follow the pointer to what it points to.

## Assigning and dereferencing a pointer

Putting declaration and dereference together:

```c
int age = 25;
int *p = &age;      // p now holds the ADDRESS of age -- "p points to age"

printf("%d\n", *p);  // dereference: "the value at the address p holds" -> 25
```

`p` and `age` are two different variables. `p` doesn't contain `25` — it
contains *the address where `25` lives*. `*p` is how you ask C to follow
that address and hand you what's actually stored there.

## Modifying a value through a pointer

Because `*p` means "the value at the address `p` holds," you can also
*assign* through it:

```c
*p = 100;   // go to the address p holds, and store 100 there
printf("%d\n", age);  // prints 100 -- age itself changed!
```

`p` never changed — it still points to the same address. What changed is
the value **sitting at** that address, which happens to be `age`. This is
the mechanism that makes pointers useful: they let one part of your
program reach out and change a variable that belongs to another part.

## Pass-by-value vs. pass-by-pointer: solving the hook

Back to `swapBroken`. When you call `swapBroken(x, y)`, C copies the
*values* of `x` and `y` into brand-new local variables `a` and `b`.
Swapping `a` and `b` swaps two copies that live nowhere near `x` and `y`
— and disappear the moment the function returns. This is called
**pass-by-value**, and it's how *every* plain parameter (`int`, `float`,
`char`, ...) works in C, always.

To actually reach `x` and `y`, you must give the function their
*addresses* instead — pass-by-pointer:

```c
void swapWorks(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// called as:
swapWorks(&x, &y);
```

Now `a` holds the address of `x`, and `b` holds the address of `y`.
`*a` and `*b` reach all the way back into `main`'s variables and swap
the real thing. Compile and run this version — `x` and `y` really do
swap this time.

C has no separate "pass by reference" keyword the way some other
languages do. **Pointers are how C does it** — explicitly, by you writing
`&` at the call site and `*` inside the function.

## Arrays and pointers: Module 6's mystery, solved

In Module 6, you learned that a function *can* modify the caller's array
directly — unlike a plain `int`. Now you know why: when you pass an array
to a function, it **decays into a pointer to its first element**. You
were never passing a copy of the whole array — you were passing an
address, exactly like `&x` above, whether you wrote `&` or not.

That means these two function signatures are interchangeable:

```c
int findMax(int arr[], int size) { ... }   // Module 6's version
int findMax(int *arr, int size)  { ... }   // exactly the same function
```

Both receive the address of the array's first element. `arr[i]` still
works either way — it's just friendlier notation for "the value `i`
slots past the address `arr` holds."

## NULL pointers

A pointer that isn't pointing at a real variable yet should be set to
`NULL` — a special value meaning "this points to nothing, on purpose."

```c
int *p = NULL;

if (p != NULL) {
    printf("%d\n", *p);
} else {
    printf("p isn't pointing anywhere yet.\n");
}
```

**Always check for `NULL` before dereferencing a pointer you're not
certain has been pointed at something.** Dereferencing `NULL` — or any
uninitialized "garbage" pointer that was never assigned an address at all
— is undefined behavior. Most often it crashes your program immediately
(a "segmentation fault"); sometimes, worse, it silently reads or corrupts
memory that isn't yours and doesn't crash at all.

## Common beginner mistakes

- Forgetting `&` when a function needs an address (e.g. `swapWorks(x, y)`
  instead of `swapWorks(&x, &y)`) — this is usually a compiler warning
  about mismatched types, not silence, so read those warnings.
- Confusing declaration-`*` with dereference-`*` — remember: only at the
  moment a pointer variable is introduced does `*` mean "this is a
  pointer type."
- Dereferencing a pointer that was never assigned an address (garbage) or
  was set to `NULL` — always check `if (p != NULL)` first when you're not
  certain.
- Assuming a pointer and the variable it points to are "the same
  variable" — they're two separate variables; one just happens to store
  the other's address.
- A sharp edge for later: `*p++` does NOT mean what it looks like at a
  glance — `++` binds tighter than `*`, so precedence rules matter a lot
  once you start combining pointer arithmetic with increment/decrement.
  You don't need to master this now; just know it's coming, and use
  parentheses like `(*p)++` when in doubt.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 7: pointers"
   git push
   ```

Next: **[Module 8 — Structs & File I/O](../08-structs-and-files/README.md)**.
