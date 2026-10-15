/*
 * MISRA C:2012 Chapter 9 - Initialization - GOOD examples.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 9.1 === */
/* Every path sets the value before it is read. */
static int32_t r9_1(int32_t flag)
{
    int32_t result = 0;
    if (flag > 0)
    {
        result = 1;
    }
    return result;
}

/* === Rule 9.2 === */
/* Braces mirror the structure of the aggregate. */
static int32_t r9_2(void)
{
    int32_t matrix[2][2] = { { 1, 2 }, { 3, 4 } };
    return matrix[1][0];
}

/* === Rule 9.3 === */
/* Initialise every element, or use { 0 } to zero the whole array (an
 * explicit exception to the rule). */
static int32_t r9_3(void)
{
    int32_t gains[4] = { 10, 20, 30, 40 };
    int32_t zeros[4] = { 0 };
    return gains[3] + zeros[3];
}

/* === Rule 9.4 === */
/* Each element initialised exactly once. */
static int32_t r9_4(void)
{
    int32_t table[3] = { [0] = 3, [1] = 2, [2] = 0 };
    return table[0];
}

/* === Rule 9.5 === */
/* Designated initialisers with an explicit array size. */
static int32_t r9_5(void)
{
    int32_t sparse[6] = { [5] = 1 };
    return sparse[0];
}

void r09_good(void)
{
    (void)r9_1(0);
    (void)r9_2();
    (void)r9_3();
    (void)r9_4();
    (void)r9_5();
}
