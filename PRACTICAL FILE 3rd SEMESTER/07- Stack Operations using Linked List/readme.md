<div align="center">

# Stack Operations using a Linked List in C

**An interactive demonstration of push, pop, and peek on a stack with no fixed capacity.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./stack_linked_list_operations.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This menu-driven program implements the same **stack** (LIFO — last in, first out) as the array-based practical in this repo, but backed by dynamically allocated nodes instead of a fixed-size array. `top` is no longer an index into an array; it's a pointer straight at the most recently pushed node:

```text
top
 │
 ▼
[30] ──▶ [20] ──▶ [10] ──▶ NULL
```

Pushing prepends a node at `top`; popping removes it. There is no `#define MAX` and no `isFull()` here — the stack can grow for as long as `malloc()` keeps succeeding, so the only failure mode is running out of memory, not running out of "slots."

## What it demonstrates

- Representing a stack as a singly linked list where **the head is the top**
- Pushing in constant time by inserting a new node in front of `top`
- Popping in constant time by advancing `top` to the next node and freeing the old one
- Using `top == NULL` as the sole emptiness check — there is no overflow check to write, since the structure has no fixed capacity
- Reporting **underflow** (pop from an empty stack) without corrupting anything
- Inspecting the top element without removing it (`peek`)
- Displaying the stack from top to bottom by walking `next` pointers
- Contrasting directly with the array-based stack practical in this repo: same interface, different capacity story

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/07- Stack operations using linked list"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `stack_linked_list_operations.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `stack_linked_list_operations.c`.

### 2. Compile

Linux or macOS:

```bash
gcc stack_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o stack_linked_list_operations
```

Windows with GCC:

```powershell
gcc stack_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o stack_linked_list_operations.exe
```

> [!TIP]
> The source compiles cleanly under `-Wall -Wextra -Wpedantic` with no warnings.

### 3. Run

Linux or macOS:

```bash
./stack_linked_list_operations
```

Windows PowerShell:

```powershell
.\stack_linked_list_operations.exe
```

## How to use it

As with the array-based version, there is **no initial build step** — the program starts with an empty stack and goes straight to the menu.

| Choice | Operation | Additional input |
| :---: | --- | --- |
| `1` | Push a value onto the top | Integer value |
| `2` | Pop the top value | None |
| `3` | Peek at the top value | None |
| `4` | Report whether the stack is empty | None |
| `5` | Display the stack, top to bottom | None |
| `6` | Exit | None |

Notice there is no `isFull` choice and, unlike the array version, `push()` **always** prompts for a value — it never rejects a push, so there's no equivalent to the array practical's overflow-guard input-desync quirk.

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| Push at any time | Always succeeds and prompts for a value; there is no capacity to exceed. |
| Pop from an empty stack | Reports `Stack Underflow. Cannot pop.` |
| Peek at an empty stack | Reports that the stack is empty and has no top element. |
| Display an empty stack | Reports that the stack is empty. |
| `isEmpty` at any time | Reports the current state without modifying the stack. |
| Choose an integer outside `1`–`6` | Reports an invalid choice and displays the menu again. |

## Example session

This abridged session pushes three values, inspects them, pops one, and checks state.

```text
Enter your choice: 4
Stack is EMPTY.

Enter your choice: 1
Enter value to push: 10
10 pushed onto stack.

Enter your choice: 1
Enter value to push: 20
20 pushed onto stack.

Enter your choice: 1
Enter value to push: 30
30 pushed onto stack.

Enter your choice: 5
Stack elements (top to bottom): 30 20 10

Enter your choice: 3
Top element is 30.

Enter your choice: 4
Stack is NOT empty.

Enter your choice: 2
30 popped from stack.

Enter your choice: 5
Stack elements (top to bottom): 20 10

Enter your choice: 4
Stack is NOT empty.

Enter your choice: 6
Exiting program.
```

### No overflow, even well past the array version's limit

The array-based practical caps out at `MAX = 5` elements. This version keeps accepting pushes past that point without complaint:

```text
Enter your choice: 5
Stack elements (top to bottom): 8 7 6 5 4 3 2 1
```

(Eight elements pushed, zero rejections — there is no ceiling to hit short of available memory.)

## How the operations work

### isEmpty

A single pointer comparison, replacing the array version's index check:

```c
int isEmpty() { return (top == NULL); }
```

### Push

A new node is allocated, its `n` is pointed at the current top, and `top` moves to the new node — no bounds check needed, because there is no bound:

```c
struct Node *nn = (struct Node *)malloc(sizeof(struct Node));
nn->d = v;
nn->n = top;
top = nn;
```

This is the mirror image of insert-at-beginning in the singly linked list practical in this repo, just under a stack's naming and interface.

### Pop

The current top node is read, `top` advances to the next node, and the old node is freed — the linked-list equivalent of the array version's "move `top` down," except memory is actually reclaimed here rather than just left in place:

```c
struct Node *t = top;
printf("%d popped from stack.\n", t->d);
top = top->n;
free(t);
```

### Peek

Identical to the read half of `pop()`, without advancing `top` or freeing anything. The stack is left exactly as it was.

### Display

Walks forward from `top` until `NULL`, printing each node — top-first, the same order the array version's downward loop produced:

```c
struct Node *t = top;
while (t != NULL) {
    printf("%d ", t->d);
    t = t->n;
}
```

## Complexity

Let `n` be the number of elements currently on the stack.

| Operation | Time | Reason |
| --- | :---: | --- |
| Push | `O(1)` | One allocation, one pointer write, one `top` reassignment. |
| Pop | `O(1)` | One pointer read, one `top` reassignment, one `free()`. |
| Peek | `O(1)` | One pointer read. |
| isEmpty | `O(1)` | A single pointer comparison. |
| Display | `O(n)` | Every stored element is visited once. |

Space is `O(n)` and grows or shrinks with actual use — the opposite trade-off from the array version's fixed `O(MAX)`. Each node also carries the overhead of a `next` pointer alongside its data, and every push/pop pays for a `malloc()`/`free()` call, whereas the array version's push/pop are pure index arithmetic with no allocator involved.

> [!TIP]
> This is the same push/pop/peek/isEmpty complexity as the array-based stack — the difference isn't asymptotic, it's what each `O(1)` operation is actually doing underneath (allocator calls and pointer writes here, versus index arithmetic and direct array writes there), and where the capacity ceiling lives (compile time here vs. none at all).

## Code map

| Component | Responsibility |
| --- | --- |
| `struct Node` | Stores an integer (`d`) and a pointer to the next node (`n`). |
| `top` | Pointer to the top node, or `NULL` when the stack is empty. |
| `isEmpty()` | Returns `1` when `top == NULL`, otherwise `0`. |
| `push()` | Reads a value, allocates a node, and makes it the new top. |
| `pop()` | Checks `isEmpty()`, then reports, unlinks, and frees the top node. |
| `peek()` | Checks `isEmpty()`, then reports the top element without removing it. |
| `display()` | Walks from `top` to `NULL`, printing each node's data. |
| `main()` | Runs the menu loop and dispatches choices, handling `isEmpty` reporting inline. |

All implementation code is in [`stack_linked_list_operations.c`](./stack_linked_list_operations.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and exercises every menu operation:

```bash
gcc stack_linked_list_operations.c -std=c11 -Wall -Wextra -Wpedantic -o stack_linked_list_operations
printf '4\n1\n10\n1\n20\n1\n30\n5\n3\n4\n2\n5\n4\n6\n' | ./stack_linked_list_operations
```

The final display should print:

```text
Stack elements (top to bottom): 20 10
```

To confirm there's no capacity ceiling, push eight values and display:

```bash
printf '1\n1\n1\n2\n1\n3\n1\n4\n1\n5\n1\n6\n1\n7\n1\n8\n5\n6\n' | ./stack_linked_list_operations
```

This should print all eight values with no overflow message at any point:

```text
Stack elements (top to bottom): 8 7 6 5 4 3 2 1
```

## Known limitations

This practical keeps input handling and structure deliberately compact:

- `scanf()` results are unchecked, so text or integers outside the C `int` range are not handled reliably. Entering a non-numeric character will cause the menu loop to spin, since the bad input is never cleared from the buffer.
- Nodes still on the stack when choice `6` exits are not explicitly freed — the process reclaiming its memory on exit is doing the cleanup, not the program.
- There is genuinely no upper bound on growth; a runaway push loop will keep allocating until `malloc()` fails, which this program does not check for or handle.
- `malloc()` results are unchecked; allocation failure is not handled, so a failed push would dereference a `NULL` node pointer.
- The stack holds `int` only; storing another type requires editing the struct and the `scanf()`/`printf()` format specifiers.
- Stack contents exist only for the current process and are not saved.
- The program has no automated tests or build configuration.

## Ideas for extending it

- Check `malloc()`'s return value in `push()` and report allocation failure instead of dereferencing a `NULL` node.
- Check `scanf()`'s return value and drain the input buffer on bad input, fixing the infinite-menu-loop issue.
- Add a `freeStack()` function that pops everything (or walks and frees directly) before exiting.
- Add a `count` operation that reports the number of nodes without popping any of them.
- Add an optional soft capacity check (comparing a running count against a configurable limit) to compare against the array version's hard limit without giving up dynamic growth.
- Apply the stack to a classic problem: balanced-bracket checking, infix-to-postfix conversion, or postfix evaluation — and compare running the same problem against the array-based stack practical.
- Generalise the element type with a `typedef`, so the stack can hold something other than `int`.
- Add unit tests for empty, single-element, and many-element cases.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**No ceiling, no slots — just nodes stacking on top of each other.**

</div>