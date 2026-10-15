/*
 * MISRA C:2012 Chapter 9 - Initialization - BAD examples.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 9.1 === */
/* Reading an automatic variable before it is set: its value is
 * indeterminate, so the result is garbage (or undefined behaviour). */
static int32_t r9_1(int32_t flag)
{
    int32_t result;
    if (flag > 0)
    {
        result = 1;
    }
    return result;          /* unset when flag <= 0 */
}

/* === Rule 9.2 === */
/* Nested aggregate initialised without the inner braces. */
static int32_t r9_2(void)
{
    int32_t matrix[2][2] = { 1, 2, 3, 4 };
    return matrix[1][0];
}

/* === Rule 9.3 === */
/* Partially initialised array: was the missing data forgotten? */
static int32_t r9_3(void)
{
    int32_t gains[4] = { 10, 20 };
    return gains[3];
}

/* === Rule 9.4 === */
/* The same element initialised twice: only the last one wins. */
static int32_t r9_4(void)
{
    int32_t table[3] = { [0] = 1, [1] = 2, [0] = 3 };
    return table[0];
}

/* === Rule 9.5 === */
/* Designated initialisers decide the size implicitly: this array has 6
 * elements, which nobody wrote down. */
static int32_t r9_5(void)
{
    int32_t sparse[] = { [5] = 1 };
    return sparse[0];
}

void r09_bad(void)
{
    (void)r9_1(0);
    (void)r9_2();
    (void)r9_3();
    (void)r9_4();
    (void)r9_5();
}
