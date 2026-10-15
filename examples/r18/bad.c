/*
 * MISRA C:2012 Chapter 18 - Pointers and arrays - BAD examples.
 */
#include <stddef.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 18.1 === */
/* Pointer arithmetic that leaves the array: forming &arr[5] for a
 * 4-element array is already undefined, before any dereference. */
static int32_t r18_1(void)
{
    int32_t arr[4] = { 1, 2, 3, 4 };
    const int32_t *p = arr + 5;
    return *(p - 2);
}

/* === Rule 18.2 === */
/* Subtracting pointers into two different arrays: undefined. */
static ptrdiff_t r18_2(void)
{
    int32_t a[4] = { 0 };
    int32_t b[4] = { 0 };
    return &b[0] - &a[0];
}

/* === Rule 18.3 === */
/* Comparing pointers to different objects with < or >: the result
 * depends on how the compiler happened to lay out memory. */
static int32_t r18_3(void)
{
    int32_t x = 0;
    int32_t y = 0;
    return (&x < &y) ? 1 : 0;
}

/* === Rule 18.4 === */
/* Pointer arithmetic with + and -: easy to get the bounds wrong, and
 * hard to see which array it relates to. */
static int32_t r18_4(const int32_t *data, int32_t i)
{
    const int32_t *p = data;
    p += 2;
    return *(p + i);
}

/* === Rule 18.5 === */
/* Three levels of pointer nesting: hard to read and to get right. */
static int32_t r18_5(int32_t ***table)
{
    return ***table;
}

/* === Rule 18.6 === */
/* The address of a local escapes the function: a dangling pointer. */
static int32_t *saved;

static int32_t *r18_6(void)
{
    int32_t local = 42;
    saved = &local;             /* stored in a longer-lived object */
    return &local;              /* returned to the caller */
}

/* === Rule 18.7 === */
/* A flexible array member: the struct's size depends on how it was
 * allocated, which usually means malloc. */
struct r18_7_packet
{
    uint16_t length;
    uint8_t  payload[];
};

/* === Rule 18.8 === */
/* A variable-length array: stack use depends on a run-time value; a
 * large n silently overflows the stack. */
static int32_t r18_8(int32_t n)
{
    int32_t scratch[n];
    scratch[0] = 1;
    return scratch[0];
}

void r18_bad(void)
{
    int32_t v = 1;
    int32_t *pv = &v;
    int32_t **ppv = &pv;
    const int32_t data[4] = { 1, 2, 3, 4 };
    (void)r18_1();
    (void)r18_2();
    (void)r18_3();
    (void)r18_4(data, 1);
    (void)r18_5(&ppv);
    (void)r18_6();
    (void)sizeof(struct r18_7_packet);
    (void)r18_8(4);
}
