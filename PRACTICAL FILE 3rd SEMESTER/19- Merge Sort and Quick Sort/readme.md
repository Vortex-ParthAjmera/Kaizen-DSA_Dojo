<div align="center">

# Merge Sort and Quick Sort in C

**A single-shot demonstration of the two classic divide-and-conquer sorts — one with a guaranteed `O(n log n)`, one with a famous worst case.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./merge_quick_sort.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This program reads an array once, copies it, and sorts the two copies with **merge sort** and **quick sort**, printing both results. Both algorithms use the same big idea — split the problem, solve the pieces recursively, put the answer together — but they do their real work at opposite ends:

```text
Merge sort:   split in half  →  sort each half  →  MERGE the sorted halves   (work happens on the way back up)
Quick sort:   PARTITION around a pivot  →  sort each side                     (work happens on the way down)
```

Like several other practicals in this repo, it is single-shot: no menu, one run, one pair of results.

## What it demonstrates

- **Merge sort**: recursively halve the array, then merge two sorted halves into one by repeatedly taking the smaller front element
- **Quick sort**: pick a pivot, rearrange so everything smaller sits left of it and everything else right, then recurse on each side (this program uses the *Lomuto* partition scheme with the last element as pivot)
- Recursion on *index ranges* (`l`, `r` / `low`, `high`) rather than on copied sub-arrays
- That merge sort's cost doesn't depend on the input's shape, while quick sort's very much does — measured below
- Using `<=` in the merge step so equal elements keep their original order

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/19- Merge sort and quick sort"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `merge_quick_sort.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `merge_quick_sort.c`.

### 2. Compile

Linux or macOS:

```bash
gcc merge_quick_sort.c -std=c11 -Wall -Wextra -Wpedantic -o merge_quick_sort
```

Windows with GCC:

```powershell
gcc merge_quick_sort.c -std=c11 -Wall -Wextra -Wpedantic -o merge_quick_sort.exe
```

> [!TIP]
> The source compiles cleanly under `-Wall -Wextra -Wpedantic` with no warnings.

### 3. Run

Linux or macOS:

```bash
./merge_quick_sort
```

Windows PowerShell:

```powershell
.\merge_quick_sort.exe
```

## How to use it

1. Enter the number of elements, `n` (at most `100` — see [Known limitations](#known-limitations)).
2. Enter the `n` integers, space- or newline-separated, in any order. Negative numbers and duplicates are fine.

The program prints the sorted array once per algorithm and exits.

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| Random input | Both sorts produce the correct result. |
| Already sorted, reverse sorted, or all-equal input | Both sorts are still correct — but quick sort hits its worst case. See below. |
| Duplicates and negative values | Sorted correctly. |
| `n = 1` | Prints the single element twice. |
| `n = 0` or negative `n` | Prints two empty lines — the recursion's `l < r` / `low < high` guard stops immediately. |
| `n > 100` | Overflows the input arrays (and, for merge sort, its fixed temporary buffers). See below. |

## Example session

```text
Enter number of elements: 6
Enter elements: 38 27 43 3 9 82
Merge Sort: 3 9 27 38 43 82
Quick Sort: 3 9 27 38 43 82
```

Correctness was cross-checked by running both sorts against a reference sort on 30 inputs — random, already sorted, reverse sorted, all-equal, and few-distinct-values arrays at sizes from 2 to 100 — with zero mismatches.

## How the algorithms work

### Merge sort

```c
void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}
```

Split the range `[l, r]` at the midpoint, sort each half recursively, then merge. A range of one element (`l == r`) is already sorted, which is the base case.

The merge step does the real work:

```c
for (int i = 0; i < n1; i++) L[i] = a[l + i];     // copy left half out
for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j]; // copy right half out
// then repeatedly take the smaller of L[i], R[j] back into a[k]
if (L[i] <= R[j]) a[k++] = L[i++];
else              a[k++] = R[j++];
```

Both halves are copied into temporary arrays `L[]` and `R[]`, then written back in order by comparing the two fronts. The `<=` (rather than `<`) takes from the **left** half on ties, which keeps equal elements in their original order — that is what makes this merge sort *stable*.

### Quick sort

```c
int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] < pivot) { i++; /* swap a[i], a[j] */ }
    }
    /* swap a[i + 1], a[high] */
    return i + 1;
}
```

The pivot is the last element of the range. `i` marks the end of the "smaller than pivot" region; each element less than the pivot is swapped into that region. Finally the pivot is swapped into the slot just after it — its **final sorted position** — and that index is returned. `quickSort()` then recurses on everything left of that index and everything right of it, never touching the pivot again.

## Measured work: where the two diverge

These were measured with an instrumented copy of both sorts (same logic, with counters added) on `n = 100`:

| Input | Merge sort comparisons | Quick sort comparisons | Quick sort max recursion depth |
| --- | :---: | :---: | :---: |
| Random | 546 | 680 | 14 |
| Already sorted | 356 | **4,950** | **99** |
| Reverse sorted | 316 | **4,950** | **99** |
| All elements equal | 356 | **4,950** | **99** |

What the numbers show:

- **Merge sort is steady**: between 316 and 546 comparisons on every shape, always within the `n log n` neighborhood. For `n = 100` it can never exceed 573 comparisons.
- **Quick sort on random data is excellent**: 680 comparisons, and a recursion only 14 levels deep.
- **Quick sort collapses on three very ordinary inputs**: sorted, reverse sorted, and all-equal each cost the full `n(n-1)/2 = 4,950` comparisons — the same as bubble sort — with recursion 99 levels deep. The cause is the pivot choice: taking the *last* element as the pivot means that on sorted or reverse-sorted data the pivot is always the smallest or largest value, so each partition splits off just one element instead of halving the range. On all-equal data, the strict `<` test never moves anything, with the same one-element-at-a-time result.

## Complexity

Let `n` be the number of elements.

| Algorithm | Best | Average | Worst | Extra space | Stable? |
| --- | :---: | :---: | :---: | :---: | :---: |
| Merge sort | `O(n log n)` | `O(n log n)` | `O(n log n)` | `O(n)` | Yes |
| Quick sort (last-element pivot) | `O(n log n)` | `O(n log n)` | `O(n²)` | `O(log n)` typical, `O(n)` worst (call stack) | No |

- **Merge sort's `O(n)` extra space** comes from the temporary `L[]` and `R[]` copies made during each merge.
- **Quick sort sorts in place** — its only extra memory is the recursion stack, which is shallow (`O(log n)`) on typical data but as deep as `n` in the worst case, as the depth-99 rows above show.
- **Stability**: merge sort is stable thanks to the `<=` merge; quick sort's partition swaps can carry an element past an equal one, so it is not. With plain `int` values this isn't visible in the output, but it matters when sorting records by a key.

> [!TIP]
> Quick sort's worst case isn't exotic — already-sorted input is common in practice. Real implementations avoid it by choosing the pivot more carefully (random, or median of three) or by switching algorithms when recursion gets too deep.

## Code map

| Component | Responsibility |
| --- | --- |
| `merge()` | Merges two adjacent sorted ranges `a[l..m]` and `a[m+1..r]` using temporary arrays `L[]` and `R[]`. |
| `mergeSort()` | Recursively halves `[l, r]` and calls `merge()` on the way back up. |
| `partition()` | Lomuto partition around `a[high]`; returns the pivot's final index. |
| `quickSort()` | Partitions `[low, high]`, then recurses on both sides of the pivot. |
| `display()` | Prints an array's elements on one line. |
| `a[100]`, `b[100]` | The two working copies — one for each algorithm — filled from the same input. |
| `main()` | Reads `n` and the elements, copies them, runs each sort on its own copy, and prints the results. |

All implementation code is in [`merge_quick_sort.c`](./merge_quick_sort.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and runs one case:

```bash
gcc merge_quick_sort.c -std=c11 -Wall -Wextra -Wpedantic -o merge_quick_sort
printf '6\n38 27 43 3 9 82\n' | ./merge_quick_sort
```

The output should end with:

```text
Merge Sort: 3 9 27 38 43 82
Quick Sort: 3 9 27 38 43 82
```

To try quick sort's worst case, feed it sorted input — it will still be correct, just slower in principle:

```bash
printf '10\n1 2 3 4 5 6 7 8 9 10\n' | ./merge_quick_sort
```

## Known limitations

- **No bounds check on `n`.** `a[]` and `b[]` hold 100 elements, but `n` is never compared against that. In testing, `n = 100` and `n = 101` ran without visible symptoms, while `n = 102` and above aborted with `*** stack smashing detected ***`. Undefined behavior that happens to look fine at the smallest overflow is easy to miss.
- **Merge sort's temporary buffers are fixed at 50 elements each** (`int L[50], R[50]`). That is exactly enough for `n = 100` — the top-level merge splits into halves of 50 and 50 — and no more. For `n = 101` the left half is 51 elements and overflows `L[]`. So raising the `100` capacity in `main()` without also enlarging `L[]` and `R[]` (or allocating them to fit) would silently corrupt memory.
- **Quick sort degrades to `O(n²)` on sorted, reverse-sorted, and all-equal input**, with recursion as deep as `n` — measured above. The arrays here are capped at 100, so the depth is harmless, but the same code on a large sorted array could exhaust the call stack.
- **`scanf()` results are unchecked.** If `n` isn't a number, it is left uninitialized and the program's behavior is undefined (a segmentation fault in testing).
- **Only `int` arrays are supported**, and both sorts are hard-wired to ascending order.
- `m = (l + r) / 2` can overflow `int` for ranges of around a billion elements — impossible here, but a well-known trap if reused at scale. `l + (r - l) / 2` avoids it.
- The program has no automated tests or build configuration.

## Ideas for extending it

- Reject `n` outside `1..100` right after reading it, with a clear message.
- Allocate merge sort's temporary arrays to the exact size needed (`malloc`, or one shared buffer for the whole sort) instead of fixed `L[50]`/`R[50]`.
- Pick quick sort's pivot with median-of-three or at random to defuse the sorted-input worst case, then re-run the table above and compare.
- Handle many equal keys better with a three-way partition (less than / equal to / greater than the pivot).
- Recurse into the smaller side of the partition first and loop on the larger, so quick sort's stack depth is guaranteed `O(log n)`.
- Add comparison counters to the program itself so the table in this README is produced by the program, not a separate instrumented copy.
- Check `scanf()`'s return value for every read and re-prompt on bad input.
- Time both sorts on large random, sorted, and reversed arrays, and compare against the `O(n²)` sorts from the earlier sorting practical.
- Add unit tests for: sorted, reversed, all-equal, duplicates, negatives, `n = 0`, `n = 1`, and `n = 100`.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**One splits first and works last; the other works first and splits after — and only one of them is never surprised by the input.**

</div>