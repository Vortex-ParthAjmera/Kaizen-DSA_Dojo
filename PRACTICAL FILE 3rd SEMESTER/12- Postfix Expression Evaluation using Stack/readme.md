<div align="center">

# Postfix Expression Evaluation using a Stack in C

**A single-shot demonstration of evaluating a postfix (Reverse Polish) expression with a numeric stack.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./postfix_evaluation.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This program evaluates a **postfix expression** (like `23*54*+9-`) down to a single number, using an integer stack: every digit is pushed, and every operator pops its two operands, computes a result, and pushes that result back.

```text
Input (postfix):  2 3 * 5 4 * + 9 -
Stack activity:   push,push,pop-pop-push,push,push,pop-pop-push,pop-pop-push,push,pop-pop-push
Final stack:      [17]  →  Result = 17
```

This is the natural second half of the pipeline started by the infix-to-postfix practical earlier in this repo: that one converts `(2+3)*...`-style expressions into postfix, and this one consumes the result. Like that practical, this program is **not menu-driven** — it reads one expression, evaluates it, prints the result, and exits.

## What it demonstrates

- Using a stack to hold operands, rather than operators as in the infix-to-postfix practical
- Pushing every digit the instant it's read, with `c - '0'` converting the character to its numeric value
- Popping exactly two operands per operator, computing, and pushing the single result back — so the stack always ends with exactly one value if the expression was well-formed
- **Operand order matters for non-commutative operators**: the operand popped first is the *second* operand — `b = pop(); a = pop();` and then `a op b`, not `b op a`
- Draining down to a single final value once the whole expression has been consumed

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/12- Postfix expression evaluation"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `postfix_evaluation.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `postfix_evaluation.c`.

### 2. Compile

Linux or macOS:

```bash
gcc postfix_evaluation.c -std=c11 -Wall -Wextra -Wpedantic -o postfix_evaluation
```

Windows with GCC:

```powershell
gcc postfix_evaluation.c -std=c11 -Wall -Wextra -Wpedantic -o postfix_evaluation.exe
```

> [!TIP]
> The source compiles cleanly under `-Wall -Wextra -Wpedantic` with no warnings.

### 3. Run

Linux or macOS:

```bash
./postfix_evaluation
```

Windows PowerShell:

```powershell
.\postfix_evaluation.exe
```

## How to use it

The program prompts once, reads one expression, evaluates it, prints the result, and exits — there is no menu and no loop.

```text
Enter postfix expression: 23*54*+9-
Result = 17
```

> [!IMPORTANT]
> Operands must be **single digits** with **no spaces** — the source comment says as much. `isdigit(c)` reads one character at a time and pushes its numeric value directly, so there is no parsing of multi-digit numbers at all; see [Known limitations](#known-limitations) for what that does to an expression like `12+`.

Supported operators: `+`, `-`, `*`, `/`. Any other non-digit character is treated as if it were an operator — see the crash and silent-miscomputation notes below.

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| Well-formed expression with single-digit operands | Evaluates correctly. |
| A single digit, no operators | Passes it straight through as the result. |
| Division where the divisor is `0` | **Crashes** with a floating-point exception (`SIGFPE`) — see below. |
| An operator with too few operands on the stack | Does **not** reliably crash — instead reads stack slots before index `0`, producing an incorrect result with no error message. |
| An unrecognized character (not a digit or one of `+ - * /`) | Silently treated as an operator: pops two values, computes `0` (the `switch` statement's `default` case), and pushes that `0` back — no error is reported. |
| Multi-digit operand (e.g. a two-digit number) | Each digit is pushed as its own separate single-digit operand — the two-digit number is never reconstructed. |

## Example session

Working through `23*54*+9-` step by step:

| Character | Action | Stack (bottom→top) |
| :---: | --- | :---: |
| `2` | Push `2` | `2` |
| `3` | Push `3` | `2 3` |
| `*` | Pop `3`, pop `2`, push `2*3 = 6` | `6` |
| `5` | Push `5` | `6 5` |
| `4` | Push `4` | `6 5 4` |
| `*` | Pop `4`, pop `5`, push `5*4 = 20` | `6 20` |
| `+` | Pop `20`, pop `6`, push `6+20 = 26` | `26` |
| `9` | Push `9` | `26 9` |
| `-` | Pop `9`, pop `26`, push `26-9 = 17` | `17` |
| *(end of input)* | Pop the final value and print it | *(empty)* |

```text
Enter postfix expression: 23*54*+9-
Result = 17
```

A few more, showing why operand order matters for `-` and `/`:

```text
23+   → Result = 5    (2+3)
23-   → Result = -1   (2-3, NOT 3-2 — the first-pushed operand is "a", not "b")
23*   → Result = 6    (2*3)
63/   → Result = 2    (6/3)
```

### The crash: division by zero

```text
$ echo "50/" | ./postfix_evaluation
Floating point exception
```

Any expression that divides by a `0` operand crashes immediately — there is no check before the `a / b` in the `switch` statement.

### The silent miscomputation: too few operands

```text
$ echo "2+" | ./postfix_evaluation
Result = 2
```

`+` needs two operands, but only `2` was ever pushed. Rather than reporting an error, `pop()` happily reads (and later writes to) array slots *before* index `0` — memory the array doesn't own — and the program prints a plausible-looking number as if nothing went wrong. See [Known limitations](#known-limitations) for exactly why.

## How the algorithm works

### Digits go straight onto the stack

```c
if (isdigit(c)) {
    push(c - '0');
}
```

`c - '0'` relies on the digit characters being contiguous in ASCII (`'0'`–`'9'`), so subtracting the character code for `'0'` yields the digit's numeric value. This only works for exactly one digit at a time — there's no accumulation of multiple digits into a larger number.

### Operators pop two, compute one, push the result

```c
int b = pop();
int a = pop();
int r;
switch (c) {
    case '+': r = a + b; break;
    case '-': r = a - b; break;
    case '*': r = a * b; break;
    case '/': r = a / b; break;
    default:  r = 0;
}
push(r);
```

The order here is deliberate and easy to get backwards: in postfix, the operator always follows its two operands in the order they appeared, so the **second** operand is the one popped **first**. That's why it's `b = pop()` before `a = pop()`, and then `a - b` (not `b - a`) for subtraction — getting this backwards would silently compute the wrong answer for every non-commutative operator (`-` and `/`) while still looking correct for `+` and `*`.

The `default: r = 0;` case is what makes an unrecognized character dangerous rather than merely unsupported: there's no `default` branch that reports an error, so the switch always produces *some* number, and execution carries on as if nothing were wrong.

### Draining to the final answer

```c
printf("Result = %d\n", pop());
```

After the whole expression is consumed, exactly one value should remain on the stack — a single final `pop()` retrieves it. There is no check that the stack actually holds exactly one value at this point.

## Complexity

Let `n` be the length of the input expression.

| Operation | Time | Reason |
| --- | :---: | --- |
| Processing one digit | `O(1)` | One push. |
| Processing one operator | `O(1)` | Two pops, one arithmetic computation, one push. |
| Full evaluation | `O(n)` | Every character is read once, and every stack operation is constant time. |

Space is `O(n)` in the worst case (an expression that is entirely digits before any operator appears would push one stack entry per digit) — bounded here by the fixed `int s[MAX]` array with `MAX = 100`.

## Code map

| Component | Responsibility |
| --- | --- |
| `MAX` | Compile-time capacity for both the operand stack and the input buffer (`100`). |
| `s[MAX]`, `top` | The operand stack and its top index. |
| `push()` / `pop()` | Minimal stack primitives — note `pop()` has no bounds check of its own, same as in the infix-to-postfix practical. |
| `main()` | Reads one expression with `scanf("%s", e)`, walks it character by character pushing digits and applying operators, then prints the final popped value. |

All implementation code is in [`postfix_evaluation.c`](./postfix_evaluation.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and checks a handful of expressions:

```bash
gcc postfix_evaluation.c -std=c11 -Wall -Wextra -Wpedantic -o postfix_evaluation
for expr in "23*54*+9-" "23+" "23-" "63/"; do
    echo "$expr" | ./postfix_evaluation
done
```

Expected output, in order:

```text
Result = 17
Result = 5
Result = -1
Result = 2
```

## Known limitations

This practical keeps the core evaluation logic front and center, at the cost of some real robustness gaps — several of them more dangerous than an outright crash, because they fail silently:

- **Division by zero crashes the program** with a `SIGFPE` (floating-point exception) — there is no check for a zero divisor before `a / b` runs.
- **Too few operands corrupts silently instead of erroring.** `pop()` has no bounds check, so an operator with fewer than two values on the stack reads from (and a subsequent `push()` writes to) array slots before index `0` — memory the array doesn't own. This is undefined behavior: in testing it happened to produce a plausible-looking wrong number rather than crashing, but that behavior isn't guaranteed by the language and could differ across compilers, optimization levels, or platforms.
- **An unrecognized character is silently treated as a zeroing operator.** Anything that isn't a digit or one of `+ - * /` falls into the `switch`'s `default: r = 0;` case, popping two real operands off the stack and replacing them with `0` — with no error message at all. A single typo'd character can quietly zero out part of a computation.
- **Multi-digit operands are silently mangled**, exactly as the source comment warns: each digit is pushed as its own single-digit operand, so `12+` evaluates as `1 + 2 = 3`, not `12`.
- `scanf()`'s return value is unchecked, so an empty or missing input line leaves `e` uninitialized.
- The operand stack and input buffer share the same fixed `MAX = 100` capacity with no bounds checking on `push()`; a long enough expression would overflow it.
- There is no check that exactly one value remains on the stack when the input ends — a malformed expression that leaves extra values behind still prints whatever ends up on top.

## Ideas for extending it

- Check the divisor before `a / b` and report a "division by zero" error instead of letting the program crash.
- Add bounds checking to `pop()` (and to `push()`) so operand-count and capacity problems fail with a clear message instead of corrupting memory.
- Replace the `default: r = 0;` case with an explicit "unrecognized operator" error that stops evaluation instead of silently continuing.
- Support multi-digit operands by accumulating consecutive digit characters into one number before pushing, mirroring the extension suggested for the infix-to-postfix practical.
- After the main loop, check that the stack holds exactly one value before printing it, and report a "malformed expression" error otherwise.
- Feed this program's input directly from the infix-to-postfix practical's output, completing the full infix → postfix → evaluate pipeline end to end.
- Add unit tests covering each operator, division by zero, too-few-operands, and unrecognized-character cases.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**Digits stack up; operators collapse them two at a time.**

</div>