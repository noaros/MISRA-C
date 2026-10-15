<sub>[◀ Previous](02-environment-and-hygiene.md) · [Contents](README.md) · [Next ▶](04-declarations-and-initialization.md)</sub>

# Part 3: Rules 5–7, names, bit-fields and literals

**Every name should mean one thing, and every constant should say exactly what type and value it has.**


---

## Chapter 5: Identifiers

C only guarantees a limited number of **significant characters** in identifiers (C99: 31 for external names, 63 for internal names and macros). Beyond that, two "different" names can be the *same* name. Separately, reusing a name in a different scope or name space is legal but confusing.

**Fix pattern:** short, module-prefixed names (`egt_sensor1`, `uart_init`), and never reuse a name.

Code: [`examples/r05/`](../examples/r05)


---

### Rule 5.1 · 🟧 Required

**External identifiers must be distinct (within the significant characters C guarantees).**

**Why:** C99 only guarantees 31 significant characters for external names. Names that differ later may link as the same object.

[❌ Bad example](../examples/r05/bad.c#L7-L12) · [✅ Good example](../examples/r05/good.c#L7-L16)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 5.2 · 🟧 Required

**Identifiers in the same scope and name space must be distinct.**

**Why:** Beyond the significance limit (63 characters in C99) the compiler may treat two names as one.

[❌ Bad example](../examples/r05/bad.c#L14-L23) · [✅ Good example](../examples/r05/good.c#L18-L25)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 5.3 · 🟧 Required

**Don't let an inner-scope identifier hide an outer one.**

**Why:** Shadowing makes it unclear which object an expression refers to, so edits update the wrong variable.

[❌ Bad example](../examples/r05/bad.c#L25-L34) · [✅ Good example](../examples/r05/good.c#L27-L36)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 5.4 · 🟧 Required

**Macro identifiers must be distinct.**

**Why:** Macro names beyond the significance limit may collide, so one silently redefines another.

[❌ Bad example](../examples/r05/bad.c#L36-L39) · [✅ Good example](../examples/r05/good.c#L38-L41)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 5.5 · 🟧 Required

**Identifiers must be distinct from macro names.**

**Why:** A name that is both a macro and an object changes meaning depending on whether `(` follows it.

[❌ Bad example](../examples/r05/bad.c#L41-L50) · [✅ Good example](../examples/r05/good.c#L43-L51)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 5.6 · 🟧 Required

**A typedef name must be unique.**

**Why:** Reusing a typedef name for anything else makes declarations ambiguous to readers.

[❌ Bad example](../examples/r05/bad.c#L52-L60) · [✅ Good example](../examples/r05/good.c#L53-L61)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 5.7 · 🟧 Required

**A struct/union/enum tag name must be unique.**

**Why:** Tags live in their own name space, so reuse compiles but confuses readers and tools.

[❌ Bad example](../examples/r05/bad.c#L62-L69) · [✅ Good example](../examples/r05/good.c#L63-L74)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 5.8 · 🟧 Required

**Identifiers with external linkage must be unique across the program.**

**Why:** Reusing a global name locally hides it and invites calling the wrong thing.

[❌ Bad example](../examples/r05/bad.c#L71-L82) · [✅ Good example](../examples/r05/good.c#L76-L83)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 5.9 · 🟦 Advisory

**Identifiers with internal linkage should be unique across the program.**

**Why:** Two `static` objects with the same name in different files look like one shared variable to a reader.

[❌ Bad example](../examples/r05/bad.c#L84-L94) · [✅ Good example](../examples/r05/good.c#L85-L93)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

## Chapter 6: Types

Bit-fields are full of implementation-defined behaviour. MISRA restricts them to types whose behaviour is well-defined.

Code: [`examples/r06/`](../examples/r06)


---

### Rule 6.1 · 🟧 Required

**Bit-fields may only use appropriate types (signed/unsigned int, `_Bool`).**

**Why:** Plain `int` bit-fields have implementation-defined signedness, and other types are implementation-defined in C99.

[❌ Bad example](../examples/r06/bad.c#L7-L15) · [✅ Good example](../examples/r06/good.c#L8-L21)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 6.2 · 🟧 Required

**A single-bit named bit-field must not be signed.**

**Why:** A signed 1-bit field holds only 0 and -1, so `flag = 1` doesn't store 1.

[❌ Bad example](../examples/r06/bad.c#L17-L29) · [✅ Good example](../examples/r06/good.c#L23-L35)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

## Chapter 7: Literals and constants

Literals should state their value and type plainly: no octal, no hidden unsigned types, no `l` that looks like `1`, and string literals are read-only.

Code: [`examples/r07/`](../examples/r07)


---

### Rule 7.1 · 🟧 Required

**Don't use octal constants.**

**Why:** `010` is 8. A leading zero for alignment silently changes the value.

[❌ Bad example](../examples/r07/bad.c#L7-L14) · [✅ Good example](../examples/r07/good.c#L8-L15)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 7.2 · 🟧 Required

**Use a `U` suffix on integer constants that have unsigned type.**

**Why:** `0x80000000` is unsigned on a 32-bit target but signed on a 64-bit `long` one. The suffix makes the type explicit and portable.

[❌ Bad example](../examples/r07/bad.c#L16-L22) · [✅ Good example](../examples/r07/good.c#L17-L22)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 7.3 · 🟧 Required

**Don't use a lowercase `l` suffix.**

**Why:** `10l` looks like `101`.

[❌ Bad example](../examples/r07/bad.c#L24-L29) · [✅ Good example](../examples/r07/good.c#L24-L29)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 7.4 · 🟧 Required

**Only assign a string literal to a pointer to const char.**

**Why:** Literals may live in read-only memory. Writing through a non-const pointer is undefined behaviour.

[❌ Bad example](../examples/r07/bad.c#L31-L39) · [✅ Good example](../examples/r07/good.c#L31-L40)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

<sub>[◀ Previous](02-environment-and-hygiene.md) · [Contents](README.md) · [Next ▶](04-declarations-and-initialization.md)</sub>
