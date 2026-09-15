<div align="center">

# Circular Doubly Linked List Operations in C

**An interactive demonstration of insertion, deletion, and traversal in a circular doubly linked list.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./circular_doubly_linked_list_operations.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This menu-driven program combines the previous two practicals: every node has both a `prev` and a `next` pointer, **and** the list loops back on itself instead of ending at `NULL`. The head's `prev` always points at the last node, and the last node's `next` always points back at the head:

```text
        head
         │
         ▼
   ┌──▶ [prev|10|next] ⇄ [prev|20|next] ⇄ [prev|30|next] ──┐
   │                                                        │
   └────────────────────────────────────────────────────────┘
```

That single fact — `head->prev` is always the last node — is what sets this practical apart from the circular *singly* linked list practical. There, finding the last node to keep the ring closed meant walking the whole list. Here, it's one pointer dereference away, so beginning and end operations go back to being `O(1)`.

## What it demonstrates

- Building an initial circular doubly linked list while preserving input order
- Inserting a node at the beginning, a chosen position, or the end, while keeping both the `prev`/`next` links and the loop closed
- Deleting a node from the beginning, a chosen position, or the end, with the same two-way, closed-loop bookkeeping
- Using `head->prev` as a constant-time reference to the last node, instead of traversing to find it
- Using a `do…while` traversal (instead of a `while (t != NULL)` loop) so the walk stops on returning to the head rather than running forever
- Validating positions up front with a `listLength()` helper before any pointer is touched
- Allocating nodes with `malloc()` and releasing deleted nodes with `free()`

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/05- Circular doubly linked list operations"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `circular_doubly_linked_list_operations.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `circular_doubly_linked_list_operations.c`.

### 2. Compile

Linux or macOS:

```bash
gcc circular_doubly_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o circular_doubly_linked_list_operations
```

Windows with GCC:

```powershell
gcc circular_doubly_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o circular_doubly_linked_list_operations.exe
```

### 3. Run

Linux or macOS:

```bash
./circular_doubly_linked_list_operations
```

Windows PowerShell:

```powershell
.\circular_doubly_linked_list_operations.exe
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
| Delete the end of a single-node list | Frees the node and resets `head` to `NULL`. |
| Insert into an empty list at the beginning, end, or position `1` | Creates the first (self-pointing) node. |
| Insert or delete at position `0` or negative | Rejected up front as an invalid position. |
| Insert beyond `n + 1` or delete beyond `n` | Rejected as an invalid position. |
| Choose an integer outside `1`–`8` | Reports an invalid choice and displays the menu again. |

## Example session

This abridged session starts with `10 ⇄ 20 ⇄ 30 ⇄ (back to 10)`, exercises all six update operations, and finishes with `10 ⇄ 15 ⇄ 30 ⇄ (back to 10)`.

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

`head->prev` already *is* the last node, so no traversal is needed to keep the loop closed — this is `O(1)`, unlike the equivalent circular singly linked list operation:

```c
struct Node *last = head->prev;   // O(1) — no traversal

newNode->next = head;
newNode->prev = last;
last->next = newNode;
head->prev = newNode;

head = newNode;
```

### Insert at a position

`listLength()` walks the whole ring once to validate the position, then a second, position-bounded loop walks to the node just before the target and splices in on both sides:

```c
struct Node *temp = head;
for (int i = 1; i < pos - 1; i++) {
    temp = temp->next;
}

newNode->next = temp->next;
newNode->prev = temp;
temp->next->prev = newNode;
temp->next = newNode;
```

### Insert at the end

Same `O(1)` trick as beginning-insertion: `head->prev` is the current last node, so the new node is spliced in right before `head` without any traversal, and `head` itself doesn't move.

### Delete from the beginning

The single-node case is handled directly. Otherwise, `head->prev` again gives constant-time access to the last node, so the whole operation is `O(1)`:

```c
struct Node *last = head->prev;   // O(1) — no traversal

head = head->next;
head->prev = last;
last->next = head;
```

### Delete from a position

After `listLength()` validates the position, the program walks forward to the target node **itself** — since it's doubly linked, no separate predecessor search is needed, and the unlink is a direct four-pointer rewrite:

```c
temp->prev->next = temp->next;
temp->next->prev = temp->prev;
free(temp);
```

### Delete from the end

The same `O(1)` shortcut applies: `head->prev` is the last node, and *its* `prev` is the new last node, so both ends of the list are reachable without a single traversal step:

```c
struct Node *last = head->prev;
struct Node *newLast = last->prev;

newLast->next = head;
head->prev = newLast;
```

### Display

Traversal uses a `do…while` loop rather than a `while (t != NULL)` loop, since no node's `next` is ever `NULL` — the walk has to check `temp != head` *after* visiting a node, or it would stop immediately without printing anything.

## Complexity

Let `n` be the current number of nodes and `p` be a requested position. Because `head->prev` gives constant-time access to the last node, this version recovers the `O(1)` beginning/end operations that the circular *singly* linked list practical lost:

| Operation | Best time | Worst time | Reason |
| --- | :---: | :---: | --- |
| Insert at beginning | `O(1)` | `O(1)` | `head->prev` is already the last node — no traversal needed to keep the loop closed. |
| Insert at position | `O(1)` | `O(n)` | Position `1` is immediate; otherwise `listLength()` plus positional traversal are required. |
| Insert at end | `O(1)` | `O(1)` | Same `head->prev` shortcut as beginning-insertion. |
| Delete from beginning | `O(1)` | `O(1)` | Single-node list is immediate; otherwise `head->prev` again avoids any traversal. |
| Delete from position | — | `O(n)` | `listLength()` runs unconditionally on every call to a non-empty list, even to delete the node right after the head. |
| Delete from end | `O(1)` | `O(1)` | Single-node list is immediate; otherwise both ends are reachable via `prev` pointers alone. |
| Display | `O(n)` | `O(n)` | Every node is visited once. |

Building the initial list is still `O(n)` overall here — unlike the earlier practicals' `O(n²)` construction — because each `insertEndValue()` call is itself `O(1)` thanks to `head->prev`. Auxiliary space per operation is `O(1)`; the list itself uses `O(n)` dynamically allocated storage, with the same larger per-node footprint (two pointers) as the plain doubly linked list practical.

> [!TIP]
> `insertMiddle()` and `deleteMiddle()` still call `listLength()` unconditionally on every invocation. Passing the already-known length in, or caching it, would remove a redundant full traversal from every middle operation — the same opportunity noted in the circular singly linked list practical.

## Code map

| Component | Responsibility |
| --- | --- |
| `struct Node` | Stores an integer plus pointers to the previous and next node. |
| `head` | Points to the head node, or remains `NULL` when the list is empty. `head->prev` always points to the last node. |
| `listLength()` | Walks the ring once to count nodes; used to validate positions before any pointer is changed. |
| `insertBeginningValue()` | Inserts a provided value at position `1` in `O(1)` using `head->prev`. |
| `insertBeginning()` | Reads a value and delegates to `insertBeginningValue()`. |
| `insertEndValue()` | Allocates and appends a provided value in `O(1)` using `head->prev`. |
| `insertEnd()` | Reads a value and delegates to `insertEndValue()`. |
| `insertMiddle()` | Validates the position against `listLength()`, then splices in a new node. |
| `deleteBeginning()` | Removes and frees the head node in `O(1)`, redirecting `head->prev` on the way. |
| `deleteMiddle()` | Validates the position, then unlinks the target node directly via its own `prev`/`next`. |
| `deleteEnd()` | Removes and frees the last node in `O(1)` using `head->prev` and its `prev`. |
| `display()` | Traverses with a `do…while` loop and prints the list in order. |
| `main()` | Builds the initial list and controls the menu loop. |

All implementation code is in [`circular_doubly_linked_list_operations.c`](./circular_doubly_linked_list_operations.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and exercises every menu operation:

```bash
gcc circular_doubly_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o circular_doubly_linked_list_operations
printf '3\n10\n20\n30\n7\n1\n5\n2\n15\n3\n3\n40\n4\n5\n3\n6\n7\n8\n' | ./circular_doubly_linked_list_operations
```

The final display should print:

```text
List elements: 10 15 30
```

## Known limitations

This practical keeps input and memory management deliberately compact:

- `insertMiddle()` and `deleteMiddle()` both call `listLength()` unconditionally, adding a full traversal even when the target position is right next to the head — the beginning/end operations don't pay this cost, but the middle ones still do.
- The initial node count is not bounded or validated; a negative count silently creates an empty list.
- `scanf()` results are unchecked, so text or integers outside the C `int` range are not handled reliably.
- `malloc()` results are unchecked; allocation failure is not handled.
- Nodes still present when choice `8` exits are not explicitly freed, and freeing a circular list requires breaking the loop first or the traversal will never terminate.
- List contents exist only for the current process and are not saved.
- The program has no automated tests or build configuration.

> [!NOTE]
> Position `0`/negative and out-of-range positions are safely rejected here, the same as in the circular singly linked list practical — `insertMiddle()` and `deleteMiddle()` both check bounds against `listLength()` before touching any pointer.

## Ideas for extending it

- Pass the already-known length into `insertMiddle()`/`deleteMiddle()` instead of recomputing it with `listLength()` on every call.
- Add a `freeList()` function that breaks the circle (e.g. by setting the last node's `next` to `NULL` first) and frees every node before exiting.
- Add a reverse-display function that walks backward using `prev`, taking advantage of both the doubly linked and circular structure.
- Add a "rotate" operation to make use of the list's circularity.
- Add search, update, count, and sort operations.
- Split the data structure and menu into separate source files.
- Add unit tests for empty, single-node, boundary-position, and multi-node cases.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**Two links and a closed loop — every end is one pointer away.**

</div>