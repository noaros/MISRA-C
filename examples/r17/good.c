/*
 * MISRA C:2012 Chapter 17 - Functions - GOOD examples.
 */
#include <stddef.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 17.1 === */
/* A fixed, typed interface: an array and its length. */
static int32_t r17_1(const int32_t *values, size_t count)
{
    int32_t total = 0;
    size_t i;
    for (i = 0U; i < count; i++)
    {
        total += values[i];
    }
    return total;
}

/* === Rule 17.2 === */
/* Iteration with a bounded, analysable stack. */
static uint32_t r17_2(uint32_t n)
{
    uint32_t result = 1U;
    uint32_t i;
    for (i = 2U; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

/* === Rule 17.3 === */
/* Every function is declared (prototyped) before it is called. */
static int32_t helper(int32_t value);

static int32_t r17_3(void)
{
    return helper(3);
}

static int32_t helper(int32_t value)
{
    return value + 1;
}

/* === Rule 17.4 === */
/* Every path returns a value explicitly. */
static int32_t r17_4(int32_t x)
{
    int32_t result = 0;
    if (x > 0)
    {
        result = x;
    }
    return result;
}

/* === Rule 17.5 === */
/* The argument has (at least) the number of elements the parameter
 * declares. */
#define R17_SET_SIZE 4U

static int32_t r17_5_sum(const int32_t values[R17_SET_SIZE])
{
    return values[0] + values[1] + values[2] + values[3];
}

static int32_t r17_5(void)
{
    const int32_t set[R17_SET_SIZE] = { 1, 2, 3, 4 };
    return r17_5_sum(set);
}

/* === Rule 17.6 === */
/* No "static" in array parameters. */
static int32_t r17_6(const int32_t values[R17_SET_SIZE])
{
    return values[3];
}

/* === Rule 17.7 === */
/* Use the result, or discard it explicitly with (void) to show the
 * decision was deliberate. */
static int32_t save_settings(void)
{
    return -1;
}

static int32_t r17_7(void)
{
    int32_t status = save_settings();
    if (status != 0)
    {
        status = -1;                /* report the failure upward */
    }
    return status;
}

/* === Rule 17.8 === */
/* Work on a local copy; the parameter keeps the caller's value. */
static int32_t r17_8(int32_t x)
{
    int32_t doubled = x * 2;
    return doubled;
}

void r17_good(void)
{
    const int32_t four[R17_SET_SIZE] = { 1, 2, 3, 4 };
    (void)r17_1(four, R17_SET_SIZE);
    (void)r17_2(5U);
    (void)r17_3();
    (void)r17_4(1);
    (void)r17_5();
    (void)r17_6(four);
    (void)r17_7();
    (void)r17_8(1);
}
