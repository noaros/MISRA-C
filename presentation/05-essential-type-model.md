<sub>[◀ Previous](04-declarations-and-initialization.md) · [Contents](README.md) · [Next ▶](06-pointer-conversions.md)</sub>

# Part 5: Rule 10, the essential type model

**The most important (and most misunderstood) part of MISRA C:2012.**


---

## The problem: C's arithmetic conversions

```c
uint8_t  a = 200U;
uint8_t  b = 100U;
uint8_t  sum = a + b;      /* 44: but no warning by default */

int32_t  s = -1;
uint32_t u = 1U;
if (s < u) { ... }         /* FALSE: s is converted to 4294967295 */

uint16_t x = 0xFFFFU;
uint32_t r = x + 1U;       /* 0x10000 on a 32-bit int CPU, 0 on a 16-bit one */
```

C silently applies **integer promotion** (small types become `int`) and the **usual arithmetic conversions** (mixed operands get a common type). The result depends on the target's `int` size and is rarely what the author meant.


---

## The solution: essential types

MISRA classifies every expression into an **essential type category**, *ignoring* integer promotion:

| Category | Examples |
|---|---|
| **Boolean** | `bool`, results of `==`, `<`, `&&`, `!` |
| **character** | `char` (plain) |
| **signed** | `int8_t`, `int16_t`, `int32_t`, `int64_t` |
| **unsigned** | `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t` |
| **enum** | each named `enum` type is its own category |
| **floating** | `float`, `double`, `long double` |

Under this model **`uint8_t + uint8_t` is an 8-bit unsigned operation**, even though C does it in `int`. The rules then forbid mixing categories and silently narrowing, so code behaves the same on 8-, 16-, 32- and 64-bit targets.


---

## Two more ideas you need

**1. Constants have the smallest type that fits.**
Under MISRA, `1U` has essential type `uint8_t`, `300U` is `uint16_t`, and `1` is *signed*. That's why `u8 + 1` breaks Rule 10.4 (unsigned + signed) and you'll see `U` suffixes everywhere.

**2. A *composite expression* is a non-constant arithmetic result.**
Examples are `a + b`, `a * b` and `x << 2`. Composite expressions are the ones that can overflow, so Rules 10.6–10.8 forbid widening them *after* the fact:

```c
uint32_t r = u16a + u16b;                       /* ❌ 10.6: added in 16 bits, then widened */
uint32_t r = (uint32_t)(u16a + u16b);           /* ❌ 10.8: cast is too late */
uint32_t r = (uint32_t)u16a + (uint32_t)u16b;   /* ✅ widen first, then add */
```


---

## The rules at a glance

| Rule | In one line |
|---|---|
| 10.1 | Use each operator only with sensible categories (no maths on `bool`, no bit-ops on signed) |
| 10.2 | Only meaningful character arithmetic (`'0' + d`, `c - '0'`) |
| 10.3 | No implicit narrowing or category change on assignment |
| 10.4 | Both operands of an arithmetic or comparison operator in the same category |
| 10.5 | Don't cast to a nonsensical category |
| 10.6 | Don't assign a composite expression to a wider type |
| 10.7 | Don't mix a composite expression with a wider operand |
| 10.8 | Don't cast a composite expression wider or to another category |

**Rule of thumb:** widen the operands *before* the operation, use `U` suffixes, compare instead of casting to `bool`, and cast only *after* checking the range.


---

## Chapter 10: The essential type model

Code: [`examples/r10/`](../examples/r10)


---

### Rule 10.1 · 🟧 Required

**Operands must not be of an inappropriate essential type.**

**Why:** Arithmetic on Booleans, bitwise operations on signed values, and arithmetic on enums all have surprising or implementation-defined results.

[❌ Bad example](../examples/r10/bad.c#L15-L25) · [✅ Good example](../examples/r10/good.c#L10-L28)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 10.2 · 🟧 Required

**Don't use character values inappropriately in addition and subtraction.**

**Why:** Only meaningful character arithmetic is allowed: `'0' + digit`, `c - '0'`, `c - 'a'`. Adding two characters means nothing as text.

[❌ Bad example](../examples/r10/bad.c#L27-L35) · [✅ Good example](../examples/r10/good.c#L30-L40)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 10.3 · 🟧 Required

**Don't assign a value to a narrower type or a different type category.**

**Why:** Implicit conversions on assignment silently truncate (`uint8_t x = 300` gives 44) or change meaning (`-1` becomes 4294967295).

[❌ Bad example](../examples/r10/bad.c#L37-L48) · [✅ Good example](../examples/r10/good.c#L42-L53)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 10.4 · 🟧 Required

**Both operands of an arithmetic or comparison operator must be in the same type category.**

**Why:** Mixing signed and unsigned converts the signed operand, so `-1 < 1U` is false.

[❌ Bad example](../examples/r10/bad.c#L50-L57) · [✅ Good example](../examples/r10/good.c#L55-L65)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 10.5 · 🟦 Advisory

**Don't cast a value to an inappropriate essential type.**

**Why:** Casting numbers to `bool` or to an `enum` (or `bool` to a number) hides intent and can create invalid values.

[❌ Bad example](../examples/r10/bad.c#L59-L66) · [✅ Good example](../examples/r10/good.c#L67-L86)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 10.6 · 🟧 Required

**Don't assign a composite expression to a wider type.**

**Why:** `uint32_t r = a16 + b16;` does the addition in 16 bits (on a 16-bit target) before widening, so the overflow happens first.

[❌ Bad example](../examples/r10/bad.c#L68-L75) · [✅ Good example](../examples/r10/good.c#L88-L94)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 10.7 · 🟧 Required

**If a composite expression is one operand, the other operand must not be wider.**

**Why:** `u32 * (a16 + b16)` looks like 32-bit arithmetic, but the inner sum may already have wrapped.

[❌ Bad example](../examples/r10/bad.c#L77-L83) · [✅ Good example](../examples/r10/good.c#L96-L101)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 10.8 · 🟧 Required

**Don't cast a composite expression to a wider type or a different category.**

**Why:** The cast happens after the narrow arithmetic. Cast the operands instead.

[❌ Bad example](../examples/r10/bad.c#L85-L93) · [✅ Good example](../examples/r10/good.c#L103-L109)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

<sub>[◀ Previous](04-declarations-and-initialization.md) · [Contents](README.md) · [Next ▶](06-pointer-conversions.md)</sub>
