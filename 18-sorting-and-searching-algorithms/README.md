# Module 18 — Sorting & Searching Algorithms

## Hook: the same search, run two ways

Compile and run this exactly as written — don't read ahead first:

```c
#include <stdio.h>

#define SIZE 1000

int linearSearch(int arr[], int size, int target, int *comparisons) {
    for (int i = 0; i < size; i++) {
        (*comparisons)++;
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int binarySearch(int arr[], int size, int target, int *comparisons) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        (*comparisons)++;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main(void) {
    static int arr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i * 2;   // sorted: 0, 2, 4, ..., 1998
    }

    int target = 1998;    // the very last element -- linear search's worst case

    int linearComparisons = 0;
    int linearResult = linearSearch(arr, SIZE, target, &linearComparisons);

    int binaryComparisons = 0;
    int binaryResult = binarySearch(arr, SIZE, target, &binaryComparisons);

    printf("Searching for %d among %d sorted numbers...\n\n", target, SIZE);
    printf("Linear search: found at index %d, took %d comparisons\n", linearResult, linearComparisons);
    printf("Binary search: found at index %d, took %d comparisons\n", binaryResult, binaryComparisons);

    return 0;
}
```

```bash
gcc hook.c -o hook
./hook
```

```
Searching for 1998 among 1000 sorted numbers...

Linear search: found at index 999, took 1000 comparisons
Binary search: found at index 999, took 10 comparisons
```

Same array, same target, same answer — **1000 comparisons versus 10.**
Both functions are correct. Both find the right answer. One of them just
does dramatically less work, because it's allowed to assume something
about the array that the other isn't. By the end of this module you'll
know exactly what that assumption is, how to write both kinds of search,
how to write the sorting algorithms that make binary search possible in
the first place, and you'll build a small leaderboard tool in this
module's project.

## Linear search: check everything

**Linear search** is the obvious approach: start at the beginning, look
at each element in order, and stop the moment you find the target (or
run out of array). That's it — no requirements, no setup.

```c
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;   // found it -- return the index immediately
        }
    }
    return -1;          // walked the whole array, never matched
}
```

The one genuine advantage of linear search: **it works on any array,
sorted or not.** The cost: in the worst case (the target is the very
last element, or isn't there at all), it has to check every single
element. For an array of 1,000 elements, that's up to 1,000 comparisons;
for a million elements, up to a million. The bigger the array, the more
work linear search might have to do — it grows right along with the
data. See [`examples/01_linear_search.c`](examples/01_linear_search.c).

## Binary search: throw away half the possibilities every step

**Binary search** is far faster, but it has a precondition: **the array
must already be sorted.** Given that, it doesn't need to check every
element — it can compare the target to the *middle* element and
immediately know which half of the array to ignore entirely.

```c
int binarySearch(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;              // found it
        } else if (arr[mid] < target) {
            low = mid + 1;           // target must be in the right half
        } else {
            high = mid - 1;          // target must be in the left half
        }
    }

    return -1;   // low crossed high -- target isn't in the array
}
```

Trace it by hand: searching a sorted 15-element array
`{2, 5, 8, 12, 16, 23, 38, 42, 45, 51, 59, 63, 71, 78, 90}` for `71`:

```
low=0  high=14 mid=7  arr[7]=42   42 < 71  -> search the right half
low=8  high=14 mid=11 arr[11]=63  63 < 71  -> search the right half
low=12 high=14 mid=13 arr[13]=78  78 > 71  -> search the left half
low=12 high=12 mid=12 arr[12]=71  found!
```

Four comparisons to find one value out of fifteen — and every single
step throws away **half** of whatever was still left, so the advantage
only gets more extreme as the array grows. That's exactly what the hook
demonstrated: 1,000 elements, and binary search still only needed 10
comparisons. See [`examples/02_binary_search.c`](examples/02_binary_search.c),
which prints this exact trace as it runs.

### The precondition is not optional

Here's the part that matters most: **binary search on an unsorted array
does not crash, does not error, does not warn you.** It runs, it
produces *an* index, and that index is sometimes just wrong — because
the whole algorithm's logic ("the target isn't here, so it must be in
this half") only holds up when the array is actually sorted. On an
unsorted array, that assumption breaks silently, and you get a plausible
-looking wrong answer instead of a message telling you something went
wrong. A crash is annoying; a silent wrong answer is *much* scarier,
because nothing tells you to go looking for the bug. **Always know
whether the array you're searching is actually sorted before reaching
for binary search** — if it isn't, either sort it first (see below) or
fall back to linear search.

## Sorting: three ways to put an array in order

Binary search needs a sorted array to work — so before you can use it,
something has to *produce* that sorted array. That's what the rest of
this module covers: three classic sorting algorithms that all do the
same job (rearrange an array into ascending order) with different
strategies.

### Bubble sort

Repeatedly walk the array comparing **adjacent pairs**, swapping them if
they're out of order. Each full pass pushes the largest remaining value
one step closer to the end — like a bubble rising to the top.

```c
void bubbleSort(int arr[], int size) {
    for (int pass = 0; pass < size - 1; pass++) {
        for (int i = 0; i < size - 1 - pass; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }
}
```

Bubble sort is the simplest sort to understand and hand-trace, which is
exactly why it's a good *first* sort to learn — but it's also one of the
slowest for large arrays, doing far more comparisons and swaps than it
needs to. Learn it for the intuition, then reach for something else
(insertion sort, or the standard library's `qsort`) on real data. See
[`examples/03_bubble_sort.c`](examples/03_bubble_sort.c).

### Selection sort

For each position, starting at index 0, find the **minimum** value in
the remaining unsorted part of the array and swap it into that position.

```c
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}
```

After pass `i`, the first `i + 1` elements are the `i + 1` smallest
values in the array, fully sorted, and every later pass only ever
touches the unsorted remainder. See
[`examples/04_selection_sort.c`](examples/04_selection_sort.c).

### Insertion sort

Build up a sorted portion at the *front* of the array, one element at a
time — exactly like sorting a hand of playing cards as you pick them up.
Each new element gets shifted left, past every already-sorted card
bigger than it, until it lands in its correct spot.

```c
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];      // the card we just "picked up"
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];   // shift a bigger sorted element right
            j--;
        }
        arr[j + 1] = key;          // drop key into its correct spot
    }
}
```

See [`examples/05_insertion_sort.c`](examples/05_insertion_sort.c).

## A first sense of "how much work is that, really?"

You don't need formal algorithm analysis to notice that these algorithms
don't all cost the same. Just count, roughly, how many comparisons each
one might need in the worst case, for a few different array sizes:

| Array size | Linear search / bubble / selection / insertion sort (roughly) | Binary search (roughly) |
|---|---|---|
| 10 | up to 10 (search) / ~100 (sort) | ~4 |
| 1,000 | up to 1,000 / ~1,000,000 | ~10 |
| 1,000,000 | up to 1,000,000 / ~1,000,000,000,000 | ~20 |

Two things jump out:

- **Linear search and all three sorts above do more and more work as the
  list grows** — the sorts especially, since comparing *every pair*
  against *every other* element scales up fast (this is why they're
  sometimes grouped as "quadratic" sorts).
- **Binary search barely grows at all**, even for a huge list — going
  from 1,000 to 1,000,000 elements (1000x bigger) only costs it about 10
  more comparisons, because it throws away half of whatever's left at
  every single step.

That's the whole intuition. (There's a formal way to describe this
precisely — "Big-O notation" — but that's a topic for a later course;
for now, the important habit is just noticing that different algorithms
can do wildly different amounts of work for the same job.)

## A quick, honest look at `qsort`

Every algorithm above is worth learning for the intuition — but real
production C code almost never hand-writes its own sort. The standard
library already provides one: **`qsort`**, from `<stdlib.h>`.

```c
int compareInts(const void *a, const void *b) {
    return (*(int *)a) - (*(int *)b);
}

qsort(values, size, sizeof(int), compareInts);
```

`qsort` takes the array, how many elements it has, the size of one
element, and a **comparator function** you write — a small function that
takes two generic pointers, casts them back to the real type, and
returns negative/zero/positive depending on which value should come
first. You don't need to understand function pointers deeply to use
this (that's its own topic, for later) — just recognize the pattern:
write a comparator with exactly this shape, hand it to `qsort`, and it
does the sorting. See
[`examples/06_qsort_from_the_standard_library.c`](examples/06_qsort_from_the_standard_library.c)
for a complete, working example.

## Common beginner mistakes

- Running binary search on an array that **isn't actually sorted** — it
  won't crash, it'll just sometimes return the wrong answer, with no
  indication anything went wrong. Always verify the array is sorted
  first.
- Off-by-one errors in binary search's bounds — using `low < high`
  instead of `low <= high` (misses the case where the target is exactly
  at `low == high`), or forgetting `mid + 1` / `mid - 1` and looping
  forever because `low`/`high` never actually move.
- Writing `mid = (low + high) / 2` instead of
  `mid = low + (high - low) / 2` — rarely matters for small arrays in
  this course, but the second form avoids integer overflow on very large
  arrays and is worth building as a habit.
- Forgetting that a sort function needs to modify the array **in place**
  (via the array parameter) — the caller's array only changes if the
  sort actually swaps elements inside it, not a local copy.
- In bubble/selection/insertion sort, mixing up `<` and `<=`, or `i` and
  `j`, in the inner loop bounds — a one-character typo silently sorts
  the array *almost* correctly, which is a genuinely hard bug to spot by
  eye. Always test a small array by hand, not just by staring at the
  code.
- Using `==` instead of `strcmp` if you experiment with sorting strings
  later — a reminder all the way back from Module 5, and it still
  applies here.

## Try it yourself

1. Work through every file in [`examples/`](examples/), compiling and
   running each one.
2. Complete [`exercises/exercise1.c`](exercises/exercise1.c).
3. Build the [module project](project/README.md).
4. Commit and push your work:

   ```bash
   git add .
   git commit -m "Complete Module 18: sorting and searching algorithms"
   git push
   ```

Next: **[Module 19 — Part 2 Capstone Project](../19-part-2-capstone-project/README.md)**.
