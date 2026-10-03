<div align="center">

# Deque (Double-Ended Queue) using an Array in C

**An interactive demonstration of inserting and deleting at both ends of a circular, fixed-capacity array.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./deque_operations.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

A **deque** (double-ended queue) allows insertion and deletion at *both* ends — it's a queue and a stack at once. This implementation reuses the circular-array trick from the circular queue practical elsewhere in this repo: `front` and `rear` both wrap around the array with modulo arithmetic, so there's no wasted space and no "false overflow."

```text
              q[0]  q[1]  q[2]  q[3]  q[4]
            ┌─────┬─────┬─────┬─────┬─────┐
            │  30 │  ?  │  ?  │  10 │  20 │     MAX = 5
            └─────┴─────┴─────┴─────┴─────┘
               ▲                 ▲
              rear              front
```

Here `front` is actually *ahead* of `rear` in array-index terms — that's perfectly normal for a circular structure: the logical order is `front → ... → rear`, wrapping past the end of the array back to index `0` as needed. `insertFront`/`deleteFront` move `front` backward and forward around the ring; `insertRear`/`deleteRear` do the same for `rear`.

## What it demonstrates

- Supporting insertion and deletion at **both** ends of the same structure
- Reusing the circular queue's `isFull()` formula — `(rear + 1) % MAX == front` — which works identically here regardless of which end is being modified
- Wrapping `front` **backward** with `(front - 1 + MAX) % MAX` for front-insertion, and `rear` **backward** with `(rear - 1 + MAX) % MAX` for rear-deletion — the `+ MAX` is what keeps the result non-negative before the modulo, since C's `%` can otherwise return negative values for a negative left-hand side
- Using the same `-1`/`-1` empty sentinel as the circular queue practical, which is what lets the deque use **all** `MAX` slots rather than sacrificing one to disambiguate full from empty
- Detecting "last element removed" from *either* end the same way — `front == rear` — and resetting both to `-1` so the structure can start fresh from index `0` again

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/14- Deque operations using array"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `deque_operations.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `deque_operations.c`.

### 2. Compile

Linux or macOS:

```bash
gcc deque_operations.c -std=c11 -Wall -Wextra -Wpedantic -o deque_operations
```

Windows with GCC:

```powershell
gcc deque_operations.c -std=c11 -Wall -Wextra -Wpedantic -o deque_operations.exe
```

> [!TIP]
> The source compiles cleanly under `-Wall -Wextra -Wpedantic` with no warnings.

### 3. Run

Linux or macOS:

```bash
./deque_operations
```

Windows PowerShell:

```powershell
.\deque_operations.exe
```

## How to use it

There is **no initial build step** — the program starts with an empty deque and goes straight to the menu.

| Choice | Operation | Additional input |
| :---: | --- | --- |
| `1` | Insert a value at the front | Integer value (only prompted if the deque is not full) |
| `2` | Insert a value at the rear | Integer value (only prompted if the deque is not full) |
| `3` | Delete the value at the front | None |
| `4` | Delete the value at the rear | None |
| `5` | Report whether the deque is full | None |
| `6` | Report whether the deque is empty | None |
| `7` | Display the deque, front to rear | None |
| `8` | Exit | None |

The capacity is fixed at compile time by `#define MAX 5` near the top of the source. To use a different capacity, change that number and recompile.

> [!IMPORTANT]
> When the deque is already full, choices `1` and `2` print the overflow message and return **without prompting for a value** — the same pattern (and the same input-desync risk) as the array-based stack and queue practicals in this repo. See [Known limitations](#known-limitations).

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| Insert (either end) onto a full deque | Reports `Deque Overflow.` and leaves the deque unchanged. |
| Delete (either end) from an empty deque | Reports `Deque Underflow.` |
| Delete the last remaining element, from either end | Resets both `front` and `rear` to `-1`, so the next insert starts fresh at index `0`. |
| Insert past the physical end of the array | Wraps around to index `0` via modulo arithmetic — no overflow is reported unless the deque is actually full. |
| `isFull` / `isEmpty` at any time | Reports the current state without modifying the deque. |
| Choose an integer outside `1`–`8` | Reports an invalid choice and displays the menu again. |

## Example session

Inserting at the rear three times, then at the front once:

```text
Enter your choice: 2
Enter value: 10
10 inserted at rear.

Enter your choice: 2
Enter value: 20
20 inserted at rear.

Enter your choice: 2
Enter value: 30
30 inserted at rear.

Enter your choice: 1
Enter value: 5
5 inserted at front.

Enter your choice: 7
Deque elements (front to rear): 5 10 20 30

Enter your choice: 8
Exiting program.
```

### Filling all five slots and wrapping around

Unlike the plain (non-circular) array queue practical in this repo, this deque can use every slot — `isFull` only reports true once all five are genuinely occupied:

```text
Enter your choice: 1
1 inserted at rear.
...(2, 3, 4, 5 inserted at rear)...

Enter your choice: 5
Deque is FULL.

Enter your choice: 3
1 deleted from front.

Enter your choice: 1
Enter value: 9
9 inserted at front.

Enter your choice: 7
Deque elements (front to rear): 9 2 3 4 5
```

That insertion at the front after the deque was full and one element was removed works by wrapping `front` back around to the slot that `1` used to occupy — no element was shifted, and no capacity was wasted.

## How the operations work

### isEmpty and isFull

```c
int isEmpty() { return front == -1; }
int isFull()  { return (rear + 1) % MAX == front; }
```

Identical in shape to the circular queue practical's checks — and for good reason: a deque is, from the array's point of view, just a circular buffer where both ends happen to be mutable instead of only one.

### Insert at front

```c
if (front == -1) {
    front = rear = 0;
} else {
    front = (front - 1 + MAX) % MAX;
}
q[front] = v;
```

The first element ever inserted (from either end) sets `front = rear = 0`. After that, inserting at the front moves `front` **backward** around the ring. The `+ MAX` before the `%` matters: without it, `front - 1` would go negative when `front == 0`, and C's `%` operator can return a negative result for a negative operand — `+ MAX` guarantees the value being reduced is non-negative first.

### Insert at rear

```c
if (front == -1) {
    front = rear = 0;
} else {
    rear = (rear + 1) % MAX;
}
q[rear] = v;
```

The mirror image of insert-at-front: `rear` moves **forward** around the ring. No `+ MAX` is needed here since `rear + 1` is never negative.

### Delete from front / delete from rear

```c
if (front == rear) {
    front = rear = -1;      // that was the last element
} else {
    front = (front + 1) % MAX;   // (or rear = (rear - 1 + MAX) % MAX; for deleteRear)
}
```

Both deletions check `front == rear` first, since that's the signal "only one element remains" regardless of which end is being read — removing it empties the whole structure, so both indices reset together. Otherwise, the relevant index moves one step closer to the other end.

### Display

```c
int cnt = (rear - front + MAX) % MAX + 1;
for (int i = 0; i < cnt; i++) {
    printf("%d ", q[(front + i) % MAX]);
}
```

Because `front` can sit at a *higher* array index than `rear` after wrapping (as in the diagram at the top of this README), a plain `for (i = front; i <= rear; i++)` loop — which would work for the non-circular array queue practical — isn't enough here. `cnt` first computes how many elements are actually present by measuring the wrapped distance from `front` to `rear`, and the loop then walks exactly that many slots forward from `front`, wrapping with `% MAX` as it goes.

## Complexity

Let `n` be the number of elements currently in the deque and `MAX` the compile-time capacity.

| Operation | Time | Reason |
| --- | :---: | --- |
| Insert at front | `O(1)` | One bounds check, one modulo-wrapped index update, one array write. |
| Insert at rear | `O(1)` | Same as insert at front, mirrored. |
| Delete from front | `O(1)` | One bounds check, one array read, one index update (or reset). |
| Delete from rear | `O(1)` | Same as delete from front, mirrored. |
| isFull | `O(1)` | A single modulo comparison. |
| isEmpty | `O(1)` | A single integer comparison. |
| Display | `O(n)` | Every stored element is visited once. |

Space is `O(MAX)` and fixed at compile time. Unlike the plain (non-circular) array queue practical in this repo, this deque has no false-overflow problem — every one of the `MAX` slots is genuinely reachable, from either end, for the lifetime of the program.

> [!TIP]
> Every operation here is the same complexity as the circular queue practical's equivalent operation — a deque with array-backed circular indexing doesn't cost anything extra over a one-ended circular queue; it simply mirrors the same trick onto both ends at once.

## Code map

| Component | Responsibility |
| --- | --- |
| `MAX` | Compile-time capacity of the deque (currently `5`). |
| `q[MAX]` | The backing array holding deque elements. |
| `front` | Index of the current front element; `-1` when the deque is empty. |
| `rear` | Index of the current rear element; `-1` when the deque is empty. |
| `isEmpty()` | Returns `1` when `front == -1`, otherwise `0`. |
| `isFull()` | Returns `1` when `(rear + 1) % MAX == front`, otherwise `0`. |
| `insertFront()` | Checks `isFull()`, then reads a value and writes it at the new (wrapped) front index. |
| `insertRear()` | Checks `isFull()`, then reads a value and writes it at the new (wrapped) rear index. |
| `deleteFront()` | Checks `isEmpty()`, then reports and removes the front element, resetting both indices if that was the last one. |
| `deleteRear()` | Checks `isEmpty()`, then reports and removes the rear element, resetting both indices if that was the last one. |
| `display()` | Computes the element count from the wrapped `front`–`rear` distance, then prints each slot from `front` forward. |
| `main()` | Runs the menu loop and dispatches choices, handling `isFull`/`isEmpty` reporting inline. |

All implementation code is in [`deque_operations.c`](./deque_operations.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and exercises every menu operation:

```bash
gcc deque_operations.c -std=c11 -Wall -Wextra -Wpedantic -o deque_operations
printf '2\n10\n2\n20\n2\n30\n1\n5\n7\n8\n' | ./deque_operations
```

The final display should print:

```text
Deque elements (front to rear): 5 10 20 30
```

To confirm the deque uses all five slots and wraps correctly, fill it, delete from the front, then insert at the front again:

```bash
printf '2\n1\n2\n2\n2\n3\n2\n4\n2\n5\n3\n1\n9\n7\n8\n' | ./deque_operations
```

This should print:

```text
Deque elements (front to rear): 9 2 3 4 5
```

## Known limitations

This practical keeps input and memory handling deliberately compact:

- **A rejected insertion can desync your input**, the same as the array-based stack and queue practicals: since `insertFront()`/`insertRear()` return before prompting when the deque is full, typing an insert choice followed by a value on a full deque causes that value to be read as the next menu choice.
- Capacity is fixed at compile time by `#define MAX 5`; resizing requires editing the source and recompiling.
- `scanf()` results are unchecked, so text or integers outside the C `int` range are not handled reliably. Entering a non-numeric character will cause the menu loop to spin, since the bad input is never cleared from the buffer.
- Deleted values are not cleared from the array; they remain in memory until overwritten by a later insertion.
- The deque holds `int` only; storing another type requires editing the array declaration and the `scanf()`/`printf()` format specifiers.
- Deque contents exist only for the current process and are not saved.
- The program has no automated tests or build configuration.

## Ideas for extending it

- Check `scanf()`'s return value and drain the input buffer on bad input, fixing both the desync and the infinite-menu-loop issue.
- Prompt for the value before the `isFull()` check (or read and discard it on rejection) so a rejected insertion doesn't leave stray input.
- Make the capacity a runtime choice using a variable-length array or `malloc()`.
- Add a `count` operation reporting the current element count directly, reusing the same formula `display()` already computes.
- Implement the same interface with a doubly linked list (each node already has the `prev`/`next` pointers a deque needs) and compare the trade-offs, as with the stack and queue practicals in this repo.
- Use the deque to implement a sliding-window algorithm (such as the maximum of every window of size `k` in an array) — a classic application that specifically needs insertion/removal at both ends.
- Add unit tests for empty, single-element, exactly-full, and both-direction wraparound cases.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**Both ends open — one ring, no wasted slots.**

</div>