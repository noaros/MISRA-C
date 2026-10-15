/*
 * MISRA C:2012 Chapter 19 - Overlapping storage - BAD examples.
 */
#include <stdint.h>
#include <string.h>
#include "misra_examples.h"

/* === Rule 19.1 === */
/* Copying between overlapping regions: memcpy has undefined behaviour
 * when source and destination overlap. */
static void r19_1(void)
{
    uint8_t buf[8] = { 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U };
    (void)memcpy(&buf[2], &buf[0], 4U);
}

/* === Rule 19.2 === */
/* A union used to reinterpret a float's bits: the layout is
 * implementation-defined (endianness, padding, representation). */
union r19_2_pun
{
    float    f;
    uint32_t u;
};

static uint32_t r19_2(float value)
{
    union r19_2_pun pun;
    pun.f = value;
    return pun.u;                   /* reads the member not last written */
}

void r19_bad(void)
{
    r19_1();
    (void)r19_2(1.0F);
}
