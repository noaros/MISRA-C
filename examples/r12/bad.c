/*
 * MISRA C:2012 Chapter 12 - Expressions - BAD examples.
 */
#include <stddef.h>
#include <stdint.h>
#include "misra_examples.h"

#define READY_MASK  0x04U

/* === Rule 12.1 === */
/* Relying on precedence. "==" binds tighter than "&", so the first
 * test is flags & (READY_MASK == 0U), i.e. always 0. And "+" binds
 * tighter than "<<". */
static uint32_t r12_1(uint32_t flags, uint32_t a, uint32_t b)
{
    uint32_t result = a << b + 1U;
    if (flags & READY_MASK == 0U)
    {
        result = 0U;
    }
    return result;
}

/* === Rule 12.2 === */
/* Shift amounts out of range for the operand's essential type. A
 * uint8_t shifted by 8, and a shift count that might be 32 or more
 * (undefined behaviour in C). */
static uint32_t r12_2(uint8_t byte, uint32_t word, uint32_t n)
{
    uint16_t high = byte << 8;
    return high + (word << n);      /* n == 32 is undefined */
}

/* === Rule 12.3 === */
/* The comma operator hides extra effects in places readers skim. */
static int32_t r12_3(int32_t a, int32_t b)
{
    int32_t i;
    int32_t j;
    int32_t x;
    for (i = 0, j = 9; i < j; i++, j--)
    {
    }
    x = (a++, b);
    return x + i;
}

/* === Rule 12.4 === */
/* A constant expression that wraps around: the intent ("all ones") is
 * hidden behind arithmetic that overflows. */
#define R12_4_ALL_ONES  (0U - 1U)

static uint32_t r12_4(void)
{
    return R12_4_ALL_ONES;
}

/* === Rule 12.5 === */
/* sizeof on an array parameter gives the size of a POINTER, not the
 * array: this "length" is 2 on a 64-bit machine, not 16. */
static size_t r12_5(const int32_t data[16])
{
    return sizeof(data) / sizeof(data[0]);
}

void r12_bad(void)
{
    const int32_t data[16] = { 0 };
    (void)r12_1(4U, 1U, 2U);
    (void)r12_2(1U, 1U, 32U);
    (void)r12_3(1, 2);
    (void)r12_4();
    (void)r12_5(data);
}
