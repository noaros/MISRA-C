<sub>[◀ Previous](06-pointer-conversions.md) · [Contents](README.md) · [Next ▶](08-control-flow.md)</sub>

# Part 7: Rules 12–13, expressions and side effects

**Make grouping explicit, keep shifts in range, and give every statement one clear effect.**


---

## Chapter 12: Expressions

Code: [`examples/r12/`](../examples/r12)


---

### Rule 12.1 · 🟦 Advisory

**Make operator precedence explicit with parentheses.**

**Why:** `flags & MASK == 0` means `flags & (MASK == 0)`. Precedence is the most common source of 'looks right' bugs.

[❌ Bad example](../examples/r12/bad.c#L10-L22) · [✅ Good example](../examples/r12/good.c#L10-L20)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 12.2 · 🟧 Required

**A shift amount must be between zero and one less than the width of the left operand's essential type.**

**Why:** Shifting by the width or more (or by a negative amount) is undefined, and MISRA measures width by essential type, so `u8 << 8` is out of range.

[❌ Bad example](../examples/r12/bad.c#L24-L32) · [✅ Good example](../examples/r12/good.c#L22-L33)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 12.3 · 🟦 Advisory

**Don't use the comma operator.**

**Why:** It hides extra side effects in places readers skim, such as `for` headers and conditions.

[❌ Bad example](../examples/r12/bad.c#L34-L46) · [✅ Good example](../examples/r12/good.c#L35-L50)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 12.4 · 🟦 Advisory

**Constant expressions shouldn't wrap around.**

**Why:** Unsigned wrap is well-defined but rarely intended in a constant; it usually signals a mistake.

[❌ Bad example](../examples/r12/bad.c#L48-L56) · [✅ Good example](../examples/r12/good.c#L52-L57)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 12.5 · 🟥 Mandatory

**Don't apply `sizeof` to a function parameter declared as an array.**

**Why:** An array parameter is really a pointer, so `sizeof` returns the pointer size, not the array size (added by Amendment 1).

[❌ Bad example](../examples/r12/bad.c#L58-L64) · [✅ Good example](../examples/r12/good.c#L59-L75)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

## Side effects and sequence points

A **side effect** changes state: assigning, `++`/`--`, writing a `volatile`, calling a function that does any of these.

C only guarantees that side effects are complete at **sequence points**: the end of a full expression, `&&`, `||`, `?:`, the comma operator, and a function call. Between two sequence points:

- modifying the same object twice, or
- modifying it and reading it for another purpose

is **undefined behaviour**. The order in which function arguments and operands are evaluated is **unspecified**.

```c
i = i++;               /* undefined */
a[i] = i++;            /* undefined */
x = f() + g();         /* f or g first? unspecified */
```

Chapter 13's rules boil down to: **one side effect per statement, in an obvious place.**


---

## Chapter 13: Side effects

Code: [`examples/r13/`](../examples/r13)


---

### Rule 13.1 · 🟧 Required

**No persistent side effects in initializer lists.**

**Why:** The evaluation order of initializers is unspecified, so the result depends on the compiler.

[❌ Bad example](../examples/r13/bad.c#L17-L24) · [✅ Good example](../examples/r13/good.c#L16-L26)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 13.2 · 🟧 Required

**An expression's value and side effects must be the same under every permitted evaluation order.**

**Why:** `a[i] = i++` and `f() - g()` (with shared state) have no single defined meaning.

[❌ Bad example](../examples/r13/bad.c#L26-L35) · [✅ Good example](../examples/r13/good.c#L28-L41)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 13.3 · 🟦 Advisory

**A full expression containing `++`/`--` shouldn't have any other side effects.**

**Why:** `buf[i++] = v` packs two effects into one line. Splitting them makes order and intent obvious.

[❌ Bad example](../examples/r13/bad.c#L37-L43) · [✅ Good example](../examples/r13/good.c#L43-L51)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 13.4 · 🟦 Advisory

**Don't use the result of an assignment.**

**Why:** `if (x = y)` is the classic `=` versus `==` mistake. `a = b = c` hides conversions.

[❌ Bad example](../examples/r13/bad.c#L45-L58) · [✅ Good example](../examples/r13/good.c#L53-L65)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 13.5 · 🟧 Required

**The right operand of `&&` or `||` must not have persistent side effects.**

**Why:** Short-circuiting means the side effect only happens sometimes.

[❌ Bad example](../examples/r13/bad.c#L60-L71) · [✅ Good example](../examples/r13/good.c#L67-L84)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 13.6 · 🟥 Mandatory

**The operand of `sizeof` must not contain side effects.**

**Why:** `sizeof(x++)` never evaluates `x++`. The side effect silently disappears.

[❌ Bad example](../examples/r13/bad.c#L73-L80) · [✅ Good example](../examples/r13/good.c#L86-L94)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

<sub>[◀ Previous](06-pointer-conversions.md) · [Contents](README.md) · [Next ▶](08-control-flow.md)</sub>
