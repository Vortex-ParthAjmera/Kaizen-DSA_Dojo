<div align="center">

# Queue Operations using an Array in C

**An interactive demonstration of enqueue, dequeue, peek, and the overflow/underflow guards of a fixed-capacity linear queue.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./queue_array_operations.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This menu-driven program implements a **queue** — a FIFO (first in, first out) structure — on top of a plain fixed-size array. Two indices track the ends: `front` points at the oldest element still waiting, and `rear` points at the most recently added one.

```text
              q[0]  q[1]  q[2]  q[3]  q[4]
            ┌─────┬─────┬─────┬─────┬─────┐
            │  10 │  20 │  30 │  ?  │  ?  │     MAX = 5
            └─────┴─────┴─────┴─────┴─────┘
               ▲                 ▲
             front              rear
```

This is a **linear** queue, not a circular one: `front` only ever moves forward, and once it passes index `0` that slot is gone for the rest of the program's run — nothing ever wraps back around to reuse it. That single design choice is the whole story of this practical's behavior, and it's called out in detail below.

## What it demonstrates

- Representing a queue as an array plus two indices, `front` and `rear`
- Using `-1`/`-1` as the sentinel pair for "empty," distinct from a queue holding a value at index `0`
- Enqueuing at `rear` and dequeuing from `front` in constant time, without shifting elements
- Guarding every enqueue with `isFull()` and every dequeue/peek with `isEmpty()`
- Reporting **overflow** (enqueue onto a full queue) and **underflow** (dequeue from an empty queue)
- Resetting both indices to `-1` when the last element is dequeued, so the queue can start fresh from index `0` again
- **The classic linear-queue limitation**: `isFull()` only checks `rear`, so dequeued space at the front of the array is never reclaimed until the queue empties out completely

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/08- Queue operations using array"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `queue_array_operations.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `queue_array_operations.c`.

### 2. Compile

Linux or macOS:

```bash
gcc queue_array_operations.c -std=c11 -Wall -Wextra -Wpedantic -o queue_array_operations
```

Windows with GCC:

```powershell
gcc queue_array_operations.c -std=c11 -Wall -Wextra -Wpedantic -o queue_array_operations.exe
```

> [!TIP]
> The source compiles cleanly under `-Wall -Wextra -Wpedantic` with no warnings.

### 3. Run

Linux or macOS:

```bash
./queue_array_operations
```

Windows PowerShell:

```powershell
.\queue_array_operations.exe
```

## How to use it

There is **no initial build step** — the program starts with an empty queue and goes straight to the menu.

| Choice | Operation | Additional input |
| :---: | --- | --- |
| `1` | Enqueue a value at the rear | Integer value (only prompted if the queue is not full) |
| `2` | Dequeue the value at the front | None |
| `3` | Peek at the front value | None |
| `4` | Report whether the queue is full | None |
| `5` | Report whether the queue is empty | None |
| `6` | Display the queue, front to rear | None |
| `7` | Exit | None |

The capacity is fixed at compile time by `#define MAX 5` near the top of the source. To use a different capacity, change that number and recompile.

> [!IMPORTANT]
> When the queue is already full, choice `1` prints the overflow message and returns **without prompting for a value**. If you type the value anyway, it will be read as your next menu choice — see [Known limitations](#known-limitations).

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| Enqueue onto a full queue | Reports `Queue Overflow. Cannot enqueue.` and leaves the queue unchanged. |
| Dequeue from an empty queue | Reports `Queue Underflow. Cannot dequeue.` |
| Peek at an empty queue | Reports that the queue is empty and has no front element. |
| Display an empty queue | Reports that the queue is empty. |
| Dequeue the last remaining element | Resets both `front` and `rear` to `-1`, so the next enqueue starts again at index `0`. |
| `isFull` / `isEmpty` at any time | Reports the current state without modifying the queue. |
| Choose an integer outside `1`–`7` | Reports an invalid choice and displays the menu again. |

## Example session

This abridged session enqueues three values, inspects them, dequeues one, and checks state.

```text
Enter your choice: 1
Enter value to enqueue: 10
10 enqueued into queue.

Enter your choice: 1
Enter value to enqueue: 20
20 enqueued into queue.

Enter your choice: 1
Enter value to enqueue: 30
30 enqueued into queue.

Enter your choice: 6
Queue elements (front to rear): 10 20 30

Enter your choice: 3
Front element is 10.

Enter your choice: 5
Queue is NOT empty.

Enter your choice: 2
10 dequeued from queue.

Enter your choice: 6
Queue elements (front to rear): 20 30

Enter your choice: 5
Queue is NOT empty.

Enter your choice: 7
Exiting program.
```

### The false-overflow problem

Fill all five slots, dequeue two, and the queue reports full — even though two slots are sitting empty:

```text
Enter your choice: 1
1 enqueued into queue.
...(2, 3, 4, 5 enqueued)...

Enter your choice: 2
1 dequeued from queue.

Enter your choice: 2
2 dequeued from queue.

Enter your choice: 6
Queue elements (front to rear): 3 4 5

Enter your choice: 1
Queue Overflow. Cannot enqueue.

Enter your choice: 4
Queue is FULL.
```

Only three elements remain (`3 4 5`), occupying indices `2`–`4`. Indices `0` and `1` are free, but `isFull()` only ever checks `rear == MAX - 1` — it has no way to know the front of the array has room, because in a linear queue that space is simply abandoned once `front` moves past it.

## How the operations work

### isEmpty and isFull

```c
int isEmpty() { return (front == -1); }        // sentinel: nothing enqueued yet
int isFull()  { return (rear == MAX - 1); }    // rear has reached the last physical slot
```

`isFull()` is purely about `rear`'s position in the array — it says nothing about how much of the front is actually free. That's the root of the false-overflow behavior above.

### Enqueue

The guard runs **before** the value is read, so a rejected enqueue consumes no input — the same pattern (and the same input-desync risk) as the array-based stack practical:

```c
if (isFull()) {
    printf("Queue Overflow. Cannot enqueue.\n");
    return;
}
// ... read v ...
if (front == -1) {
    front = 0;   // first element in the queue
}
rear++;
q[rear] = v;
```

The `front == -1` check only fires once, on the very first enqueue after the queue was empty — it's what plants `front` at index `0` to begin with.

### Dequeue

The oldest element is read and reported, then `front` moves forward by one — **unless** it was the last element in the queue, in which case both indices reset to `-1` so the next enqueue can start over at index `0`:

```c
printf("%d dequeued from queue.\n", q[front]);

if (front == rear) {
    front = -1;
    rear = -1;
} else {
    front++;
}
```

That reset is the *only* way this queue ever reclaims front-of-array space — it has to become completely empty first.

### Peek

Identical to dequeue's read, minus the index update. The queue is left exactly as it was.

### Display

The loop runs `front` to `rear` inclusive, in the queue's natural order — no reversal, unlike the stack practicals' top-to-bottom display:

```c
for (int i = front; i <= rear; i++) {
    printf("%d ", q[i]);
}
```

## Complexity

Let `n` be the number of elements currently in the queue and `MAX` the compile-time capacity.

| Operation | Time | Reason |
| --- | :---: | --- |
| Enqueue | `O(1)` | One bounds check, one index increment, one array write. |
| Dequeue | `O(1)` | One bounds check, one array read, one index update (or reset). |
| Peek | `O(1)` | One bounds check and one array read. |
| isFull | `O(1)` | A single integer comparison. |
| isEmpty | `O(1)` | A single integer comparison. |
| Display | `O(n)` | Every stored element is visited once. |

Space is `O(MAX)` and fixed at compile time. But the *effective* capacity over a long run of mixed enqueues and dequeues can be far lower than `MAX`, since abandoned slots at the front are never reused until the queue empties completely — a queue that never fully drains can report "full" while holding fewer than `MAX` elements.

> [!TIP]
> A **circular queue** (wrapping both `front` and `rear` back to index `0` with modulo arithmetic) fixes exactly this problem, reclaiming front-of-array space without needing the queue to empty out first — while keeping the same `O(1)` operations and fixed-array storage.

## Code map

| Component | Responsibility |
| --- | --- |
| `MAX` | Compile-time capacity of the queue (currently `5`). |
| `q[MAX]` | The backing array holding queue elements. |
| `front` | Index of the oldest element; `-1` when the queue is empty. |
| `rear` | Index of the newest element; `-1` when the queue is empty. |
| `isEmpty()` | Returns `1` when `front == -1`, otherwise `0`. |
| `isFull()` | Returns `1` when `rear == MAX - 1`, otherwise `0`. |
| `enqueue()` | Checks `isFull()`, then reads a value and stores it at the new rear. |
| `dequeue()` | Checks `isEmpty()`, then reports and removes the front element, resetting both indices if the queue is now empty. |
| `peek()` | Checks `isEmpty()`, then reports the front element without removing it. |
| `display()` | Prints all elements from `front` to `rear`. |
| `main()` | Runs the menu loop and dispatches choices, handling `isFull`/`isEmpty` reporting inline. |

All implementation code is in [`queue_array_operations.c`](./queue_array_operations.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and exercises every menu operation:

```bash
gcc queue_array_operations.c -std=c11 -Wall -Wextra -Wpedantic -o queue_array_operations
printf '1\n10\n1\n20\n1\n30\n6\n3\n5\n2\n6\n5\n7\n' | ./queue_array_operations
```

The final display should print:

```text
Queue elements (front to rear): 20 30
```

To reproduce the false-overflow behavior, fill the queue, dequeue two elements, then try to enqueue again:

```bash
printf '1\n1\n1\n2\n1\n3\n1\n4\n1\n5\n2\n2\n6\n1\n99\n4\n6\n7\n' | ./queue_array_operations
```

This should report `Queue Overflow. Cannot enqueue.` and `Queue is FULL.` even though the display shows only three elements (`3 4 5`) with two slots free.

## Known limitations

This practical keeps input handling and structure deliberately compact, and its central limitation is by design (it's the setup for a circular-queue practical):

- **False overflow.** `isFull()` only checks `rear`, so a queue that has dequeued elements from the front reports full long before its actual contents fill `MAX` slots — freed front-of-array space is only reclaimed once the queue empties out completely.
- **A rejected enqueue can desync your input**, the same as the array-based stack practical: since `enqueue()` returns before prompting when the queue is full, typing the choice `1` followed by a value causes that value to be read as the next menu choice.
- Capacity is fixed at compile time by `#define MAX 5`; resizing requires editing the source and recompiling.
- `scanf()` results are unchecked, so text or integers outside the C `int` range are not handled reliably. Entering a non-numeric character will cause the menu loop to spin, since the bad input is never cleared from the buffer.
- Dequeued values are not cleared from the array; they remain in memory until overwritten (which, per the false-overflow issue above, may never happen for slots before the current `front`).
- The queue holds `int` only; storing another type requires editing the array declaration and the `scanf()`/`printf()` format specifiers.
- Queue contents exist only for the current process and are not saved.
- The program has no automated tests or build configuration.

## Ideas for extending it

- Convert `front` and `rear` to wrap with modulo arithmetic (`(rear + 1) % MAX`), turning this into a circular queue and fixing the false-overflow problem directly.
- Check `scanf()`'s return value and drain the input buffer on bad input, fixing both the desync and the infinite-menu-loop issue.
- Prompt for the value before the `isFull()` check (or read and discard it on rejection) so a rejected enqueue doesn't leave stray input.
- Add a `count` operation reporting `rear - front + 1` elements in use (once the false-overflow issue no longer makes that ambiguous).
- Make the capacity a runtime choice using a variable-length array or `malloc()`.
- Implement the same interface with a linked list and compare the trade-offs, as with the two stack practicals in this repo.
- Apply the queue to a classic problem: level-order tree traversal, task scheduling, or a producer/consumer simulation.
- Add unit tests specifically targeting the false-overflow scenario, so a future circular-queue rewrite can be checked against it.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**First in, first out — as long as the front never wraps back around.**

</div>