/*
 * MISRA C:2012 Chapter 19 - Overlapping storage - GOOD examples.
 */
#include <stdint.h>
#include <string.h>
#include "misra_examples.h"

/* === Rule 19.1 === */
/* memmove is defined for overlapping regions (or copy via a temporary). */
static void r19_1(void)
{
    uint8_t buf[8] = { 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U };
    (void)memmove(&buf[2], &buf[0], 4U);
}

/* === Rule 19.2 === */
/* Store alternatives in separate struct members with a tag saying which
 * one is valid. It costs a few bytes but no storage is ever read as a
 * type it was not written as. (If raw bit patterns really are needed,
 * confine that code to one function under a documented deviation.) */
enum r19_kind { R19_KIND_FLOAT, R19_KIND_INT };

struct r19_value
{
    enum r19_kind kind;
    float         as_float;
    int32_t       as_int;
};

static float r19_2(const struct r19_value *v)
{
    float result = 0.0F;
    if (v->kind == R19_KIND_FLOAT)
    {
        result = v->as_float;
    }
    else
    {
        result = (float)v->as_int;
    }
    return result;
}

void r19_good(void)
{
    const struct r19_value v = { R19_KIND_FLOAT, 1.0F, 0 };
    r19_1();
    (void)r19_2(&v);
}
