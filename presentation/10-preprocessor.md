<sub>[◀ Previous](09-functions-pointers-arrays.md) · [Contents](README.md) · [Next ▶](11-library-and-resources.md)</sub>

# Part 10: Rule 20, the preprocessor

**The preprocessor works on text, not on C. It knows nothing about types, scope or precedence, so MISRA keeps its use simple and predictable.**


---

## Macro guidelines at a glance

- Prefer `static inline` functions and `const`/`enum` constants to macros ([Dir 4.9](01-directives.md)).
- If you write a function-like macro: **parenthesise every parameter and the whole body** (20.7).
- Guard every header (Dir 4.10), put all `#include`s at the top (20.1).
- Keep `#if` expressions to defined macros with values 0/1, or explicit comparisons (20.8, 20.9).
- Avoid `#` and `##` (20.10). If you must use them, keep the parameter rules (20.11, 20.12).

```c
#define SQUARE(x)  x * x          /* ❌ SQUARE(1 + 2) == 5 */
#define SQUARE(x)  ((x) * (x))    /* ⚠️ still evaluates x twice */
static inline int32_t square(int32_t x) { return x * x; }   /* ✅ */
```


---

## Chapter 20: Preprocessing directives

Code: [`examples/r20/`](../examples/r20)


---

### Rule 20.1 · 🟦 Advisory

**Only preprocessor directives or comments may come before an `#include`.**

**Why:** An include placed after code sees different declarations depending on its position.

[❌ Bad example](../examples/r20/bad.c#L7-L11) · [✅ Good example](../examples/r20/good.c#L4-L8)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 20.2 · 🟧 Required

**Header file names must not contain `'`, `"`, `\`, `/*` or `//`.**

**Why:** These characters in header names are undefined behaviour and break across operating systems.

[❌ Bad example](../examples/r20/bad.c#L13-L19) · [✅ Good example](../examples/r20/good.c#L10-L12)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 20.3 · 🟧 Required

**`#include` must be followed by `<filename>` or `"filename"`.**

**Why:** Anything else is undefined behaviour.

[❌ Bad example](../examples/r20/bad.c#L21-L26) · [✅ Good example](../examples/r20/good.c#L14-L15)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 20.4 · 🟧 Required

**Don't define a macro with the same name as a keyword.**

**Why:** `#define volatile` silently changes the meaning of all later code.

[❌ Bad example](../examples/r20/bad.c#L28-L30) · [✅ Good example](../examples/r20/good.c#L17-L20)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 20.5 · 🟦 Advisory

**Don't use `#undef`.**

**Why:** A macro whose meaning changes partway through a file confuses readers.

[❌ Bad example](../examples/r20/bad.c#L32-L37) · [✅ Good example](../examples/r20/good.c#L22-L24)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 20.6 · 🟧 Required

**No preprocessing directives inside macro arguments.**

**Why:** Undefined behaviour, and cppcheck refuses to analyse such files.

[❌ Bad example](../examples/r20/bad.c#L39-L61) · [✅ Good example](../examples/r20/good.c#L26-L39)

<sub>🔎 cppcheck 2.13: not analysed: cppcheck refuses to parse files containing it</sub>


---

### Rule 20.7 · 🟧 Required

**Parenthesise macro parameters in expansions.**

**Why:** `#define SQ(x) x * x` makes `SQ(1 + 2)` equal 5.

[❌ Bad example](../examples/r20/bad.c#L63-L70) · [✅ Good example](../examples/r20/good.c#L41-L49)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 20.8 · 🟧 Required

**`#if`/`#elif` conditions must evaluate to 0 or 1.**

**Why:** A value like 2 blurs whether a macro is a flag or a level.

[❌ Bad example](../examples/r20/bad.c#L72-L77) · [✅ Good example](../examples/r20/good.c#L51-L56)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 20.9 · 🟧 Required

**Define every identifier used in `#if`/`#elif` before it is evaluated.**

**Why:** An undefined identifier silently counts as 0, so a typo quietly disables a feature.

[❌ Bad example](../examples/r20/bad.c#L79-L84) · [✅ Good example](../examples/r20/good.c#L58-L67)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 20.10 · 🟦 Advisory

**Don't use the `#` and `##` operators.**

**Why:** Their evaluation order is unspecified, and generated identifiers can't be found by searching the source.

[❌ Bad example](../examples/r20/bad.c#L86-L91) · [✅ Good example](../examples/r20/good.c#L69-L71)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 20.11 · 🟧 Required

**A parameter right after `#` must not be followed by `##`.**

**Why:** Which operator applies first is unspecified.

[❌ Bad example](../examples/r20/bad.c#L93-L95) · [✅ Good example](../examples/r20/good.c#L73-L75)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 20.12 · 🟧 Required

**A parameter used with `#` or `##` that would otherwise be macro-expanded must only be used with those operators.**

**Why:** Otherwise the same parameter expands in one place and not in the other.

[❌ Bad example](../examples/r20/bad.c#L97-L100) · [✅ Good example](../examples/r20/good.c#L77-L80)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 20.13 · 🟧 Required

**A line starting with `#` must be a valid preprocessing directive.**

**Why:** Typos like `#esle` in skipped code go unreported until the code is enabled.

[❌ Bad example](../examples/r20/bad.c#L102-L107) · [✅ Good example](../examples/r20/good.c#L82-L86)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 20.14 · 🟧 Required

**`#else`, `#elif` and `#endif` must be in the same file as their `#if`.**

**Why:** Conditionals spanning files are unreadable and fragile.

[❌ Bad example](../examples/r20/bad.c#L109-L118) · [✅ Good example](../examples/r20/good.c#L88-L90)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

<sub>[◀ Previous](09-functions-pointers-arrays.md) · [Contents](README.md) · [Next ▶](11-library-and-resources.md)</sub>
