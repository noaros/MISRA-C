/*
 * MISRA C:2012 Chapter 4 - Character sets and lexical conventions - GOOD.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 4.1 === */
/* Every escape is terminated by another escape or by the end of the
 * literal; string concatenation makes the boundary explicit. */
static const char *r4_1(void)
{
    return "\101" "7";
}

/* === Rule 4.2 === */
/* Escape the second '?' so no trigraph can form. */
static const char *r4_2(void)
{
    return "Enter date ?\?/?\?/????";
}

void r04_good(void)
{
    (void)r4_1();
    (void)r4_2();
}
