<div align="center">

# Factorial, Fibonacci, and GCD using Recursion in C

**An interactive demonstration of three classic recursive algorithms — and where each one's simplicity starts to cost something.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./recursion_basics.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This menu-driven program runs three textbook recursive functions on demand: **factorial**, **Fibonacci**, and **GCD** (greatest common divisor, via the Euclidean algorithm). Each one is written as directly as possible — a base case and a recursive call, nothing more:

```c
int factorial(int n) { return (n <= 1) ? 1 : n * factorial(n - 1); }
int fibonacci(int n) { return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2); }
int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a % b); }
```

That directness is exactly the point of the practical — and also exactly where each function's real-world limits show up fastest: `factorial` overflows a 32-bit `int` after `12!`, `fibonacci` recomputes the same values over and over and becomes impractically slow by the low 40s, and `gcd` can return a negative result because nothing ever takes an absolute value. All three are measured and documented below, not just asserted.

## What it demonstrates

- The base case / recursive case shape common to all three functions
- **Factorial**: straightforward linear recursion, one multiplication per call
- **Fibonacci**: *branching* recursion — each call spawns two more, which is what makes its cost blow up
- **GCD**: the Euclidean algorithm, reducing `(a, b)` to `(b, a % b)` until the remainder hits zero
- Where `int`'s fixed width quietly breaks each of these algorithms, once inputs get large enough

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/15- Recursion basics"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `recursion_basics.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `recursion_basics.c`.

### 2. Compile

Linux or macOS:

```bash
gcc recursion_basics.c -std=c11 -Wall -Wextra -Wpedantic -o recursion_basics
```

Windows with GCC:

```powershell
gcc recursion_basics.c -std=c11 -Wall -Wextra -Wpedantic -o recursion_basics.exe
```

> [!TIP]
> The source compiles cleanly under `-Wall -Wextra -Wpedantic` with no warnings.

### 3. Run

Linux or macOS:

```bash
./recursion_basics
```

Windows PowerShell:

```powershell
.\recursion_basics.exe
```

## How to use it

There is **no initial setup** — the program starts straight at the menu.

| Choice | Operation | Additional input |
| :---: | --- | --- |
| `1` | Compute `n!` | A single integer `n` |
| `2` | Print the first `n` Fibonacci terms | A single integer `n` |
| `3` | Compute `gcd(a, b)` | Two integers, space-separated |
| `4` | Exit | None |

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| `n = 0` for factorial | `1`, correctly (`0! = 1` by convention). |
| `n < 0` for factorial | Silently returns `1` — the base case `n <= 1` doesn't distinguish "zero" from "negative," so there's no error for an operation that's undefined for negative integers. |
| `n >= 13` for factorial | The true result exceeds a 32-bit `int`'s range; the printed value is wrapped/garbage, not the mathematically correct factorial. See below. |
| `n <= 0` terms requested for Fibonacci | Prints an empty series — the display loop simply never runs. |
| Either GCD input is `0` | Returns the other input unchanged, correctly. |
| Either GCD input is negative | May return a **negative** result — see below. |
| `gcd(0, 0)` | Returns `0`. |

## Example session

```text
----- RECURSION MENU -----
1. Factorial
2. Fibonacci (first n terms)
3. GCD
4. Exit
Enter your choice: 1
Enter n: 5
Factorial of 5 = 120

----- RECURSION MENU -----
1. Factorial
2. Fibonacci (first n terms)
3. GCD
4. Exit
Enter your choice: 2
Enter number of terms: 10
Fibonacci series: 0 1 1 2 3 5 8 13 21 34

----- RECURSION MENU -----
1. Factorial
2. Fibonacci (first n terms)
3. GCD
4. Exit
Enter your choice: 3
Enter two numbers: 48 18
GCD of 48 and 18 = 6

----- RECURSION MENU -----
1. Factorial
2. Fibonacci (first n terms)
3. GCD
4. Exit
Enter your choice: 4
Exiting program.
```

### Factorial: correct, then silently wrong

```text
Enter n: 12
Factorial of 12 = 479001600      ← correct: 12! = 479,001,600, just under INT_MAX (2,147,483,647)

Enter n: 13
Factorial of 13 = 1932053504     ← WRONG: true 13! = 6,227,020,800, which overflows a 32-bit int
```

Every result from `13!` onward is some wrapped value, not the real factorial — the program gives no indication anything went wrong.

### GCD: a negative input can produce a negative result

```text
Enter two numbers: -12 8
GCD of -12 and 8 = -4            ← mathematically, gcd(-12, 8) = 4

Enter two numbers: 12 -8
GCD of 12 and -8 = 4             ← correct here, by coincidence of which operand hits zero last
```

The sign of the result depends on which argument the recursion happens to be holding when `b` reaches `0` — it isn't consistently positive, consistently matching either input's sign, or consistently anything in particular. `gcd()` never takes an absolute value anywhere.

### Fibonacci: correct, then impractically slow

Timed on the machine used to verify this README:

| Terms requested | Measured time |
| :---: | :---: |
| 30 | ~0.015 s |
| 35 | ~0.135 s |
| 40 | ~1.49 s |

Each jump of 5 terms costs roughly **9–11×** longer — consistent with the function's exponential growth. Extrapolating that trend, 50 terms would already be on the order of a couple of minutes; this isn't a one-off slow input, it's the shape of the whole function. See below for why.

## How the algorithms work

### Factorial — linear recursion

```c
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

One call per decrement of `n`, so the call chain is exactly `n` deep: `factorial(5)` calls `factorial(4)`, which calls `factorial(3)`, and so on down to the base case, then each pending multiplication resolves on the way back up. This recursion is **not** tail-recursive — the multiplication happens *after* the recursive call returns — so a compiler can't collapse it into a plain loop even with optimizations enabled.

### Fibonacci — branching recursion

```c
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

Every call that isn't a base case makes **two** further calls. Drawn as a tree, `fibonacci(5)`'s call tree has branches that each re-expand the same smaller sub-problems independently — `fibonacci(3)` gets computed from scratch inside both the `fibonacci(4)` branch and the `fibonacci(5)` branch's direct call, with no memory of the first computation. That duplicated work is what produces the exponential blow-up measured above — and it happens **again, from scratch, for every single term printed**, since `main()`'s display loop calls `fibonacci(i)` fresh for each `i` from `0` to `n - 1` rather than building each term from the last.

### GCD — the Euclidean algorithm

```c
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
```

Each call replaces `(a, b)` with `(b, a % b)` — the pair shrinks quickly (the Euclidean algorithm is one of the oldest provably-fast algorithms in existence, logarithmic in the smaller input). This recursion *is* tail-recursive, unlike `factorial()`, since the recursive call's result is returned directly with no further computation around it.

## Complexity

Let `n` be the relevant input (or, for GCD, let `a` and `b` be the two inputs).

| Operation | Time | Space (call stack depth) | Reason |
| --- | :---: | :---: | --- |
| Factorial | `O(n)` | `O(n)` | One call per decrement; `n` stack frames outstanding at the deepest point. |
| GCD | `O(log(min(a, b)))` | `O(log(min(a, b)))` | Each step reduces the pair roughly the way the Euclidean algorithm always does — very few calls even for large inputs. |
| Fibonacci (one call) | `O(φⁿ)` | `O(n)` | Exponential in `n` (φ ≈ 1.618, the golden ratio) — each call branches into two, with massive overlap between branches. |
| Fibonacci (the menu's "first n terms" display) | `O(φⁿ)` total, but with a larger constant than a single `fibonacci(n)` call | `O(n)` | Every term from `0` to `n - 1` is computed independently from scratch, so the total work is the *sum* of the costs of `n` separate exponential calls, not just one. |

All three functions use `O(depth)` auxiliary space on the call stack, proportional to how deep the recursion goes — `factorial` and `fibonacci` both scale with `n`, while `gcd`'s stack depth stays small even for large inputs, since it shrinks logarithmically.

> [!TIP]
> A memoized or iterative Fibonacci (building each term from the previous two, bottom-up) turns the exponential `O(φⁿ)` into linear `O(n)` — the classic fix for exactly the inefficiency measured above.

## Code map

| Component | Responsibility |
| --- | --- |
| `factorial()` | Computes `n!` via linear, non-tail recursion. |
| `fibonacci()` | Computes the `n`th Fibonacci number via branching recursion. |
| `gcd()` | Computes the greatest common divisor via the (tail-recursive) Euclidean algorithm. |
| `main()` | Runs the menu loop, reads the relevant input for each choice, and prints the result — for choice `2`, it loops over `i = 0 .. n-1` calling `fibonacci(i)` fresh each time. |

All implementation code is in [`recursion_basics.c`](./recursion_basics.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and checks each operation:

```bash
gcc recursion_basics.c -std=c11 -Wall -Wextra -Wpedantic -o recursion_basics
printf '1\n5\n2\n10\n3\n48 18\n4\n' | ./recursion_basics
```

The output should include:

```text
Factorial of 5 = 120
Fibonacci series: 0 1 1 2 3 5 8 13 21 34
GCD of 48 and 18 = 6
```

To reproduce the factorial overflow:

```bash
printf '1\n13\n4\n' | ./recursion_basics
```

This prints `Factorial of 13 = 1932053504` — not the true value, `6227020800`.

## Known limitations

This practical keeps each algorithm's recursive structure front and center, at the cost of some real correctness and performance gaps:

- **Factorial silently overflows past `12!`.** `int` is 32 bits on the platform used to verify this README, and `13!` (`6,227,020,800`) exceeds `INT_MAX` (`2,147,483,647`). Signed integer overflow is undefined behavior in C; in practice this build wraps to a meaningless value rather than erroring, and the program gives no indication anything went wrong.
- **Negative factorial input is accepted silently.** `n <= 1` is the only base-case check, so any negative `n` immediately returns `1` rather than reporting that factorial is undefined for negative integers.
- **GCD can return a negative result.** `gcd()` never applies an absolute value anywhere in its logic, so a negative input can propagate through to a negative final answer — confirmed above with `gcd(-12, 8) = -4`. The conventional mathematical definition of GCD is always non-negative.
- **The Fibonacci display is exponentially slow, and more wastefully so than a single naive Fibonacci call needs to be**, because every term is recomputed completely independently rather than building on the previous one. The timings above (30/35/40 terms) demonstrate the trend directly; by the time `n` reaches the 45–50 range, a single run would likely take minutes.
- Neither `factorial()` nor `fibonacci()` has any recursion-depth guard — a very large `n` could, in principle, exhaust the call stack, though in testing even `factorial(100000)` completed without crashing (it just returned an already-overflowed, meaningless value).
- `scanf()`'s return value is unchecked throughout, so non-numeric input is not handled reliably.
- The program has no automated tests or build configuration.

## Ideas for extending it

- Switch to `unsigned long long` (or an arbitrary-precision/bignum approach) for `factorial()` to push the overflow point much further out, and document the new limit explicitly rather than leaving it implicit.
- Reject negative `n` for `factorial()` with an explicit error message instead of silently returning `1`.
- Wrap `gcd()`'s final result in `abs()` (or take absolute values of the inputs up front) so the output always matches the conventional non-negative definition.
- Replace the naive recursive `fibonacci()` with a memoized version (caching each computed term) or an iterative bottom-up loop, and compare the timings directly against the numbers measured above.
- Change the menu's Fibonacci display to build each term from the previous two as it goes, rather than calling `fibonacci(i)` fresh for every `i` — this alone would turn the display from exponential to linear without even touching the recursive function itself.
- Add an explicit recursion-depth or input-size cap with a clear error message, rather than relying on the platform's call stack to simply be "big enough."
- Add unit tests covering: factorial of 0, 1, a large value that overflows, and a negative value; GCD with zero, negative, and mixed-sign inputs; and Fibonacci's first several terms.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**Three functions, three ceilings — recursion is simple right up until the numbers aren't.**

</div>