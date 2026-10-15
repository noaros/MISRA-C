/*
 * MISRA C:2012 Chapter 16 - Switch statements - BAD examples.
 */
#include <stdbool.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 16.1 === */
/* A badly formed switch: a statement before the first label. It looks
 * like set-up code but can never run. */
static int32_t r16_1(int32_t mode)
{
    int32_t result = 0;
    switch (mode)
    {
        result = 99;                /* unreachable */
        case 0:
            result = 1;
            break;
        default:
            break;
    }
    return result;
}

/* === Rule 16.2 === */
/* A case label inside a nested block (Duff's device style). */
static int32_t r16_2(int32_t mode, bool flag)
{
    int32_t result = 0;
    switch (mode)
    {
        case 0:
            if (flag)
            {
        case 1:
                result = 1;
            }
            break;
        default:
            break;
    }
    return result;
}

/* === Rule 16.3 === */
/* Fall-through: case 0 runs case 1's code too. Intentional? */
static int32_t r16_3(int32_t mode)
{
    int32_t result = 0;
    switch (mode)
    {
        case 0:
            result = 10;
        case 1:
            result += 1;
            break;
        default:
            break;
    }
    return result;
}

/* === Rule 16.4 === */
/* No default: unexpected values are silently ignored. */
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
    }
    return result;
}

/* === Rule 16.5 === */
/* default hidden in the middle of the cases. */
static int32_t r16_5(int32_t mode)
{
    int32_t result = 0;
    switch (mode)
    {
        case 0:
            result = 1;
            break;
        default:
            result = -1;
            break;
        case 1:
            result = 2;
            break;
    }
    return result;
}

/* === Rule 16.6 === */
/* A switch with only one clause is just an "if" in disguise. */
static int32_t r16_6(int32_t mode)
{
    int32_t result = 0;
    switch (mode)
    {
        default:
            result = mode;
            break;
    }
    return result;
}

/* === Rule 16.7 === */
/* Switching on a Boolean: use if / else. */
static int32_t r16_7(bool flag)
{
    int32_t result = 0;
    switch (flag)
    {
        case true:
            result = 1;
            break;
        default:
            break;
    }
    return result;
}

void r16_bad(void)
{
    (void)r16_1(0);
    (void)r16_2(1, true);
    (void)r16_3(0);
    (void)r16_4(2);
    (void)r16_5(1);
    (void)r16_6(1);
    (void)r16_7(true);
}
