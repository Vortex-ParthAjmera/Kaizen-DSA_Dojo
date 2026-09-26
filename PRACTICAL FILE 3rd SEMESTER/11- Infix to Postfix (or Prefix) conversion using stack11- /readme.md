<div align="center">

# Queue Operations using a Linked List in C

**An interactive demonstration of enqueue, dequeue, and peek on a queue with no fixed capacity.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./queue_linked_list_operations.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This menu-driven program implements the same **queue** (FIFO — first in, first out) as the two array-based queue practicals in this repo, but backed by dynamically allocated nodes instead of a fixed-size array. Two pointers replace the two indices: `front` is the oldest node, `rear` is the newest one:

```text
front                          rear
  │                              │
  ▼                              ▼
[10] ──▶ [20] ──▶ [30] ──▶ NULL
```

Enqueuing links a new node after `rear` and moves `rear` to it. Dequeuing advances `front` to the next node and frees the old one. Because `rear` is tracked explicitly, both ends of the queue are reachable in constant time — no traversal, no fixed array, and no `isFull()` to write, since the only limit on growth is available memory.

## What it demonstrates

- Representing a queue as a singly linked list with two entry points — `front` for removal, `rear` for insertion
- Enqueuing in constant time by appending directly at `rear`, without walking the list to find the tail
- Dequeuing in constant time by advancing `front` and freeing the old node
- Resetting `rear` to `NULL` when the last node is dequeued, mirroring the array-based queue practical's index reset
- Reporting **underflow** (dequeue from an empty queue) without corrupting anything
- Inspecting the front element without removing it (`peek`)
- Displaying the queue from front to rear by walking `next` pointers
- Contrasting directly with both array-based queue practicals in this repo: same interface, no capacity ceiling, and no false-overflow problem to design around

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/10- Queue operations using linked list"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `queue_linked_list_operations.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `queue_linked_list_operations.c`.

### 2. Compile

Linux or macOS:

```bash
gcc queue_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o queue_linked_list_operations
```

Windows with GCC:

```powershell
gcc queue_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o queue_linked_list_operations.exe
```

> [!TIP]
> The source compiles cleanly under `-Wall -Wextra -Wpedantic` with no warnings.

### 3. Run

Linux or macOS:

```bash
./queue_linked_list_operations
```

Windows PowerShell:

```powershell
.\queue_linked_list_operations.exe
```

## How to use it

As with the array-based queue practicals, there is **no initial build step** — the program starts with an empty queue and goes straight to the menu.

| Choice | Operation | Additional input |
| :---: | --- | --- |
| `1` | Enqueue a value at the rear | Integer value |
| `2` | Dequeue the value at the front | None |
| `3` | Peek at the front value | None |
| `4` | Report whether the queue is empty | None |
| `5` | Display the queue, front to rear | None |
| `6` | Exit | None |

Notice there is no `isFull` choice and, unlike both array-based queue practicals, `enqueue()` **always** prompts for a value — it never rejects an enqueue, so there's no equivalent to their overflow-guard input-desync quirk.

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| Enqueue at any time | Always succeeds and prompts for a value; there is no capacity to exceed. |
| Dequeue from an empty queue | Reports `Queue Underflow. Cannot dequeue.` |
| Peek at an empty queue | Reports that the queue is empty and has no front element. |
| Display an empty queue | Reports that the queue is empty. |
| Dequeue the last remaining node | Resets `front` **and** `rear` to `NULL`, so the next enqueue starts a fresh list. |
| `isEmpty` at any time | Reports the current state without modifying the queue. |
| Choose an integer outside `1`–`6` | Reports an invalid choice and displays the menu again. |

## Example session

This abridged session enqueues three values, inspects them, dequeues one, and checks state.

```text
Enter your choice: 4
Queue is EMPTY.

Enter your choice: 1
Enter value to enqueue: 10
10 enqueued into queue.

Enter your choice: 1
Enter value to enqueue: 20
20 enqueued into queue.

Enter your choice: 1
Enter value to enqueue: 30
30 enqueued into queue.

Enter your choice: 5
Queue elements (front to rear): 10 20 30

Enter your choice: 3
Front element is 10.

Enter your choice: 4
Queue is NOT empty.

Enter your choice: 2
10 dequeued from queue.

Enter your choice: 5
Queue elements (front to rear): 20 30

Enter your choice: 4
Queue is NOT empty.

Enter your choice: 6
Exiting program.
```

### No overflow, even well past the array versions' limit

Both array-based queue practicals cap out at `MAX = 5` elements (and the plain linear one can report full even earlier — see that practical's README). This version keeps accepting enqueues past that point without complaint:

```text
Enter your choice: 5
Queue elements (front to rear): 1 2 3 4 5 6 7 8
```

(Eight elements enqueued, zero rejections.)

### Draining completely and starting over

Enqueue two, dequeue both, then enqueue again — `front` and `rear` both correctly return to `NULL` in between, so the queue starts fresh rather than getting stuck:

```text
Enter your choice: 1
1 enqueued into queue.

Enter your choice: 1
2 enqueued into queue.

Enter your choice: 2
1 dequeued from queue.

Enter your choice: 2
2 dequeued from queue.

Enter your choice: 1
Enter value to enqueue: 99
99 enqueued into queue.

Enter your choice: 5
Queue elements (front to rear): 99
```

## How the operations work

### isEmpty

A single pointer comparison, replacing the array versions' index check:

```c
int isEmpty() { return (front == NULL); }
```

### Enqueue

A new node is allocated and linked in after the current `rear` — or, if the queue was empty, it becomes both `front` and `rear` at once:

```c
struct Node *nn = (struct Node *)malloc(sizeof(struct Node));
nn->d = v;
nn->n = NULL;

if (front == NULL) {
    front = nn;
    rear = nn;
} else {
    rear->n = nn;
    rear = nn;
}
```

Keeping `rear` as an explicit pointer is what makes this `O(1)`. Compare this to the plain singly linked list practical earlier in this repo, where appending at the end cost a full traversal because no tail pointer was kept — this queue avoids that exact pitfall by design.

### Dequeue

The front node is read and reported, `front` advances to the next node, and the old node is freed. If that was the last node, `rear` is reset too, so it doesn't dangle on a freed node:

```c
struct Node *t = front;
printf("%d dequeued from queue.\n", t->d);

front = front->n;
if (front == NULL) {
    rear = NULL;   // queue is now empty
}

free(t);
```

### Peek

Identical to the read half of `dequeue()`, without advancing `front` or freeing anything. The queue is left exactly as it was.

### Display

Walks forward from `front` until `NULL`, printing each node in queue order — the same front-to-rear order the array-based versions produce, just reached by pointer-chasing instead of index arithmetic:

```c
struct Node *t = front;
while (t != NULL) {
    printf("%d ", t->d);
    t = t->n;
}
```

## Complexity

Let `n` be the number of elements currently in the queue.

| Operation | Time | Reason |
| --- | :---: | --- |
| Enqueue | `O(1)` | One allocation, one pointer write at `rear`, one `rear` reassignment — no traversal, thanks to the explicit `rear` pointer. |
| Dequeue | `O(1)` | One pointer read, one `front` reassignment, one `free()`. |
| Peek | `O(1)` | One pointer read. |
| isEmpty | `O(1)` | A single pointer comparison. |
| Display | `O(n)` | Every stored element is visited once. |

Space is `O(n)` and grows or shrinks with actual use, the same trade-off as the linked-list stack practical: no fixed ceiling, but each node carries pointer overhead and every enqueue/dequeue pays for a `malloc()`/`free()` call. Compared to the two array-based queue practicals, this version trades their fixed `O(MAX)` array (and, for the plain linear one, its false-overflow problem) for unlimited growth at the cost of per-node allocation.

> [!TIP]
> This queue's `O(1)` enqueue is not automatic for linked lists — it only holds because `rear` is tracked explicitly. The takeaway pairs directly with the circular queue practical in this repo: two very different fixes (an explicit tail pointer here, modulo-wrapped indices there) solve two different flavors of the same "don't pay for a full traversal on every insert" problem.

## Code map

| Component | Responsibility |
| --- | --- |
| `struct Node` | Stores an integer (`d`) and a pointer to the next node (`n`). |
| `front` | Pointer to the oldest node, or `NULL` when the queue is empty. |
| `rear` | Pointer to the newest node, or `NULL` when the queue is empty. |
| `isEmpty()` | Returns `1` when `front == NULL`, otherwise `0`. |
| `enqueue()` | Reads a value, allocates a node, and links it in after `rear`. |
| `dequeue()` | Checks `isEmpty()`, then reports, unlinks, and frees the front node, resetting `rear` if the queue is now empty. |
| `peek()` | Checks `isEmpty()`, then reports the front element without removing it. |
| `display()` | Walks from `front` to `NULL`, printing each node's data. |
| `main()` | Runs the menu loop and dispatches choices, handling `isEmpty` reporting inline. |

All implementation code is in [`queue_linked_list_operations.c`](./queue_linked_list_operations.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and exercises every menu operation:

```bash
gcc queue_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o queue_linked_list_operations
printf '1\n10\n1\n20\n1\n30\n5\n3\n4\n2\n5\n4\n6\n' | ./queue_linked_list_operations
```

The final display should print:

```text
Queue elements (front to rear): 20 30
```

To confirm there's no capacity ceiling, enqueue eight values and display:

```bash
printf '1\n1\n1\n2\n1\n3\n1\n4\n1\n5\n1\n6\n1\n7\n1\n8\n5\n6\n' | ./queue_linked_list_operations
```

This should print all eight values with no overflow message at any point:

```text
Queue elements (front to rear): 1 2 3 4 5 6 7 8
```

## Known limitations

This practical keeps input handling and structure deliberately compact:

- `scanf()` results are unchecked, so text or integers outside the C `int` range are not handled reliably. Entering a non-numeric character will cause the menu loop to spin, since the bad input is never cleared from the buffer.
- Nodes still in the queue when choice `6` exits are not explicitly freed — the process reclaiming its memory on exit is doing the cleanup, not the program.
- There is genuinely no upper bound on growth; a runaway enqueue loop will keep allocating until `malloc()` fails, which this program does not check for or handle.
- `malloc()` results are unchecked; allocation failure is not handled, so a failed enqueue would dereference a `NULL` node pointer.
- The queue holds `int` only; storing another type requires editing the struct and the `scanf()`/`printf()` format specifiers.
- Queue contents exist only for the current process and are not saved.
- The program has no automated tests or build configuration.

## Ideas for extending it

- Check `malloc()`'s return value in `enqueue()` and report allocation failure instead of dereferencing a `NULL` node.
- Check `scanf()`'s return value and drain the input buffer on bad input, fixing the infinite-menu-loop issue.
- Add a `freeQueue()` function that dequeues everything (or walks and frees directly) before exiting.
- Add a `count` operation that reports the number of nodes without dequeuing any of them.
- Add an optional soft capacity check (comparing a running count against a configurable limit) to compare against the array-based practicals' hard limit without giving up dynamic growth.
- Apply the queue to a classic problem: level-order tree traversal, task scheduling, or a producer/consumer simulation — and compare running the same problem against both array-based queue practicals.
- Generalise the element type with a `typedef`, so the queue can hold something other than `int`.
- Add unit tests for empty, single-element, and many-element cases.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**First in, first out — no ceiling, just nodes handed off from front to rear.**

</div>