<sub>[◀ Previous](12-beyond-c2012.md) · [Contents](README.md) · Next ▶</sub>

# Part 13: Putting MISRA C into practice

**Tools, deviations, compliance and workflow.**


---

## Tooling: what a free tool really catches

We ran **cppcheck 2.13** with its MISRA addon over every `bad.c` in this repository (one file at a time):

| Result | Rules |
|---|---|
| ● Found by the MISRA addon | **109** |
| ◐ Found by a core check, but not reported as MISRA | **14** |
| ○ Not found | **31** |
| — Not analysed (example disabled or unparseable) | **4** |

What the misses have in common:

- **Undecidable rules** (9.1, 18.1, 13.1, 21.20): the answer depends on run-time paths.
- **System-scope rules** (5.1, 5.8, 8.6, 8.7): need the whole program at once.
- **Subtle semantic rules** (10.2, 12.5, 21.13, 21.14): need deeper analysis.

The per-rule result is on each rule slide and in the [cheatsheet](../CHEATSHEET.md). Reproduce it with `make misra` in `examples/`.

Commercial analysers (e.g. Polyspace, Helix QAC, LDRA, PC-lint Plus, Parasoft C/C++test, CodeSonar, Coverity) claim much higher coverage, but every vendor still lists rules that need manual review.


---

## A practical toolchain

1. **Compiler in strict mode:** `-std=c99 -pedantic-errors -Wall -Wextra -Werror`, plus `-Wconversion -Wsign-conversion` (these flag many essential-type issues).
2. **A MISRA checker** in CI on every commit (fail the build on new violations).
3. **Code review checklist** for the guidelines the tool can't decide.
4. **Unit tests and coverage** (dead code shows up as uncovered lines).
5. **A deviation log** under version control, next to the code.

Example CI step:

```yaml
- name: MISRA check
  run: |
    sudo apt-get install -y cppcheck
    cd examples && make && make misra-good
```


---

## Deviation record template

| Field | Example |
|---|---|
| **ID** | DEV-007 |
| **Guideline** | Rule 11.4 (Advisory) |
| **Scope** | `drivers/gpio_regs.h`, macro `GPIO_REG` only |
| **Justification** | Memory-mapped peripheral registers at fixed addresses can only be reached by converting an integer address to a pointer |
| **Risk** | Wrong address or access width writes to the wrong peripheral |
| **Mitigation** | Addresses generated from the vendor SVD file; register access unit-tested on target; conversion confined to one macro |
| **Approved by** | [name, role], [date] |

In code, mark each use so reviewers and tools can find it:

```c
/* MISRA deviation DEV-007: Rule 11.4, see deviations.md */
#define GPIO_REG(addr)  (*(volatile uint32_t *)(addr))
```


---

## Guideline Compliance Summary (excerpt)

| Guideline | Category | Compliance |
|---|---|---|
| Dir 4.12 | Required | Compliant |
| Rule 8.7 | Advisory | Disapplied (see GRP-002) |
| Rule 10.3 | Required | Compliant |
| Rule 11.4 | Advisory | Deviations (DEV-007) |
| Rule 15.5 | Advisory | Disapplied (see GRP-003) |
| Rule 21.6 | Required | Deviations (DEV-002: logging module only) |
| Rule 9.1 | Mandatory | Compliant |

One line per guideline, kept up to date in each release. That's what an auditor asks for.


---

## Adopting MISRA on a real project

**New code:** enable the checker from day one and treat violations like compiler errors. It's far cheaper than retrofitting.

**Existing code:**

1. Run the tool to get a **baseline** (expect thousands of findings).
2. Turn on 🟥 Mandatory and high-value 🟧 Required rules first (Chapter 10, 9.1, 17.7, 15.6, 16.x).
3. Require **new and changed code** to be clean.
4. Pay down the baseline module by module, deviating where change is riskier than the violation.

**Common pitfalls:**

- "MISRA compliant" ≠ "correct". The guidelines remove classes of defects, not logic errors.
- Don't make code *worse* to silence a tool (deep nesting just for single exit, casts sprinkled everywhere).
- Suppressing a warning without a deviation record is not compliance.


---

## Where to go next

- 📘 Buy the guidelines from [misra.org.uk](https://misra.org.uk/) (MISRA C:2012 or C:2025, plus *MISRA Compliance:2020*).
- 🧪 Re-read each `bad.c` and try to fix it yourself before looking at `good.c`.
- 🔎 Run `make misra` and compare the tool's findings with the rule markers.
- 📋 Keep the [cheatsheet](../CHEATSHEET.md) next to your editor.

**Thanks for following along!** · [Back to contents](README.md)


---

<sub>[◀ Previous](12-beyond-c2012.md) · [Contents](README.md) · Next ▶</sub>
