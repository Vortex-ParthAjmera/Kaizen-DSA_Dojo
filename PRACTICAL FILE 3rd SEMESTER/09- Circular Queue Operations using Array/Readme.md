# Circular Queue Operations using Array (C)

A menu-driven C program implementing a **Circular Queue** using a static array, built as part of a Data Structures and Algorithms (DSA) practical.

---

## 📌 Overview

A circular queue overcomes the main limitation of a simple linear queue — wasted space after repeated dequeues — by wrapping the `rear` and `front` pointers around to the beginning of the array using modulo arithmetic (`% MAX`). This gives O(1) enqueue/dequeue with full reuse of array slots.

This program provides an interactive, menu-driven interface to perform all standard circular queue operations.

---

## ⚙️ Operations Implemented

| # | Operation | Description |
|---|-----------|-------------|
| 1 | `enqueue()` | Inserts an element at the rear of the queue |
| 2 | `dequeue()` | Removes an element from the front of the queue |
| 3 | `peek()` | Displays the front element without removing it |
| 4 | `isFull()` | Checks whether the queue is full |
| 5 | `isEmpty()` | Checks whether the queue is empty |
| 6 | `display()` | Prints all current elements from front to rear |

---

## 🧠 How It Works

- `front` and `rear` are initialized to `-1`, indicating an empty queue.
- **Enqueue**: `rear = (rear + 1) % MAX`, then insert the value at `q[rear]`.
- **Dequeue**: read `q[front]`, then `front = (front + 1) % MAX` (or reset both to `-1` if the queue becomes empty).
- **isFull**: the queue is full when `(rear + 1) % MAX == front` — this "sacrifices" one slot to distinguish full from empty.
- **isEmpty**: the queue is empty when `front == -1`.

### Complexity

| Operation | Time | Space |
|-----------|------|-------|
| Enqueue   | O(1) | O(1)  |
| Dequeue   | O(1) | O(1)  |
| Peek      | O(1) | O(1)  |
| isFull / isEmpty | O(1) | O(1) |
| Overall queue storage | — | O(MAX) |

---

## 🗂️ File Structure

```
.
├── circular_queue_array_operations.c   # Source code
└── README.md                           # Documentation (this file)
```

---

## 🛠️ Compilation & Execution

**Requirements:** GCC (or any standard C compiler)

```bash
# Compile
gcc circular_queue_array_operations.c -o circular_queue_array_operations

# Run
./circular_queue_array_operations
```

On Windows (with MinGW):

```bash
gcc circular_queue_array_operations.c -o circular_queue_array_operations.exe
circular_queue_array_operations.exe
```

---

## 🖥️ Sample Run

```
----- CIRCULAR QUEUE OPERATIONS MENU -----
1. Enqueue
2. Dequeue
3. Peek
4. isFull
5. isEmpty
6. Display
7. Exit
Enter your choice: 1
Enter value to enqueue: 10
10 enqueued into queue.

----- CIRCULAR QUEUE OPERATIONS MENU -----
Enter your choice: 1
Enter value to enqueue: 20
20 enqueued into queue.

----- CIRCULAR QUEUE OPERATIONS MENU -----
Enter your choice: 6
Queue elements (front to rear): 10 20

----- CIRCULAR QUEUE OPERATIONS MENU -----
Enter your choice: 2
10 dequeued from queue.

----- CIRCULAR QUEUE OPERATIONS MENU -----
Enter your choice: 7
Exiting program.
```

---

## ⚠️ Edge Cases Handled

- **Queue Overflow** — enqueue is blocked once the queue is full.
- **Queue Underflow** — dequeue/peek are blocked when the queue is empty.
- **Full wrap-around** — the array reuses freed slots correctly (`% MAX` arithmetic), so the queue doesn't run out of usable space after repeated enqueue/dequeue cycles.
- **Invalid menu input** — falls through to a default "Invalid choice" message.

> **Note:** `MAX` is set to `5`, meaning the queue can effectively hold `MAX - 1 = 4` elements at a time, since one slot is intentionally left empty to distinguish the "full" state from the "empty" state.

---

## 🚀 Possible Extensions

- Parameterize `MAX` via command-line argument or `#define` at compile time
- Convert to a **dynamic circular queue** using `malloc`/`realloc`
- Add a **circular doubly-ended queue (deque)** variant
- Wrap the logic in a reusable header (`circular_queue.h`) for use in other DSA practicals

---

## 👤 Author

**Parth Ajmera**
B.Tech Computer Science, Doon University
DSA Practical — Circular Queue using Array