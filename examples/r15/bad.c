/*
 * MISRA C:2012 Chapter 15 - Control flow - BAD examples.
 */
#include <stdbool.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 15.1 === */
/* goto: control flow that is hard to follow and to analyse. */
static int32_t r15_1(int32_t x)
{
    int32_t result = 0;
    if (x < 0)
    {
        goto done;
    }
    result = x * 2;
done:
    return result;
}

/* === Rule 15.2 === */
/* A backwards goto: an unstructured loop. */
static int32_t r15_2(int32_t x)
{
    int32_t n = x;
again:
    n--;
    if (n > 0)
    {
        goto again;
    }
    return n;
}

/* === Rule 15.3 === */
/* goto into a nested block, skipping the initialisation of "y". */
static int32_t r15_3(int32_t x)
{
    if (x > 0)
    {
        goto inside;
    }
    {
        int32_t y = 5;
inside:
        x = x + y;                  /* y may be uninitialised */
    }
    return x;
}

/* === Rule 15.4 === */
/* A loop with several exits: every break is another path to reason
 * about. */
static int32_t r15_4(const int32_t *data, int32_t n)
{
    int32_t i;
    for (i = 0; i < n; i++)
    {
        if (data[i] < 0)
        {
            break;
        }
        if (data[i] == 99)
        {
            break;
        }
    }
    return i;
}

/* === Rule 15.5 === */
/* Several return statements: clean-up code at the end can be skipped. */
static int32_t r15_5(int32_t x)
{
    if (x < 0)
    {
        return -1;
    }
    if (x == 0)
    {
        return 0;
    }
    return 1;
}

/* === Rule 15.6 === */
/* Bodies without braces: the second statement LOOKS guarded but
 * always runs (the "goto fail" class of bug). */
static int32_t r15_6(int32_t x)
{
    int32_t errors = 0;
    if (x < 0)
        errors++;
        x = 0;                      /* always executes */
    while (x > 10)
        x--;
    return errors + x;
}

/* === Rule 15.7 === */
/* An if / else-if chain with no final else: was the remaining case
 * forgotten or deliberately ignored? */
static int32_t r15_7(int32_t x)
{
    int32_t category = 0;
    if (x < 0)
    {
        category = -1;
    }
    else if (x > 0)
    {
        category = 1;
    }
    return category;
}

void r15_bad(void)
{
    const int32_t data[3] = { 1, 99, 2 };
    (void)r15_1(1);
    (void)r15_2(3);
    (void)r15_3(1);
    (void)r15_4(data, 3);
    (void)r15_5(1);
    (void)r15_6(1);
    (void)r15_7(1);
}
