<sub>[◀ Previous](01-directives.md) · [Contents](README.md) · [Next ▶](03-identifiers-types-literals.md)</sub>

# Part 2: Rules 1–4, the basics

**Speak only standard C, keep the code free of clutter, and avoid lexical traps.**


---

## Chapter 1: The standard C environment

These rules set the ground: the program must be **valid standard C** with **no undefined behaviour**. Rule 1.3 is the "umbrella" rule, and much of the rest of MISRA exists to make it achievable in practice.

Code: [`examples/r01/`](../examples/r01)


---

### Rule 1.1 · 🟧 Required

**Stay within standard C: no syntax or constraint violations, no exceeding translation limits.**

**Why:** Anything outside the standard has no defined meaning. Compilers may accept it differently, or not at all.

[❌ Bad example](../examples/r01/bad.c#L7-L18) · [✅ Good example](../examples/r01/good.c#L8-L15)

<sub>🔎 cppcheck 2.13: not analysed: compilers reject this example, so it is disabled</sub>


---

### Rule 1.2 · 🟦 Advisory

**Don't use language extensions.**

**Why:** Extensions (GNU statement expressions, `__attribute__`, case ranges) tie code to one compiler and are often poorly specified.

[❌ Bad example](../examples/r01/bad.c#L20-L35) · [✅ Good example](../examples/r01/good.c#L17-L27)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 1.3 · 🟧 Required

**No undefined or critical unspecified behaviour.**

**Why:** Undefined behaviour means the compiler may do anything: crash, appear to work, or optimise away your checks. This rule is the heart of MISRA, and many other rules exist to make it achievable.

[❌ Bad example](../examples/r01/bad.c#L37-L47) · [✅ Good example](../examples/r01/good.c#L29-L40)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 1.4 · 🟧 Required

**Don't use 'emergent' language features (from C11 onwards) that the guidelines don't yet cover.**

**Why:** Newer features like `_Noreturn`, `_Generic` and threads were not yet trusted by Amendment 2. MISRA C:2023 replaces this blanket ban with specific rules for each feature.

[❌ Bad example](../examples/r01/bad.c#L49-L58) · [✅ Good example](../examples/r01/good.c#L42-L51)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

## Chapter 2: Unused code

Unused and unreachable code is never harmless. At best it's noise; often it's **evidence of a bug** (a misplaced `return`, a forgotten variable). Safety standards also require every line to be tested, and dead code can't be.

Code: [`examples/r02/`](../examples/r02)


---

### Rule 2.1 · 🟧 Required

**No unreachable code.**

**Why:** Code that can never run is untestable and usually signals a logic error (e.g. a misplaced `return`).

[❌ Bad example](../examples/r02/bad.c#L7-L13) · [✅ Good example](../examples/r02/good.c#L7-L17)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 2.2 · 🟧 Required

**No dead code: operations whose removal would change nothing.**

**Why:** Dead code confuses readers about intent and often hides a bug (a value computed and then forgotten).

[❌ Bad example](../examples/r02/bad.c#L15-L22) · [✅ Good example](../examples/r02/good.c#L19-L25)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 2.3 · 🟦 Advisory

**No unused type declarations.**

**Why:** Unused declarations are clutter that suggests missing code, or code removed without tidying up.

[❌ Bad example](../examples/r02/bad.c#L24-L30) · [✅ Good example](../examples/r02/good.c#L27-L34)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 2.4 · 🟦 Advisory

**No unused tag declarations.**

**Why:** As for types: an unused `struct`/`union`/`enum` tag is noise or a sign of something missing.

[❌ Bad example](../examples/r02/bad.c#L32-L37) · [✅ Good example](../examples/r02/good.c#L36-L47)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 2.5 · 🟦 Advisory

**No unused macros.**

**Why:** Unused macros mislead readers into thinking they configure something.

[❌ Bad example](../examples/r02/bad.c#L39-L41) · [✅ Good example](../examples/r02/good.c#L49-L56)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 2.6 · 🟦 Advisory

**No unused labels.**

**Why:** A label nobody jumps to is a leftover. It may even indicate that a `goto` was mistyped.

[❌ Bad example](../examples/r02/bad.c#L43-L49) · [✅ Good example](../examples/r02/good.c#L58-L63)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 2.7 · 🟦 Advisory

**No unused function parameters.**

**Why:** An unused parameter suggests the function is not doing what its interface promises.

[❌ Bad example](../examples/r02/bad.c#L51-L56) · [✅ Good example](../examples/r02/good.c#L65-L71)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

## Chapter 3: Comments

Two small rules that prevent code from silently disappearing into comments.

Code: [`examples/r03/`](../examples/r03)


---

### Rule 3.1 · 🟧 Required

**Don't write `/*` or `//` inside a comment.**

**Why:** A nested `/*` usually means a missing `*/`: code you think is live is actually commented out, or the other way round.

[❌ Bad example](../examples/r03/bad.c#L7-L16) · [✅ Good example](../examples/r03/good.c#L7-L14)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 3.2 · 🟧 Required

**No line-splicing (trailing backslash) in `//` comments.**

**Why:** A `\` at the end of a `//` comment silently pulls the next line into the comment, deleting a statement.

[❌ Bad example](../examples/r03/bad.c#L18-L27) · [✅ Good example](../examples/r03/good.c#L16-L24)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

## Chapter 4: Character sets and lexical conventions

Character-level traps that change what the compiler sees compared with what you wrote.

Code: [`examples/r04/`](../examples/r04)


---

### Rule 4.1 · 🟧 Required

**Terminate octal and hexadecimal escape sequences.**

**Why:** `"\x41BC"` is one escape (0x41BC), not `"ABC"`. Ending an escape at the end of the literal or with another escape removes the ambiguity.

[❌ Bad example](../examples/r04/bad.c#L7-L14) · [✅ Good example](../examples/r04/good.c#L7-L13)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 4.2 · 🟦 Advisory

**Don't use trigraphs.**

**Why:** `??/` becomes `\` and `??-` becomes `~` before the compiler sees your string, so text silently changes.

[❌ Bad example](../examples/r04/bad.c#L16-L22) · [✅ Good example](../examples/r04/good.c#L15-L20)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

<sub>[◀ Previous](01-directives.md) · [Contents](README.md) · [Next ▶](03-identifiers-types-literals.md)</sub>
