/*
 * MISRA C:2012 Chapter 10 - The essential type model - BAD examples.
 *
 * "Essential type" is MISRA's stricter view of C's types: Boolean,
 * character, signed, unsigned, enum and floating are separate categories,
 * and the integer promotions are ignored. A uint8_t stays an 8-bit
 * unsigned value even though C promotes it to int.
 */
#include <stdbool.h>
#include <stdint.h>
#include "misra_examples.h"

enum colour { COLOUR_RED, COLOUR_GREEN, COLOUR_BLUE };

/* === Rule 10.1 === */
/* Operands of the wrong category: arithmetic on a Boolean, shifts and
 * bitwise operations on signed values, arithmetic on an enum. */
static int32_t r10_1(bool flag, int32_t s, enum colour c)
{
    int32_t a = flag + 1;           /* Boolean used as a number */
    int32_t b = s << 2;             /* shifting a signed (maybe negative) value */
    int32_t d = s & 0x0F;           /* bitwise AND on a signed value */
    int32_t e = c * 2;              /* enum used as a number */
    return a + b + d + e;
}

/* === Rule 10.2 === */
/* Characters used as numbers: adding two characters, or multiplying one,
 * has no meaning as text. */
static char r10_2(char c1, char c2)
{
    char sum = c1 + c2;
    char twice = c1 * 2;
    return sum + twice;
}

/* === Rule 10.3 === */
/* Assignments to a narrower type or a different category. Each one
 * converts silently. */
static int32_t r10_3(uint16_t u16, int32_t s32, uint32_t u32)
{
    uint8_t small = u16;            /* narrower: high byte is lost */
    uint32_t u = s32;               /* signed to unsigned: -1 becomes 4294967295 */
    int32_t s = u32;                /* unsigned to signed */
    float f = s32;                  /* integer to floating: may lose precision */
    bool b = 1;                     /* number to Boolean */
    return (int32_t)small + (int32_t)u + s + (int32_t)f + (b ? 1 : 0);
}

/* === Rule 10.4 === */
/* Mixing signed and unsigned in one operation. The signed operand is
 * converted to unsigned, so -1 compares GREATER than 1U. */
static bool r10_4(int32_t s32, uint32_t u32)
{
    uint32_t sum = u32 + s32;
    return (s32 < u32) && (sum > 0U) && ((u32 + 1) > 0U);   /* "1" is signed */
}

/* === Rule 10.5 === */
/* Casts to an inappropriate category. */
static enum colour r10_5(uint32_t count, bool flag)
{
    bool any = (bool)count;         /* number to Boolean by cast */
    int32_t n = (int32_t)flag;      /* Boolean to number by cast */
    return (enum colour)(n + (any ? 1 : 0));    /* number to enum: may be invalid */
}

/* === Rule 10.6 === */
/* A 16-bit sum assigned to a 32-bit object. On a 16-bit int target the
 * addition wraps BEFORE the widening, so the "wide" result is wrong. */
static uint32_t r10_6(uint16_t a, uint16_t b)
{
    uint32_t total = a + b;
    return total;
}

/* === Rule 10.7 === */
/* A composite (16-bit) expression combined with a wider operand: the
 * reader assumes 32-bit arithmetic, but (a + b) is done in 16 bits. */
static uint32_t r10_7(uint32_t scale, uint16_t a, uint16_t b)
{
    return scale * (a + b);
}

/* === Rule 10.8 === */
/* Casting a composite expression to a wider type or a different
 * category: the cast happens AFTER the narrow arithmetic. */
static uint32_t r10_8(uint16_t a, uint16_t b)
{
    uint32_t wide = (uint32_t)(a + b);      /* wider */
    int32_t diff = (int32_t)(a - b);        /* different category */
    return wide + (uint32_t)diff;
}

void r10_bad(void)
{
    (void)r10_1(true, 1, COLOUR_RED);
    (void)r10_2('a', 'b');
    (void)r10_3(300U, -1, 5U);
    (void)r10_4(-1, 1U);
    (void)r10_5(3U, true);
    (void)r10_6(1U, 2U);
    (void)r10_7(2U, 1U, 2U);
    (void)r10_8(1U, 2U);
}
