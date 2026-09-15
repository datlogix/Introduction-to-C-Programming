# Module 16 — Enums, Unions & Bitwise Operators

## Hook: one number, eight switches

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>

#define FLAG_READ    (1 << 0)
#define FLAG_WRITE   (1 << 1)
#define FLAG_EXECUTE (1 << 2)
#define FLAG_DELETE  (1 << 3)
#define FLAG_SHARE   (1 << 4)
#define FLAG_ADMIN   (1 << 5)
#define FLAG_BACKUP  (1 << 6)
#define FLAG_AUDIT   (1 << 7)

void printPermissions(int perms) {
    printf("READ=%d WRITE=%d EXECUTE=%d DELETE=%d SHARE=%d ADMIN=%d BACKUP=%d AUDIT=%d\n",
        (perms & FLAG_READ)    != 0,
        (perms & FLAG_WRITE)   != 0,
        (perms & FLAG_EXECUTE) != 0,
        (perms & FLAG_DELETE)  != 0,
        (perms & FLAG_SHARE)   != 0,
        (perms & FLAG_ADMIN)   != 0,
        (perms & FLAG_BACKUP)  != 0,
        (perms & FLAG_AUDIT)   != 0);
}

int main(void) {
    int userPermissions = FLAG_READ | FLAG_WRITE | FLAG_EXECUTE;

    printf("Before:\n");
    printPermissions(userPermissions);

    userPermissions |= FLAG_SHARE;   // flip ONE switch on, nothing else

    printf("After granting SHARE:\n");
    printPermissions(userPermissions);

    return 0;
}
```

```bash
gcc hook.c -o hook
./hook
```

```
Before:
READ=1 WRITE=1 EXECUTE=1 DELETE=0 SHARE=0 ADMIN=0 BACKUP=0 AUDIT=0
After granting SHARE:
READ=1 WRITE=1 EXECUTE=1 DELETE=0 SHARE=1 ADMIN=0 BACKUP=0 AUDIT=0
```

One number, eight switches, and one line of code (`userPermissions |=
FLAG_SHARE;`) flipped exactly one of them — every other flag, untouched.
There's no array, no eight separate `bool` variables, just a single `int`
holding eight independent yes/no answers at once. By the end of this
module you'll know exactly how that line works, and you'll build a fuller
version of this permissions system in this module's project.

## `enum`: naming a fixed set of related constants

Back in Module 2 you met `int`, `float`, `double`, and `char`. An **`enum`**
(short for "enumeration") is a type you define yourself: a fixed, named
set of integer constants that all belong together.

```c
enum GameState { MENU, PLAYING, PAUSED, GAME_OVER };
```

This declares four named constants — `MENU`, `PLAYING`, `PAUSED`,
`GAME_OVER` — and a new type, `enum GameState`, that you can use just like
`int` when declaring a variable:

```c
enum GameState state = PLAYING;
```

Unless you say otherwise, C numbers enum members automatically starting
at `0`: `MENU` is `0`, `PLAYING` is `1`, `PAUSED` is `2`, `GAME_OVER` is
`3`. You can also assign your own values explicitly:

```c
enum Direction { NORTH = 1, SOUTH = 2, EAST = 4, WEST = 8 };
```

See [`examples/01_enums_basics.c`](examples/01_enums_basics.c).

## Why bother? Replacing magic numbers

Before enums, code that tracks "what state is the game in?" often looks
like this:

```c
if (state == 1) {
    // ... playing
}
```

That `1` is a **magic number** — a value with meaning that exists only in
the programmer's head (or a comment that will eventually go stale). Six
months from now, is `1` "playing," or did someone renumber the states?
With an enum, the same check reads as plain English and the compiler
still sees the same underlying integer comparison:

```c
if (state == PLAYING) {
    // ... playing
}
```

See [`examples/02_enums_vs_magic_numbers.c`](examples/02_enums_vs_magic_numbers.c)
for the same logic written both ways, side by side.

## Enums are really just ints — convenience and limitation

Under the hood, an enum value *is* an `int`. That's exactly why
`printf("%d", state)` works with no special format specifier, and why you
can compare an enum value with `==` just like any other integer. It's
also the limitation: **C does not stop you from putting any `int` into an
enum variable**, valid member or not.

```c
enum GameState sneaky = 99;   // compiles fine -- 99 isn't a real GameState
```

There's no real type safety here — an enum is a naming convenience for
you and future readers, not a guarantee enforced by the compiler. Keep
that in the back of your mind; it won't bite you often, but it can.

## Bitwise operators: working on individual bits

Every value in your program is, underneath, a sequence of bits — `0`s and
`1`s. The **bitwise operators** let you inspect and manipulate those bits
directly, rather than treating a number only as "a quantity." C has six:
`&`, `|`, `^`, `~`, `<<`, and `>>`.

Take `a = 12` (binary `00001100`) and `b = 10` (binary `00001010`):

| Operator | Name | Result on `a`, `b` | Rule |
|---|---|---|---|
| `a & b` | AND | `00001000` (`8`) | `1` only where **both** bits are `1` |
| `a \| b` | OR | `00001110` (`14`) | `1` where **either** bit is `1` |
| `a ^ b` | XOR | `00000110` (`6`) | `1` where the bits **differ** |
| `~a` | NOT | `11110011` (`243` as `unsigned char`) | every bit flipped |
| `a << 2` | left shift | `00110000` (`48`) | bits move left, zeros fill in (≈ `a * 4`) |
| `a >> 2` | right shift | `00000011` (`3`) | bits move right (≈ `a / 4`) |

Run [`examples/03_bitwise_operators.c`](examples/03_bitwise_operators.c) —
it prints each of these out bit by bit so you can watch the patterns
rather than just trust the table.

**Do not confuse `&` and `|` with `&&` and `||`.** `&&` and `||` are the
*logical* operators from Module 2 — they work on whole true/false values
and short-circuit. `&` and `|` are *bitwise* — they work bit by bit on
the binary representation of a number. `6 && 1` is `1` (both nonzero, so
both "true"). `6 & 1` is `0` (`0110` and `0001` share no `1` bits). They
can produce completely different answers on the same operands — mixing
them up is a real, easy-to-make bug.

## Flags: one number, several independent switches

The hook's real trick is combining `<<` with `|`: define each flag as a
power of two — `1`, `2`, `4`, `8`, ...` — so each one claims exactly one
bit that none of the others use.

```c
#define FLAG_READ    (1 << 0)   // 1  -- 00000001
#define FLAG_WRITE   (1 << 1)   // 2  -- 00000010
#define FLAG_EXECUTE (1 << 2)   // 4  -- 00000100
```

`1 << n` is a common, readable way to spell "the bit at position `n`" —
it reads as "1, shifted left n places," which is clearer at a glance than
memorizing that `FLAG_EXECUTE` happens to be `4`.

With the bits laid out like that, one `int` variable can track many
independent yes/no answers at once, using three small patterns:

```c
int permissions = 0;

permissions |= FLAG_READ;          // SET a flag: OR it in
permissions |= FLAG_EXECUTE;

if (permissions & FLAG_READ) {     // CHECK a flag: AND with it, see if anything survives
    printf("READ is set.\n");
}

permissions &= ~FLAG_READ;         // CLEAR a flag: AND with everything EXCEPT that bit
```

`~FLAG_READ` flips every bit of `FLAG_READ`, so ANDing with it turns
*only* that one bit off and leaves every other bit exactly as it was —
which is exactly what the hook demonstrated: granting `FLAG_SHARE`
touched nothing else. See
[`examples/04_flags_with_bitwise_or_and_and.c`](examples/04_flags_with_bitwise_or_and_and.c).

## `union`: different types sharing the same memory

A **`union`** looks like a `struct`, but behaves very differently: all of
its members share the *same* block of memory instead of each getting
their own. Only one member is meaningful at a time — writing through one
member and then reading through a *different* member does not convert
the value, it **reinterprets the same raw bytes** as a different type,
which is almost always a bug.

```c
union {
    int i;
    float f;
} v;

v.i = 42;
printf("%f\n", v.f);   // NOT 42.0 -- same bits, read as a float instead
```

Because that's dangerous on its own, real code almost always pairs a
union with a separate **tag** field that records which member is
currently valid — check the tag before you read:

```c
enum ValueType { TYPE_INT, TYPE_FLOAT };

typedef struct {
    enum ValueType type;   // the tag
    union {
        int i;
        float f;
    } data;
} Variant;
```

Now `if (v.type == TYPE_INT) { ... v.data.i ... }` is always reading the
member that was actually written. This tagged-union pattern is exactly
how safe, real-world code uses unions. See
[`examples/05_unions_basics.c`](examples/05_unions_basics.c), which shows
both the safe tagged version and the unsafe "read the wrong member" bug,
side by side.

## Scope check: what you'll actually reach for

Of the three tools in this module, you'll use them at very different
rates. **Enums** are something you'll reach for often — anywhere you'd
otherwise scatter magic numbers, an enum is usually the right call.
**Unions** and **raw bit manipulation** are more specialized: you might
write only a handful of unions in typical beginner/intermediate code, and
most day-to-day flag-like problems in C are solved with `bool` variables
or arrays long before you'd reach for hand-rolled bitwise flags. That
said, recognizing both when you meet them — in a library header, a
device driver, a file format, or a job's existing codebase — matters, and
now you can.

## Common beginner mistakes

- Confusing `&`/`|` (bitwise) with `&&`/`||` (logical) — they can produce
  different results on the same values, not just different syntax.
- Assuming an enum variable can only ever hold a "real" member value — C
  won't stop you from assigning any `int`.
- Forgetting that `~FLAG_X` is required to clear a flag —
  `permissions &= FLAG_X;` (no `~`) does the opposite of what you want.
- Writing one union member and reading a different one, expecting a
  conversion — you get the same bytes reinterpreted, not a converted
  value.
- Choosing flag values that aren't distinct powers of two (e.g. `1, 2,
  3`) — `3` overlaps with both `1` and `2`'s bits, breaking the
  one-bit-per-flag guarantee.
- Forgetting that shifting and masking bind more loosely than you might
  expect in a larger expression — when unsure, add parentheses, exactly
  as Module 2 taught you for arithmetic.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one. For `03_bitwise_operators.c`, predict each binary
   result before you run it, then check.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 16: enums, unions, and bitwise operators"
   git push
   ```

Next: **[Module 17 — Command-Line Arguments & CLI Tools](../17-command-line-arguments-and-cli-tools/README.md)**.
