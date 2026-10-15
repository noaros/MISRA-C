/*
 * MISRA C:2012 Chapter 2 - Unused code - BAD examples.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 2.1 === */
/* Unreachable code: nothing after the return can ever execute. */
static int32_t r2_1(int32_t x)
{
    return x;
    x = x + 1;              /* unreachable */
}

/* === Rule 2.2 === */
/* Dead code: it executes, but removing it would change nothing. */
static int32_t r2_2(int32_t a)
{
    int32_t scaled = a * 2;     /* computed, never used */
    a + 0;                      /* expression with no effect */
    return a;
}

/* === Rule 2.3 === */
/* A type declared and never used. */
static int32_t r2_3(int32_t a)
{
    typedef int16_t unused_sample_t;
    return a;
}

/* === Rule 2.4 === */
/* A tag declared and never used. */
struct r2_4_unused_tag
{
    int16_t field;
};

/* === Rule 2.5 === */
/* A macro defined and never used. */
#define R2_5_UNUSED_LIMIT   42U

/* === Rule 2.6 === */
/* A label that nothing jumps to. */
static int32_t r2_6(int32_t a)
{
retry:
    return a;
}

/* === Rule 2.7 === */
/* A parameter the function never reads. */
static int32_t r2_7(int32_t a, int32_t unused_scale)
{
    return a;
}

void r02_bad(void)
{
    (void)r2_1(1);
    (void)r2_2(1);
    (void)r2_3(1);
    (void)r2_6(1);
    (void)r2_7(1, 2);
}
