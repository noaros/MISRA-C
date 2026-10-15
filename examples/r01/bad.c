/*
 * MISRA C:2012 Chapter 1 - The standard C environment - BAD examples.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 1.1 === */
/* A constraint violation: modifying a const object. A conforming compiler
 * must reject this, so it is hidden behind SHOW_COMPILE_ERRORS.
 * Exceeding translation limits (e.g. more than 127 parameters, 63 levels
 * of nested parentheses) is the other half of this rule. */
#ifdef SHOW_COMPILE_ERRORS
static void r1_1(void)
{
    const int32_t limit = 10;
    limit = 20;
}
#endif

/* === Rule 1.2 === */
/* GNU extensions: a statement expression and a case range. Code like
 * this only compiles on GCC/Clang. */
static int32_t r1_2(int32_t a, int32_t b)
{
    int32_t m = ({ int32_t t = a; (t > b) ? t : b; });
    switch (m)
    {
        case 0 ... 9:
            m = 0;
            break;
        default:
            break;
    }
    return m;
}

/* === Rule 1.3 === */
/* Undefined behaviour: signed overflow, and modifying a variable twice
 * between sequence points. The compiler may do anything at all. */
static int32_t r1_3(void)
{
    int32_t big = INT32_MAX;
    int32_t i = 0;
    big = big + 1;          /* signed overflow */
    i = i++ + 1;            /* unsequenced modification */
    return big + i;
}

/* === Rule 1.4 === */
/* A C11 "emergent" feature (_Noreturn) used in a project that has not
 * adopted MISRA's C11 guidance. Amendment 2 lists these features as not
 * yet trusted; MISRA C:2023 replaces the blanket ban with specific rules. */
static _Noreturn void r1_4(void)
{
    for (;;)
    {
    }
}

void r01_bad(void)
{
    (void)r1_2(1, 2);
    (void)r1_3();
    r1_4();
}
