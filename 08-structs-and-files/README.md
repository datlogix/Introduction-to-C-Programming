# Module 8 — Structs & File I/O

## Hook: a program that remembers

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>

typedef struct {
    int highScore;
} GameData;

int main(void) {
    GameData data;
    FILE *file = fopen("save.txt", "r");

    if (file == NULL) {
        printf("No save file found -- starting fresh.\n");
        data.highScore = 0;
    } else {
        fscanf(file, "%d", &data.highScore);
        fclose(file);
        printf("Welcome back! Your previous high score was %d.\n", data.highScore);
    }

    int newScore;
    printf("Enter your score this round: ");
    scanf("%d", &newScore);

    if (newScore > data.highScore) {
        data.highScore = newScore;
        printf("New high score!\n");
    }

    file = fopen("save.txt", "w");
    if (file == NULL) {
        printf("Error: could not save your score.\n");
        return 1;
    }
    fprintf(file, "%d", data.highScore);
    fclose(file);

    printf("High score (%d) saved. Run this program again and see for yourself.\n", data.highScore);
    return 0;
}
```

```bash
gcc hook.c -o hook
./hook
```

Enter a score, let it tell you it saved a new high score, then **run
`./hook` again**. This time it greets you by name of achievement — "Welcome
back! Your previous high score was..." — using data from a run of the
program that already ended. Every variable from that first run is long
gone from memory; only the *file* survived. By the end of this module
you'll understand every line of this, and you'll build a bigger version
of the same trick in the module project.

## Grouping data that belongs together

Modules 1–7 gave you variables, arrays, and functions, but every array
you've built so far holds only ONE kind of thing: an array of `int`, an
array of `char`. Real data doesn't come in single columns — a student has
a name AND an age AND a GPA, all at once, all describing the same person.

Without structs, you'd track that with **parallel arrays**:

```c
char names[3][30] = {"Ama", "Kwame", "Efua"};
int ages[3]        = {20, 22, 21};
float gpas[3]       = {3.8f, 3.2f, 3.9f};
```

This works, but it's fragile: `names[i]`, `ages[i]`, and `gpas[i]` only
describe "the same student" because *you* remember to keep all three
arrays in sync by hand. Sort one and forget the other two, and Ama's name
silently ends up next to Kwame's age. The compiler has no idea these
three arrays are related, so it can't warn you when they drift apart.

## Defining a struct

A **struct** groups related variables — called **members** — into a
single new type:

```c
struct Student {
    char name[30];
    int age;
    float gpa;
};
```

This doesn't create a variable yet — it defines a new *type* called
`struct Student`, the same way `int` or `char` is a type. To actually get
a variable, declare one like anything else:

```c
struct Student s1;
```

## Accessing members with `.`

Use the **dot operator** (`.`) to read or set a member of a struct
variable:

```c
strcpy(s1.name, "Ama");   // char arrays still need strcpy (Module 5)
s1.age = 20;
s1.gpa = 3.8f;

printf("%s is %d\n", s1.name, s1.age);
```

You can also fill in every member at once, in declaration order:

```c
struct Student s2 = {"Kwame", 22, 3.2f};
```

## `typedef`: a shorter name for the same type

Typing `struct Student` every time you declare a variable gets old fast.
`typedef` lets you attach a shorter alias to the type:

```c
typedef struct {
    char name[30];
    int age;
    float gpa;
} Student;

Student s1;   // instead of: struct Student s1;
```

This is **purely a naming convenience** — `Student` and the struct it
names are exactly the same type underneath, using exactly the same
amount of memory, with exactly the same members. `typedef` just saves
you keystrokes and reads a little cleaner. From here on, this module
uses the `typedef` style.

## Arrays of structs

The whole point of fixing the parallel-arrays problem: one array, where
each slot is a *complete* student.

```c
Student class[3] = {
    {"Ama",   20, 3.8f},
    {"Kwame", 22, 3.2f},
    {"Efua",  21, 3.9f}
};

for (int i = 0; i < 3; i++) {
    printf("%s is %d, GPA %.1f\n", class[i].name, class[i].age, class[i].gpa);
}
```

Looping looks exactly like the array loops from Module 5 — you're just
reaching one member deeper with `.` on each element.

## Structs and pointers: the arrow operator

Module 7 taught you `&` (address-of) and `*` (dereference). Both still
work exactly the same way on structs:

```c
Student s1 = {"Ama", 20, 3.8f};
Student *p = &s1;

printf("%d\n", (*p).age);   // dereference p, THEN access .age
```

The parentheses around `*p` are required — `.` binds tighter than `*`,
so `*p.age` would (incorrectly) try to do `p.age` first. Because
`(*p).member` is so common, C gives you a dedicated operator for it: the
**arrow operator**, `->`.

```c
printf("%d\n", p->age);     // exactly the same thing as (*p).age
```

`p->age` and `(*p).age` mean *identically* the same thing — always prefer
`->`, it's what every C programmer expects to read. And because `p`
*points at* `s1` rather than holding a separate copy, writing through the
pointer really does change the original:

```c
p->age = 21;
printf("%d\n", s1.age);   // prints 21 -- same variable
```

## Passing structs to functions by pointer

Module 7's biggest lesson was: passing a variable to a function normally
passes a *copy*, so changes inside the function don't escape it — unless
you pass a pointer instead. That rule applies to structs exactly as it
applies to `int`:

```c
void birthdayByValue(Student s) {
    s.age = s.age + 1;   // only changes the LOCAL copy
}

void birthdayByPointer(Student *s) {
    s->age = s->age + 1;  // changes the CALLER's struct
}

int main(void) {
    Student s1 = {"Ama", 20, 3.8f};
    birthdayByValue(s1);
    printf("%d\n", s1.age);      // still 20

    birthdayByPointer(&s1);
    printf("%d\n", s1.age);      // now 21
}
```

Rule of thumb: pass a struct **by pointer** whenever a function needs to
*modify* the caller's copy — `&s1` at the call site, `Student *s` as the
parameter, `s->member` inside the function.

## Basic file I/O

Every program you've written so far forgets everything the moment it
exits — all its variables live in memory, and memory is wiped clean when
the process ends. To make data survive, you have to write it to a
**file** on disk.

### Opening a file: `fopen`

```c
FILE *file = fopen("students.txt", "w");
```

`fopen` takes a filename and a **mode** string describing what you intend
to do:

| Mode | Meaning |
|---|---|
| `"w"` | **Write.** Creates the file if missing; **erases** existing contents if it already exists. |
| `"r"` | **Read.** Fails if the file doesn't exist. |
| `"a"` | **Append.** Like `"w"`, but adds to the *end* of an existing file instead of erasing it. |

### Always check for `NULL`

`fopen` can fail — the file doesn't exist (in `"r"` mode), a bad path, no
permission to write there. When it fails, it returns `NULL` instead of a
usable `FILE*`. **Always** check before using the result:

```c
if (file == NULL) {
    printf("Error: could not open the file.\n");
    return 1;
}
```

Skipping this check is one of the most common real-world C bugs: the
program crashes the instant it tries to read or write through a `NULL`
file pointer, often with a confusing error far from the real cause.

### Writing: `fprintf`

Works exactly like `printf`, except the first argument says *where* the
text goes:

```c
fprintf(file, "%s %d %.2f\n", s.name, s.age, s.gpa);
```

### Reading back: `fscanf`

Works exactly like `scanf` (Module 3), except it reads from a file
instead of the keyboard. It returns how many values it successfully
matched, which is exactly what you need to loop until the file runs out:

```c
Student s;
while (fscanf(file, "%29s %d %f", s.name, &s.age, &s.gpa) == 3) {
    // got one full student -- store it, e.g. class[count++] = s;
}
```

### Closing: `fclose` — and why it matters

```c
fclose(file);
```

Text you write with `fprintf` isn't necessarily on disk the instant you
call it — it can sit in a memory buffer for efficiency, and only actually
get written when the buffer fills up, the program ends normally, or you
close the file. `fclose` forces that write to happen *now*, and releases
the file so nothing else is blocked from using it. A program that writes
data but crashes (or is killed) before closing its files can lose data it
thinks it already saved. Get in the habit: every successful `fopen` gets
a matching `fclose`.

## Putting it together

The hook at the top of this module is the whole pattern in miniature:
write struct data to a file with `fprintf` in one run, read it back with
`fscanf` into a fresh array in a completely separate run, and the data
behaves as if the program never forgot it. [`examples/06_writing_a_file.c`](examples/06_writing_a_file.c)
and [`examples/07_reading_a_file.c`](examples/07_reading_a_file.c) show
this with a full array of structs instead of a single number — run `06`
first, then `07`, and watch the array come back exactly as you saved it.

This is also exactly what [Module 9's capstone project](../09-capstone-project/README.md)
requires: a struct type stored in an array, saved and reloaded so the
program's data survives being closed and reopened. Everything in this
module exists to make that requirement feel routine by the time you get
there.

## Common beginner mistakes

- Forgetting to check `fopen`'s return value for `NULL` before using it —
  this crashes the program the moment the file doesn't exist or can't be
  opened.
- Forgetting `fclose` — your data may never actually make it to disk, or
  later attempts to open the same file may behave unexpectedly.
- Opening a file in `"w"` mode when you meant `"a"` (or vice versa) and
  accidentally erasing everything that was there.
- Writing `*p.age` instead of `(*p).age` or `p->age` — `.` binds tighter
  than `*`, so this doesn't do what it looks like it does.
- Mismatching the `fscanf` format string with what `fprintf` actually
  wrote (wrong order, wrong number of fields, or a name containing a
  space when `%s` stops at the first space) — read the file back with a
  text editor if a read isn't behaving as expected.
- Forgetting the size limit in `%29s`-style reads into a fixed-size
  `char` array, allowing a read to overflow the array (Module 5's
  string-safety lesson still applies here).

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one. Run `06_writing_a_file.c`, then `07_reading_a_file.c`
   right after it, in the same folder — you're proving to yourself that
   the second run really does read what the first run wrote.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md) — run it, save, quit,
   and run it again to prove your data survived.
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 8: structs and file I/O"
   git push
   ```

Next: **[Module 9 — Capstone Project](../09-capstone-project/README.md)**.
