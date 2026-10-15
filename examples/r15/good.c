/*
 * MISRA C:2012 Chapter 15 - Control flow - GOOD examples.
 */
#include <stdbool.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 15.1 === */
/* Structured control flow instead of goto. */
static int32_t r15_1(int32_t x)
{
    int32_t result = 0;
    if (x >= 0)
    {
        result = x * 2;
    }
    return result;
}

/* === Rule 15.2 === */
/* A real loop instead of a backwards jump. (If goto is used at all
 * under a deviation of 15.1, it must only jump forwards.) */
static int32_t r15_2(int32_t x)
{
    int32_t n = x;
    do
    {
        n--;
    } while (n > 0);
    return n;
}

/* === Rule 15.3 === */
/* No jumps into blocks: declare first, then branch. */
static int32_t r15_3(int32_t x)
{
    int32_t y = 5;
    int32_t result = x;
    if (x <= 0)
    {
        result = x + y;
    }
    return result;
}

/* === Rule 15.4 === */
/* One exit condition, expressed in the loop header. */
static int32_t r15_4(const int32_t *data, int32_t n)
{
    int32_t i = 0;
    bool stop = false;
    while ((i < n) && (!stop))
    {
        if ((data[i] < 0) || (data[i] == 99))
        {
            stop = true;
        }
        else
        {
            i++;
        }
    }
    return i;
}

/* === Rule 15.5 === */
/* A single point of exit at the end. */
static int32_t r15_5(int32_t x)
{
    int32_t sign;
    if (x < 0)
    {
        sign = -1;
    }
    else if (x == 0)
    {
        sign = 0;
    }
    else
    {
        sign = 1;
    }
    return sign;
}

/* === Rule 15.6 === */
/* Always braces: what is guarded is exactly what is inside them. */
static int32_t r15_6(int32_t x)
{
    int32_t errors = 0;
    int32_t value = x;
    if (value < 0)
    {
        errors++;
        value = 0;
    }
    while (value > 10)
    {
        value--;
    }
    return errors + value;
}

/* === Rule 15.7 === */
/* A final else, even if it only holds a comment explaining why nothing
 * happens. */
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
    else
    {
        /* x == 0: category stays 0 */
    }
    return category;
}

void r15_good(void)
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
