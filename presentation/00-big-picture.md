<sub>◀ Previous · [Contents](README.md) · [Next ▶](01-directives.md)</sub>

# MISRA C: the big picture

**A guided tour of MISRA C:2012 (with Amendments 1 and 2), the coding guidelines for safety- and security-critical C.**

Part 0 of 13 · [Contents](README.md)

> Use the arrows at the top and bottom of each page to move between parts. Each `---` line is a slide break.


---

## What is MISRA C?

- A set of **guidelines** that define a safer **subset of the C language**.
- Published by **MISRA** (originally the *Motor Industry Software Reliability Association*, UK).
- Goal: C code that is **safe, secure, portable and reliable**, and that tools and reviewers can **analyse**.
- MISRA C doesn't add features. It tells you **which parts of C to avoid**, and **how to use the rest**.

> "C is a powerful language, but it gives you more than enough rope."


---

## A short history

| Edition | Year | Notes |
|---|---|---|
| MISRA C:1998 | 1998 | Written for automotive software, C90 |
| MISRA C:2004 | 2004 | Broadened to all critical industries |
| **MISRA C:2012** | 2013 | Major rewrite: **directives + rules**, C99 support, *decidability*, the *essential type model* |
| Amendment 1 | 2016 | **Security** guidelines (Dir 4.14, Rules 12.5, 21.13–21.20, 22.7–22.10) |
| C:2012 Revision 1 | 2019 | Folds in Amendment 1 and Technical Corrigendum 1 |
| Amendment 2 | 2020 | C11/C18 baseline (Rule 1.4 "emergent features", Rule 21.21) |
| Amendments 3 and 4 | 2022–23 | C11 features in detail, then **multithreading** |
| MISRA C:2023 | 2023 | One consolidated document: C:2012 plus Amendments 1–4 |
| MISRA C:2025 | 2025 | The latest edition |

This course covers **C:2012 + Amendments 1 and 2**: the 17 directives and 158 rules most projects and tools still reference. [Part 12](12-beyond-c2012.md) summarises what came later.


---

## Why does C need this?

C was designed for flexibility and speed, not safety. The standard deliberately leaves many things open:

| Kind | Meaning | Example |
|---|---|---|
| **Undefined behaviour** | *Anything* can happen, including "seems to work" | Signed overflow, out-of-bounds access, using an uninitialised variable |
| **Unspecified behaviour** | One of several outcomes, not documented | Order in which function arguments are evaluated |
| **Implementation-defined** | Compiler chooses and documents | Size of `int`, signedness of `char`, `>>` on negative numbers |

C99 lists **about 190 undefined behaviours** in its Annex J. Optimising compilers *exploit* them: a check that "can't be true" under the standard's rules may simply be deleted.

On top of that, C has features that are **easy to misuse**: `=` vs `==`, fall-through in `switch`, implicit conversions, macros.


---

## Who uses MISRA C?

MISRA C is referenced (directly or as "an accepted coding standard") by functional-safety standards:

| Industry | Standard |
|---|---|
| Automotive | ISO 26262 |
| Aerospace | DO-178C |
| Medical devices | IEC 62304 |
| Railway | EN 50128 / EN 50716 |
| Industrial / generic | IEC 61508 |

It's also widely used outside regulated industries, anywhere embedded C must not fail: IoT, robotics, defence and space.


---

## Two kinds of guideline

| | **Directive** | **Rule** |
|---|---|---|
| What it covers | Process, documentation, design | The source code itself |
| How you check it | Reviews, requirements, design documents, *and* code | From the source code alone |
| Count (C:2012 + Amd 1 + Amd 2) | **17** (Dir 1.1 – Dir 4.14) | **158** (Rule 1.1 – Rule 22.10) |
| Example | *Dir 4.12: Don't use dynamic memory* | *Rule 21.3: Don't call `malloc`/`free`* |

Directives often have a matching rule. The directive states the goal; the rule is the checkable part.


---

## Three categories

| Category | Meaning | Can you deviate? |
|---|---|---|
| 🟥 **Mandatory** (16 rules) | Must always be followed | **Never** |
| 🟧 **Required** | Must be followed unless formally deviated | **Yes**, with a documented, approved deviation |
| 🟦 **Advisory** | Recommended good practice | Yes, and *disapplying* it needs less formality, but should still be recorded |

A project may make categories **stricter** (Advisory → Required, Required → Mandatory) in a *Guideline Re-categorization Plan*, but never more lenient.

The 16 mandatory rules are all about undefined behaviour or plain errors: 9.1, 12.5, 13.6, 17.3, 17.4, 17.6, 19.1, 21.13, 21.17–21.20, 22.2, 22.4–22.6.


---

## Decidable vs undecidable

- **Decidable**: a tool can *always* answer "compliant or not" from the code. Example: Rule 7.1 (no octal constants).
- **Undecidable**: the answer can depend on run-time values, so tools give **false positives or false negatives**. Example: Rule 9.1 (reading an uninitialised variable depends on which paths actually execute).

And by **scope**:

- **Single translation unit**: check one `.c` file at a time.
- **System**: need the whole program, e.g. Rule 8.6 (exactly one definition) or Rule 5.1 (distinct external names).

👉 This is why **no tool can prove full compliance** by itself, and why reviews still matter. [Part 13](13-in-practice.md) shows how much a free tool really catches on these examples.


---

## Deviations: breaking a rule on purpose

Sometimes following a rule makes things worse (e.g. hardware register access needs Rule 11.4's integer-to-pointer cast). MISRA's answer is a **deviation**: a documented, reviewed, approved exception.

A deviation record states:

1. **Which guideline** and **where** (file, function, or a whole pattern).
2. **Why** compliance isn't reasonable here.
3. **What could go wrong**, and **how that risk is mitigated** (tests, reviews, extra checks).
4. **Who approved it.**

You can't deviate from 🟥 Mandatory guidelines. Common patterns can be pre-approved as **deviation permits**. There's a template in [Part 13](13-in-practice.md).


---

## Claiming compliance

A project claims "MISRA compliant" with a **Guideline Compliance Summary**: one line per guideline saying

- **Compliant** (no violations),
- **Deviations** (violations exist, each covered by an approved deviation), or
- **Disapplied** (Advisory guideline the project chose not to apply).

The rules for doing this are in the separate document **MISRA Compliance:2020**.

> "MISRA compliant" means *every violation is accounted for*, not "zero warnings in one tool".


---

## The big themes

Almost every guideline serves one of these goals:

| Theme | Example guidelines |
|---|---|
| **No undefined behaviour** | 1.3, 9.1, 12.2, 13.2, 18.1, 19.1 |
| **Make types explicit and strict** (the *essential type model*) | Chapter 10, 7.2, Dir 4.6 |
| **Keep control flow simple and analysable** | Chapters 14–16, 17.2 |
| **No unbounded resources** | Dir 4.12, 17.2, 18.8, 21.3 |
| **Treat the preprocessor with suspicion** | Chapter 20, Dir 4.9 |
| **Use only the dependable parts of the library** | Chapters 21–22 |
| **Say what you mean** | 8.13, 12.1, 14.4, 15.6, 15.7, 16.4 |


---

## How the rest of this course works

Each guideline gets a slide:

```
### Rule 10.3 · 🟧 Required
**Plain-English summary**
**Why:** the risk the rule removes
[❌ Bad example] · [✅ Good example]   ← links to the exact lines of real code
🔎 cppcheck 2.13: found / not found     ← what a free tool caught
```

The code lives in [`examples/`](../examples): one `bad.c` and one `good.c` per chapter, each rule in its own marked block.

- Every `good.c` compiles cleanly with `-std=c99 -pedantic-errors -Wall -Wextra -Werror`, and they all run.
- Every `bad.c` compiles (with warnings), except a few blocks that no modern compiler accepts, which are hidden behind `SHOW_COMPILE_ERRORS`.

> ⚠️ The summaries are **paraphrases**, not the official MISRA wording (which is copyrighted). Get the real guidelines from [misra.org.uk](https://misra.org.uk/). They're inexpensive and have far more detail and examples.


---

## Try it yourself

```sh
cd examples
make            # build good (strict) and bad (warnings expected)
make run        # run every good example
make misra      # run the cppcheck MISRA addon on all files
./misra.sh r10/bad.c   # check one file
```

Requires `gcc` or `clang`, `make`, and optionally `cppcheck` (2.x) for the MISRA checks.


---

## Roadmap

| Part | Topic |
|---|---|
| [1](01-directives.md) | The directives (Dir 1.1 – 4.14) |
| [2](02-environment-and-hygiene.md) | Rules 1–4: standard C, unused code, comments, lexical traps |
| [3](03-identifiers-types-literals.md) | Rules 5–7: identifiers, bit-fields, literals |
| [4](04-declarations-and-initialization.md) | Rules 8–9: declarations, definitions, initialization |
| [5](05-essential-type-model.md) | Rule 10: **the essential type model** |
| [6](06-pointer-conversions.md) | Rule 11: pointer conversions |
| [7](07-expressions-and-side-effects.md) | Rules 12–13: expressions and side effects |
| [8](08-control-flow.md) | Rules 14–16: loops, `goto`, `if`, `switch` |
| [9](09-functions-pointers-arrays.md) | Rules 17–19: functions, pointers, arrays, overlap |
| [10](10-preprocessor.md) | Rule 20: the preprocessor |
| [11](11-library-and-resources.md) | Rules 21–22: standard library and resources |
| [12](12-beyond-c2012.md) | What MISRA C:2023 and C:2025 added |
| [13](13-in-practice.md) | Putting it into practice: tools, deviations, workflow |
| [Cheatsheet](../CHEATSHEET.md) | Everything on one page |


---

<sub>◀ Previous · [Contents](README.md) · [Next ▶](01-directives.md)</sub>
