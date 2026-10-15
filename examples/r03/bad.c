/*
 * MISRA C:2012 Chapter 3 - Comments - BAD examples.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 3.1 === */
/* Comment markers inside comments.
 * Spec link: http://example.com/spec   <- the "//" here is a violation */
static int32_t r3_1(int32_t a)
{
    /* Was this meant to close?  /* nested open is a violation */
    int32_t b = a;
    // a "/*" inside a line comment is also a violation
    return b;
}

/* === Rule 3.2 === */
/* A line comment ending in a backslash swallows the next line: the
 * increment below is part of the comment and never executes. */
static int32_t r3_2(int32_t a)
{
    int32_t b = a;
    // add one to b \
    b = b + 1;
    return b;
}

void r03_bad(void)
{
    (void)r3_1(1);
    (void)r3_2(1);
}
