<sub>[◀ Previous](05-essential-type-model.md) · [Contents](README.md) · [Next ▶](07-expressions-and-side-effects.md)</sub>

# Part 6: Rule 11, pointer type conversions

**A pointer should only ever be treated as the type it really points to.**


---

## Why pointer casts are dangerous

- **Alignment:** a `uint32_t *` pointing at an odd address faults on many CPUs (Arm Cortex-M0, many DSPs).
- **Strict aliasing:** the optimiser assumes a `float *` and a `uint32_t *` never point at the same memory, so a cast can make code read stale values.
- **Representation:** function and data pointers can have different sizes (Harvard architectures), and integers may not hold a pointer.
- **Qualifiers:** casting away `const` or `volatile` lets you write read-only memory or lets the compiler remove hardware accesses.

| Conversion | Rule | Category |
|---|---|---|
| function pointer ↔ anything | 11.1 | 🟧 R |
| incomplete-type pointer ↔ anything | 11.2 | 🟧 R |
| object pointer → different object pointer | 11.3 | 🟧 R |
| object pointer ↔ integer | 11.4 | 🟦 A |
| `void *` → object pointer | 11.5 | 🟦 A |
| `void *` ↔ arithmetic | 11.6 | 🟧 R |
| object pointer ↔ non-integer arithmetic | 11.7 | 🟧 R |
| removing `const` / `volatile` | 11.8 | 🟧 R |
| `0` as a null pointer | 11.9 | 🟧 R |


---

## Chapter 11: Pointer type conversions

Code: [`examples/r11/`](../examples/r11)


---

### Rule 11.1 · 🟧 Required

**Don't convert between function pointers and any other type.**

**Why:** Code and data pointers can differ in size and address space. The result is undefined.

[❌ Bad example](../examples/r11/bad.c#L9-L20) · [✅ Good example](../examples/r11/good.c#L10-L22)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 11.2 · 🟧 Required

**Don't convert between a pointer to an incomplete type and any other type.**

**Why:** An incomplete (opaque) type's layout is unknown by design, so converting it defeats encapsulation.

[❌ Bad example](../examples/r11/bad.c#L22-L31) · [✅ Good example](../examples/r11/good.c#L24-L34)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 11.3 · 🟧 Required

**Don't cast between pointers to different object types.**

**Why:** This can produce misaligned access (a hardware fault on many CPUs) and breaks strict aliasing.

[❌ Bad example](../examples/r11/bad.c#L33-L40) · [✅ Good example](../examples/r11/good.c#L36-L46)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 11.4 · 🟦 Advisory

**Don't convert between pointers and integers.**

**Why:** The mapping is implementation-defined. Memory-mapped I/O usually needs it, so confine it to one place under a documented deviation.

[❌ Bad example](../examples/r11/bad.c#L42-L49) · [✅ Good example](../examples/r11/good.c#L48-L58)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 11.5 · 🟦 Advisory

**Don't convert from `void *` to a pointer to an object.**

**Why:** Nothing checks that the memory really holds that type, so prefer typed interfaces.

[❌ Bad example](../examples/r11/bad.c#L51-L58) · [✅ Good example](../examples/r11/good.c#L60-L65)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 11.6 · 🟧 Required

**Don't cast between `void *` and an arithmetic type.**

**Why:** The result is implementation-defined, and hides pointer arithmetic in integer maths.

[❌ Bad example](../examples/r11/bad.c#L60-L66) · [✅ Good example](../examples/r11/good.c#L67-L72)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 11.7 · 🟧 Required

**Don't cast between an object pointer and a non-integer arithmetic type.**

**Why:** Casting a pointer to `float` or `bool` has no meaningful result. Compare with `NULL` instead.

[❌ Bad example](../examples/r11/bad.c#L68-L73) · [✅ Good example](../examples/r11/good.c#L74-L79)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 11.8 · 🟧 Required

**Don't cast away `const` or `volatile`.**

**Why:** Writing to a const object is undefined behaviour, and dropping `volatile` lets the compiler remove hardware accesses.

[❌ Bad example](../examples/r11/bad.c#L75-L82) · [✅ Good example](../examples/r11/good.c#L81-L89)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 11.9 · 🟧 Required

**Use `NULL` as the only form of integer null pointer constant.**

**Why:** `p = 0` looks like integer arithmetic. `NULL` states the intent.

[❌ Bad example](../examples/r11/bad.c#L84-L90) · [✅ Good example](../examples/r11/good.c#L91-L97)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

<sub>[◀ Previous](05-essential-type-model.md) · [Contents](README.md) · [Next ▶](07-expressions-and-side-effects.md)</sub>
