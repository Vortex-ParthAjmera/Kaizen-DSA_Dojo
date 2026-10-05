<div align="center">

# Tower of Hanoi in C

**A single-shot demonstration of the classic three-peg recursive puzzle — and the one case where "exponential" isn't a bug.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./tower_of_hanoi.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

Tower of Hanoi: move `n` disks from peg `A` to peg `C`, one at a time, using peg `B` as a spare, never placing a larger disk on a smaller one. The classic recursive solution is three lines:

```c
hanoi(n - 1, from, to, aux);                       // 1. move the top n-1 disks out of the way
printf("Move disk %d from %c to %c\n", n, from, to); // 2. move the big disk
hanoi(n - 1, aux, from, to);                       // 3. move the n-1 disks back on top
```

This program reads `n`, runs that recursion once, prints every move, and reports the total. Like several other single-shot practicals in this repo, there's no menu — it runs once and exits.

## What it demonstrates

- The three-step recursive decomposition that solves Hanoi for any `n`: clear the top `n - 1` disks, move the bottom disk, replace the top `n - 1` disks
- Swapping the roles of `aux` and `to` between the two recursive calls — the same peg acts as the "spare" for one sub-problem and the "destination" for the other
- A genuinely **necessary** exponential: `2ⁿ - 1` is the mathematically proven *minimum* number of moves for `n` disks — no cleverer algorithm exists that solves it in fewer. This is a useful contrast with the Fibonacci practical elsewhere in this repo, where the exponential blow-up comes from *redundant* recomputation that a smarter algorithm avoids entirely.
- Counting moves with a global variable (`cnt`) that accumulates as a side effect of the recursion, rather than being computed or returned directly

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/16- Tower of Hanoi"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `tower_of_hanoi.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `tower_of_hanoi.c`.

### 2. Compile

Linux or macOS:

```bash
gcc tower_of_hanoi.c -std=c11 -Wall -Wextra -Wpedantic -o tower_of_hanoi
```

Windows with GCC:

```powershell
gcc tower_of_hanoi.c -std=c11 -Wall -Wextra -Wpedantic -o tower_of_hanoi.exe
```

> [!TIP]
> The source compiles cleanly under `-Wall -Wextra -Wpedantic` with no warnings.

### 3. Run

Linux or macOS:

```bash
./tower_of_hanoi
```

Windows PowerShell:

```powershell
.\tower_of_hanoi.exe
```

## How to use it

The program prompts once for the number of disks, prints every move it makes, then prints the total move count and exits.

```text
Enter number of disks: 3
Move disk 1 from A to C
Move disk 2 from A to B
Move disk 1 from C to B
Move disk 3 from A to C
Move disk 1 from B to A
Move disk 2 from B to C
Move disk 1 from A to C
Total moves = 7
```

> [!IMPORTANT]
> Entering a **negative** number of disks crashes the program. See below — this is the headline limitation of this practical, not a minor edge case.

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| `n = 0` | Prints no moves; `Total moves = 0`. Correct — zero disks need zero moves. |
| `n = 1` | `Total moves = 1`, the minimum possible non-trivial case. |
| Any positive `n` | `Total moves = 2ⁿ - 1`, the proven-minimal move count. |
| **Negative `n`** | **Crashes** with a segmentation fault — confirmed for `-1`, `-2`, and `-5`. See below. |
| Large `n` (20+) | Still correct, but output volume and runtime both grow exponentially — see the timing table below. |

## Example session

```text
Enter number of disks: 3
Move disk 1 from A to C
Move disk 2 from A to B
Move disk 1 from C to B
Move disk 3 from A to C
Move disk 1 from B to A
Move disk 2 from B to C
Move disk 1 from A to C
Total moves = 7
```

Move counts for several values of `n`, all matching `2ⁿ - 1` exactly:

```text
n=1  → 1 move
n=2  → 3 moves
n=3  → 7 moves
n=4  → 15 moves
n=5  → 31 moves
n=10 → 1023 moves
```

### The crash: negative input

```text
$ echo "-1" | ./tower_of_hanoi
Segmentation fault
```

The base case is `if (n == 0) return;` — it checks for **exactly** zero, not "zero or below." For a negative starting value, each recursive call computes `n - 1`, so the sequence runs `-1, -2, -3, ...` and never once equals `0`. The recursion never terminates on its own; it only stops once it has driven the call stack past its limit, which the OS enforces as a segmentation fault.

### Exponential growth in action

Timed on the machine used to verify this README — all time here goes into producing `2ⁿ - 1` lines of genuinely necessary output, not wasted computation:

| Disks (`n`) | Moves (`2ⁿ - 1`) | Measured time |
| :---: | :---: | :---: |
| 15 | 32,767 | ~0.005 s |
| 18 | 262,143 | ~0.028 s |
| 20 | 1,048,575 | ~0.105 s |
| 22 | 4,194,303 | ~0.454 s |

Each `+2` disks roughly quadruples both the move count and the runtime — exactly what `2ⁿ` predicts. Unlike the Fibonacci practical's timing table, there's no faster algorithm waiting to fix this: `2ⁿ - 1` moves really is the minimum required to legally relocate `n` disks under Hanoi's rules.

## How the algorithm works

### The three-step recursive move

```c
void hanoi(int n, char from, char aux, char to) {
    if (n == 0) return;
    hanoi(n - 1, from, to, aux);                         // clear the top n-1 disks onto aux
    printf("Move disk %d from %c to %c\n", n, from, to);  // move disk n, the largest remaining
    cnt++;
    hanoi(n - 1, aux, from, to);                          // move the n-1 disks from aux onto to
}
```

Notice the peg arguments swap roles between the two recursive calls: in the first call, `to` is passed where `aux` normally goes — it's temporarily the "spare" while the top `n - 1` disks get out of the way. In the second call, `from` takes that same spare role, since the original source peg is now empty and free to hold disks in transit. This argument-swapping is the entire trick behind the algorithm; nothing else about the recursive structure changes between the two calls.

### Depth vs. total work

The recursion is only `n` levels deep at any moment — `hanoi(n, ...)` calls `hanoi(n-1, ...)`, which calls `hanoi(n-2, ...)`, and so on down to the base case, exactly like the factorial practical elsewhere in this repo. What's different is the *branching*: each level makes **two** further calls (before and after its own print statement), so the total number of calls — and therefore the total number of moves — is `2ⁿ - 1`, not `n`. This is the same depth-vs-total-work distinction worth drawing against the Fibonacci practical: Fibonacci's branching recursion is exponential **and avoidable** (a bottom-up loop fixes it); Hanoi's branching recursion is exponential **and required**, since every one of those `2ⁿ - 1` moves corresponds to an actual, necessary disk relocation.

### Counting as a side effect

```c
int cnt = 0;   // global
...
cnt++;
```

The move count isn't computed directly (it could simply be printed as `(1 << n) - 1`) — it's accumulated by incrementing a global variable once per move, as a side effect of the same recursive calls that print each move. This works correctly here because the program only ever runs `hanoi()` once per execution, but it's a design choice worth noticing: `cnt` carries state outside the function's own parameters and return value.

## Complexity

Let `n` be the number of disks.

| Metric | Value | Reason |
| --- | :---: | --- |
| Time | `O(2ⁿ)` | `2ⁿ - 1` total moves, each one `O(1)` work (a print and an increment). |
| Recursion depth (space) | `O(n)` | At most `n` calls are outstanding on the stack at once, same shape as the factorial practical. |
| Move count | Exactly `2ⁿ - 1` | Proven to be the minimum possible for this problem — not an artifact of this particular implementation. |

> [!TIP]
> This is the cleanest illustration in the whole repo of the difference between "exponential because the true answer is exponentially large" (Hanoi) and "exponential because the algorithm redundantly repeats work" (the naive recursive Fibonacci practical). Only the second kind has a faster fix.

## Code map

| Component | Responsibility |
| --- | --- |
| `cnt` | Global counter, incremented once per move, printed as the final total. |
| `hanoi()` | The recursive solver: clears the top `n-1` disks, moves disk `n`, then replaces the top `n-1` disks, swapping the auxiliary/destination roles between the two recursive calls. |
| `main()` | Reads `n`, calls `hanoi(n, 'A', 'B', 'C')` once, and prints the final move count. |

All implementation code is in [`tower_of_hanoi.c`](./tower_of_hanoi.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and checks a small case:

```bash
gcc tower_of_hanoi.c -std=c11 -Wall -Wextra -Wpedantic -o tower_of_hanoi
echo "3" | ./tower_of_hanoi
```

Expected output:

```text
Move disk 1 from A to C
Move disk 2 from A to B
Move disk 1 from C to B
Move disk 3 from A to C
Move disk 1 from B to A
Move disk 2 from B to C
Move disk 1 from A to C
Total moves = 7
```

To confirm the move-count formula holds, compare against `2ⁿ - 1` for a few values of `n`:

```bash
for n in 1 2 3 4 5; do echo "$n" | ./tower_of_hanoi | tail -1; done
```

Expected: `1`, `3`, `7`, `15`, `31` moves respectively.

## Known limitations

- **Negative `n` crashes the program.** The base case `if (n == 0) return;` only catches exactly zero. A negative starting value decrements forever (`-1, -2, -3, ...`) without ever hitting `0`, so the recursion runs until the call stack is exhausted — confirmed to segfault for `-1`, `-2`, and `-5`.
- **`cnt` is a 32-bit `int`, which would itself overflow for a large enough `n`** — `2ⁿ - 1` exceeds `INT_MAX` once `n` reaches 32, mirroring the factorial overflow bug in the recursion-basics practical elsewhere in this repo. This is mostly theoretical here: `n = 32` means over four billion individual `printf()` calls, which would take far longer to run than anyone would wait for regardless of whether the counter itself is correct.
- There is no practical upper limit on `n`; the program will attempt to print all `2ⁿ - 1` moves for whatever value it's given, with no warning that, say, `n = 30` means over a billion lines of output.
- `scanf()`'s return value is unchecked, so non-numeric input is not handled reliably.
- The program has no automated tests or build configuration.

## Ideas for extending it

- Add an explicit check that rejects negative `n` with a clear error message, instead of letting the recursion run away — this alone fixes the crash.
- Compute the total move count directly as `(1 << n) - 1` and print it immediately, rather than relying on `cnt` to accumulate it correctly across billions of increments.
- Add a "quiet mode" or a `n` threshold past which individual moves aren't printed — only the final count — so large `n` stays informative without flooding the terminal.
- Switch `cnt` (and the printed total) to a wider type such as `long long` or `unsigned long long`, to push the overflow point out far past where runtime itself becomes the limiting factor.
- Make `cnt` a return value (or accumulate it via a pointer parameter) instead of global state, so the function is self-contained and safe to call more than once in the same program.
- Add an animated or graphical visualization of the disk moves, rather than text output alone.
- Add unit tests covering `n = 0`, `n = 1`, a handful of positive values checked against `2ⁿ - 1`, and a documented (not crashing) response to negative input once that's fixed.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**Three pegs, one recursive idea, and a move count no algorithm can shrink.**

</div>