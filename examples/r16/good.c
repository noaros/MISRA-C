/*
 * MISRA C:2012 Chapter 16 - Switch statements - GOOD examples.
 *
 * The well-formed shape (Rule 16.1) that every example below follows:
 *
 *   switch (expr)
 *   {
 *       case A:            <- labels only directly in the switch body
 *       case B:            <- empty clauses may share code
 *           ...statements...
 *           break;         <- every clause ends in an unconditional break
 *       default:           <- always present, first or last
 *           ...
 *           break;
 *   }
 */
#include <stdbool.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 16.1 === */
/* Labels, statements, break: nothing else. */
static int32_t r16_1(int32_t mode)
{
    int32_t result = 0;
    switch (mode)
    {
        case 0:
            result = 1;
            break;
        default:
            result = 99;
            break;
    }
    return result;
}

/* === Rule 16.2 === */
/* Case labels only at the top level of the switch body. */
static int32_t r16_2(int32_t mode, bool flag)
{
    int32_t result = 0;
    switch (mode)
    {
        case 0:
            if (flag)
            {
                result = 1;
            }
            break;
        case 1:
            result = 1;
            break;
        default:
            break;
    }
    return result;
}

/* === Rule 16.3 === */
/* Every non-empty clause ends with break. Consecutive labels with no
 * statements between them are allowed. */
static int32_t r16_3(int32_t mode)
{
    int32_t result = 0;
    switch (mode)
    {
        case 0:
            result = 11;
            break;
        case 1:
        case 2:
            result = 1;
            break;
        default:
            break;
    }
    return result;
}

/* === Rule 16.4 === */
/* A default clause, with a comment if it does nothing on purpose. */
static int32_t r16_4(int32_t mode)
{
    int32_t result = 0;
    switch (mode)
    {
        case 0:
            result = 1;
            break;
        case 1:
            result = 2;
            break;
        default:
            /* other modes are not used: result stays 0 */
            break;
    }
    return result;
}

/* === Rule 16.5 === */
/* default first or last. */
static int32_t r16_5(int32_t mode)
{
    int32_t result = 0;
    switch (mode)
    {
        case 0:
            result = 1;
            break;
        case 1:
            result = 2;
            break;
        default:
            result = -1;
            break;
    }
    return result;
}

/* === Rule 16.6 === */
/* One decision: use an if. Keep switch for two or more clauses. */
static int32_t r16_6(int32_t mode)
{
    int32_t result = 0;
    if (mode > 0)
    {
        result = mode;
    }
    return result;
}

/* === Rule 16.7 === */
/* Booleans are tested with if / else. */
static int32_t r16_7(bool flag)
{
    int32_t result = 0;
    if (flag)
    {
        result = 1;
    }
    return result;
}

void r16_good(void)
{
    (void)r16_1(0);
    (void)r16_2(1, true);
    (void)r16_3(0);
    (void)r16_4(2);
    (void)r16_5(1);
    (void)r16_6(1);
    (void)r16_7(true);
}
