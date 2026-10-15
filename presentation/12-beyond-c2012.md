<sub>[◀ Previous](11-library-and-resources.md) · [Contents](README.md) · [Next ▶](13-in-practice.md)</sub>

# Part 12: Beyond C:2012

**What MISRA C:2023 and MISRA C:2025 changed.**


---

## MISRA C:2023: one consolidated document

MISRA C:2023 = **C:2012 Revision 1 + Amendments 2, 3 and 4 + Technical Corrigendum 2**, in one book.

- **The numbering of existing guidelines is kept**, so everything in Parts 1–11 still applies with the same numbers (a few rules were amended or tightened).
- Full support for **C11 and C18** replaces the blanket ban of Rule 1.4 with specific guidelines.
- **Concurrency** (C11 threads) is covered for the first time.


---

## Main additions (C11/C18)

| Area | Where | Idea |
|---|---|---|
| `_Generic` selections | New chapter 23 (Rules 23.1 – 23.8) | Only use `_Generic` inside macros, with consistent, complete type lists |
| `_Noreturn` | Rules 17.9 – 17.11 | A `_Noreturn` function must not return and must be `void`; functions that never return should say so |
| `_Atomic`, `_Alignas` | Chapters 8, 9, 11, 12 | Rules for atomic objects and alignment specifiers |
| Random numbers | Rule 21.24 | Don't use `rand`/`srand` |
| Threads (`<threads.h>`) | Rules 22.11 – 22.20 | Correct use of threads, mutexes, condition variables and thread-specific storage |
| Concurrency design | Dir 5.1 – 5.3 | No data races, no deadlocks, no dynamic thread creation |

> ⚠️ This table is a summary from memory of the amendment contents. Check exact rule numbers and wording against your copy of MISRA C:2023 or C:2025 before citing them.


---

## MISRA C:2025 and related documents

- **MISRA C:2025** is the current edition. It refines and extends C:2023 with new and revised guidelines.
- **MISRA Compliance:2020**: how to claim compliance, deviate, and re-categorise.
- **MISRA C:2012 Addendum 2/3**: maps MISRA rules to ISO/IEC TS 17961 and CERT C (the security coding standards).
- **MISRA C++:2023**: the separate standard for C++17.

**Practical advice:** pick one edition per project, write it in your compliance plan, and configure your tools to match. Most tools let you select C:2012, C:2012 + amendments, C:2023 or C:2025.


---

<sub>[◀ Previous](11-library-and-resources.md) · [Contents](README.md) · [Next ▶](13-in-practice.md)</sub>
