/*
 * MISRA C:2012 Chapter 1 - The standard C environment - GOOD examples.
 */
#include <stdbool.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 1.1 === */
/* Strict ISO C only. This whole file builds with
 * -std=c99 -pedantic-errors, so the compiler enforces every constraint. */
static int32_t r1_1(int32_t limit)
{
    const int32_t doubled = limit * 2;
    return doubled;
}

/* === Rule 1.2 === */
/* The same logic in portable standard C. */
static int32_t r1_2(int32_t a, int32_t b)
{
    int32_t m = (a > b) ? a : b;
    if ((m >= 0) && (m <= 9))
    {
        m = 0;
    }
    return m;
}

/* === Rule 1.3 === */
/* Check the range before the operation that could overflow, and keep at
 * most one modification per expression. */
static int32_t r1_3(int32_t x)
{
    int32_t result = INT32_MAX;
    if (x < INT32_MAX)
    {
        result = x + 1;
    }
    return result;
}

/* === Rule 1.4 === */
/* Plain C99: "does not return in the fault case" is documented rather
 * than encoded with _Noreturn. The flag lets the caller decide. */
static void r1_4(volatile const bool *stop)
{
    while (!(*stop))
    {
        /* wait for the watchdog to reset the device */
    }
}

void r01_good(void)
{
    static volatile const bool stop = true;
    (void)r1_1(4);
    (void)r1_2(1, 2);
    (void)r1_3(5);
    r1_4(&stop);
}
