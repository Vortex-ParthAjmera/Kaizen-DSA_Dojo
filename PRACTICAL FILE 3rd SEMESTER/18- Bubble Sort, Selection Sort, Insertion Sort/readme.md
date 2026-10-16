<div align="center">

# Bubble, Selection, and Insertion Sort in C

**A single-shot demonstration of three classic `O(n²)` sorts, run side by side on the same input.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./sorting_basics.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This program reads an array once, makes two copies of it, and sorts each of the three copies with a different algorithm — **bubble sort**, **selection sort**, and **insertion sort** — then prints all three results. Because each sort gets its own copy (`a[]`, `b[]`, `c[]`), they all start from the same unsorted data, and all three should print the identical sorted array.

```text
Entered:   [64, 25, 12, 22, 11, 90]
Bubble:    [11, 12, 22, 25, 64, 90]
Selection: [11, 12, 22, 25, 64, 90]
Insertion: [11, 12, 22, 25, 64, 90]
```

Like several other practicals in this repo, it is single-shot: no menu, one run, one set of results. All three algorithms take the same time complexity on paper — what differs is *how much work each does* on different kinds of input, which is measured below.

## What it demonstrates

- **Bubble sort**: repeatedly compare neighbors and swap them if they're out of order, so the largest remaining value "bubbles" to the end on each pass
- **Selection sort**: repeatedly find the smallest remaining value and swap it into place at the front
- **Insertion sort**: grow a sorted prefix one element at a time, shifting larger elements right to make room for each new one
- That three algorithms with the same `O(n²)` worst case can behave very differently — in comparisons, in swaps, and on already-sorted input
- Sorting copies, so one input can be used to compare several algorithms fairly

The program uses only the C standard library and has no third-party dependencies.

## Quick start

### Prerequisite

Install GCC or another compiler that supports C99 or later. The commands below use GCC and compile the program as C11.

Check that GCC is available:

```bash
gcc --version
```

### 1. Get the repository

```bash
git clone https://github.com/Vortex-ParthAjmera/Kaizen-DSA_Dojo.git
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/18- Sorting basics"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `sorting_basics.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `sorting_basics.c`.

### 2. Compile

Linux or macOS:

```bash
gcc sorting_basics.c -std=c11 -Wall -Wextra -Wpedantic -o sorting_basics
```

Windows with GCC:

```powershell
gcc sorting_basics.c -std=c11 -Wall -Wextra -Wpedantic -o sorting_basics.exe
```

> [!TIP]
> The source compiles cleanly under `-Wall -Wextra -Wpedantic` with no warnings.

### 3. Run

Linux or macOS:

```bash
./sorting_basics
```

Windows PowerShell:

```powershell
.\sorting_basics.exe
```

## How to use it

1. Enter the number of elements, `n` (at most `100` — see [Known limitations](#known-limitations)).
2. Enter the `n` integers, space- or newline-separated, in any order. Negative numbers and duplicates are fine.

The program prints the sorted array three times, once per algorithm, and exits.

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| Already-sorted input | Sorts correctly; all three algorithms leave the array unchanged. |
| Reverse-sorted input | Sorts correctly — the worst case for bubble and insertion sort. |
| Duplicates and negative values | Sorted correctly; verified against a reference sort. |
| `n = 1` | Prints the single element three times. |
| `n = 0` or negative `n` | Prints three empty lines — every loop simply never runs. |
| `n > 100` | Overflows the fixed `a[]`, `b[]`, and `c[]` arrays. See below. |

## Example session

```text
Enter number of elements: 6
Enter elements: 64 25 12 22 11 90
Bubble Sort   : 11 12 22 25 64 90
Selection Sort: 11 12 22 25 64 90
Insertion Sort: 11 12 22 25 64 90
```

With duplicates and negatives:

```text
Enter number of elements: 8
Enter elements: 5 -3 5 0 -3 9 5 1
Bubble Sort   : -3 -3 0 1 5 5 5 9
Selection Sort: -3 -3 0 1 5 5 5 9
Insertion Sort: -3 -3 0 1 5 5 5 9
```

Correctness was cross-checked by running all three sorts on random inputs of 2, 10, 57, and 100 elements and comparing each result against a reference sort — all matched.

## How the algorithms work

### Bubble sort

```c
for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - 1 - i; j++)
        if (a[j] > a[j + 1]) { /* swap a[j], a[j+1] */ }
```

Each outer pass walks the unsorted region and swaps any adjacent pair that is out of order. After pass `i`, the `i + 1` largest values are in their final places at the end, which is why the inner loop's bound shrinks by `i` each time. As written, there is **no early-exit check**: even if a pass makes zero swaps (meaning the array is already sorted), the remaining passes still run.

### Selection sort

```c
for (int i = 0; i < n - 1; i++) {
    int minIdx = i;
    for (int j = i + 1; j < n; j++)
        if (a[j] < a[minIdx]) minIdx = j;
    /* swap a[i], a[minIdx] */
}
```

For each position `i`, scan everything to its right to find the smallest value, then swap it into position `i`. The scan always covers the whole remaining region regardless of the data, so selection sort does the same number of comparisons on *every* input. The upside is that it performs at most one swap per outer pass — at most `n - 1` swaps total, however scrambled the input. (The code swaps unconditionally each pass, including when `minIdx == i`, which just swaps an element with itself.)

### Insertion sort

```c
for (int i = 1; i < n; i++) {
    int key = a[i];
    int j = i - 1;
    while (j >= 0 && a[j] > key) {
        a[j + 1] = a[j];
        j--;
    }
    a[j + 1] = key;
}
```

Treat `a[0..i-1]` as already sorted. Take the next element (`key`), slide every larger element one slot to the right, and drop `key` into the gap. If `key` is already in the right place, the `while` loop exits immediately after one comparison — which is why insertion sort is fast on nearly sorted data.

## Measured work: not all `O(n²)` sorts are equal

All three have the same `O(n²)` worst case, but the *actual* operation counts differ sharply. These were measured with an instrumented copy of the three functions (same logic, with counters added) on `n = 100`:

| Input | Algorithm | Comparisons | Swaps / shifts |
| --- | --- | :---: | :---: |
| **Already sorted** | Bubble | 4,950 | 0 |
| | Selection | 4,950 | 0 |
| | Insertion | **99** | 0 |
| **Reverse sorted** | Bubble | 4,950 | 4,950 |
| | Selection | 4,950 | 50 |
| | Insertion | 4,950 | 4,950 |
| **Random** | Bubble | 4,950 | 2,647 |
| | Selection | 4,950 | 95 |
| | Insertion | 2,742 | 2,647 |

*Selection's swap column counts swaps that actually move something; the program itself executes `n - 1 = 99` swap statements regardless, as noted above.*

What the numbers show:

- **Bubble and selection always make exactly 4,950 comparisons** (`n(n-1)/2`), no matter how the data is arranged — neither one notices when the array is already sorted.
- **Insertion sort makes just 99 comparisons on sorted input** — one per element — because its inner loop stops as soon as it finds the right spot. This is the "adaptive" behavior that makes it the practical choice for nearly sorted data.
- **Selection sort moves very little data**: 95 real swaps on random input versus 2,647 for the other two. If writes are expensive, that matters.
- **Bubble swaps and insertion shifts are always equal** (4,950 reversed, 2,647 random). Both equal the number of *inversions* in the input — pairs of elements that are in the wrong order relative to each other — since each adjacent swap or shift fixes exactly one inversion.

## Complexity

Let `n` be the number of elements.

| Algorithm | Best | Average | Worst | Extra space | Stable? | Adaptive? |
| --- | :---: | :---: | :---: | :---: | :---: | :---: |
| Bubble sort (as written) | `O(n²)` | `O(n²)` | `O(n²)` | `O(1)` | Yes | No |
| Selection sort | `O(n²)` | `O(n²)` | `O(n²)` | `O(1)` | No | No |
| Insertion sort | `O(n)` | `O(n²)` | `O(n²)` | `O(1)` | Yes | Yes |

- **Stable** means equal elements keep their original relative order. Bubble and insertion sort only move an element past a *strictly* greater one (`>`), so equal elements never cross. Selection sort's long-distance swap can leap an element over an equal one, so it is not stable. (With plain `int` values this isn't visible in the output — equal integers are indistinguishable — but it matters as soon as you sort records by a key.)
- **Adaptive** means the algorithm does less work on input that is already close to sorted. Only insertion sort does here. Bubble sort *can* be made adaptive with an early-exit flag, but this version isn't.
- Every sort here works in place, using `O(1)` extra space beyond the input — though the program as a whole uses `O(n)` for the three copies.

> [!TIP]
> `O(n²)` sorts are for learning and for small or nearly sorted inputs. For real workloads, merge sort, quicksort, or the library's `qsort()` run in `O(n log n)`.

## Code map

| Component | Responsibility |
| --- | --- |
| `bubbleSort()` | Sorts by repeatedly swapping adjacent out-of-order pairs. |
| `selectionSort()` | Sorts by repeatedly swapping the smallest remaining value into place. |
| `insertionSort()` | Sorts by inserting each element into the sorted prefix, shifting larger values right. |
| `display()` | Prints an array's elements on one line. |
| `a[100]`, `b[100]`, `c[100]` | The three working copies — one per algorithm — all filled from the same input. |
| `main()` | Reads `n` and the elements, copies them, runs each sort on its own copy, and prints the results. |

All implementation code is in [`sorting_basics.c`](./sorting_basics.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and runs one case:

```bash
gcc sorting_basics.c -std=c11 -Wall -Wextra -Wpedantic -o sorting_basics
printf '6\n64 25 12 22 11 90\n' | ./sorting_basics
```

The output should end with:

```text
Bubble Sort   : 11 12 22 25 64 90
Selection Sort: 11 12 22 25 64 90
Insertion Sort: 11 12 22 25 64 90
```

## Known limitations

- **No bounds check on `n`.** All three arrays hold 100 elements, but `n` is never compared against that. Entering more than 100 elements writes past the end of the arrays — undefined behavior. In testing, `n = 101` and `n = 102` ran with no visible symptoms, while `n = 103` and above aborted with `*** stack smashing detected ***`. Small overflows looking harmless is exactly what makes this bug easy to miss.
- **`scanf()` results are unchecked.** If `n` isn't a number, it is left uninitialized and the program's behavior is undefined; non-numeric element values are likewise unhandled.
- **Bubble sort has no early exit**, so already-sorted input still costs all 4,950 comparisons at `n = 100`, as measured above.
- **Selection sort swaps unconditionally**, performing a pointless self-swap whenever the minimum is already in place.
- **Only `int` arrays are supported**, and the sorts are hard-wired to ascending order.
- **The program doesn't report which algorithm did less work** — the comparison in this README came from a separate instrumented copy, not from the program itself.
- The program has no automated tests or build configuration.

## Ideas for extending it

- Reject `n` outside `1..100` right after reading it, with a clear message.
- Check `scanf()`'s return value for every read and re-prompt on bad input.
- Add a "swapped" flag to bubble sort so it stops after a pass with no swaps — turning its best case from `O(n²)` into `O(n)`.
- Add comparison and swap counters to each sort and print them next to the results, so the table above is produced by the program itself.
- Guard selection sort's swap with `if (minIdx != i)`.
- Let the user choose ascending or descending order, or pass a comparison function.
- Add an `O(n log n)` sort (merge sort or quicksort) and compare its counts on the same input.
- Generate large random, sorted, and reversed inputs automatically and time each algorithm.
- Add unit tests for: sorted, reversed, all-equal, duplicates, negatives, `n = 0`, and `n = 1`.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**Three ways to put things in order — same destination, very different journeys.**

</div>