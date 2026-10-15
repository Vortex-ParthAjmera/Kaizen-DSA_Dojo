<div align="center">

# Linear Search and Binary Search in C

**A single-shot comparison of scanning an array front to back versus halving a sorted one — run on the same data, with the same key.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./searching.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This program reads an array and a search key, then looks for the key two ways: a **linear search** over the array exactly as entered, and a **binary search** over a sorted copy of it. Binary search only works on sorted data, so the program keeps the original untouched in `a[]`, copies it into `b[]`, sorts `b[]` with bubble sort, and searches that.

```text
Entered:   a = [40, 10, 30, 20, 50]      → linearSearch(a, key)
Sorted:    b = [10, 20, 30, 40, 50]      → binarySearch(b, key)
```

Like several other practicals in this repo, it is single-shot: no menu, one run, one answer from each algorithm.

## What it demonstrates

- **Linear search**: check every element in order and stop at the first match — works on any array, sorted or not
- **Binary search**: compare against the middle element, then discard the half that can't contain the key — works only on sorted data
- Why binary search needs a precondition (sortedness) that linear search doesn't, and what the program does to satisfy it: sort a **copy**, so the original order is still available for the linear search
- Returning `-1` as a "not found" sentinel, since `-1` is never a valid array index
- That the two searches can report **different indices** for the same key, because they search different arrays

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/17- Linear and binary search"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `searching.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `searching.c`.

### 2. Compile

Linux or macOS:

```bash
gcc searching.c -std=c11 -Wall -Wextra -Wpedantic -o searching
```

Windows with GCC:

```powershell
gcc searching.c -std=c11 -Wall -Wextra -Wpedantic -o searching.exe
```

> [!TIP]
> The source compiles cleanly under `-Wall -Wextra -Wpedantic` with no warnings.

### 3. Run

Linux or macOS:

```bash
./searching
```

Windows PowerShell:

```powershell
.\searching.exe
```

## How to use it

1. Enter the number of elements, `n` (at most `100` — see [Known limitations](#known-limitations)).
2. Enter the `n` integers, space- or newline-separated, in any order.
3. Enter the key to search for.

The program then prints one result line for each search and exits.

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| Key present, all elements distinct | Both searches report it found; the indices may differ (linear reports the position in your original order, binary the position in the sorted order). |
| Key absent | `Not found` from both searches. |
| Key appears more than once | Linear search reports the **first** (lowest-index) occurrence. Binary search reports **whichever occurrence the midpoint probe lands on first** — not necessarily the first or last. |
| `n = 0` or negative `n` | Both searches report `Not found` — the loops simply never run. |
| `n = 1` | Works as expected. |
| `n > 100` | Overflows the fixed `a[100]`/`b[100]` arrays. See below. |

## Example session

```text
Enter number of elements: 5
Enter elements: 40 10 30 20 50
Enter key to search: 40
Linear Search: Found at index 0
Binary Search: Found at index 3 (in sorted array)
```

The key `40` sits at index `0` of the array as entered, but at index `3` of the sorted copy `[10, 20, 30, 40, 50]`. Both answers are right — they are indices into two different arrays. The `(in sorted array)` suffix on the binary search line exists for exactly this reason.

### Duplicates: same key, different answers

```text
Enter number of elements: 7
Enter elements: 5 3 5 1 5 9 5
Enter key to search: 5
Linear Search: Found at index 0
Binary Search: Found at index 3 (in sorted array)
```

The sorted copy is `[1, 3, 5, 5, 5, 5, 9]`, so `5` occupies indices `2`–`5`. Binary search returns index `3` simply because that is where its first midpoint probe (`(0 + 6) / 2 = 3`) happens to land. It stops at the first match it sees and makes no attempt to find the leftmost one.

## How the algorithms work

### Linear search

```c
for (int i = 0; i < n; i++) {
    if (a[i] == key) return i;
}
return -1;
```

Walk from the front and return the moment a match appears. If the loop finishes, nothing matched.

### Binary search

```c
int lo = 0, hi = n - 1;
while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (a[mid] == key) return mid;
    else if (a[mid] < key) lo = mid + 1;
    else hi = mid - 1;
}
return -1;
```

`lo` and `hi` bracket the part of the array that could still contain the key. Each pass checks the middle: on a match it returns; if the middle is smaller than the key, everything at or below `mid` is ruled out (`lo = mid + 1`); if larger, everything at or above it is (`hi = mid - 1`). The window halves every pass, and `lo > hi` means it has emptied without finding the key.

The `+ 1` and `- 1` matter: without them, `mid` stays inside the window and the loop can fail to shrink it.

### Sorting the copy

```c
for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1 - i; j++) {
        if (b[j] > b[j + 1]) { /* swap */ }
    }
}
```

Bubble sort: each outer pass floats the largest remaining value to the end of the unsorted region, which is why the inner loop's bound shrinks by `i` each time. It sorts `b[]` only, so `a[]` keeps its original order for the linear search.

## Complexity

Let `n` be the number of elements.

| Operation | Best | Worst | Reason |
| --- | :---: | :---: | --- |
| Linear search | `O(1)` | `O(n)` | Best case is a match at index `0`; worst case is a match at the end or no match at all. |
| Binary search (on sorted data) | `O(1)` | `O(log n)` | Best case is a match at the first midpoint; otherwise the window halves each pass. |
| Bubble sort of the copy | `O(n²)` | `O(n²)` | There is no early-exit check, so even already-sorted input performs every comparison. |
| **This program, end to end** | `O(n²)` | `O(n²)` | The sort dominates; binary search's `O(log n)` is a rounding error next to it. |

Space is `O(n)` for the extra copy `b[]`.

For `n = 100`, linear search makes at most 100 comparisons and binary search at most 7 — but the sort ahead of it makes `100 × 99 / 2 = 4,950` comparisons. Binary search pays off when the data is sorted **once** and searched **many times**; in this program it is sorted once and searched once, so the sort costs far more than the search saves.

> [!TIP]
> That trade-off is the real lesson of this practical. Binary search is fast *given* sorted data; if you have to sort first and search only once, a plain linear scan is cheaper overall.

## Code map

| Component | Responsibility |
| --- | --- |
| `linearSearch()` | Scans `a[0..n-1]` in order and returns the first matching index, or `-1`. |
| `binarySearch()` | Repeatedly halves the window `[lo, hi]` of a sorted array and returns a matching index, or `-1`. |
| `a[100]` | The array as entered; searched by `linearSearch()`. |
| `b[100]` | A copy of `a[]`, sorted in `main()` with bubble sort; searched by `binarySearch()`. |
| `main()` | Reads `n`, the elements, and the key; runs both searches and prints each result. |

All implementation code is in [`searching.c`](./searching.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and runs a case where the two indices differ:

```bash
gcc searching.c -std=c11 -Wall -Wextra -Wpedantic -o searching
printf '5\n40 10 30 20 50\n40\n' | ./searching
```

The last two lines of output should be:

```text
Linear Search: Found at index 0
Binary Search: Found at index 3 (in sorted array)
```

To check the not-found path:

```bash
printf '5\n40 10 30 20 50\n99\n' | ./searching
```

Both searches should report `Not found`.

## Known limitations

- **No bounds check on `n`.** `a[]` and `b[]` hold 100 elements each, but `n` is never compared against that. Entering more than 100 elements writes past the end of both arrays — undefined behavior. In testing, `n = 101` happened to run without visible symptoms, while `n = 105` and `n = 150` aborted with `*** stack smashing detected ***`. The fact that the smallest overflow looks fine is part of what makes this kind of bug easy to miss.
- **Binary search reports an arbitrary match among duplicates**, as shown above — not the first, not the last. If you need a specific one, the algorithm needs a small change (keep searching after a match).
- **The binary-search index is not an index into your original array.** It refers to the sorted copy, which the program does not map back to original positions.
- **`scanf()` results are unchecked.** If `n` isn't a number, it is left uninitialized and the program's behavior is undefined (a segmentation fault in testing). Non-numeric element or key input is likewise unhandled.
- **The sort has no early exit**, so a sorted input still costs the full `O(n²)`.
- `mid = (lo + hi) / 2` can overflow `int` for arrays of around a billion elements — impossible here with a cap of 100, but a well-known trap if this function is reused on large arrays. `lo + (hi - lo) / 2` avoids it.
- The program has no automated tests or build configuration.

## Ideas for extending it

- Reject `n` outside `1..100` right after reading it, with a clear message.
- Check `scanf()`'s return value for every read and re-prompt on bad input.
- Track original positions while sorting (for example, sort an array of index/value pairs) so binary search can report where the key was in the *entered* order.
- Write a "leftmost match" variant of binary search that keeps narrowing after a hit, so duplicates give a predictable answer.
- Replace bubble sort with an `O(n log n)` sort such as merge sort or `qsort()`, and add an early-exit flag if keeping bubble sort for teaching.
- Count comparisons in each search and print the totals, so the `O(n)` vs `O(log n)` gap is visible on real input.
- Add a recursive version of binary search to compare with the iterative one, in the spirit of the recursion practicals in this repo.
- Add unit tests for: key at the first, middle, and last position; key absent; duplicates; `n = 1`; and `n = 0`.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**Look at everything, or halve what's left — but halving needs the order first.**

</div>