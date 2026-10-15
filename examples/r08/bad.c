/*
 * MISRA C:2012 Chapter 8 - Declarations and definitions - BAD examples.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 8.1 === */
/* Implicit int: the type is never written. C99 compilers warn; newer
 * ones reject it outright, so it is hidden behind SHOW_COMPILE_ERRORS. */
#ifdef SHOW_COMPILE_ERRORS
static r8_1_counter = 0;
const r8_1_limit = 10;
#endif

/* === Rule 8.2 === */
/* Not a prototype: "()" means "unknown parameters", so calls are not
 * checked. And a prototype without parameter names. */
static int32_t r8_2_read();
static int32_t r8_2_scale(int32_t, int32_t);

static int32_t r8_2_read() { return 1; }
static int32_t r8_2_scale(int32_t value, int32_t factor) { return value * factor; }

/* === Rule 8.3 === */
/* Declaration and definition disagree on parameter names: a caller
 * reading the declaration swaps width and height. */
static int32_t r8_3_area(int32_t width, int32_t height);

static int32_t r8_3_area(int32_t height, int32_t width)
{
    return width * (height + 1);
}

/* === Rule 8.4 === */
/* An external object defined with no prior declaration in scope. Other
 * files declare it themselves, possibly with a different type. */
int32_t r8_4_counter = 0;

/* === Rule 8.5 === */
/* An external declaration written in a .c file (and repeated). It
 * belongs in exactly one header. */
extern int32_t r8_5_value;
extern int32_t r8_5_value;

/* === Rule 8.6 === */
/* Used but never defined anywhere: the program fails to link. (Two
 * definitions in two files would violate the rule too.) */
extern int32_t r8_6_missing;

static int32_t r8_6(void)
{
    return r8_6_missing;
}

/* === Rule 8.7 === */
/* External linkage for a helper only this file uses: it pollutes the
 * global namespace and invites name clashes. */
int32_t r8_7_helper(int32_t a);
int32_t r8_7_helper(int32_t a)
{
    return a + 1;
}

/* === Rule 8.8 === */
/* Declared static, defined without static. It is still internal, but
 * the definition misleads the reader. */
static int32_t r8_8_twice(int32_t a);

int32_t r8_8_twice(int32_t a)
{
    return a * 2;
}

/* === Rule 8.9 === */
/* File-scope object used in only one function. */
static int32_t r8_9_scratch;

static int32_t r8_9(int32_t a)
{
    r8_9_scratch = a * 3;
    return r8_9_scratch;
}

/* === Rule 8.10 === */
/* An inline function with external linkage. C99 then requires an
 * external definition elsewhere; behaviour differs between compilers. */
inline int32_t r8_10_square(int32_t a)
{
    return a * a;
}

/* === Rule 8.11 === */
/* External array declared without a size: users cannot check bounds. */
extern const int32_t r8_11_table[];

/* === Rule 8.12 === */
/* BLUE is implicitly GREEN + 1, which is 2: the same value as RED.
 * Two names, one value, and nobody wrote that down. */
enum r8_12_colour { RED = 2, GREEN = 1, BLUE };

/* === Rule 8.13 === */
/* The function only reads through the pointer but does not say so. */
static int32_t r8_13_sum(int32_t *values, int32_t n)
{
    int32_t total = 0;
    int32_t i;
    for (i = 0; i < n; i++)
    {
        total += values[i];
    }
    return total;
}

/* === Rule 8.14 === */
/* restrict: a promise of no aliasing that the compiler trusts blindly.
 * Calling it with overlapping buffers is undefined behaviour. */
static void r8_14_copy(int32_t *restrict dst, const int32_t *restrict src)
{
    dst[0] = src[0];
}

void r08_bad(void)
{
    int32_t v[2] = { 1, 2 };
    (void)r8_2_read();
    (void)r8_2_scale(1, 2);
    (void)r8_3_area(2, 3);
    (void)r8_6();
    (void)r8_7_helper(1);
    (void)r8_8_twice(1);
    (void)r8_9(1);
    (void)r8_10_square(2);
    (void)r8_13_sum(v, 2);
    r8_14_copy(v, v);           /* overlapping: undefined */
    r8_4_counter = BLUE + r8_5_value + r8_11_table[0];
}
