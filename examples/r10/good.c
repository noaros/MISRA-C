/*
 * MISRA C:2012 Chapter 10 - The essential type model - GOOD examples.
 */
#include <stdbool.h>
#include <stdint.h>
#include "misra_examples.h"

enum colour { COLOUR_RED, COLOUR_GREEN, COLOUR_BLUE };

/* === Rule 10.1 === */
/* Booleans are tested, shifts and masks use unsigned values, and enums
 * are compared rather than used as numbers. */
static uint32_t r10_1(bool flag, uint32_t u, enum colour c)
{
    uint32_t a = 0U;
    uint32_t b = u << 2U;
    uint32_t d = u & 0x0FU;
    uint32_t e = 0U;
    if (flag)
    {
        a = 1U;
    }
    if (c == COLOUR_RED)
    {
        e = 1U;
    }
    return a + b + d + e;
}

/* === Rule 10.2 === */
/* The permitted character arithmetic: digit to character and
 * character to digit. These are the patterns Rule 10.2 explicitly
 * allows; some tools (cppcheck 2.13) still report them under 10.3, a
 * known false positive worth recognising. */
static int32_t r10_2(int32_t digit, char c)
{
    char digit_char = '0' + digit;      /* character + integer -> character */
    int32_t value = c - '0';            /* character - character -> integer */
    return (digit_char == c) ? value : -1;
}

/* === Rule 10.3 === */
/* Narrow or re-categorise only with an explicit, range-checked cast. */
static uint8_t r10_3(uint16_t u16)
{
    uint8_t small = UINT8_MAX;
    bool in_range = (u16 <= UINT8_MAX);
    if (in_range)
    {
        small = (uint8_t)u16;
    }
    return small;
}

/* === Rule 10.4 === */
/* Both operands in the same category; constants carry the U suffix. */
static bool r10_4(int32_t s32, uint32_t u32)
{
    bool less = true;
    if (s32 >= 0)
    {
        less = ((uint32_t)s32 < u32);
    }
    return less && ((u32 + 1U) > 0U);
}

/* === Rule 10.5 === */
/* Use comparisons and explicit mappings instead of casts. */
static enum colour r10_5(uint32_t count, bool flag)
{
    enum colour result = COLOUR_RED;
    bool any = (count != 0U);
    if (any && flag)
    {
        result = COLOUR_BLUE;
    }
    else if (any)
    {
        result = COLOUR_GREEN;
    }
    else
    {
        /* no change: COLOUR_RED */
    }
    return result;
}

/* === Rule 10.6 === */
/* Widen an operand first so the arithmetic itself is 32-bit. */
static uint32_t r10_6(uint16_t a, uint16_t b)
{
    uint32_t total = (uint32_t)a + (uint32_t)b;
    return total;
}

/* === Rule 10.7 === */
/* Widen inside the parentheses so every step is 32-bit. */
static uint32_t r10_7(uint32_t scale, uint16_t a, uint16_t b)
{
    return scale * ((uint32_t)a + (uint32_t)b);
}

/* === Rule 10.8 === */
/* Cast the operands, not the composite result. */
static int32_t r10_8(uint16_t a, uint16_t b)
{
    int32_t diff = (int32_t)a - (int32_t)b;
    return diff;
}

void r10_good(void)
{
    (void)r10_1(true, 1U, COLOUR_RED);
    (void)r10_2(7, '7');
    (void)r10_3(300U);
    (void)r10_4(-1, 1U);
    (void)r10_5(3U, true);
    (void)r10_6(1U, 2U);
    (void)r10_7(2U, 1U, 2U);
    (void)r10_8(1U, 2U);
}
