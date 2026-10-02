<div align="center">

# Balanced Parentheses Checking using a Stack in C

**A single-shot demonstration of validating matched, correctly-nested brackets with a character stack.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/standard-C11-4B8BBE?style=flat-square)
![Interface](https://img.shields.io/badge/interface-terminal-2E3440?style=flat-square)
[![License](https://img.shields.io/badge/license-MIT-22C55E?style=flat-square)](../../LICENSE)

[Quick start](#quick-start) · [Usage](#how-to-use-it) · [Complexity](#complexity) · [Source](./balanced_parentheses.c) · [Back to the Dojo](../../README.md)

</div>

## Overview

This program answers one yes/no question about an expression: are its `()`, `{}`, and `[]` brackets **balanced** — every opening bracket matched by the same type of closing bracket, properly nested? It uses a stack to remember which brackets are still "open," in order:

```text
Input:   {[()]}
Stack:   { → {[ → {[( → {[ (pop, '(' matches ')') → { (pop, '[' matches ']') → (empty, pop, '{' matches '}')
Result:  Balanced
```

Like the infix-to-postfix and postfix-evaluation practicals earlier in this repo, this program is **not menu-driven** — it reads one expression, checks it, prints the verdict, and exits. Unlike those two, this one is **the most defensively written of the stack practicals in this repo**: it checks for an empty stack *before* popping, using short-circuit evaluation, rather than popping unconditionally and hoping for the best.

## What it demonstrates

- Using a stack to track "still open" brackets, popping the most recently opened one whenever a closing bracket arrives
- Matching bracket **type**, not just presence — `(]` is rejected even though both symbols are "a bracket"
- **Correctly guarding against an empty-stack pop** with short-circuit evaluation: `isEmptyStack() || !isMatch(pop(), c)` only calls `pop()` once the left side has confirmed the stack isn't empty, so an extra closing bracket can never trigger an out-of-bounds read
- Checking for **leftover unclosed brackets** after the scan ends, catching the opposite failure mode (too many opens, not enough closes)
- Ignoring any character that isn't one of the six bracket symbols, so brackets embedded in ordinary text or code (`a(b)c`) are checked correctly without the rest of the content interfering

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
cd "Kaizen-DSA_Dojo/PRACTICAL FILE 3rd SEMESTER/13- Balanced parentheses checking"
```

> [!NOTE]
> Adjust the folder name above if your copy of the practical lives under a different path — swap in wherever `balanced_parentheses.c` actually sits.

If you already have the repository, open a terminal directly in the folder containing `balanced_parentheses.c`.

### 2. Compile

Linux or macOS:

```bash
gcc balanced_parentheses.c -std=c11 -Wall -Wextra -Wpedantic -o balanced_parentheses
```

Windows with GCC:

```powershell
gcc balanced_parentheses.c -std=c11 -Wall -Wextra -Wpedantic -o balanced_parentheses.exe
```

> [!TIP]
> The source compiles cleanly under `-Wall -Wextra -Wpedantic` with no warnings.

### 3. Run

Linux or macOS:

```bash
./balanced_parentheses
```

Windows PowerShell:

```powershell
.\balanced_parentheses.exe
```

## How to use it

The program prompts once, reads one expression, checks it, prints `Balanced` or `Not Balanced`, and exits — there is no menu and no loop.

```text
Enter expression: {[()]}
Balanced
```

Non-bracket characters are allowed and simply ignored, so you can check real code or expressions directly, not just bare bracket sequences — `a(b)c` and `{[(a+b)*c]}` both check correctly. As with the other single-shot practicals in this repo, the expression must contain **no spaces**: `scanf("%s", e)` stops reading at the first whitespace character.

### Edge-case behavior

| Situation | Program response |
| --- | --- |
| Every bracket matched and correctly nested | `Balanced` |
| Brackets present but of mismatched types (e.g. `(]`) | `Not Balanced` |
| An opening bracket with no matching close | `Not Balanced` — caught by the leftover-stack check after the scan |
| A closing bracket with no matching open | `Not Balanced` — caught immediately, without ever dereferencing an empty stack |
| Non-bracket characters anywhere in the input | Ignored entirely; only the bracket characters affect the verdict |
| No brackets in the input at all (or empty input) | `Balanced` — vacuously true, since there's nothing left unmatched |

## Example session

A balanced expression:

```text
Enter expression: {[()]}
Balanced
```

A mismatched-type expression — note that this fails even though the bracket *count* is even and every bracket does eventually close:

```text
Enter expression: ([)]
Not Balanced
```

Walking through why: `(` is pushed, then `[` is pushed. The next character is `)`, so `pop()` returns `[` — and `isMatch('[', ')')` is false, since `[` only matches `]`. The check fails immediately, before the loop even reaches the end of the string.

An unclosed bracket:

```text
Enter expression: (()
Not Balanced
```

Here every closing bracket that does appear matches correctly, so the loop runs to completion without ever triggering `balanced = 0` — but the stack still holds one unmatched `(` afterward, and the `if (!isEmptyStack()) balanced = 0;` check at the end catches exactly that.

An extra closing bracket, with no matching open:

```text
Enter expression: ())
Not Balanced
```

This is the case that crashes the infix-to-postfix practical elsewhere in this repo. Here it doesn't: `isEmptyStack()` is checked *before* `pop()` is ever called, so the empty-stack case is caught safely instead of reading past the bottom of the array.

## How the algorithm works

### Opening brackets: push and move on

```c
if (c == '(' || c == '{' || c == '[') {
    push(c);
}
```

Every opening bracket just goes on the stack — there's nothing to check yet, since an opening bracket can never be "wrong" on its own.

### Closing brackets: check empty, then check type — in that order

```c
else if (c == ')' || c == '}' || c == ']') {
    if (isEmptyStack() || !isMatch(pop(), c)) {
        balanced = 0;
        break;
    }
}
```

This is the line that makes this practical safer than the other two in this repo. `||` short-circuits in C: if `isEmptyStack()` is true, `!isMatch(pop(), c)` is never evaluated, so `pop()` is never called on an empty stack. Only once the stack is confirmed non-empty does `pop()` run — and at that point, its result is immediately checked against `c` with `isMatch()`. A wrong-type match (popping `[` to close against `)`) fails this check exactly the same way an empty stack does.

### Catching leftover opens after the scan

```c
if (!isEmptyStack()) balanced = 0;
```

The loop above only ever catches a *premature* or *mismatched* closing bracket. It has no way to notice "the string ended but there's still an open bracket waiting" — that's a different failure mode, and this one-line check after the loop is what catches it, by testing whether anything is still on the stack once there's no more input left to process.

### isMatch: type-checking, not just presence-checking

```c
int isMatch(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}
```

A simpler (and wrong) version of this checker might just count brackets and ignore type, which would incorrectly accept something like `([)]`. Pairing the popped opening bracket with the current closing bracket through `isMatch()` is what makes type-mismatches get caught.

## Complexity

Let `n` be the length of the input expression.

| Operation | Time | Reason |
| --- | :---: | --- |
| Processing one non-bracket character | `O(1)` | Ignored — no stack operation at all. |
| Processing one opening bracket | `O(1)` | One push. |
| Processing one closing bracket | `O(1)` | One empty check, at most one pop, one match check. |
| Full check | `O(n)` | Every character is visited at most once; the loop can also exit early via `break` on the first detected mismatch. |

Space is `O(n)` in the worst case — an expression that is entirely opening brackets pushes one stack entry per character — bounded here by the fixed `char s[MAX]` array with `MAX = 100`.

## Code map

| Component | Responsibility |
| --- | --- |
| `MAX` | Compile-time capacity for both the bracket stack and the input buffer (`100`). |
| `s[MAX]`, `top` | The stack of currently-open bracket characters and its top index. |
| `push()` / `pop()` / `isEmptyStack()` | Minimal stack primitives. |
| `isMatch()` | Checks whether a popped opening bracket is the correct type for the current closing bracket. |
| `main()` | Reads one expression, scans it applying the push/check logic above, checks for leftover opens, and prints the verdict. |

All implementation code is in [`balanced_parentheses.c`](./balanced_parentheses.c).

## Verify the program

There is no automated test suite yet. On a POSIX shell, the following smoke test compiles the source and checks a handful of expressions:

```bash
gcc balanced_parentheses.c -std=c11 -Wall -Wextra -Wpedantic -o balanced_parentheses
for expr in "{[()]}" "([)]" "(()" "())" "a(b)c"; do
    echo "$expr" | ./balanced_parentheses
done
```

Expected output, in order:

```text
Balanced
Not Balanced
Not Balanced
Not Balanced
Balanced
```

## Known limitations

This is the most defensively written of the stack practicals in this repo, but it still has one real gap worth knowing about:

- **`scanf("%s", e)` has no field width, so a sufficiently long input overflows the 100-byte `e[]` buffer.** Testing confirms this crashes with `*** stack smashing detected ***` for inputs well past the buffer's capacity (150 characters, for example); smaller overflows are still undefined behavior even where they don't visibly crash. This is the same unguarded-`scanf` pattern as the other single-shot practicals in this repo.
- As a direct consequence of `e[]` and `s[]` sharing the same `MAX = 100` size, `push()`'s own lack of a bounds check is — in this particular program — "safe by accident" rather than by design: every character that could ever be pushed came from `e[]`, which overflows first if the input is too long, so `s[]` itself can never actually overflow while reading from a well-formed-length `scanf` input. This wouldn't hold if `MAX` were ever changed independently for the two arrays, or if the input came from a different source than `scanf("%s", ...)`.
- As with the other single-shot practicals, spaces anywhere in the input cause everything from the first space onward to be silently dropped, since `scanf("%s", e)` stops at the first whitespace character.
- Non-bracket, non-alphanumeric characters (punctuation, operators, anything) are accepted and simply ignored — there's no validation of the character set beyond the six bracket symbols.
- `scanf()`'s return value is unchecked, so an empty or missing input line leaves `e` uninitialized (though an all-empty `e` buffer in practice still reports `Balanced`, since the loop body never runs).
- The program reports only `Balanced` / `Not Balanced` — it gives no indication of *where* in the expression a mismatch occurred, which would be the natural next thing to add for a more useful diagnostic tool.

## Ideas for extending it

- Replace `scanf("%s", e)` with a width-limited read (`scanf("%99s", e)` or `fgets()`) to close off the buffer-overflow risk directly.
- Report the index of the first mismatch, rather than just a final verdict — useful for something like a code editor's bracket-matching feature.
- Support additional paired delimiters, such as matching quote characters, as a second checking pass.
- Reject (rather than silently ignore) characters outside an expected set, if the goal is strict syntax validation rather than "brackets anywhere in free text."
- Add a mode that also reports *how many* brackets were left unclosed or unmatched, rather than a single balanced/not-balanced verdict.
- Add unit tests covering each of the five documented edge cases, plus the long-input overflow case, so a future rewrite (e.g. switching to `fgets()`) can be checked against them.

## License

This project is available under the repository's [MIT License](../../LICENSE).

---

<div align="center">

**Every opening bracket gets the closing it's owed — or the check fails.**

</div>