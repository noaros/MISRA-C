/*
 * MISRA C:2012 Chapter 6 - Types - GOOD examples.
 */
#include <stdbool.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 6.1 === */
/* Bit-fields use explicitly signed or unsigned int (or _Bool). */
struct r6_1_flags
{
    unsigned int mode   : 3;
    unsigned int status : 4;
    bool         ready  : 1;
};

static uint32_t r6_1(void)
{
    struct r6_1_flags f = { 5U, 9U, true };
    return (uint32_t)f.mode + (uint32_t)f.status;
}

/* === Rule 6.2 === */
/* A single-bit field is unsigned: it holds 0 and 1 as expected. */
struct r6_2_flags
{
    unsigned int enabled : 1;
};

static bool r6_2(void)
{
    struct r6_2_flags f;
    f.enabled = 1U;
    return f.enabled == 1U;
}

void r06_good(void)
{
    (void)r6_1();
    (void)r6_2();
}
