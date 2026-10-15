/*
 * MISRA C:2012 Chapter 3 - Comments - GOOD examples.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 3.1 === */
/* Spec link: example.com/spec (no comment markers inside comments). */
static int32_t r3_1(int32_t a)
{
    /* One comment, one open marker, one close marker. */
    int32_t b = a;
    return b;
}

/* === Rule 3.2 === */
/* Comments never end with a backslash, so no line splicing occurs. */
static int32_t r3_2(int32_t a)
{
    int32_t b = a;
    /* add one to b */
    b = b + 1;
    return b;
}

void r03_good(void)
{
    (void)r3_1(1);
    (void)r3_2(1);
}
