<sub>[◀ Previous](10-preprocessor.md) · [Contents](README.md) · [Next ▶](12-beyond-c2012.md)</sub>

# Part 11: Rules 21–22, the standard library and resources

**Much of the C standard library is unsuitable for critical systems. What remains must be used carefully.**


---

## The banned list

| Banned | Rule | Use instead |
|---|---|---|
| `malloc`, `calloc`, `realloc`, `free` | 21.3 | Static allocation, fixed pools |
| `<setjmp.h>` | 21.4 | Error codes returned up the call chain |
| `<signal.h>` | 21.5 | Platform interrupt handling (documented) |
| `<stdio.h>` | 21.6 | Project drivers with typed interfaces |
| `atof`, `atoi`, `atol`, `atoll` | 21.7 | `strtol`/`strtod` + `errno` + end-pointer checks |
| `abort`, `exit`, ... | 21.8 | Return an error, then enter a safe state |
| `bsearch`, `qsort` | 21.9 | Simple bounded algorithms written for the job |
| `<time.h>` | 21.10 | A project clock driver |
| `<tgmath.h>` | 21.11 | Type-specific `<math.h>` functions (`sqrtf`) |
| `<fenv.h>` exceptions | 21.12 | Check operands before the operation |
| `system` | 21.21 | Call the functionality directly |

Projects that genuinely need `stdio` or `malloc` **deviate** from 21.3 or 21.6, and then Chapter 22 governs how they're used.


---

## Chapter 21: Standard libraries

Code: [`examples/r21/`](../examples/r21)


---

### Rule 21.1 · 🟧 Required

**Don't `#define` or `#undef` reserved identifiers or macro names.**

**Why:** Names like `_BUFFER` or `__DEBUG` belong to the implementation, and redefining them is undefined behaviour.

[❌ Bad example](../examples/r21/bad.c#L16-L20) · [✅ Good example](../examples/r21/good.c#L14-L17)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.2 · 🟧 Required

**Don't declare reserved identifiers or macro names.**

**Why:** File-scope names starting with `_`, or names of standard library functions, may clash with the implementation.

[❌ Bad example](../examples/r21/bad.c#L22-L25) · [✅ Good example](../examples/r21/good.c#L19-L20)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 21.3 · 🟧 Required

**Don't use `malloc`, `calloc`, `realloc` or `free`.**

**Why:** This is the code-level counterpart of Dir 4.12: allocation failure, fragmentation, leaks and unbounded timing.

[❌ Bad example](../examples/r21/bad.c#L27-L35) · [✅ Good example](../examples/r21/good.c#L22-L53)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.4 · 🟧 Required

**Don't use `<setjmp.h>`.**

**Why:** `longjmp` bypasses normal function exits and leaves locals indeterminate.

[❌ Bad example](../examples/r21/bad.c#L37-L54) · [✅ Good example](../examples/r21/good.c#L55-L70)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.5 · 🟧 Required

**Don't use `<signal.h>`.**

**Why:** Signal handling is largely implementation-defined and has many undefined corner cases.

[❌ Bad example](../examples/r21/bad.c#L56-L67) · [✅ Good example](../examples/r21/good.c#L72-L82)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.6 · 🟧 Required

**Don't use standard I/O functions (`<stdio.h>`).**

**Why:** Their error behaviour and buffering are implementation-defined, and format strings are unchecked. Projects that need them deviate and follow Chapter 22.

[❌ Bad example](../examples/r21/bad.c#L69-L75) · [✅ Good example](../examples/r21/good.c#L84-L93)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.7 · 🟧 Required

**Don't use `atof`, `atoi`, `atol`, `atoll`.**

**Why:** They can't report errors, and overflow is undefined. Use `strtol` and friends with error checks.

[❌ Bad example](../examples/r21/bad.c#L77-L83) · [✅ Good example](../examples/r21/good.c#L95-L112)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.8 · 🟧 Required

**Don't use the termination functions (`abort`, `exit`, ...).**

**Why:** Abrupt termination skips putting the system into a safe state. The original C:2012 text also listed `getenv` and `system` here.

[❌ Bad example](../examples/r21/bad.c#L85-L96) · [✅ Good example](../examples/r21/good.c#L114-L124)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.9 · 🟧 Required

**Don't use `bsearch` or `qsort`.**

**Why:** Their behaviour with equal elements is unspecified and implementations may recurse.

[❌ Bad example](../examples/r21/bad.c#L98-L109) · [✅ Good example](../examples/r21/good.c#L126-L142)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.10 · 🟧 Required

**Don't use the time and date functions (`<time.h>`).**

**Why:** They have implementation-defined, unspecified and undefined aspects (shared static buffers, -1 on failure).

[❌ Bad example](../examples/r21/bad.c#L111-L117) · [✅ Good example](../examples/r21/good.c#L144-L151)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.11 · 🟧 Required

**Don't use `<tgmath.h>`.**

**Why:** Type-generic macros pick the real function invisibly, based on argument types.

[❌ Bad example](../examples/r21/bad.c#L119-L125) · [✅ Good example](../examples/r21/good.c#L153-L158)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.12 · 🟦 Advisory

**Don't use the exception-handling features of `<fenv.h>`.**

**Why:** Floating-point exception support varies, so prevent the exception instead of testing flags.

[❌ Bad example](../examples/r21/bad.c#L127-L137) · [✅ Good example](../examples/r21/good.c#L160-L170)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.13 · 🟥 Mandatory

**Values passed to `<ctype.h>` functions must fit in `unsigned char` (or be `EOF`).**

**Why:** A negative `char` passed to `isdigit` is undefined behaviour, a classic portability bug (Amendment 1).

[❌ Bad example](../examples/r21/bad.c#L139-L146) · [✅ Good example](../examples/r21/good.c#L172-L177)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 21.14 · 🟧 Required

**Don't use `memcmp` to compare null-terminated strings.**

**Why:** `memcmp` also compares bytes after the terminator.

[❌ Bad example](../examples/r21/bad.c#L148-L154) · [✅ Good example](../examples/r21/good.c#L179-L184)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 21.15 · 🟧 Required

**Pointer arguments to `memcpy`/`memmove`/`memcmp` must point to compatible types.**

**Why:** Copying between different types copies representations, not values.

[❌ Bad example](../examples/r21/bad.c#L156-L163) · [✅ Good example](../examples/r21/good.c#L186-L193)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.16 · 🟧 Required

**Only use `memcmp` on pointers, signed, unsigned, Boolean or enum types.**

**Why:** Structs contain padding with unspecified values, and floats have multiple representations of equal values (+0/-0).

[❌ Bad example](../examples/r21/bad.c#L165-L177) · [✅ Good example](../examples/r21/good.c#L195-L206)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.17 · 🟥 Mandatory

**String functions from `<string.h>` must not access beyond the bounds of their objects.**

**Why:** Buffer overflows corrupt memory and are a leading security vulnerability.

[❌ Bad example](../examples/r21/bad.c#L179-L185) · [✅ Good example](../examples/r21/good.c#L208-L220)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 21.18 · 🟥 Mandatory

**`size_t` arguments to `<string.h>` functions must have valid values.**

**Why:** A length larger than the object causes out-of-bounds access.

[❌ Bad example](../examples/r21/bad.c#L187-L193) · [✅ Good example](../examples/r21/good.c#L222-L228)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 21.19 · 🟥 Mandatory

**Treat pointers returned by `localeconv`, `getenv`, `setlocale`, `strerror` as pointers to const.**

**Why:** The returned strings belong to the library. Modifying them is undefined behaviour.

[❌ Bad example](../examples/r21/bad.c#L195-L202) · [✅ Good example](../examples/r21/good.c#L230-L239)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 21.20 · 🟥 Mandatory

**Don't use a pointer from `asctime`, `ctime`, `gmtime`, `localtime`, `localeconv`, `getenv`, `setlocale` or `strerror` after calling the same function again.**

**Why:** These functions may reuse one static buffer, so the old pointer now shows new data.

[❌ Bad example](../examples/r21/bad.c#L204-L212) · [✅ Good example](../examples/r21/good.c#L241-L250)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 21.21 · 🟧 Required

**Don't use `system`.**

**Why:** It runs arbitrary commands through the host shell: unpredictable and a command-injection risk (Amendment 2).

[❌ Bad example](../examples/r21/bad.c#L214-L220) · [✅ Good example](../examples/r21/good.c#L252-L258)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

## Chapter 22: Resources

These rules assume a deviation allows `<stdio.h>` or `<stdlib.h>` allocation, and make sure resources are **released**, used **in the right mode**, and errors read through **`errno` correctly**.

The `errno` protocol (22.8 – 22.10):

```c
errno = 0;                         /* 22.8: clear immediately before */
value = strtol(text, &end, 10);    /* an errno-setting function */
if (errno != 0) { /* error */ }    /* 22.9: test immediately after */
```

Code: [`examples/r22/`](../examples/r22)


---

### Rule 22.1 · 🟧 Required

**Release every resource obtained from the standard library.**

**Why:** Leaked file handles and memory eventually exhaust a long-running system.

[❌ Bad example](../examples/r22/bad.c#L10-L19) · [✅ Good example](../examples/r22/good.c#L15-L30)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 22.2 · 🟥 Mandatory

**Only free memory that was allocated by the standard library, and only once.**

**Why:** Freeing a stack address or freeing twice corrupts the heap.

[❌ Bad example](../examples/r22/bad.c#L21-L30) · [✅ Good example](../examples/r22/good.c#L32-L43)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 22.3 · 🟧 Required

**Don't open the same file for reading and writing on different streams at the same time.**

**Why:** Two independent buffers give inconsistent views of the same data.

[❌ Bad example](../examples/r22/bad.c#L32-L44) · [✅ Good example](../examples/r22/good.c#L45-L59)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 22.4 · 🟥 Mandatory

**Don't write to a stream opened read-only.**

**Why:** This is undefined behaviour.

[❌ Bad example](../examples/r22/bad.c#L46-L56) · [✅ Good example](../examples/r22/good.c#L61-L73)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 22.5 · 🟥 Mandatory

**Don't dereference a `FILE *`.**

**Why:** `FILE` is private to the library, and a copy of it is not a working stream.

[❌ Bad example](../examples/r22/bad.c#L58-L65) · [✅ Good example](../examples/r22/good.c#L75-L80)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 22.6 · 🟥 Mandatory

**Don't use a `FILE *` after its stream has been closed.**

**Why:** The pointer is dangling, so using it is undefined behaviour.

[❌ Bad example](../examples/r22/bad.c#L67-L77) · [✅ Good example](../examples/r22/good.c#L82-L93)

<sub>🔎 cppcheck 2.13: found by a core check, not reported as MISRA</sub>


---

### Rule 22.7 · 🟧 Required

**Only compare `EOF` with the unmodified return value of the function that can return it.**

**Why:** Storing `fgetc`'s result in a `char` makes byte 0xFF look like `EOF` (or `EOF` impossible to detect).

[❌ Bad example](../examples/r22/bad.c#L79-L93) · [✅ Good example](../examples/r22/good.c#L95-L107)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 22.8 · 🟧 Required

**Set `errno` to zero before calling an errno-setting function.**

**Why:** Otherwise a stale error from earlier code looks like a new failure.

[❌ Bad example](../examples/r22/bad.c#L95-L106) · [✅ Good example](../examples/r22/good.c#L109-L119)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 22.9 · 🟧 Required

**Test `errno` after calling an errno-setting function.**

**Why:** That is the only way functions like `strtol` report overflow.

[❌ Bad example](../examples/r22/bad.c#L108-L114) · [✅ Good example](../examples/r22/good.c#L109-L119)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 22.10 · 🟧 Required

**Only test `errno` after a function that is documented to set it.**

**Why:** Other functions may leave `errno` with any value, so a test after them means nothing.

[❌ Bad example](../examples/r22/bad.c#L116-L134) · [✅ Good example](../examples/r22/good.c#L121-L135)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

<sub>[◀ Previous](10-preprocessor.md) · [Contents](README.md) · [Next ▶](12-beyond-c2012.md)</sub>
