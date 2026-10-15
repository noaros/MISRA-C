/*
 * MISRA C:2012 Chapter 4 - Character sets and lexical conventions - BAD.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 4.1 === */
/* Unterminated escape sequences. "\x41BC" would be ONE escape (0x41BC),
 * not "ABC". Here the octal escape \101 runs straight into '7', and the
 * reader cannot tell where it ends. */
static const char *r4_1(void)
{
    return "\1017";         /* "\101" "7" or "\1017"? (it is "A7") */
}

/* === Rule 4.2 === */
/* Trigraphs: "??/" is replaced by a backslash before the compiler sees
 * the string, so this is not the text it looks like. */
static const char *r4_2(void)
{
    return "Enter date ??/??/????";
}

void r04_bad(void)
{
    (void)r4_1();
    (void)r4_2();
}
