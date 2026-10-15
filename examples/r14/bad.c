/*
 * MISRA C:2012 Chapter 14 - Control statement expressions - BAD examples.
 */
#include <stddef.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 14.1 === */
/* A floating-point loop counter: 0.1 is not exact in binary, so this
 * loop may run 10 or 11 times depending on rounding. */
static int32_t r14_1(void)
{
    int32_t iterations = 0;
    float x;
    for (x = 0.0F; x < 1.0F; x += 0.1F)
    {
        iterations++;
    }
    return iterations;
}

/* === Rule 14.2 === */
/* A badly formed for loop: the counter is also changed in the body, and
 * the condition changes another object. */
static int32_t r14_2(const int32_t *data, int32_t n)
{
    int32_t i;
    int32_t found = 0;
    for (i = 0; (i < n) && (found++ < 5); i++)
    {
        if (data[i] == 0)
        {
            i++;                    /* skips an element */
        }
    }
    return found;
}

/* === Rule 14.3 === */
/* Controlling expressions that can never change: an unsigned value is
 * always >= 0, and a uint8_t is always < 300 (an infinite loop). */
static uint32_t r14_3(uint8_t u8)
{
    uint32_t n = 0U;
    uint8_t i;
    if (u8 >= 0U)
    {
        n = 1U;
    }
    for (i = 0U; i < 300U; i++)
    {
        n++;
    }
    return n;
}

/* === Rule 14.4 === */
/* Non-Boolean controlling expressions: integers and pointers tested
 * for "truth". */
static int32_t r14_4(uint32_t count, const int32_t *p)
{
    int32_t result = 0;
    if (count)
    {
        result = 1;
    }
    while (p)
    {
        p = NULL;
    }
    return result;
}

void r14_bad(void)
{
    const int32_t data[4] = { 1, 0, 2, 3 };
    (void)r14_1();
    (void)r14_2(data, 4);
    (void)r14_3(1U);
    (void)r14_4(1U, data);
}
