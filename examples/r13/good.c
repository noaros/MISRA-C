/*
 * MISRA C:2012 Chapter 13 - Side effects - GOOD examples.
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "misra_examples.h"

static int32_t next_id(void)
{
    static int32_t next_id_counter = 0;
    next_id_counter++;
    return next_id_counter;
}

/* === Rule 13.1 === */
/* Do the side effects first, in a defined order. */
static int32_t r13_1(void)
{
    int32_t first = next_id();
    int32_t second = next_id();
    int32_t pair[2] = { 0, 0 };
    pair[0] = first;
    pair[1] = second;
    return pair[0] + pair[1];
}

/* === Rule 13.2 === */
/* One side effect per statement, so order cannot matter. */
static int32_t r13_2(void)
{
    int32_t arr[4] = { 0, 0, 0, 0 };
    int32_t i = 1;
    int32_t a;
    int32_t b;
    arr[i] = i;
    i++;
    a = next_id();
    b = next_id();
    return arr[1] + (a - b) + i;
}

/* === Rule 13.3 === */
/* The increment stands alone. */
static void r13_3(uint8_t *buf, size_t idx, uint8_t value)
{
    size_t pos = idx;
    buf[pos] = value;
    pos++;
    buf[pos] = value;
}

/* === Rule 13.4 === */
/* Assignments are statements, never values. */
static int32_t r13_4(void)
{
    int32_t a = 0;
    int32_t b = 0;
    int32_t n = next_id();
    if (n != 0)
    {
        a = n;
    }
    return a + b;
}

/* === Rule 13.5 === */
/* Make the side effect unconditional (or conditional on purpose,
 * visibly), then test. */
static int32_t r13_5(int32_t x)
{
    static int32_t counter = 0;
    int32_t result = x;
    if (x > 0)
    {
        bool under_limit = (counter < 10);
        counter++;
        if (under_limit)
        {
            result = 0;
        }
    }
    return result;
}

/* === Rule 13.6 === */
/* sizeof on a plain object; side effects are separate statements. */
static size_t r13_6(void)
{
    int32_t x = 0;
    size_t size = sizeof(x);
    x++;
    return size + (size_t)x;
}

void r13_good(void)
{
    uint8_t buf[4] = { 0 };
    (void)r13_1();
    (void)r13_2();
    r13_3(buf, 0U, 1U);
    (void)r13_4();
    (void)r13_5(1);
    (void)r13_6();
}
