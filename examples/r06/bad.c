/*
 * MISRA C:2012 Chapter 6 - Types - BAD examples.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 6.1 === */
/* Plain "int" bit-fields have implementation-defined signedness, and
 * types like uint8_t are not guaranteed to work as bit-field types in
 * C99 at all. */
struct r6_1_flags
{
    int     mode   : 3;     /* signed or unsigned? compiler decides */
    uint8_t status : 4;     /* implementation-defined in C99 */
};

/* === Rule 6.2 === */
/* A signed 1-bit field can only hold 0 and -1, never +1. */
struct r6_2_flags
{
    signed int enabled : 1;
};

static int32_t r6_2(void)
{
    struct r6_2_flags f;
    f.enabled = 1;          /* stores -1 (or traps) */
    return (f.enabled == 1) ? 1 : 0;    /* always 0 */
}

void r06_bad(void)
{
    struct r6_1_flags f = { 0, 0U };
    (void)f;
    (void)r6_2();
}
