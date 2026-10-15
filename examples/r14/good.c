/*
 * MISRA C:2012 Chapter 14 - Control statement expressions - GOOD examples.
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 14.1 === */
/* Count with an integer; derive the floating value from it. */
static int32_t r14_1(void)
{
    int32_t iterations = 0;
    int32_t step;
    for (step = 0; step < 10; step++)
    {
        float x = (float)step * 0.1F;
        if (x < 1.0F)
        {
            iterations++;
        }
    }
    return iterations;
}

/* === Rule 14.2 === */
/* A well-formed for loop: one counter, initialised, tested and stepped
 * in the header only. Other logic lives in the body. */
static int32_t r14_2(const int32_t *data, int32_t n)
{
    int32_t i;
    int32_t found = 0;
    for (i = 0; i < n; i++)
    {
        if ((data[i] == 0) && (found < 5))
        {
            found++;
        }
    }
    return found;
}

/* === Rule 14.3 === */
/* Conditions that can really be true or false, and a counter wide
 * enough for its range. (An intentional infinite loop such as
 * "for (;;)" is a permitted exception.) */
static uint32_t r14_3(uint8_t u8)
{
    uint32_t n = 0U;
    uint16_t i;
    if (u8 > 0U)
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
/* Every controlling expression is essentially Boolean. */
static int32_t r14_4(uint32_t count, const int32_t *p)
{
    int32_t result = 0;
    const int32_t *q = p;
    if (count != 0U)
    {
        result = 1;
    }
    while (q != NULL)
    {
        q = NULL;
    }
    return result;
}

void r14_good(void)
{
    const int32_t data[4] = { 1, 0, 2, 3 };
    (void)r14_1();
    (void)r14_2(data, 4);
    (void)r14_3(1U);
    (void)r14_4(1U, data);
}
