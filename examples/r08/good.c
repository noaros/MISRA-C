/*
 * MISRA C:2012 Chapter 8 - Declarations and definitions - GOOD examples.
 */
#include <stdint.h>
#include "misra_examples.h"
#include "good.h"

/* === Rule 8.1 === */
/* Every declaration states its type. */
static int32_t r8_1(void)
{
    const int32_t limit = 10;
    int32_t counter = limit;
    return counter;
}

/* === Rule 8.2 === */
/* Prototypes everywhere: (void) for "no parameters", and named
 * parameters that document their meaning. */
static int32_t r8_2_read(void);
static int32_t r8_2_scale(int32_t value, int32_t factor);

static int32_t r8_2_read(void)
{
    return 1;
}

static int32_t r8_2_scale(int32_t value, int32_t factor)
{
    return value * factor;
}

/* === Rule 8.3 === */
/* Declaration and definition match exactly. */
static int32_t r8_3_area(int32_t width, int32_t height);

static int32_t r8_3_area(int32_t width, int32_t height)
{
    return width * height;
}

/* === Rule 8.4 === */
/* good.h declares "extern int32_t r08_counter;" and is included above,
 * so the compiler checks this definition against it. */
int32_t r08_counter = 0;

/* === Rule 8.5 === */
/* The external declaration lives in good.h only, never in a .c file. */

/* === Rule 8.6 === */
/* Exactly one definition of each external object: here. */
const int32_t r08_table[R08_TABLE_SIZE] = { 1, 2, 3, 4 };

/* === Rule 8.7 === */
/* A helper used only in this file has internal linkage. */
static int32_t r8_7_helper(int32_t a)
{
    return a + 1;
}

/* === Rule 8.8 === */
/* "static" on every declaration of an internal function. */
static int32_t r8_8_twice(int32_t a);

static int32_t r8_8_twice(int32_t a)
{
    return a * 2;
}

/* === Rule 8.9 === */
/* An object used by one function is declared inside it. */
static int32_t r8_9(int32_t a)
{
    int32_t scratch = a * 3;
    return scratch;
}

/* === Rule 8.10 === */
/* Inline functions are static. */
static inline int32_t r8_10_square(int32_t a)
{
    return a * a;
}

/* === Rule 8.11 === */
/* good.h declares "extern const int32_t r08_table[R08_TABLE_SIZE];". */

/* === Rule 8.12 === */
/* Either give every enumerator a value or none: no hidden collisions. */
enum r8_12_colour { RED = 0, GREEN = 1, BLUE = 2 };

/* === Rule 8.13 === */
/* Read-only access through a pointer to const. */
static int32_t r8_13_sum(const int32_t *values, int32_t n)
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
/* No restrict: correctness does not depend on an unchecked promise. */
static void r8_14_copy(int32_t *dst, const int32_t *src)
{
    dst[0] = src[0];
}

void r08_good(void)
{
    int32_t v[2] = { 1, 2 };
    enum r8_12_colour c = BLUE;
    (void)r8_2_read();
    (void)r8_2_scale(1, 2);
    (void)r8_3_area(2, 3);
    (void)r8_7_helper(1);
    (void)r8_8_twice(1);
    (void)r8_9(1);
    (void)r8_10_square(2);
    (void)r8_13_sum(v, 2);
    r8_14_copy(&v[0], &v[1]);
    r08_counter = r08_table[0] + r8_1() + ((c == BLUE) ? 1 : 0);
}
