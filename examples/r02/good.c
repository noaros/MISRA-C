/*
 * MISRA C:2012 Chapter 2 - Unused code - GOOD examples.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 2.1 === */
/* Every statement can execute. */
static int32_t r2_1(int32_t x)
{
    int32_t result = x;
    if (x < 100)
    {
        result = x + 1;
    }
    return result;
}

/* === Rule 2.2 === */
/* Every operation contributes to the result. */
static int32_t r2_2(int32_t a)
{
    int32_t scaled = a * 2;
    return scaled;
}

/* === Rule 2.3 === */
/* Declare a type only where it is used. */
typedef int16_t sample_t;

static sample_t r2_3(sample_t a)
{
    return a;
}

/* === Rule 2.4 === */
/* The tag is used. */
struct r2_4_point
{
    int16_t x;
    int16_t y;
};

static int16_t r2_4(const struct r2_4_point *p)
{
    return p->x;
}

/* === Rule 2.5 === */
/* The macro is used. */
#define R2_5_LIMIT  42

static int32_t r2_5(int32_t a)
{
    return (a > R2_5_LIMIT) ? R2_5_LIMIT : a;
}

/* === Rule 2.6 === */
/* No stray labels: the loop needs none. */
static int32_t r2_6(int32_t a)
{
    return a;
}

/* === Rule 2.7 === */
/* Every parameter is used. If an interface forces an unused parameter,
 * MISRA accepts a documented deviation, or remove it from the API. */
static int32_t r2_7(int32_t a, int32_t scale)
{
    return a * scale;
}

void r02_good(void)
{
    const struct r2_4_point p = { 1, 2 };
    (void)r2_1(1);
    (void)r2_2(1);
    (void)r2_3(1);
    (void)r2_4(&p);
    (void)r2_5(1);
    (void)r2_6(1);
    (void)r2_7(1, 2);
}
