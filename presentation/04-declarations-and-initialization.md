<sub>[◀ Previous](03-identifiers-types-literals.md) · [Contents](README.md) · [Next ▶](05-essential-type-model.md)</sub>

# Part 4: Rules 8–9, declarations and initialization

**One declaration in one header, one definition, the smallest possible scope, and everything initialised before use.**


---

## The declaration pattern MISRA wants

```c
/* module.h: the ONLY place external names are declared (8.4, 8.5) */
#ifndef MODULE_H
#define MODULE_H
#include <stdint.h>
#define TABLE_SIZE 4U
extern int32_t module_counter;                    /* declared once */
extern const int32_t module_table[TABLE_SIZE];    /* with its size (8.11) */
int32_t module_read(uint8_t channel);             /* prototype, named params (8.2) */
#endif

/* module.c */
#include "module.h"              /* definitions checked against declarations */
int32_t module_counter = 0;      /* the one definition (8.6) */
static int32_t helper(void);     /* private: static (8.7, 8.8) */
```

See it in action: [`examples/r08/good.h`](../examples/r08/good.h) + [`examples/r08/good.c`](../examples/r08/good.c)


---

## Chapter 8: Declarations and definitions

Most of these rules ensure that **the compiler can check every use of a name against one authoritative declaration**, and that names are visible only where needed.

Code: [`examples/r08/`](../examples/r08)


---

### Rule 8.1 · 🟧 Required

**State types explicitly: no implicit `int`.**

**Why:** C90's implicit `int` hides mistakes and is invalid in C99.

[❌ Bad example](../examples/r08/bad.c#L7-L13) · [✅ Good example](../examples/r08/good.c#L8-L15)

<sub>🔎 cppcheck 2.13: not analysed: compilers reject this example, so it is disabled</sub>


---

### Rule 8.2 · 🟧 Required

**Use prototype form for functions, with named parameters.**

**Why:** `f()` means 'unknown parameters', so arguments are not checked. Names document meaning.

[❌ Bad example](../examples/r08/bad.c#L15-L22) · [✅ Good example](../examples/r08/good.c#L17-L31)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 8.3 · 🟧 Required

**All declarations of an object or function must use the same names and qualifiers.**

**Why:** If a header says `(width, height)` and the definition says `(height, width)`, callers will pass them the wrong way round.

[❌ Bad example](../examples/r08/bad.c#L24-L32) · [✅ Good example](../examples/r08/good.c#L33-L40)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 8.4 · 🟧 Required

**A compatible declaration must be visible where an external object or function is defined.**

**Why:** Including the header in its own .c file lets the compiler check that declaration and definition agree.

[❌ Bad example](../examples/r08/bad.c#L34-L37) · [✅ Good example](../examples/r08/good.c#L42-L45)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 8.5 · 🟧 Required

**Declare an external object or function once, in one file (a header).**

**Why:** Repeated `extern` declarations in .c files drift out of sync with the definition.

[❌ Bad example](../examples/r08/bad.c#L39-L43) · [✅ Good example](../examples/r08/good.c#L47-L48)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 8.6 · 🟧 Required

**An external identifier must have exactly one definition.**

**Why:** Zero definitions fail to link. Two may silently merge or conflict depending on the toolchain.

[❌ Bad example](../examples/r08/bad.c#L45-L53) · [✅ Good example](../examples/r08/good.c#L50-L52)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 8.7 · 🟦 Advisory

**Don't give external linkage to things used in only one translation unit.**

**Why:** Use `static`: it shrinks the global namespace and makes dependencies explicit.

[❌ Bad example](../examples/r08/bad.c#L55-L62) · [✅ Good example](../examples/r08/good.c#L54-L59)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 8.8 · 🟧 Required

**Use `static` on every declaration of an internal-linkage object or function.**

**Why:** If the definition omits `static`, readers think it is global.

[❌ Bad example](../examples/r08/bad.c#L64-L72) · [✅ Good example](../examples/r08/good.c#L61-L68)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 8.9 · 🟦 Advisory

**Define an object at block scope if it's used in only one function.**

**Why:** Narrow scope means fewer places can modify it, and reasoning stays local.

[❌ Bad example](../examples/r08/bad.c#L74-L82) · [✅ Good example](../examples/r08/good.c#L70-L76)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 8.10 · 🟧 Required

**Declare inline functions `static`.**

**Why:** C99's rules for non-static inline functions are subtle and differ between compilers and linkers.

[❌ Bad example](../examples/r08/bad.c#L84-L90) · [✅ Good example](../examples/r08/good.c#L78-L83)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 8.11 · 🟦 Advisory

**Give an explicit size when declaring an external array.**

**Why:** `extern int t[];` lets nobody check bounds against the real size.

[❌ Bad example](../examples/r08/bad.c#L92-L94) · [✅ Good example](../examples/r08/good.c#L85-L86)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 8.12 · 🟧 Required

**Implicitly valued enumerators must not duplicate other enumerator values.**

**Why:** Mixing explicit and implicit values can give two names the same value without anyone noticing.

[❌ Bad example](../examples/r08/bad.c#L96-L99) · [✅ Good example](../examples/r08/good.c#L88-L90)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 8.13 · 🟦 Advisory

**Point to const whenever possible.**

**Why:** `const` documents and enforces read-only access, and catches accidental writes at compile time.

[❌ Bad example](../examples/r08/bad.c#L101-L112) · [✅ Good example](../examples/r08/good.c#L92-L103)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 8.14 · 🟧 Required

**Don't use `restrict`.**

**Why:** `restrict` is an unchecked promise of no aliasing. Breaking it is undefined behaviour the compiler will optimise on.

[❌ Bad example](../examples/r08/bad.c#L114-L120) · [✅ Good example](../examples/r08/good.c#L105-L110)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

## Chapter 9: Initialization

Reading uninitialised memory is one of C's most common sources of non-reproducible bugs. These rules make initialisation complete and unambiguous.

Code: [`examples/r09/`](../examples/r09)


---

### Rule 9.1 · 🟥 Mandatory

**Don't read an automatic variable before it has been set.**

**Why:** Uninitialised locals hold indeterminate values, which can be different on every run and are undefined behaviour in some cases.

[❌ Bad example](../examples/r09/bad.c#L7-L18) · [✅ Good example](../examples/r09/good.c#L7-L17)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 9.2 · 🟧 Required

**Enclose initializers for aggregates and unions in braces.**

**Why:** Braces that mirror the structure make it obvious which value goes where.

[❌ Bad example](../examples/r09/bad.c#L20-L26) · [✅ Good example](../examples/r09/good.c#L19-L25)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 9.3 · 🟧 Required

**Don't partially initialize arrays.**

**Why:** Was the rest forgotten? `{ 0 }` (zero everything) and designated initializers are the allowed exceptions.

[❌ Bad example](../examples/r09/bad.c#L28-L34) · [✅ Good example](../examples/r09/good.c#L27-L35)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 9.4 · 🟧 Required

**Don't initialize the same element more than once.**

**Why:** With designated initializers the last one silently wins, which is almost always a mistake.

[❌ Bad example](../examples/r09/bad.c#L36-L42) · [✅ Good example](../examples/r09/good.c#L37-L43)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 9.5 · 🟧 Required

**When using designated initializers for an array, state its size.**

**Why:** Otherwise the array size depends on the highest index used, which is easy to change by accident.

[❌ Bad example](../examples/r09/bad.c#L44-L51) · [✅ Good example](../examples/r09/good.c#L45-L51)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

<sub>[◀ Previous](03-identifiers-types-literals.md) · [Contents](README.md) · [Next ▶](05-essential-type-model.md)</sub>
