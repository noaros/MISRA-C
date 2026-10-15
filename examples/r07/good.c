/*
 * MISRA C:2012 Chapter 7 - Literals and constants - GOOD examples.
 */
#include <stddef.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 7.1 === */
/* Decimal (or hex) only. Zero itself is fine: it is not considered an
 * octal constant by this rule. */
static int32_t r7_1(size_t index)
{
    static const int32_t codes[3] = { 100, 10, 1 };
    return codes[index];
}

/* === Rule 7.2 === */
/* The U suffix makes the unsigned type visible. */
static uint32_t r7_2(void)
{
    return 0x80000000U;
}

/* === Rule 7.3 === */
/* Uppercase L only. */
static int64_t r7_3(void)
{
    return 10L;
}

/* === Rule 7.4 === */
/* String literals go through pointers to const char. To modify text,
 * copy it into an array first. */
static char r7_4(void)
{
    const char *greeting = "hello";
    char editable[6] = { 'h', 'e', 'l', 'l', 'o', '\0' };
    editable[0] = 'H';
    return (greeting[0] == 'h') ? editable[0] : '?';
}

void r07_good(void)
{
    (void)r7_1(1U);
    (void)r7_2();
    (void)r7_3();
    (void)r7_4();
}
