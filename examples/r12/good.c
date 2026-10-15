/*
 * MISRA C:2012 Chapter 12 - Expressions - GOOD examples.
 */
#include <stddef.h>
#include <stdint.h>
#include "misra_examples.h"

#define READY_MASK  0x04U

/* === Rule 12.1 === */
/* Parentheses state the intended grouping. */
static uint32_t r12_1(uint32_t flags, uint32_t a, uint32_t b)
{
    uint32_t result = a << (b + 1U);
    if ((flags & READY_MASK) == 0U)
    {
        result = 0U;
    }
    return result;
}

/* === Rule 12.2 === */
/* Widen before shifting, and check variable shift counts. */
static uint32_t r12_2(uint8_t byte, uint32_t word, uint32_t n)
{
    uint16_t high = (uint16_t)((uint16_t)byte << 8U);
    uint32_t shifted = 0U;
    if (n < 32U)
    {
        shifted = word << n;
    }
    return (uint32_t)high + shifted;
}

/* === Rule 12.3 === */
/* One loop variable in the for header; separate statements elsewhere. */
static int32_t r12_3(int32_t a, int32_t b)
{
    int32_t i;
    int32_t j = 9;
    int32_t x;
    int32_t a_copy = a;
    for (i = 0; i < j; i++)
    {
        j--;
    }
    a_copy++;
    x = b + a_copy;
    return x + i;
}

/* === Rule 12.4 === */
/* Name the value you mean. */
static uint32_t r12_4(void)
{
    return UINT32_MAX;
}

/* === Rule 12.5 === */
/* Pass the length explicitly; sizeof is only used on real arrays. */
#define R12_DATA_LEN 16U

static size_t r12_5(const int32_t *data, size_t length)
{
    size_t count = 0U;
    size_t i;
    for (i = 0U; i < length; i++)
    {
        if (data[i] != 0)
        {
            count++;
        }
    }
    return count;
}

void r12_good(void)
{
    const int32_t data[R12_DATA_LEN] = { 0 };
    (void)r12_1(4U, 1U, 2U);
    (void)r12_2(1U, 1U, 32U);
    (void)r12_3(1, 2);
    (void)r12_4();
    (void)r12_5(data, sizeof(data) / sizeof(data[0]));
}
