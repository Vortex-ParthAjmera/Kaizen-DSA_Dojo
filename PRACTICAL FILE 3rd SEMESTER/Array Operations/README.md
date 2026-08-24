<div align="center">

# Array Operations in C

**A compact, interactive demonstration of traversal, insertion, and deletion in a fixed-size array.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./Array%20operations.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This program is a menu-driven introduction to three fundamental operations on a one-dimensional array of integers:

| Operation | What it does |
| --- | --- |
| **Traverse** | Visits every stored element and prints it in order. |
| **Insert** | Adds a value at a chosen position and shifts later elements one place to the right. |
| **Delete** | Removes the value at a chosen position and shifts later elements one place to the left. |

The array has a fixed capacity of **100 integers**. Positions entered in the terminal are **1-based**, so position `1` refers to the first element.

## Highlights

- Interactive terminal menu that repeats until you choose **Exit**
- User-defined starting array containing from `0` to `100` integers
- Insertion at the beginning, middle, or end of the current array
- Deletion from any occupied position
- Clear handling for empty arrays, full arrays, and invalid positions
- Standard C implementation with no third-party dependencies

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/Array Operations"
```

If you already have the repository, open a terminal directly in the `Array Operations` folder.

### 2. Compile

On Linux or macOS:

```bash
gcc "Array operations.c" -std=c11 -Wall -Wextra -Wpedantic -o array_operations
```

On Windows with GCC:

```powershell
gcc "Array operations.c" -std=c11 -Wall -Wextra -Wpedantic -o array_operations.exe
```

> [!IMPORTANT]
> The source filename contains a space, so keep `"Array operations.c"` inside quotes.

### 3. Run

Linux or macOS:

```bash
./array_operations
```

Windows PowerShell:

```powershell
.\array_operations.exe
```

## How to use it

1. Enter the initial number of elements, from `0` through `100`.
2. Enter each starting integer when prompted.
3. Choose an operation from the menu:

   | Choice | Action | Required input |
   | :---: | --- | --- |
   | `1` | Traverse | None |
   | `2` | Insert | An integer value and a position from `1` to `n + 1` |
   | `3` | Delete | A position from `1` to `n` |
   | `4` | Exit | None |

4. Continue performing operations; every change remains available until the program exits.

Use valid integers for all prompts. An initial size outside `0`–`100` resets the array to empty. The program does not validate non-numeric input.

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| Traverse an empty array | Reports that the array is empty. |
| Delete from an empty array | Rejects the operation because there is nothing to delete. |
| Insert into an array with 100 elements | Rejects the operation because the array is full. |
| Enter an invalid insert or delete position | Reports an invalid position and leaves the array unchanged. |
| Enter an initial size below `0` or above `100` | Reports an invalid size and starts with an empty array. |
| Choose an integer other than `1`–`4` | Reports an invalid choice and displays the menu again. |

## Example session

The following abridged session starts with `[10, 20, 30]`, inserts `15` at position `2`, deletes the value at position `3`, and displays the final array.

```text
Enter initial number of elements (0 to 100): 3
Enter element 1: 10
Enter element 2: 20
Enter element 3: 30

----- ARRAY OPERATIONS MENU -----
1. Traverse
2. Insert
3. Delete
4. Exit
Enter your choice: 1
Array elements: 10 20 30

Enter your choice: 2
Enter value to insert: 15
Enter position (1 to 4): 2
Value 15 inserted at position 2.

Enter your choice: 3
Enter position to delete (1 to 4): 3
Value 20 deleted from position 3.

Enter your choice: 1
Array elements: 10 15 30

Enter your choice: 4
Exiting program.
```

## How the algorithms work

### Insertion

To insert at a position, the program moves every element from that position onward one slot to the right, working from the end toward the insertion point. It then writes the new value into the open slot.

```text
Insert 15 at position 2

Before:       [10, 20, 30,  _]
Shift right:  [10, 20, 20, 30]
Write value:  [10, 15, 20, 30]
```

Working backward prevents an element from being overwritten before it has been copied.

### Deletion

To delete a position, the program moves each following element one slot to the left, filling the gap left by the removed value. The logical size is then reduced by one.

```text
Delete position 3

Before:      [10, 15, 20, 30]
Shift left:  [10, 15, 30, 30]
Resize:      [10, 15, 30]
```

The duplicate value after the shift is outside the new logical size and is no longer part of the array's active contents.

## Complexity

Let `n` be the current number of elements.

| Operation | Best time | Worst time | Why |
| --- | :---: | :---: | --- |
| Traverse | `O(n)` | `O(n)` | Every element is visited. |
| Insert | `O(1)` | `O(n)` | Appending needs no shifts; inserting near the front shifts elements. |
| Delete | `O(1)` | `O(n)` | Deleting the last value needs no shifts; deleting near the front shifts elements. |

The algorithms use `O(1)` auxiliary space. The program reserves a fixed `O(MAX)` array, where `MAX = 100`.

## Code map

| Component | Responsibility |
| --- | --- |
| `arr[MAX]` | Stores up to 100 integers. |
| `n` | Tracks the number of active elements. |
| `traverse()` | Prints the active elements from left to right. |
| `insert()` | Validates a position, shifts elements right, and inserts a value. |
| `deleteElement()` | Validates a position, shifts elements left, and removes a value. |
| `main()` | Reads the initial array and controls the menu loop. |

All implementation code is in [`Array operations.c`](./Array%20operations.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, this smoke test compiles the source and exercises all three operations:

```bash
gcc "Array operations.c" -std=c11 -Wall -Wextra -Wpedantic -o array_operations
printf '3\n10\n20\n30\n1\n2\n15\n2\n1\n3\n3\n1\n4\n' | ./array_operations
```

The last traversal should print:

```text
Array elements: 10 15 30
```

## Current scope

This practical intentionally focuses on the mechanics of array traversal and element shifting. It does not currently include:

- Searching, sorting, or updating an element in place
- Dynamic resizing beyond the 100-element capacity
- Saving data between program runs
- Recovery from non-numeric terminal input
- Automated unit tests or a build system

These are natural directions for extending the exercise after the core operations are understood.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**Learn the shift, understand the cost.**

</div>
