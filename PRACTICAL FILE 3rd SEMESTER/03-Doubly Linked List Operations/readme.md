<div align="center">

# Doubly Linked List Operations in C

**An interactive, pointer-focused demonstration of insertion, deletion, and traversal in a doubly linked list.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./doubly_linked_list_operations.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This menu-driven program demonstrates the core mechanics of a **doubly linked list**. Each dynamically allocated node stores an integer along with pointers to both the previous and the next node:

```text
        head
         │
         ▼
NULL ⇄ [prev|10|next] ⇄ [prev|20|next] ⇄ [prev|30|next] ⇄ NULL
```

Because every node keeps a `prev` pointer as well as a `next` pointer, the list can be walked in either direction, and a node can be deleted or relinked using only a reference to itself — no separate search for its predecessor is required, unlike in a singly linked list.

## What it demonstrates

- Building an initial list while preserving input order
- Inserting a node at the beginning, a chosen position, or the end
- Deleting a node from the beginning, a chosen position, or the end
- Keeping `prev` and `next` pointers consistent on every insert and delete
- Traversing and displaying every node
- Allocating nodes with `malloc()` and releasing deleted nodes with `free()`
- Handling empty and single-node lists during deletion

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/03- Doubly linked list operations"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `doubly_linked_list_operations.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `doubly_linked_list_operations.c`.

### 2. Compile

Linux or macOS:

```bash
gcc doubly_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o doubly_linked_list_operations
```

Windows with GCC:

```powershell
gcc doubly_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o doubly_linked_list_operations.exe
```

### 3. Run

Linux or macOS:

```bash
./doubly_linked_list_operations
```

Windows PowerShell:

```powershell
.\doubly_linked_list_operations.exe
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

Here, `n` is the current number of nodes. All positions are **1-based**: position `1` is the head, and position `n` is the final existing node. Enter integer values only.

> [!NOTE]
> The menu calls choices `2` and `5` "middle" operations, but they accept any valid position. Insertion at position `1` delegates to beginning insertion, and deletion at position `1` delegates to beginning deletion.

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| Display an empty list | Reports that the list is empty. |
| Delete from an empty list | Reports that the list is empty. |
| Delete the end of a single-node list | Frees the node and resets `head` to `NULL`. |
| Insert into an empty list at the beginning, end, or position `1` | Creates the first node. |
| Enter a position beyond the valid upper bound | Reports an invalid position and leaves the list unchanged. |
| Choose an integer outside `1`–`8` | Reports an invalid choice and displays the menu again. |

## Example session

This abridged session starts with `10 → 20 → 30`, exercises all six update operations, and finishes with `10 → 15 → 30`.

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

A new node points forward to the current head, the current head's `prev` is redirected back to the new node, and `head` is updated. No traversal is required.

```text
Before:  head ──▶ [10] ⇄ [20] ⇄ NULL

1. new ⇄ old head
2. head = new

After:   head ──▶ [5] ⇄ [10] ⇄ [20] ⇄ NULL
```

### Insert at a position

The program follows `next` pointers to the node immediately before the requested position, then splices the new node in on both sides:

```c
newNode->next = temp->next;
newNode->prev = temp;
if (temp->next != NULL) {
    temp->next->prev = newNode;
}
temp->next = newNode;
```

Updating four pointers (instead of two, as in a singly linked list) keeps both directions of traversal intact.

### Insert at the end

The program traverses until it finds the node whose `next` pointer is `NULL`, then attaches the new node and links it backward with `prev`. If the list is empty, the new node becomes `head`.

### Delete from the beginning

The second node becomes the new head, its `prev` is cleared, and the former head is released:

```c
struct Node *temp = head;
head = head->next;
if (head != NULL) head->prev = NULL;
free(temp);
```

### Delete from a position

Because every node already knows its own predecessor, the program traverses directly to the **target node itself** (not to a predecessor, as a singly linked list would require) and rewires the neighbors on both sides before freeing it:

```c
temp->prev->next = temp->next;
if (temp->next != NULL) {
    temp->next->prev = temp->prev;
}
free(temp);
```

### Delete from the end

The program finds the last node using `next` pointers, releases it, and sets its `prev` node's `next` pointer to `NULL`. A single-node list is handled separately.

## Complexity

Let `n` be the current number of nodes and `p` be a requested position.

| Operation | Best time | Worst time | Reason |
| --- | :---: | :---: | --- |
| Insert at beginning | `O(1)` | `O(1)` | Only `head` and two links change. |
| Insert at position | `O(1)` | `O(n)` | Position `1` is immediate; later positions require traversal to the predecessor. |
| Insert at end | `O(1)` | `O(n)` | An empty list is immediate; otherwise the tail must be found. |
| Delete from beginning | `O(1)` | `O(1)` | The head node is directly accessible. |
| Delete from position | `O(1)` | `O(n)` | Position `1` is immediate; otherwise traversal reaches the node itself, which then unlinks in `O(1)` using its own `prev`/`next`. |
| Delete from end | `O(1)` | `O(n)` | Empty and single-node lists are immediate; longer lists require traversal. |
| Display | `O(n)` | `O(n)` | Every node is visited once. |

Building the initial list is `O(n²)` because every value is appended by traversing from `head` to the current final node. Each individual update uses `O(1)` auxiliary space; the list itself uses `O(n)` dynamically allocated storage, with a slightly larger per-node footprint than a singly linked list due to the extra `prev` pointer.

> [!TIP]
> Keeping a separate tail pointer would make insertion at the end `O(1)` and reduce initial construction to `O(n)`.

## Code map

| Component | Responsibility |
| --- | --- |
| `struct Node` | Stores an integer plus pointers to the previous and next node. |
| `head` | Points to the first node or remains `NULL` when the list is empty. |
| `insertBeginningValue()` | Inserts a provided value at position `1`, relinking the old head's `prev`. |
| `insertBeginning()` | Reads a value and delegates to `insertBeginningValue()`. |
| `insertEndValue()` | Allocates and appends a provided value, traversing to the tail. |
| `insertEnd()` | Reads a value and delegates to `insertEndValue()`. |
| `insertMiddle()` | Inserts at a user-provided 1-based position, updating both neighbors. |
| `deleteBeginning()` | Removes and frees the head node, clearing the new head's `prev`. |
| `deleteMiddle()` | Traverses to the target node itself and unlinks it via `prev`/`next`. |
| `deleteEnd()` | Removes and frees the final node using its `prev` link. |
| `display()` | Traverses forward and prints the list in order. |
| `main()` | Builds the initial list and controls the menu loop. |

All implementation code is in [`doubly_linked_list_operations.c`](./doubly_linked_list_operations.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and exercises every menu operation:

```bash
gcc doubly_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o doubly_linked_list_operations
printf '3\n10\n20\n30\n7\n1\n5\n2\n15\n3\n3\n40\n4\n5\n3\n6\n7\n8\n' | ./doubly_linked_list_operations
```

The final display should print:

```text
List elements: 10 15 30
```

## Known limitations

This practical keeps input and memory management deliberately compact:

- **Position `0` or negative for Delete at Middle crashes the program.** Because `pos == 1` is the only value that short-circuits to `deleteBeginning()`, a value of `0` (or lower) falls through the traversal loop without ever running it, leaving `temp` pointing at `head`. The code then dereferences `temp->prev->next`, and since the head's `prev` is `NULL`, this segfaults.
- Position `0` or negative for Insert at Middle does not crash, but it is not rejected either — it silently inserts immediately after the head instead of reporting an error.
- The initial node count is not bounded or validated; a negative count silently creates an empty list.
- `scanf()` results are unchecked, so text or integers outside the C `int` range are not handled reliably.
- `malloc()` results are unchecked; allocation failure is not handled.
- Nodes still present when choice `8` exits are not explicitly freed.
- List contents exist only for the current process and are not saved.
- The program has no automated tests or build configuration.

## Ideas for extending it

- Validate that positions are `>= 1` before entering any traversal loop, closing the position-`0` crash.
- Add a `freeList()` function and call it before exiting.
- Track a tail pointer for constant-time end insertion.
- Add a reverse-display function that walks backward using `prev`, showcasing what a doubly linked list enables over a singly linked one.
- Add search, update, count, and sort operations.
- Split the data structure and menu into separate source files.
- Add unit tests for empty, single-node, boundary-position, and multi-node cases.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**Two links per node, one list that reads both ways.**

</div>