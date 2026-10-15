<sub>[◀ Previous](07-expressions-and-side-effects.md) · [Contents](README.md) · [Next ▶](09-functions-pointers-arrays.md)</sub>

# Part 8: Rules 14–16, control flow

**Loops whose iteration count you can reason about, structured jumps, braces everywhere, and switches in one simple shape.**


---

## The well-formed `for` loop (Rule 14.2)

```c
for (i = 0U; i < count; i++)   /* one counter: set here, tested here, stepped here */
{
    /* body: may READ i, must NOT modify i or the loop bound's variables */
}
```

- The first clause only initialises the counter (or is empty).
- The second clause has no side effects and tests the counter.
- The third clause only changes the counter.
- The body doesn't modify the counter.

If you need anything fancier, use a `while` loop.


---

## Chapter 14: Control statement expressions

Code: [`examples/r14/`](../examples/r14)


---

### Rule 14.1 · 🟧 Required

**Loop counters must not be floating-point.**

**Why:** Rounding makes the iteration count unpredictable (`0.1` is not exact in binary).

[❌ Bad example](../examples/r14/bad.c#L8-L20) · [✅ Good example](../examples/r14/good.c#L9-L24)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 14.2 · 🟧 Required

**A `for` loop must be well-formed.**

**Why:** One counter, set in the first clause, tested in the second, stepped in the third and not modified in the body. This keeps the iteration count analysable.

[❌ Bad example](../examples/r14/bad.c#L22-L37) · [✅ Good example](../examples/r14/good.c#L26-L41)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 14.3 · 🟧 Required

**Controlling expressions must not be invariant.**

**Why:** A condition that is always true or false (`u8 < 300`) is dead logic or an accidental infinite loop. Intentional infinite loops like `for (;;)` are allowed.

[❌ Bad example](../examples/r14/bad.c#L39-L55) · [✅ Good example](../examples/r14/good.c#L43-L60)

<sub>🔎 cppcheck 2.13: **not found**</sub>


---

### Rule 14.4 · 🟧 Required

**Conditions of `if` and loops must be essentially Boolean.**

**Why:** `if (count)` and `while (p)` hide what is being tested. Write `count != 0U` and `p != NULL`.

[❌ Bad example](../examples/r14/bad.c#L57-L72) · [✅ Good example](../examples/r14/good.c#L62-L77)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

## Chapter 15: Control flow

Code: [`examples/r15/`](../examples/r15)


---

### Rule 15.1 · 🟦 Advisory

**Don't use `goto`.**

**Why:** Unstructured jumps make control flow hard to follow and to analyse.

[❌ Bad example](../examples/r15/bad.c#L8-L20) · [✅ Good example](../examples/r15/good.c#L8-L18)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 15.2 · 🟧 Required

**`goto` may only jump forwards, to a later label in the same function.**

**Why:** Backward jumps create unstructured loops.

[❌ Bad example](../examples/r15/bad.c#L22-L34) · [✅ Good example](../examples/r15/good.c#L20-L31)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 15.3 · 🟧 Required

**A `goto` label must be in the same block as the `goto` or in an enclosing block.**

**Why:** Jumping into a block skips initialisations and breaks scope reasoning.

[❌ Bad example](../examples/r15/bad.c#L36-L50) · [✅ Good example](../examples/r15/good.c#L33-L44)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 15.4 · 🟦 Advisory

**Use at most one `break` or `goto` to leave a loop.**

**Why:** Every extra exit is another path to test and reason about.

[❌ Bad example](../examples/r15/bad.c#L52-L70) · [✅ Good example](../examples/r15/good.c#L46-L64)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 15.5 · 🟦 Advisory

**A function should have a single exit point, at the end.**

**Why:** One exit makes clean-up and post-conditions easy to verify (a much debated rule, often relaxed by projects).

[❌ Bad example](../examples/r15/bad.c#L72-L85) · [✅ Good example](../examples/r15/good.c#L66-L84)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 15.6 · 🟧 Required

**The body of every loop and `if`/`else`/`switch` must be a compound statement (braces).**

**Why:** Without braces, a second indented line looks guarded but isn't. This is the root of Apple's 'goto fail' bug.

[❌ Bad example](../examples/r15/bad.c#L87-L99) · [✅ Good example](../examples/r15/good.c#L86-L102)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 15.7 · 🟧 Required

**Every `if ... else if` chain must end with an `else`.**

**Why:** A final `else` shows that the remaining case was considered, even if it does nothing.

[❌ Bad example](../examples/r15/bad.c#L101-L116) · [✅ Good example](../examples/r15/good.c#L104-L123)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

## The well-formed `switch` (Rule 16.1)

```c
switch (mode)                  /* not Boolean (16.7) */
{
    case MODE_IDLE:            /* labels only at the top level (16.2) */
        stop_motor();
        break;                 /* every clause ends with break (16.3) */
    case MODE_RUN:
    case MODE_BOOST:           /* empty clauses may share code */
        run_motor();
        break;
    default:                   /* always present (16.4), first or last (16.5) */
        enter_safe_state();
        break;
}                              /* at least two clauses (16.6) */
```


---

## Chapter 16: Switch statements

Code: [`examples/r16/`](../examples/r16)


---

### Rule 16.1 · 🟧 Required

**Every `switch` statement must be well-formed.**

**Why:** Labels, clauses and breaks in a fixed, simple shape. The other rules in this chapter define it.

[❌ Bad example](../examples/r16/bad.c#L8-L24) · [✅ Good example](../examples/r16/good.c#L21-L36)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 16.2 · 🟧 Required

**Only use a `switch` label directly in the `switch` body.**

**Why:** Labels nested in inner blocks (Duff's device) create jumps into the middle of other statements.

[❌ Bad example](../examples/r16/bad.c#L26-L44) · [✅ Good example](../examples/r16/good.c#L38-L58)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 16.3 · 🟧 Required

**End every non-empty switch clause with an unconditional `break`.**

**Why:** Fall-through is a classic source of bugs, and readers can't tell whether it was intended.

[❌ Bad example](../examples/r16/bad.c#L46-L62) · [✅ Good example](../examples/r16/good.c#L60-L79)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 16.4 · 🟧 Required

**Every `switch` must have a `default` label.**

**Why:** Unexpected values (corrupt data, new enum members) must be handled deliberately.

[❌ Bad example](../examples/r16/bad.c#L64-L79) · [✅ Good example](../examples/r16/good.c#L81-L99)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 16.5 · 🟧 Required

**`default` must be the first or last label.**

**Why:** A `default` hidden among the cases is easy to miss.

[❌ Bad example](../examples/r16/bad.c#L81-L99) · [✅ Good example](../examples/r16/good.c#L101-L119)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 16.6 · 🟧 Required

**Every `switch` must have at least two clauses.**

**Why:** A one-clause `switch` is an `if` in disguise.

[❌ Bad example](../examples/r16/bad.c#L101-L113) · [✅ Good example](../examples/r16/good.c#L121-L131)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

### Rule 16.7 · 🟧 Required

**Don't switch on a Boolean expression.**

**Why:** Use `if`/`else`. A Boolean `switch` is confusing and some compilers mishandle it.

[❌ Bad example](../examples/r16/bad.c#L115-L129) · [✅ Good example](../examples/r16/good.c#L133-L143)

<sub>🔎 cppcheck 2.13: **found** by the MISRA addon</sub>


---

<sub>[◀ Previous](07-expressions-and-side-effects.md) · [Contents](README.md) · [Next ▶](09-functions-pointers-arrays.md)</sub>
