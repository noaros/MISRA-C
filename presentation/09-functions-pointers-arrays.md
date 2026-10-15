<sub>[◀ Previous](08-control-flow.md) · [Contents](README.md) · [Next ▶](10-preprocessor.md)</sub>

# Part 9: Rules 17–19, functions, pointers and arrays

**Typed interfaces, bounded stacks, every result checked, and memory accessed only inside its object.**


---

## Chapter 17: Functions

Two big ideas: **every call is type-checked** (no implicit declarations, no variadics) and **stack usage is bounded** (no recursion, see also VLAs in Rule 18.8).

Code: [`examples/r17/`](../examples/r17)


---

### Rule 17.1 · 🟧 Required

**Don't use `<stdarg.h>` (variadic functions).**

**Why:** Variable argument lists are not type-checked, and a mismatch is undefined behaviour.

[❌ Bad example](../examples/r17/bad.c#L8-L23) · [✅ Good example](../examples/r17/good.c#L8-L19)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 17.2 · 🟧 Required

**Functions must not call themselves, directly or indirectly.**

**Why:** Recursion makes stack usage depend on input data, which can't be bounded statically.

[❌ Bad example](../examples/r17/bad.c#L25-L36) · [✅ Good example](../examples/r17/good.c#L21-L32)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 17.3 · 🟥 Mandatory

**Don't call a function without a declaration in scope.**

**Why:** Implicit declarations assume an `int` return and unchecked arguments (invalid since C99).

[❌ Bad example](../examples/r17/bad.c#L38-L47) · [✅ Good example](../examples/r17/good.c#L34-L46)

<sub>🔎 cppcheck 2.13: not analysed: compilers reject this example, so it is disabled</sub>


---

### Rule 17.4 · 🟥 Mandatory

**Every exit from a non-void function must return a value explicitly.**

**Why:** Falling off the end and using the result is undefined behaviour.

[❌ Bad example](../examples/r17/bad.c#L49-L58) · [✅ Good example](../examples/r17/good.c#L48-L58)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 17.5 · 🟦 Advisory

**An array argument must have at least as many elements as the parameter declares.**

**Why:** Passing a shorter array leads to out-of-bounds reads that the compiler won't flag.

[❌ Bad example](../examples/r17/bad.c#L60-L71) · [✅ Good example](../examples/r17/good.c#L60-L74)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 17.6 · 🟥 Mandatory

**Don't use `static` inside the `[]` of an array parameter.**

**Why:** `int a[static 4]` is a promise the caller can break, giving undefined behaviour.

[❌ Bad example](../examples/r17/bad.c#L73-L79) · [✅ Good example](../examples/r17/good.c#L76-L81)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 17.7 · 🟧 Required

**Use the return value of a non-void function (or cast it to `(void)`).**

**Why:** Silently ignored results hide errors. The `(void)` cast makes discarding a visible decision.

[❌ Bad example](../examples/r17/bad.c#L81-L91) · [✅ Good example](../examples/r17/good.c#L83-L99)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 17.8 · 🟦 Advisory

**Don't modify a function parameter.**

**Why:** Readers expect a parameter to hold the caller's value throughout. Work on a local copy.

[❌ Bad example](../examples/r17/bad.c#L93-L100) · [✅ Good example](../examples/r17/good.c#L101-L107)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

## Chapter 18: Pointers and arrays

Pointer arithmetic is only defined **within one array object** (plus one-past-the-end). Most of these rules spell out that boundary; the advisory ones nudge you towards array indexing, which is easier to check.

Code: [`examples/r18/`](../examples/r18)


---

### Rule 18.1 · 🟧 Required

**Pointer arithmetic must stay within the same array.**

**Why:** Even forming a pointer beyond one-past-the-end is undefined, before any dereference.

[❌ Bad example](../examples/r18/bad.c#L8-L16) · [✅ Good example](../examples/r18/good.c#L11-L22)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 18.2 · 🟧 Required

**Only subtract pointers that point into the same array.**

**Why:** Subtracting unrelated pointers is undefined behaviour.

[❌ Bad example](../examples/r18/bad.c#L18-L25) · [✅ Good example](../examples/r18/good.c#L24-L34)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 18.3 · 🟧 Required

**Only use `<`, `<=`, `>`, `>=` on pointers into the same object.**

**Why:** The ordering of unrelated objects in memory is meaningless and undefined.

[❌ Bad example](../examples/r18/bad.c#L27-L35) · [✅ Good example](../examples/r18/good.c#L36-L44)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 18.4 · 🟦 Advisory

**Don't use `+`, `-`, `+=`, `-=` on pointers.**

**Why:** Array indexing (`p[i]`) is clearer and easier to bounds-check.

[❌ Bad example](../examples/r18/bad.c#L37-L45) · [✅ Good example](../examples/r18/good.c#L46-L51)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 18.5 · 🟦 Advisory

**Use at most two levels of pointer nesting.**

**Why:** `int ***p` is hard to read, review and get right.

[❌ Bad example](../examples/r18/bad.c#L47-L52) · [✅ Good example](../examples/r18/good.c#L53-L58)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 18.6 · 🟧 Required

**Don't let the address of an automatic object outlive it.**

**Why:** Returning or storing a pointer to a local creates a dangling pointer.

[❌ Bad example](../examples/r18/bad.c#L54-L63) · [✅ Good example](../examples/r18/good.c#L60-L66)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 18.7 · 🟧 Required

**Don't declare flexible array members.**

**Why:** They usually imply dynamic allocation, and copying the struct silently drops the array.

[❌ Bad example](../examples/r18/bad.c#L65-L72) · [✅ Good example](../examples/r18/good.c#L68-L81)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 18.8 · 🟧 Required

**Don't use variable-length arrays.**

**Why:** Stack usage depends on a run-time value, and a large size overflows the stack silently.

[❌ Bad example](../examples/r18/bad.c#L74-L82) · [✅ Good example](../examples/r18/good.c#L83-L97)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

## Chapter 19: Overlapping storage

Code: [`examples/r19/`](../examples/r19)


---

### Rule 19.1 · 🟥 Mandatory

**Don't assign or copy an object to an overlapping object.**

**Why:** Overlapping `memcpy` or union member copies are undefined behaviour.

[❌ Bad example](../examples/r19/bad.c#L8-L15) · [✅ Good example](../examples/r19/good.c#L8-L14)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 19.2 · 🟦 Advisory

**Don't use `union`.**

**Why:** Reading a member other than the one last written depends on representation (endianness, padding).

[❌ Bad example](../examples/r19/bad.c#L17-L31) · [✅ Good example](../examples/r19/good.c#L16-L42)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

<sub>[◀ Previous](08-control-flow.md) · [Contents](README.md) · [Next ▶](10-preprocessor.md)</sub>
