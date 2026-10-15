/*
 * MISRA C:2012 Chapter 7 - Literals and constants - BAD examples.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 7.1 === */
/* Octal constants: the leading zero silently changes the base. */
static const int32_t r7_1_codes[3] =
{
    100,
    010,        /* this is 8, not 10 */
    001
};

/* === Rule 7.2 === */
/* 0x80000000 does not fit in a 32-bit int, so its type is unsigned int,
 * but nothing in the source says so. */
static uint32_t r7_2(void)
{
    return 0x80000000;
}

/* === Rule 7.3 === */
/* A lowercase "l" suffix looks like the digit 1: is this 101 or 10L? */
static int64_t r7_3(void)
{
    return 10l;
}

/* === Rule 7.4 === */
/* A string literal assigned to a non-const pointer. Writing through it
 * is undefined behaviour (literals may live in read-only memory). */
static char r7_4(void)
{
    char *greeting = "hello";
    greeting[0] = 'H';          /* undefined behaviour */
    return greeting[0];
}

void r07_bad(void)
{
    (void)r7_1_codes[0];
    (void)r7_2();
    (void)r7_3();
    (void)r7_4();
}
