<div align="center">

# Singly Linked List Operations in C

**An interactive, pointer-focused demonstration of insertion, deletion, and traversal in a singly linked list.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./Linked%20list%20operations.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This menu-driven program demonstrates the core mechanics of a **singly linked list**. Each dynamically allocated node stores an integer and a pointer to the next node:

```text
 head
  │
  ▼
[10 | next] ──▶ [20 | next] ──▶ [30 | NULL]
```

Unlike an array, the nodes do not need to occupy adjacent memory locations. The `head` pointer identifies the first node, and each `next` pointer forms the path to the rest of the list.

## What it demonstrates

- Building an initial list while preserving input order
- Inserting a node at the beginning, a chosen position, or the end
- Deleting a node from the beginning, a chosen position, or the end
- Traversing and displaying every node
- Allocating nodes with `malloc()` and releasing deleted nodes with `free()`
- Updating links without shifting stored values
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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/02- Linked list operations"
```

If you already have the repository, open a terminal directly in the `02- Linked list operations` folder.

### 2. Compile

Linux or macOS:

```bash
gcc "Linked list operations.c" -std=c11 -Wall -Wextra -Wpedantic -o linked_list_operations
```

Windows with GCC:

```powershell
gcc "Linked list operations.c" -std=c11 -Wall -Wextra -Wpedantic -o linked_list_operations.exe
```

> [!IMPORTANT]
> The source filename contains spaces, so keep `"Linked list operations.c"` inside quotes.

### 3. Run

Linux or macOS:

```bash
./linked_list_operations
```

Windows PowerShell:

```powershell
.\linked_list_operations.exe
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
> The menu calls choices `2` and `5` “middle” operations, but they accept any valid position. Insertion at position `1` delegates to beginning insertion, and insertion at `n + 1` appends a node.

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

A new node points to the current head, then `head` is updated to the new node. No traversal is required.

```text
Before:  head ──▶ [10] ──▶ [20] ──▶ NULL

1. new ─────────▶ [ 5] ──▶ old head
2. head = new

After:   head ──▶ [ 5] ──▶ [10] ──▶ [20] ──▶ NULL
```

### Insert at a position

The program follows `next` pointers to the node immediately before the requested position. It links the new node to the successor first, then links the predecessor to the new node:

```c
newNode->next = temp->next;
temp->next = newNode;
```

This order preserves the remainder of the list.

### Insert at the end

The program traverses until it finds the node whose `next` pointer is `NULL`, then attaches the new node. If the list is empty, the new node becomes `head`.

### Delete from the beginning

The second node becomes the new head, and the former head is released:

```c
struct Node *temp = head;
head = head->next;
free(temp);
```

### Delete from a position

The program finds the preceding node, bypasses the target by updating one link, and releases the removed node with `free()`.

### Delete from the end

The program finds the second-to-last node, releases the final node, and changes the second-to-last node's `next` pointer to `NULL`. A single-node list is handled separately.

## Complexity

Let `n` be the current number of nodes and `p` be a requested position.

| Operation | Best time | Worst time | Reason |
| --- | :---: | :---: | --- |
| Insert at beginning | `O(1)` | `O(1)` | Only `head` and one new link change. |
| Insert at position | `O(1)` | `O(n)` | Position `1` is immediate; later positions require traversal. |
| Insert at end | `O(1)` | `O(n)` | An empty list is immediate; otherwise the tail must be found. |
| Delete from beginning | `O(1)` | `O(1)` | The head node is directly accessible. |
| Delete from position | `O(1)` | `O(n)` | Position `1` is immediate; later positions require traversal. |
| Delete from end | `O(1)` | `O(n)` | Empty and single-node lists are immediate; longer lists require traversal. |
| Display | `O(n)` | `O(n)` | Every node is visited once. |

Building the initial list is `O(n²)` because every value is appended by traversing from `head` to the current final node. Each individual update uses `O(1)` auxiliary space, while the list itself uses `O(n)` dynamically allocated storage.

> [!TIP]
> Keeping a separate tail pointer would make insertion at the end `O(1)` and reduce initial construction to `O(n)`.

## Code map

| Component | Responsibility |
| --- | --- |
| `struct Node` | Stores an integer and a pointer to the next node. |
| `head` | Points to the first node or remains `NULL` when the list is empty. |
| `insertBeginning()` | Reads and inserts a value at the head. |
| `insertBeginningHelper()` | Inserts a provided value at position `1`. |
| `insertEnd()` | Reads a value and reports an end insertion. |
| `insertEndValue()` | Allocates and appends a provided value. |
| `insertMiddle()` | Inserts at a user-provided 1-based position. |
| `deleteBeginning()` | Removes and frees the head node. |
| `deleteMiddle()` | Removes and frees a node at a position. |
| `deleteEnd()` | Removes and frees the final node. |
| `display()` | Traverses and prints the list in order. |
| `main()` | Builds the initial list and controls the menu loop. |

All implementation code is in [`Linked list operations.c`](./Linked%20list%20operations.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and exercises every menu operation:

```bash
gcc "Linked list operations.c" -std=c11 -Wall -Wextra -Wpedantic -o linked_list_operations
printf '3\n10\n20\n30\n7\n1\n5\n2\n15\n3\n3\n40\n4\n5\n3\n6\n7\n8\n' | ./linked_list_operations
```

The final display should print:

```text
List elements: 10 15 30
```

## Known limitations

This practical keeps input and memory management deliberately compact:

- Positions `0` and below are not safely rejected; use only the documented positive ranges.
- The initial node count is not bounded or validated; a negative count silently creates an empty list.
- `scanf()` results are unchecked, so text or integers outside the C `int` range are not handled reliably.
- `malloc()` results are unchecked; allocation failure is not handled.
- Nodes still present when choice `8` exits are not explicitly freed.
- List contents exist only for the current process and are not saved.
- The program has no automated tests or build configuration.

## Ideas for extending it

- Validate every input and reprompt after invalid entries.
- Add a `freeList()` function and call it before exiting.
- Track a tail pointer for constant-time end insertion.
- Add search, update, count, reverse, and sort operations.
- Split the data structure and menu into separate source files.
- Add unit tests for empty, single-node, boundary-position, and multi-node cases.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**Follow the pointer, preserve the chain.**

</div>
