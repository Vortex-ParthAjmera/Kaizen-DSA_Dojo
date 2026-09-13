<div align="center">

# Circular Linked List Operations in C

**An interactive demonstration of insertion, deletion, and traversal in a singly circular linked list.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./circular_linked_list_operations.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This menu-driven program demonstrates the core mechanics of a **circular linked list**. Each dynamically allocated node stores an integer (`d`) and a pointer to the next node (`n`) — but unlike the earlier practicals, no node's `n` ever points to `NULL`. Instead, the final node's `n` points straight back to the head, closing the loop:

```text
      ┌─────────────────────────────┐
      │                             │
      ▼                             │
h ──▶ [10] ──▶ [20] ──▶ [30] ────────┘
```

Because there is no `NULL` to stop at, every traversal in this program has to test against the head pointer (`h`) itself to know when it has gone all the way around — and, as covered below, that same lack of a stopping point changes the time complexity of several operations compared to a straight (non-circular) list.

## What it demonstrates

- Building an initial circular list while preserving input order
- Inserting a node at the beginning, a chosen position, or the end, while keeping the loop closed
- Deleting a node from the beginning, a chosen position, or the end, while keeping the loop closed
- Using a `do…while` traversal (instead of a `while (t != NULL)` loop) so the walk stops on returning to the head rather than running forever
- Validating positions up front with a `listLength()` helper before any pointer is touched
- Allocating nodes with `malloc()` and releasing deleted nodes with `free()`
- Handling empty and single-node lists as special cases

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/04- Circular linked list operations"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `circular_linked_list_operations.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `circular_linked_list_operations.c`.

### 2. Compile

Linux or macOS:

```bash
gcc circular_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o circular_linked_list_operations
```

Windows with GCC:

```powershell
gcc circular_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o circular_linked_list_operations.exe
```

### 3. Run

Linux or macOS:

```bash
./circular_linked_list_operations
```

Windows PowerShell:

```powershell
.\circular_linked_list_operations.exe
```

## How to use it

1. Enter a non-negative initial number of nodes.
2. Enter each starting integer when prompted. The program appends these values in the same order.
3. Choose an operation from the repeating menu:

   | Choice | Operation | Additional input |
   | :---: | --- | --- |
   | `1` | Insert at beginning | Integer value |
   | `2` | Insert at a position | Integer value and position from `1` to `n + 1` |
   | `3` | Insert at end | Integer value |
   | `4` | Delete from beginning | None |
   | `5` | Delete from a position | Position from `1` to `n` |
   | `6` | Delete from end | None |
   | `7` | Display the list | None |
   | `8` | Exit | None |

4. Continue performing operations; every change remains available until the program exits.

Here, `n` is the current number of nodes, computed fresh on every middle insert/delete via `listLength()`. All positions are **1-based**: position `1` is the head, and position `n` is the final existing node. Enter integer values only.

> [!NOTE]
> The menu calls choices `2` and `5` "middle" operations, but they accept any valid position. Insertion at position `1` delegates to beginning insertion, and deletion at position `1` delegates to beginning deletion.

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| Display an empty list | Reports that the list is empty. |
| Delete from an empty list | Reports that the list is empty. |
| Delete the end of a single-node list | Frees the node and resets `h` to `NULL`. |
| Insert into an empty list at the beginning, end, or position `1` | Creates the first (self-pointing) node. |
| Insert or delete at position `0` or negative | Rejected up front as an invalid position. |
| Insert beyond `n + 1` or delete beyond `n` | Rejected as an invalid position. |
| Choose an integer outside `1`–`8` | Reports an invalid choice and displays the menu again. |

## Example session

This abridged session starts with `10 → 20 → 30 → (back to 10)`, exercises all six update operations, and finishes with `10 → 15 → 30 → (back to 10)`.

```text
Enter initial number of nodes: 3
Enter element 1: 10
Enter element 2: 20
Enter element 3: 30

Enter your choice: 7
List elements: 10 20 30

Enter your choice: 1
Enter value to insert: 5
5 inserted at beginning.

Enter your choice: 2
Enter value to insert: 15
Enter position to insert at: 3
15 inserted at position 3.

Enter your choice: 3
Enter value to insert: 40
40 inserted at end.

Enter your choice: 4
5 deleted from beginning.

Enter your choice: 5
Enter position to delete: 3
20 deleted from position 3.

Enter your choice: 6
40 deleted from end.

Enter your choice: 7
List elements: 10 15 30

Enter your choice: 8
Exiting program.
```

## How the operations work

### Insert at the beginning

Because the last node's `n` has to keep pointing at whatever the head becomes, inserting at the front still requires walking the whole loop to find that last node — this is the main way a circular list differs from the earlier practicals, where beginning-insertion was a pure `O(1)` pointer swap:

```c
struct Node *l = h;
while (l->n != h) l = l->n;   // find the last node

nn->n = h;   // new node points at the old head
h = nn;      // head moves to the new node
l->n = h;    // last node now points at the new head
```

An empty list is the one fast path: the new node simply points at itself and becomes `h`.

### Insert at a position

`listLength()` walks the whole ring first to get a bound for validation, then a second, position-bounded loop walks to the node just before the target and splices in:

```c
struct Node *t = h;
for (int i = 1; i < p - 1; i++) {
    t = t->n;
}

nn->n = t->n;
t->n = nn;
```

Because the position was already validated against `listLength()`, this loop doesn't need a `NULL`/head guard the way the earlier practicals' loops did.

### Insert at the end

The program walks until it finds the node whose `n` points back to `h` (the current last node), attaches the new node there, and points the new node's `n` back at `h` to re-close the loop.

### Delete from the beginning

The single-node case is handled directly. Otherwise, exactly like insertion at the beginning, the program must find the last node so its `n` pointer can be redirected to the new head:

```c
struct Node *l = h;
while (l->n != h) l = l->n;   // find the last node

h = h->n;   // head moves forward
l->n = h;   // last node now points at the new head
```

### Delete from a position

After `listLength()` validates the position, the program walks to the node **just before** the target — this list only stores a `next` pointer, so (unlike the doubly linked list practical) the predecessor has to be found by traversal rather than read off a `prev` field:

```c
struct Node *td = t->n;
t->n = td->n;
free(td);
```

### Delete from the end

The program walks until it finds the second-to-last node (`t->n->n == h`), frees the last node, and points `t->n` back at `h`. A single-node list is handled separately.

### Display

Traversal uses a `do…while` loop rather than a `while (t != NULL)` loop, since no node's `n` is ever `NULL` — the walk has to check `t != h` *after* visiting a node, or it would stop immediately without printing anything.

## Complexity

Let `n` be the current number of nodes and `p` be a requested position. The absence of a tail pointer (and the unconditional `listLength()` call on every middle operation) makes this version noticeably more traversal-heavy than the singly and doubly linked list practicals:

| Operation | Best time | Worst time | Reason |
| --- | :---: | :---: | --- |
| Insert at beginning | `O(1)` | `O(n)` | Empty list is immediate; otherwise the last node must be found to redirect its `n` pointer. |
| Insert at position | `O(1)` | `O(n)` | Empty list + position `1` is immediate; any non-empty list pays for `listLength()` regardless of target position. |
| Insert at end | `O(1)` | `O(n)` | Empty list is immediate; otherwise the tail must be found. |
| Delete from beginning | `O(1)` | `O(n)` | Single-node list is immediate; otherwise the last node must be found to redirect its `n` pointer. |
| Delete from position | — | `O(n)` | `listLength()` runs unconditionally on every call to a non-empty list, even to delete the node right after the head. |
| Delete from end | `O(1)` | `O(n)` | Single-node list is immediate; otherwise traversal finds the second-to-last node. |
| Display | `O(n)` | `O(n)` | Every node is visited once. |

Building the initial list is `O(n²)` for the same reason as the earlier practicals: each `insertEndValue()` call walks from `h` to the current last node. Auxiliary space per operation is `O(1)`; the list itself uses `O(n)` dynamically allocated storage.

> [!TIP]
> A tail pointer would make beginning/end insertion and deletion `O(1)` again, and passing the already-known length into `insertMiddle()`/`deleteMiddle()` (instead of recomputing it via `listLength()` on every call) would remove a redundant full traversal from every middle operation.

## Code map

| Component | Responsibility |
| --- | --- |
| `struct Node` | Stores an integer (`d`) and a pointer to the next node (`n`). |
| `h` | Points to the head node, or remains `NULL` when the list is empty. |
| `listLength()` | Walks the ring once to count nodes; used to validate positions before any pointer is changed. |
| `insertBeginningValue()` | Inserts a provided value at position `1`, finding the last node to keep the loop closed. |
| `insertBeginning()` | Reads a value and delegates to `insertBeginningValue()`. |
| `insertEndValue()` | Allocates and appends a provided value, traversing to the current last node. |
| `insertEnd()` | Reads a value and delegates to `insertEndValue()`. |
| `insertMiddle()` | Validates the position against `listLength()`, then splices in a new node. |
| `deleteBeginning()` | Removes and frees the head node, redirecting the last node's `n` pointer. |
| `deleteMiddle()` | Validates the position, then unlinks the target node via its predecessor. |
| `deleteEnd()` | Removes and frees the final node, redirecting its predecessor's `n` pointer. |
| `display()` | Traverses with a `do…while` loop and prints the list in order. |
| `main()` | Builds the initial list and controls the menu loop. |

All implementation code is in [`circular_linked_list_operations.c`](./circular_linked_list_operations.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and exercises every menu operation:

```bash
gcc circular_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o circular_linked_list_operations
printf '3\n10\n20\n30\n7\n1\n5\n2\n15\n3\n3\n40\n4\n5\n3\n6\n7\n8\n' | ./circular_linked_list_operations
```

The final display should print:

```text
List elements: 10 15 30
```

## Known limitations

This practical keeps input and memory management deliberately compact:

- No tail pointer is kept, so beginning-insertion, beginning-deletion, and both end operations all cost a full traversal on anything but the smallest lists — a step down in efficiency from the singly and doubly linked list practicals in this repo.
- `insertMiddle()` and `deleteMiddle()` both call `listLength()` unconditionally, adding a second full traversal even when the target position is right next to the head.
- The initial node count is not bounded or validated; a negative count silently creates an empty list.
- `scanf()` results are unchecked, so text or integers outside the C `int` range are not handled reliably.
- `malloc()` results are unchecked; allocation failure is not handled.
- Nodes still present when choice `8` exits are not explicitly freed.
- List contents exist only for the current process and are not saved.
- The program has no automated tests or build configuration.

> [!NOTE]
> Unlike the doubly linked list practical in this repo, position `0`/negative and out-of-range positions are safely rejected here — `insertMiddle()` and `deleteMiddle()` both check bounds against `listLength()` before touching any pointer, so there's no equivalent crash on bad input.

## Ideas for extending it

- Add a tail pointer so beginning/end insertion and deletion become `O(1)`.
- Pass the already-known length into `insertMiddle()`/`deleteMiddle()` instead of recomputing it with `listLength()` on every call.
- Add a `freeList()` function that breaks the circle and frees every node before exiting.
- Add a "rotate" or "Josephus-style" operation to make use of the list's circularity.
- Add search, update, count, and sort operations.
- Split the data structure and menu into separate source files.
- Add unit tests for empty, single-node, boundary-position, and multi-node cases.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**No head, no tail — just a loop that always finds its way back.**

</div>