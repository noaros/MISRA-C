/*
 * MISRA C:2012 Chapter 13 - Side effects - BAD examples.
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "misra_examples.h"

static int32_t next_id_counter = 0;

static int32_t next_id(void)
{
    next_id_counter++;
    return next_id_counter;
}

/* === Rule 13.1 === */
/* Side effects inside an initializer list: C does not say which
 * next_id() call runs first, so the pair may be {1,2} or {2,1}. */
static int32_t r13_1(void)
{
    int32_t pair[2] = { next_id(), next_id() };
    return pair[0];
}

/* === Rule 13.2 === */
/* The result depends on evaluation order. Is arr[i] written before or
 * after i is incremented? Undefined. */
static int32_t r13_2(void)
{
    int32_t arr[4] = { 0, 0, 0, 0 };
    int32_t i = 1;
    arr[i] = i++;
    return arr[1] + (next_id() - next_id());    /* unspecified order */
}

/* === Rule 13.3 === */
/* An increment combined with another side effect (the assignment). */
static void r13_3(uint8_t *buf, size_t idx, uint8_t value)
{
    buf[idx++] = value;
    buf[idx] = value;
}

/* === Rule 13.4 === */
/* Using the result of an assignment: "=" or "=="? */
static int32_t r13_4(void)
{
    int32_t a;
    int32_t b;
    int32_t n;
    a = b = 0;
    if ((n = next_id()) != 0)
    {
        a = n;
    }
    return a + b;
}

/* === Rule 13.5 === */
/* A side effect on the right of && only happens sometimes: the counter
 * is not incremented when x <= 0. */
static int32_t r13_5(int32_t x)
{
    static int32_t counter = 0;
    if ((x > 0) && (counter++ < 10))
    {
        x = 0;
    }
    return x;
}

/* === Rule 13.6 === */
/* The operand of sizeof is NOT evaluated: x is never incremented. */
static size_t r13_6(void)
{
    int32_t x = 0;
    size_t size = sizeof(x++);
    return size + (size_t)x;        /* x is still 0 */
}

void r13_bad(void)
{
    uint8_t buf[4] = { 0U };
    (void)r13_1();
    (void)r13_2();
    r13_3(buf, 0U, 1U);
    (void)r13_4();
    (void)r13_5(1);
    (void)r13_6();
}
