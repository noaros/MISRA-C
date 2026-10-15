<sub>[◀ Previous](00-big-picture.md) · [Contents](README.md) · [Next ▶](02-environment-and-hygiene.md)</sub>

# Part 1: The directives

**Dir 1.1 – Dir 4.14**: guidelines about the *process around* the code (documentation, requirements, design) as well as the code itself.


---

## The directive groups

| Group | Topic | Directives |
|---|---|---|
| 1 | The implementation | Dir 1.1 |
| 2 | Compilation and build | Dir 2.1 |
| 3 | Requirements traceability | Dir 3.1 |
| 4 | Code design | Dir 4.1 – 4.14 |

You can't fully check directives by looking at a `.c` file. They need **evidence**: compiler documentation, requirement IDs, design reviews. The example files show what that evidence looks like in code.

Code: [`examples/dir/bad.c`](../examples/dir/bad.c) · [`examples/dir/good.c`](../examples/dir/good.c) · headers [`bad.h`](../examples/dir/bad.h) / [`good.h`](../examples/dir/good.h)


---

### Dir 1.1 · 🟧 Required

**Document every implementation-defined behaviour your code relies on.**

**Why:** C leaves many details to the compiler (sizes of types, signedness of `char`, right-shift of negative values). If the code depends on them, the assumptions must be written down and checked, or the program silently changes meaning on another compiler.

[❌ Bad example](../examples/dir/bad.c#L11-L22) · [✅ Good example](../examples/dir/good.c#L12-L24)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 2.1 · 🟧 Required

**The code must compile with no errors.**

**Why:** A compiler that 'accepts with errors' (or a build that ignores them) produces a program whose meaning is undefined. Clean builds are the floor every other guideline stands on.

[❌ Bad example](../examples/dir/bad.c#L24-L33) · [✅ Good example](../examples/dir/good.c#L26-L28)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 3.1 · 🟧 Required

**All code must trace back to documented requirements.**

**Why:** Code with no requirement behind it is either untested, unnecessary, or a hidden requirement. Traceability is what lets reviewers and auditors argue that the software does what it should and nothing else.

[❌ Bad example](../examples/dir/bad.c#L35-L40) · [✅ Good example](../examples/dir/good.c#L30-L38)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.1 · 🟧 Required

**Minimise the chance of run-time failures.**

**Why:** Division by zero, overflow, out-of-bounds access and null dereferences crash or corrupt critical systems. Prevent them by design (checks, ranges, defensive code) and show how in your documentation.

[❌ Bad example](../examples/dir/bad.c#L42-L47) · [✅ Good example](../examples/dir/good.c#L40-L50)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.2 · 🟦 Advisory

**Document any assembly language.**

**Why:** Assembly bypasses the C type system and every tool that checks it. Reviewers need to know why it is there and what it does.

[❌ Bad example](../examples/dir/bad.c#L49-L54) · [✅ Good example](../examples/dir/good.c#L52-L60)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.3 · 🟧 Required

**Keep assembly encapsulated and isolated, never mixed into C logic.**

**Why:** Inline assembly scattered through C code is unanalysable and unportable. Wrapping it in small, documented functions or macros keeps the rest of the code checkable.

[❌ Bad example](../examples/dir/bad.c#L56-L65) · [✅ Good example](../examples/dir/good.c#L62-L68)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.4 · 🟦 Advisory

**Don't leave code commented out.**

**Why:** Commented-out code is ambiguous: dead, temporary or a forgotten fix? Delete it (version control remembers) or control it with a documented configuration switch.

[❌ Bad example](../examples/dir/bad.c#L67-L74) · [✅ Good example](../examples/dir/good.c#L70-L76)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.5 · 🟦 Advisory

**Names in the same scope should not look alike.**

**Why:** `l1`, `ll` and `lI`, or `O0` and `OO`, are easily confused when reading or reviewing, which leads to using the wrong variable.

[❌ Bad example](../examples/dir/bad.c#L76-L85) · [✅ Good example](../examples/dir/good.c#L78-L85)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.6 · 🟦 Advisory

**Use fixed-size typedefs (e.g. `int32_t`) instead of basic numeric types.**

**Why:** `int` and `long` change size between targets. Fixed-width types make the size and signedness explicit, which the essential type rules depend on.

[❌ Bad example](../examples/dir/bad.c#L87-L93) · [✅ Good example](../examples/dir/good.c#L87-L92)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.7 · 🟧 Required

**If a function returns error information, test it.**

**Why:** An ignored error code means execution continues with invalid data. Every failure path must be handled, or deliberately and visibly discarded.

[❌ Bad example](../examples/dir/bad.c#L95-L113) · [✅ Good example](../examples/dir/good.c#L94-L115)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.8 · 🟦 Advisory

**Hide the definition of a struct/union if users only need a pointer to it.**

**Why:** Opaque types stop other modules depending on (and corrupting) internal fields, which keeps interfaces small and changes local.

[❌ Bad example](../examples/dir/bad.c#L115-L123) · [✅ Good example](../examples/dir/good.c#L117-L134)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.9 · 🟦 Advisory

**Prefer functions to function-like macros where either would work.**

**Why:** Functions check argument types, evaluate each argument exactly once and respect scope. Macros do none of that.

[❌ Bad example](../examples/dir/bad.c#L125-L132) · [✅ Good example](../examples/dir/good.c#L136-L141)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.10 · 🟧 Required

**Guard every header against multiple inclusion.**

**Why:** Including a header twice redefines types and objects, which is a compile error at best and an ODR-style inconsistency at worst.

[❌ Bad example](../examples/dir/bad.c#L134-L135) · [✅ Good example](../examples/dir/good.c#L143-L144)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.11 · 🟧 Required

**Check that values passed to library functions are valid.**

**Why:** Library functions have domains (`sqrt` of a negative, `strlen(NULL)`). Outside them the behaviour is undefined, so the caller must check.

[❌ Bad example](../examples/dir/bad.c#L137-L142) · [✅ Good example](../examples/dir/good.c#L146-L156)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.12 · 🟧 Required

**Don't use dynamic memory allocation.**

**Why:** Heap allocation can fail, fragment memory, leak, and take unbounded time, all of which are hard to rule out in a system that must keep running.

[❌ Bad example](../examples/dir/bad.c#L144-L149) · [✅ Good example](../examples/dir/good.c#L158-L166)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.13 · 🟦 Advisory

**Call functions that operate on a resource in the right sequence.**

**Why:** Open, use, close; init before use. APIs should make the correct order obvious and detect misuse.

[❌ Bad example](../examples/dir/bad.c#L151-L160) · [✅ Good example](../examples/dir/good.c#L168-L185)

<sub>Checked by review and process, not by cppcheck.</sub>


---

### Dir 4.14 · 🟧 Required

**Check the validity of values received from external sources.**

**Why:** Input from networks, files, sensors or users may be wrong or malicious. Validate it before it controls indices, sizes or behaviour (added by Amendment 1, the security amendment).

[❌ Bad example](../examples/dir/bad.c#L162-L170) · [✅ Good example](../examples/dir/good.c#L187-L201)

<sub>Checked by review and process, not by cppcheck.</sub>


---

<sub>[◀ Previous](00-big-picture.md) · [Contents](README.md) · [Next ▶](02-environment-and-hygiene.md)</sub>
