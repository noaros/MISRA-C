# MISRA C:2012 cheatsheet

**All 17 directives and 158 rules (C:2012 + Amendments 1 and 2) on one page, with links to bad and good code.**

Summaries are paraphrased, not the official wording: get the real text from [misra.org.uk](https://misra.org.uk/). · [Presentation](presentation/README.md) · [Examples](examples/)

**Legend.** Category: 🟥 **M** Mandatory (never deviate) · 🟧 **R** Required (deviate only with a formal record) · 🟦 **A** Advisory (recommended).
Code: ❌ bad example · ✅ good example. cppcheck 2.13 on the bad example: ● found by the MISRA addon · ◐ found by a core check · ○ missed · — not analysed.

---

## The 12 habits that cover most of MISRA

1. **Fixed-width types** everywhere: `uint8_t`, `int32_t`, ... (Dir 4.6)
2. **`U` suffix** on unsigned constants; **never mix signed and unsigned** in one operation (7.2, 10.4)
3. **Widen before the operation**, not after: `(uint32_t)a + b`, not `(uint32_t)(a + b)` (10.6–10.8)
4. **Compare, don't coerce:** `x != 0U`, `p != NULL`, never `if (x)` or `(bool)x` (14.4, 10.5)
5. **Braces on every body**, a final `else` on every `else if` chain (15.6, 15.7)
6. **Every `switch`**: `break` in each clause, a `default`, no Boolean switch (16.x)
7. **One side effect per statement**: no `a[i++] = x`, no `if ((x = f()))` (13.x)
8. **Initialise every variable**, return a value on every path (9.1, 17.4)
9. **Check every error return**, or discard it explicitly with `(void)` (Dir 4.7, 17.7)
10. **No heap, no recursion, no VLAs**: bounded memory and stack (Dir 4.12, 21.3, 17.2, 18.8)
11. **Macros:** parenthesise everything, prefer `static inline` functions, guard headers (20.7, Dir 4.9, Dir 4.10)
12. **`static`** for anything file-local, **`const`** for anything read-only (8.7, 8.13)

---

## Quick reference: essential types (Chapter 10)

| Category | Types | Allowed with | Never |
|---|---|---|---|
| Boolean | `bool`, comparisons, `&&` `\|\|` `!` | `&&` `\|\|` `!` `==` `!=` `?:` | arithmetic, bitwise, relational `<` |
| character | `char` | `==` `!=` `<`..., `'0' + n`, `c - '0'` | `*` `/` `%`, bitwise, char + char |
| signed | `int8_t` ... `int64_t` | arithmetic, comparison | bitwise `& \| ^ ~`, shifts |
| unsigned | `uint8_t` ... `uint64_t` | everything numeric, shifts, bitwise | unary minus |
| enum | each `enum` type | `==` `!=`, assignment of its own constants | arithmetic, bitwise |
| floating | `float`, `double` | arithmetic, comparison | bitwise, shifts, `%`, loop counters |

Constants take the **smallest type that fits**: `1U` is `uint8_t`, `300U` is `uint16_t`, `1` is signed.

---

## Well-formed shapes

```c
for (i = 0U; i < n; i++) { /* don't touch i or n here */ }       /* 14.2 */

switch (mode)                                                    /* 16.1 – 16.7 */
{
    case A:  do_a(); break;
    case B:
    case C:  do_bc(); break;
    default: safe_state(); break;
}

if (x < 0) { neg(); } else if (x > 0) { pos(); } else { /* zero */ }   /* 15.6, 15.7 */

errno = 0; v = strtol(s, &end, 10); if (errno != 0) { error(); }      /* 22.8, 22.9 */
```

---

## 🟥 The 16 mandatory rules (no deviation, ever)

| Rule | In plain words |
|---|---|
| 9.1 | Don't read a local variable before setting it |
| 12.5 | No `sizeof` on an array parameter |
| 13.6 | No side effects inside `sizeof` |
| 17.3 | No calls to undeclared functions |
| 17.4 | Every path of a non-void function returns a value |
| 17.6 | No `static` inside array parameter brackets |
| 19.1 | No copying between overlapping objects |
| 21.13 | `<ctype.h>` arguments must fit `unsigned char` or be `EOF` |
| 21.17 | `<string.h>` functions must stay in bounds |
| 21.18 | `<string.h>` size arguments must be valid |
| 21.19 | Library-owned strings (`strerror`, `getenv`, ...) are read-only |
| 21.20 | Don't reuse such a string after calling the function again |
| 22.2 | Free only heap memory, only once |
| 22.4 | Don't write to a read-only stream |
| 22.5 | Never dereference a `FILE *` |
| 22.6 | Don't use a stream after closing it |

---

## Directives

| Dir | Cat | In plain words | Code |
|---|---|---|---|
| Dir 1.1 | 🟧 R | Document every implementation-defined behaviour your code relies on. | [❌](examples/dir/bad.c#L11-L22) [✅](examples/dir/good.c#L12-L24) |
| Dir 2.1 | 🟧 R | The code must compile with no errors. | [❌](examples/dir/bad.c#L24-L33) [✅](examples/dir/good.c#L26-L28) |
| Dir 3.1 | 🟧 R | All code must trace back to documented requirements. | [❌](examples/dir/bad.c#L35-L40) [✅](examples/dir/good.c#L30-L38) |
| Dir 4.1 | 🟧 R | Minimise the chance of run-time failures. | [❌](examples/dir/bad.c#L42-L47) [✅](examples/dir/good.c#L40-L50) |
| Dir 4.2 | 🟦 A | Document any assembly language. | [❌](examples/dir/bad.c#L49-L54) [✅](examples/dir/good.c#L52-L60) |
| Dir 4.3 | 🟧 R | Keep assembly encapsulated and isolated, never mixed into C logic. | [❌](examples/dir/bad.c#L56-L65) [✅](examples/dir/good.c#L62-L68) |
| Dir 4.4 | 🟦 A | Don't leave code commented out. | [❌](examples/dir/bad.c#L67-L74) [✅](examples/dir/good.c#L70-L76) |
| Dir 4.5 | 🟦 A | Names in the same scope should not look alike. | [❌](examples/dir/bad.c#L76-L85) [✅](examples/dir/good.c#L78-L85) |
| Dir 4.6 | 🟦 A | Use fixed-size typedefs (e.g. `int32_t`) instead of basic numeric types. | [❌](examples/dir/bad.c#L87-L93) [✅](examples/dir/good.c#L87-L92) |
| Dir 4.7 | 🟧 R | If a function returns error information, test it. | [❌](examples/dir/bad.c#L95-L113) [✅](examples/dir/good.c#L94-L115) |
| Dir 4.8 | 🟦 A | Hide the definition of a struct/union if users only need a pointer to it. | [❌](examples/dir/bad.c#L115-L123) [✅](examples/dir/good.c#L117-L134) |
| Dir 4.9 | 🟦 A | Prefer functions to function-like macros where either would work. | [❌](examples/dir/bad.c#L125-L132) [✅](examples/dir/good.c#L136-L141) |
| Dir 4.10 | 🟧 R | Guard every header against multiple inclusion. | [❌](examples/dir/bad.c#L134-L135) [✅](examples/dir/good.c#L143-L144) |
| Dir 4.11 | 🟧 R | Check that values passed to library functions are valid. | [❌](examples/dir/bad.c#L137-L142) [✅](examples/dir/good.c#L146-L156) |
| Dir 4.12 | 🟧 R | Don't use dynamic memory allocation. | [❌](examples/dir/bad.c#L144-L149) [✅](examples/dir/good.c#L158-L166) |
| Dir 4.13 | 🟦 A | Call functions that operate on a resource in the right sequence. | [❌](examples/dir/bad.c#L151-L160) [✅](examples/dir/good.c#L168-L185) |
| Dir 4.14 | 🟧 R | Check the validity of values received from external sources. | [❌](examples/dir/bad.c#L162-L170) [✅](examples/dir/good.c#L187-L201) |

## Rules


### 1. The standard C environment

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 1.1 | 🟧 R | Stay within standard C: no syntax or constraint violations, no exceeding translation limits. | [❌](examples/r01/bad.c#L7-L18) [✅](examples/r01/good.c#L8-L15) | — |
| 1.2 | 🟦 A | Don't use language extensions. | [❌](examples/r01/bad.c#L20-L35) [✅](examples/r01/good.c#L17-L27) | ● addon |
| 1.3 | 🟧 R | No undefined or critical unspecified behaviour. | [❌](examples/r01/bad.c#L37-L47) [✅](examples/r01/good.c#L29-L40) | ◐ core |
| 1.4 | 🟧 R | Don't use 'emergent' language features (from C11 onwards) that the guidelines don't yet cover. | [❌](examples/r01/bad.c#L49-L58) [✅](examples/r01/good.c#L42-L51) | ● addon |

### 2. Unused code

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 2.1 | 🟧 R | No unreachable code. | [❌](examples/r02/bad.c#L7-L13) [✅](examples/r02/good.c#L7-L17) | ○ missed |
| 2.2 | 🟧 R | No dead code: operations whose removal would change nothing. | [❌](examples/r02/bad.c#L15-L22) [✅](examples/r02/good.c#L19-L25) | ● addon |
| 2.3 | 🟦 A | No unused type declarations. | [❌](examples/r02/bad.c#L24-L30) [✅](examples/r02/good.c#L27-L34) | ○ missed |
| 2.4 | 🟦 A | No unused tag declarations. | [❌](examples/r02/bad.c#L32-L37) [✅](examples/r02/good.c#L36-L47) | ○ missed |
| 2.5 | 🟦 A | No unused macros. | [❌](examples/r02/bad.c#L39-L41) [✅](examples/r02/good.c#L49-L56) | ○ missed |
| 2.6 | 🟦 A | No unused labels. | [❌](examples/r02/bad.c#L43-L49) [✅](examples/r02/good.c#L58-L63) | ○ missed |
| 2.7 | 🟦 A | No unused function parameters. | [❌](examples/r02/bad.c#L51-L56) [✅](examples/r02/good.c#L65-L71) | ● addon |

### 3. Comments

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 3.1 | 🟧 R | Don't write `/*` or `//` inside a comment. | [❌](examples/r03/bad.c#L7-L16) [✅](examples/r03/good.c#L7-L14) | ● addon |
| 3.2 | 🟧 R | No line-splicing (trailing backslash) in `//` comments. | [❌](examples/r03/bad.c#L18-L27) [✅](examples/r03/good.c#L16-L24) | ● addon |

### 4. Character sets and lexical conventions

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 4.1 | 🟧 R | Terminate octal and hexadecimal escape sequences. | [❌](examples/r04/bad.c#L7-L14) [✅](examples/r04/good.c#L7-L13) | ● addon |
| 4.2 | 🟦 A | Don't use trigraphs. | [❌](examples/r04/bad.c#L16-L22) [✅](examples/r04/good.c#L15-L20) | ● addon |

### 5. Identifiers

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 5.1 | 🟧 R | External identifiers must be distinct (within the significant characters C guarantees). | [❌](examples/r05/bad.c#L7-L12) [✅](examples/r05/good.c#L7-L16) | ○ missed |
| 5.2 | 🟧 R | Identifiers in the same scope and name space must be distinct. | [❌](examples/r05/bad.c#L14-L23) [✅](examples/r05/good.c#L18-L25) | ● addon |
| 5.3 | 🟧 R | Don't let an inner-scope identifier hide an outer one. | [❌](examples/r05/bad.c#L25-L34) [✅](examples/r05/good.c#L27-L36) | ○ missed |
| 5.4 | 🟧 R | Macro identifiers must be distinct. | [❌](examples/r05/bad.c#L36-L39) [✅](examples/r05/good.c#L38-L41) | ● addon |
| 5.5 | 🟧 R | Identifiers must be distinct from macro names. | [❌](examples/r05/bad.c#L41-L50) [✅](examples/r05/good.c#L43-L51) | ● addon |
| 5.6 | 🟧 R | A typedef name must be unique. | [❌](examples/r05/bad.c#L52-L60) [✅](examples/r05/good.c#L53-L61) | ○ missed |
| 5.7 | 🟧 R | A struct/union/enum tag name must be unique. | [❌](examples/r05/bad.c#L62-L69) [✅](examples/r05/good.c#L63-L74) | ○ missed |
| 5.8 | 🟧 R | Identifiers with external linkage must be unique across the program. | [❌](examples/r05/bad.c#L71-L82) [✅](examples/r05/good.c#L76-L83) | ○ missed |
| 5.9 | 🟦 A | Identifiers with internal linkage should be unique across the program. | [❌](examples/r05/bad.c#L84-L94) [✅](examples/r05/good.c#L85-L93) | ○ missed |

### 6. Types

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 6.1 | 🟧 R | Bit-fields may only use appropriate types (signed/unsigned int, `_Bool`). | [❌](examples/r06/bad.c#L7-L15) [✅](examples/r06/good.c#L8-L21) | ● addon |
| 6.2 | 🟧 R | A single-bit named bit-field must not be signed. | [❌](examples/r06/bad.c#L17-L29) [✅](examples/r06/good.c#L23-L35) | ● addon |

### 7. Literals and constants

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 7.1 | 🟧 R | Don't use octal constants. | [❌](examples/r07/bad.c#L7-L14) [✅](examples/r07/good.c#L8-L15) | ● addon |
| 7.2 | 🟧 R | Use a `U` suffix on integer constants that have unsigned type. | [❌](examples/r07/bad.c#L16-L22) [✅](examples/r07/good.c#L17-L22) | ● addon |
| 7.3 | 🟧 R | Don't use a lowercase `l` suffix. | [❌](examples/r07/bad.c#L24-L29) [✅](examples/r07/good.c#L24-L29) | ● addon |
| 7.4 | 🟧 R | Only assign a string literal to a pointer to const char. | [❌](examples/r07/bad.c#L31-L39) [✅](examples/r07/good.c#L31-L40) | ● addon |

### 8. Declarations and definitions

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 8.1 | 🟧 R | State types explicitly: no implicit `int`. | [❌](examples/r08/bad.c#L7-L13) [✅](examples/r08/good.c#L8-L15) | — |
| 8.2 | 🟧 R | Use prototype form for functions, with named parameters. | [❌](examples/r08/bad.c#L15-L22) [✅](examples/r08/good.c#L17-L31) | ● addon |
| 8.3 | 🟧 R | All declarations of an object or function must use the same names and qualifiers. | [❌](examples/r08/bad.c#L24-L32) [✅](examples/r08/good.c#L33-L40) | ○ missed |
| 8.4 | 🟧 R | A compatible declaration must be visible where an external object or function is defined. | [❌](examples/r08/bad.c#L34-L37) [✅](examples/r08/good.c#L42-L45) | ● addon |
| 8.5 | 🟧 R | Declare an external object or function once, in one file (a header). | [❌](examples/r08/bad.c#L39-L43) [✅](examples/r08/good.c#L47-L48) | ○ missed |
| 8.6 | 🟧 R | An external identifier must have exactly one definition. | [❌](examples/r08/bad.c#L45-L53) [✅](examples/r08/good.c#L50-L52) | ○ missed |
| 8.7 | 🟦 A | Don't give external linkage to things used in only one translation unit. | [❌](examples/r08/bad.c#L55-L62) [✅](examples/r08/good.c#L54-L59) | ○ missed |
| 8.8 | 🟧 R | Use `static` on every declaration of an internal-linkage object or function. | [❌](examples/r08/bad.c#L64-L72) [✅](examples/r08/good.c#L61-L68) | ○ missed |
| 8.9 | 🟦 A | Define an object at block scope if it's used in only one function. | [❌](examples/r08/bad.c#L74-L82) [✅](examples/r08/good.c#L70-L76) | ● addon |
| 8.10 | 🟧 R | Declare inline functions `static`. | [❌](examples/r08/bad.c#L84-L90) [✅](examples/r08/good.c#L78-L83) | ● addon |
| 8.11 | 🟦 A | Give an explicit size when declaring an external array. | [❌](examples/r08/bad.c#L92-L94) [✅](examples/r08/good.c#L85-L86) | ● addon |
| 8.12 | 🟧 R | Implicitly valued enumerators must not duplicate other enumerator values. | [❌](examples/r08/bad.c#L96-L99) [✅](examples/r08/good.c#L88-L90) | ● addon |
| 8.13 | 🟦 A | Point to const whenever possible. | [❌](examples/r08/bad.c#L101-L112) [✅](examples/r08/good.c#L92-L103) | ○ missed |
| 8.14 | 🟧 R | Don't use `restrict`. | [❌](examples/r08/bad.c#L114-L120) [✅](examples/r08/good.c#L105-L110) | ● addon |

### 9. Initialization

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 9.1 | 🟥 M | Don't read an automatic variable before it has been set. | [❌](examples/r09/bad.c#L7-L18) [✅](examples/r09/good.c#L7-L17) | ○ missed |
| 9.2 | 🟧 R | Enclose initializers for aggregates and unions in braces. | [❌](examples/r09/bad.c#L20-L26) [✅](examples/r09/good.c#L19-L25) | ● addon |
| 9.3 | 🟧 R | Don't partially initialize arrays. | [❌](examples/r09/bad.c#L28-L34) [✅](examples/r09/good.c#L27-L35) | ● addon |
| 9.4 | 🟧 R | Don't initialize the same element more than once. | [❌](examples/r09/bad.c#L36-L42) [✅](examples/r09/good.c#L37-L43) | ● addon |
| 9.5 | 🟧 R | When using designated initializers for an array, state its size. | [❌](examples/r09/bad.c#L44-L51) [✅](examples/r09/good.c#L45-L51) | ● addon |

### 10. The essential type model

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 10.1 | 🟧 R | Operands must not be of an inappropriate essential type. | [❌](examples/r10/bad.c#L15-L25) [✅](examples/r10/good.c#L10-L28) | ● addon |
| 10.2 | 🟧 R | Don't use character values inappropriately in addition and subtraction. | [❌](examples/r10/bad.c#L27-L35) [✅](examples/r10/good.c#L30-L40) | ○ missed |
| 10.3 | 🟧 R | Don't assign a value to a narrower type or a different type category. | [❌](examples/r10/bad.c#L37-L48) [✅](examples/r10/good.c#L42-L53) | ● addon |
| 10.4 | 🟧 R | Both operands of an arithmetic or comparison operator must be in the same type category. | [❌](examples/r10/bad.c#L50-L57) [✅](examples/r10/good.c#L55-L65) | ● addon |
| 10.5 | 🟦 A | Don't cast a value to an inappropriate essential type. | [❌](examples/r10/bad.c#L59-L66) [✅](examples/r10/good.c#L67-L86) | ● addon |
| 10.6 | 🟧 R | Don't assign a composite expression to a wider type. | [❌](examples/r10/bad.c#L68-L75) [✅](examples/r10/good.c#L88-L94) | ● addon |
| 10.7 | 🟧 R | If a composite expression is one operand, the other operand must not be wider. | [❌](examples/r10/bad.c#L77-L83) [✅](examples/r10/good.c#L96-L101) | ● addon |
| 10.8 | 🟧 R | Don't cast a composite expression to a wider type or a different category. | [❌](examples/r10/bad.c#L85-L93) [✅](examples/r10/good.c#L103-L109) | ● addon |

### 11. Pointer type conversions

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 11.1 | 🟧 R | Don't convert between function pointers and any other type. | [❌](examples/r11/bad.c#L9-L20) [✅](examples/r11/good.c#L10-L22) | ○ missed |
| 11.2 | 🟧 R | Don't convert between a pointer to an incomplete type and any other type. | [❌](examples/r11/bad.c#L22-L31) [✅](examples/r11/good.c#L24-L34) | ● addon |
| 11.3 | 🟧 R | Don't cast between pointers to different object types. | [❌](examples/r11/bad.c#L33-L40) [✅](examples/r11/good.c#L36-L46) | ● addon |
| 11.4 | 🟦 A | Don't convert between pointers and integers. | [❌](examples/r11/bad.c#L42-L49) [✅](examples/r11/good.c#L48-L58) | ● addon |
| 11.5 | 🟦 A | Don't convert from `void *` to a pointer to an object. | [❌](examples/r11/bad.c#L51-L58) [✅](examples/r11/good.c#L60-L65) | ● addon |
| 11.6 | 🟧 R | Don't cast between `void *` and an arithmetic type. | [❌](examples/r11/bad.c#L60-L66) [✅](examples/r11/good.c#L67-L72) | ● addon |
| 11.7 | 🟧 R | Don't cast between an object pointer and a non-integer arithmetic type. | [❌](examples/r11/bad.c#L68-L73) [✅](examples/r11/good.c#L74-L79) | ○ missed |
| 11.8 | 🟧 R | Don't cast away `const` or `volatile`. | [❌](examples/r11/bad.c#L75-L82) [✅](examples/r11/good.c#L81-L89) | ● addon |
| 11.9 | 🟧 R | Use `NULL` as the only form of integer null pointer constant. | [❌](examples/r11/bad.c#L84-L90) [✅](examples/r11/good.c#L91-L97) | ● addon |

### 12. Expressions

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 12.1 | 🟦 A | Make operator precedence explicit with parentheses. | [❌](examples/r12/bad.c#L10-L22) [✅](examples/r12/good.c#L10-L20) | ● addon |
| 12.2 | 🟧 R | A shift amount must be between zero and one less than the width of the left operand's essential type. | [❌](examples/r12/bad.c#L24-L32) [✅](examples/r12/good.c#L22-L33) | ● addon |
| 12.3 | 🟦 A | Don't use the comma operator. | [❌](examples/r12/bad.c#L34-L46) [✅](examples/r12/good.c#L35-L50) | ● addon |
| 12.4 | 🟦 A | Constant expressions shouldn't wrap around. | [❌](examples/r12/bad.c#L48-L56) [✅](examples/r12/good.c#L52-L57) | ● addon |
| 12.5 | 🟥 M | Don't apply `sizeof` to a function parameter declared as an array. | [❌](examples/r12/bad.c#L58-L64) [✅](examples/r12/good.c#L59-L75) | ○ missed |

### 13. Side effects

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 13.1 | 🟧 R | No persistent side effects in initializer lists. | [❌](examples/r13/bad.c#L17-L24) [✅](examples/r13/good.c#L16-L26) | ○ missed |
| 13.2 | 🟧 R | An expression's value and side effects must be the same under every permitted evaluation order. | [❌](examples/r13/bad.c#L26-L35) [✅](examples/r13/good.c#L28-L41) | ◐ core |
| 13.3 | 🟦 A | A full expression containing `++`/`--` shouldn't have any other side effects. | [❌](examples/r13/bad.c#L37-L43) [✅](examples/r13/good.c#L43-L51) | ● addon |
| 13.4 | 🟦 A | Don't use the result of an assignment. | [❌](examples/r13/bad.c#L45-L58) [✅](examples/r13/good.c#L53-L65) | ● addon |
| 13.5 | 🟧 R | The right operand of `&&` or `\|\|` must not have persistent side effects. | [❌](examples/r13/bad.c#L60-L71) [✅](examples/r13/good.c#L67-L84) | ● addon |
| 13.6 | 🟥 M | The operand of `sizeof` must not contain side effects. | [❌](examples/r13/bad.c#L73-L80) [✅](examples/r13/good.c#L86-L94) | ● addon |

### 14. Control statement expressions

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 14.1 | 🟧 R | Loop counters must not be floating-point. | [❌](examples/r14/bad.c#L8-L20) [✅](examples/r14/good.c#L9-L24) | ● addon |
| 14.2 | 🟧 R | A `for` loop must be well-formed. | [❌](examples/r14/bad.c#L22-L37) [✅](examples/r14/good.c#L26-L41) | ● addon |
| 14.3 | 🟧 R | Controlling expressions must not be invariant. | [❌](examples/r14/bad.c#L39-L55) [✅](examples/r14/good.c#L43-L60) | ○ missed |
| 14.4 | 🟧 R | Conditions of `if` and loops must be essentially Boolean. | [❌](examples/r14/bad.c#L57-L72) [✅](examples/r14/good.c#L62-L77) | ● addon |

### 15. Control flow

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 15.1 | 🟦 A | Don't use `goto`. | [❌](examples/r15/bad.c#L8-L20) [✅](examples/r15/good.c#L8-L18) | ● addon |
| 15.2 | 🟧 R | `goto` may only jump forwards, to a later label in the same function. | [❌](examples/r15/bad.c#L22-L34) [✅](examples/r15/good.c#L20-L31) | ● addon |
| 15.3 | 🟧 R | A `goto` label must be in the same block as the `goto` or in an enclosing block. | [❌](examples/r15/bad.c#L36-L50) [✅](examples/r15/good.c#L33-L44) | ● addon |
| 15.4 | 🟦 A | Use at most one `break` or `goto` to leave a loop. | [❌](examples/r15/bad.c#L52-L70) [✅](examples/r15/good.c#L46-L64) | ● addon |
| 15.5 | 🟦 A | A function should have a single exit point, at the end. | [❌](examples/r15/bad.c#L72-L85) [✅](examples/r15/good.c#L66-L84) | ● addon |
| 15.6 | 🟧 R | The body of every loop and `if`/`else`/`switch` must be a compound statement (braces). | [❌](examples/r15/bad.c#L87-L99) [✅](examples/r15/good.c#L86-L102) | ● addon |
| 15.7 | 🟧 R | Every `if ... else if` chain must end with an `else`. | [❌](examples/r15/bad.c#L101-L116) [✅](examples/r15/good.c#L104-L123) | ● addon |

### 16. Switch statements

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 16.1 | 🟧 R | Every `switch` statement must be well-formed. | [❌](examples/r16/bad.c#L8-L24) [✅](examples/r16/good.c#L21-L36) | ● addon |
| 16.2 | 🟧 R | Only use a `switch` label directly in the `switch` body. | [❌](examples/r16/bad.c#L26-L44) [✅](examples/r16/good.c#L38-L58) | ● addon |
| 16.3 | 🟧 R | End every non-empty switch clause with an unconditional `break`. | [❌](examples/r16/bad.c#L46-L62) [✅](examples/r16/good.c#L60-L79) | ● addon |
| 16.4 | 🟧 R | Every `switch` must have a `default` label. | [❌](examples/r16/bad.c#L64-L79) [✅](examples/r16/good.c#L81-L99) | ● addon |
| 16.5 | 🟧 R | `default` must be the first or last label. | [❌](examples/r16/bad.c#L81-L99) [✅](examples/r16/good.c#L101-L119) | ● addon |
| 16.6 | 🟧 R | Every `switch` must have at least two clauses. | [❌](examples/r16/bad.c#L101-L113) [✅](examples/r16/good.c#L121-L131) | ● addon |
| 16.7 | 🟧 R | Don't switch on a Boolean expression. | [❌](examples/r16/bad.c#L115-L129) [✅](examples/r16/good.c#L133-L143) | ● addon |

### 17. Functions

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 17.1 | 🟧 R | Don't use `<stdarg.h>` (variadic functions). | [❌](examples/r17/bad.c#L8-L23) [✅](examples/r17/good.c#L8-L19) | ● addon |
| 17.2 | 🟧 R | Functions must not call themselves, directly or indirectly. | [❌](examples/r17/bad.c#L25-L36) [✅](examples/r17/good.c#L21-L32) | ● addon |
| 17.3 | 🟥 M | Don't call a function without a declaration in scope. | [❌](examples/r17/bad.c#L38-L47) [✅](examples/r17/good.c#L34-L46) | — |
| 17.4 | 🟥 M | Every exit from a non-void function must return a value explicitly. | [❌](examples/r17/bad.c#L49-L58) [✅](examples/r17/good.c#L48-L58) | ◐ core |
| 17.5 | 🟦 A | An array argument must have at least as many elements as the parameter declares. | [❌](examples/r17/bad.c#L60-L71) [✅](examples/r17/good.c#L60-L74) | ○ missed |
| 17.6 | 🟥 M | Don't use `static` inside the `[]` of an array parameter. | [❌](examples/r17/bad.c#L73-L79) [✅](examples/r17/good.c#L76-L81) | ● addon |
| 17.7 | 🟧 R | Use the return value of a non-void function (or cast it to `(void)`). | [❌](examples/r17/bad.c#L81-L91) [✅](examples/r17/good.c#L83-L99) | ● addon |
| 17.8 | 🟦 A | Don't modify a function parameter. | [❌](examples/r17/bad.c#L93-L100) [✅](examples/r17/good.c#L101-L107) | ● addon |

### 18. Pointers and arrays

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 18.1 | 🟧 R | Pointer arithmetic must stay within the same array. | [❌](examples/r18/bad.c#L8-L16) [✅](examples/r18/good.c#L11-L22) | ○ missed |
| 18.2 | 🟧 R | Only subtract pointers that point into the same array. | [❌](examples/r18/bad.c#L18-L25) [✅](examples/r18/good.c#L24-L34) | ◐ core |
| 18.3 | 🟧 R | Only use `<`, `<=`, `>`, `>=` on pointers into the same object. | [❌](examples/r18/bad.c#L27-L35) [✅](examples/r18/good.c#L36-L44) | ◐ core |
| 18.4 | 🟦 A | Don't use `+`, `-`, `+=`, `-=` on pointers. | [❌](examples/r18/bad.c#L37-L45) [✅](examples/r18/good.c#L46-L51) | ● addon |
| 18.5 | 🟦 A | Use at most two levels of pointer nesting. | [❌](examples/r18/bad.c#L47-L52) [✅](examples/r18/good.c#L53-L58) | ● addon |
| 18.6 | 🟧 R | Don't let the address of an automatic object outlive it. | [❌](examples/r18/bad.c#L54-L63) [✅](examples/r18/good.c#L60-L66) | ◐ core |
| 18.7 | 🟧 R | Don't declare flexible array members. | [❌](examples/r18/bad.c#L65-L72) [✅](examples/r18/good.c#L68-L81) | ● addon |
| 18.8 | 🟧 R | Don't use variable-length arrays. | [❌](examples/r18/bad.c#L74-L82) [✅](examples/r18/good.c#L83-L97) | ● addon |

### 19. Overlapping storage

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 19.1 | 🟥 M | Don't assign or copy an object to an overlapping object. | [❌](examples/r19/bad.c#L8-L15) [✅](examples/r19/good.c#L8-L14) | ◐ core |
| 19.2 | 🟦 A | Don't use `union`. | [❌](examples/r19/bad.c#L17-L31) [✅](examples/r19/good.c#L16-L42) | ● addon |

### 20. Preprocessing directives

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 20.1 | 🟦 A | Only preprocessor directives or comments may come before an `#include`. | [❌](examples/r20/bad.c#L7-L11) [✅](examples/r20/good.c#L4-L8) | ● addon |
| 20.2 | 🟧 R | Header file names must not contain `'`, `"`, `\`, `/*` or `//`. | [❌](examples/r20/bad.c#L13-L19) [✅](examples/r20/good.c#L10-L12) | ● addon |
| 20.3 | 🟧 R | `#include` must be followed by `<filename>` or `"filename"`. | [❌](examples/r20/bad.c#L21-L26) [✅](examples/r20/good.c#L14-L15) | ● addon |
| 20.4 | 🟧 R | Don't define a macro with the same name as a keyword. | [❌](examples/r20/bad.c#L28-L30) [✅](examples/r20/good.c#L17-L20) | ● addon |
| 20.5 | 🟦 A | Don't use `#undef`. | [❌](examples/r20/bad.c#L32-L37) [✅](examples/r20/good.c#L22-L24) | ● addon |
| 20.6 | 🟧 R | No preprocessing directives inside macro arguments. | [❌](examples/r20/bad.c#L39-L61) [✅](examples/r20/good.c#L26-L39) | — |
| 20.7 | 🟧 R | Parenthesise macro parameters in expansions. | [❌](examples/r20/bad.c#L63-L70) [✅](examples/r20/good.c#L41-L49) | ● addon |
| 20.8 | 🟧 R | `#if`/`#elif` conditions must evaluate to 0 or 1. | [❌](examples/r20/bad.c#L72-L77) [✅](examples/r20/good.c#L51-L56) | ● addon |
| 20.9 | 🟧 R | Define every identifier used in `#if`/`#elif` before it is evaluated. | [❌](examples/r20/bad.c#L79-L84) [✅](examples/r20/good.c#L58-L67) | ● addon |
| 20.10 | 🟦 A | Don't use the `#` and `##` operators. | [❌](examples/r20/bad.c#L86-L91) [✅](examples/r20/good.c#L69-L71) | ● addon |
| 20.11 | 🟧 R | A parameter right after `#` must not be followed by `##`. | [❌](examples/r20/bad.c#L93-L95) [✅](examples/r20/good.c#L73-L75) | ● addon |
| 20.12 | 🟧 R | A parameter used with `#` or `##` that would otherwise be macro-expanded must only be used with those operators. | [❌](examples/r20/bad.c#L97-L100) [✅](examples/r20/good.c#L77-L80) | ○ missed |
| 20.13 | 🟧 R | A line starting with `#` must be a valid preprocessing directive. | [❌](examples/r20/bad.c#L102-L107) [✅](examples/r20/good.c#L82-L86) | ● addon |
| 20.14 | 🟧 R | `#else`, `#elif` and `#endif` must be in the same file as their `#if`. | [❌](examples/r20/bad.c#L109-L118) [✅](examples/r20/good.c#L88-L90) | ● addon |

### 21. Standard libraries

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 21.1 | 🟧 R | Don't `#define` or `#undef` reserved identifiers or macro names. | [❌](examples/r21/bad.c#L16-L20) [✅](examples/r21/good.c#L14-L17) | ● addon |
| 21.2 | 🟧 R | Don't declare reserved identifiers or macro names. | [❌](examples/r21/bad.c#L22-L25) [✅](examples/r21/good.c#L19-L20) | ○ missed |
| 21.3 | 🟧 R | Don't use `malloc`, `calloc`, `realloc` or `free`. | [❌](examples/r21/bad.c#L27-L35) [✅](examples/r21/good.c#L22-L53) | ● addon |
| 21.4 | 🟧 R | Don't use `<setjmp.h>`. | [❌](examples/r21/bad.c#L37-L54) [✅](examples/r21/good.c#L55-L70) | ● addon |
| 21.5 | 🟧 R | Don't use `<signal.h>`. | [❌](examples/r21/bad.c#L56-L67) [✅](examples/r21/good.c#L72-L82) | ● addon |
| 21.6 | 🟧 R | Don't use standard I/O functions (`<stdio.h>`). | [❌](examples/r21/bad.c#L69-L75) [✅](examples/r21/good.c#L84-L93) | ● addon |
| 21.7 | 🟧 R | Don't use `atof`, `atoi`, `atol`, `atoll`. | [❌](examples/r21/bad.c#L77-L83) [✅](examples/r21/good.c#L95-L112) | ● addon |
| 21.8 | 🟧 R | Don't use the termination functions (`abort`, `exit`, ...). | [❌](examples/r21/bad.c#L85-L96) [✅](examples/r21/good.c#L114-L124) | ● addon |
| 21.9 | 🟧 R | Don't use `bsearch` or `qsort`. | [❌](examples/r21/bad.c#L98-L109) [✅](examples/r21/good.c#L126-L142) | ● addon |
| 21.10 | 🟧 R | Don't use the time and date functions (`<time.h>`). | [❌](examples/r21/bad.c#L111-L117) [✅](examples/r21/good.c#L144-L151) | ● addon |
| 21.11 | 🟧 R | Don't use `<tgmath.h>`. | [❌](examples/r21/bad.c#L119-L125) [✅](examples/r21/good.c#L153-L158) | ● addon |
| 21.12 | 🟦 A | Don't use the exception-handling features of `<fenv.h>`. | [❌](examples/r21/bad.c#L127-L137) [✅](examples/r21/good.c#L160-L170) | ● addon |
| 21.13 | 🟥 M | Values passed to `<ctype.h>` functions must fit in `unsigned char` (or be `EOF`). | [❌](examples/r21/bad.c#L139-L146) [✅](examples/r21/good.c#L172-L177) | ○ missed |
| 21.14 | 🟧 R | Don't use `memcmp` to compare null-terminated strings. | [❌](examples/r21/bad.c#L148-L154) [✅](examples/r21/good.c#L179-L184) | ○ missed |
| 21.15 | 🟧 R | Pointer arguments to `memcpy`/`memmove`/`memcmp` must point to compatible types. | [❌](examples/r21/bad.c#L156-L163) [✅](examples/r21/good.c#L186-L193) | ● addon |
| 21.16 | 🟧 R | Only use `memcmp` on pointers, signed, unsigned, Boolean or enum types. | [❌](examples/r21/bad.c#L165-L177) [✅](examples/r21/good.c#L195-L206) | ● addon |
| 21.17 | 🟥 M | String functions from `<string.h>` must not access beyond the bounds of their objects. | [❌](examples/r21/bad.c#L179-L185) [✅](examples/r21/good.c#L208-L220) | ◐ core |
| 21.18 | 🟥 M | `size_t` arguments to `<string.h>` functions must have valid values. | [❌](examples/r21/bad.c#L187-L193) [✅](examples/r21/good.c#L222-L228) | ◐ core |
| 21.19 | 🟥 M | Treat pointers returned by `localeconv`, `getenv`, `setlocale`, `strerror` as pointers to const. | [❌](examples/r21/bad.c#L195-L202) [✅](examples/r21/good.c#L230-L239) | ● addon |
| 21.20 | 🟥 M | Don't use a pointer from `asctime`, `ctime`, `gmtime`, `localtime`, `localeconv`, `getenv`, `setlocale` or `strerror` after calling the same function again. | [❌](examples/r21/bad.c#L204-L212) [✅](examples/r21/good.c#L241-L250) | ○ missed |
| 21.21 | 🟧 R | Don't use `system`. | [❌](examples/r21/bad.c#L214-L220) [✅](examples/r21/good.c#L252-L258) | ● addon |

### 22. Resources

| Rule | Cat | In plain words | Code | cppcheck |
|---|---|---|---|---|
| 22.1 | 🟧 R | Release every resource obtained from the standard library. | [❌](examples/r22/bad.c#L10-L19) [✅](examples/r22/good.c#L15-L30) | ◐ core |
| 22.2 | 🟥 M | Only free memory that was allocated by the standard library, and only once. | [❌](examples/r22/bad.c#L21-L30) [✅](examples/r22/good.c#L32-L43) | ◐ core |
| 22.3 | 🟧 R | Don't open the same file for reading and writing on different streams at the same time. | [❌](examples/r22/bad.c#L32-L44) [✅](examples/r22/good.c#L45-L59) | ◐ core |
| 22.4 | 🟥 M | Don't write to a stream opened read-only. | [❌](examples/r22/bad.c#L46-L56) [✅](examples/r22/good.c#L61-L73) | ◐ core |
| 22.5 | 🟥 M | Don't dereference a `FILE *`. | [❌](examples/r22/bad.c#L58-L65) [✅](examples/r22/good.c#L75-L80) | ● addon |
| 22.6 | 🟥 M | Don't use a `FILE *` after its stream has been closed. | [❌](examples/r22/bad.c#L67-L77) [✅](examples/r22/good.c#L82-L93) | ◐ core |
| 22.7 | 🟧 R | Only compare `EOF` with the unmodified return value of the function that can return it. | [❌](examples/r22/bad.c#L79-L93) [✅](examples/r22/good.c#L95-L107) | ● addon |
| 22.8 | 🟧 R | Set `errno` to zero before calling an errno-setting function. | [❌](examples/r22/bad.c#L95-L106) [✅](examples/r22/good.c#L109-L119) | ● addon |
| 22.9 | 🟧 R | Test `errno` after calling an errno-setting function. | [❌](examples/r22/bad.c#L108-L114) [✅](examples/r22/good.c#L109-L119) | ● addon |
| 22.10 | 🟧 R | Only test `errno` after a function that is documented to set it. | [❌](examples/r22/bad.c#L116-L134) [✅](examples/r22/good.c#L121-L135) | ● addon |

---

## Standard library: banned and replacements

| Don't use | Rule | Use instead |
|---|---|---|
| `malloc` `calloc` `realloc` `free` | 21.3, Dir 4.12 | static buffers, fixed pools |
| `<setjmp.h>` | 21.4 | error codes |
| `<signal.h>` | 21.5 | documented interrupt handlers + flags |
| `<stdio.h>` | 21.6 | project drivers (or deviate and follow Ch. 22) |
| `atoi` `atol` `atoll` `atof` | 21.7 | `strtol` / `strtod` + `errno` + end pointer |
| `abort` `exit` `_Exit` `quick_exit` | 21.8 | return errors, enter a safe state |
| `qsort` `bsearch` | 21.9 | simple bounded algorithms |
| `<time.h>` | 21.10 | project clock driver |
| `<tgmath.h>` | 21.11 | `sqrtf`, `sqrt`, `sqrtl` by name |
| `<fenv.h>` exceptions | 21.12 | validate operands first |
| `system` | 21.21 | call the function directly |
| `<stdarg.h>` | 17.1 | arrays + lengths, fixed parameters |

---

## Deviation checklist

- [ ] Guideline is **not** Mandatory
- [ ] Scope is as narrow as possible (one function, macro or file)
- [ ] Justification explains why compliance is impractical or less safe
- [ ] Risks and **mitigations** listed (tests, reviews, extra checks)
- [ ] Approved by the right person and recorded in version control
- [ ] Every use marked in code with the deviation ID
- [ ] Listed in the Guideline Compliance Summary

---

<sub>Generated from the same data as the [presentation](presentation/README.md). Line links are kept current by `python3 tools/relink.py`.</sub>
