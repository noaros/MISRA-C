/*
 * MISRA C:2012 Chapter 18 - Pointers and arrays - GOOD examples.
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "misra_examples.h"

#define ARR_LEN 4U

/* === Rule 18.1 === */
/* Index within bounds; checked when the index comes from outside. */
static int32_t r18_1(size_t index)
{
    const int32_t arr[ARR_LEN] = { 1, 2, 3, 4 };
    int32_t value = 0;
    if (index < ARR_LEN)
    {
        value = arr[index];
    }
    return value;
}

/* === Rule 18.2 === */
/* Subtract only pointers into the same array. Rule 18.4 (advisory)
 * still discourages pointer arithmetic in general, so many projects
 * compute the difference of indices instead. */
static ptrdiff_t r18_2(void)
{
    const int32_t a[ARR_LEN] = { 0 };
    const int32_t *first = &a[0];
    const int32_t *last = &a[ARR_LEN - 1U];
    return last - first;
}

/* === Rule 18.3 === */
/* Relational comparison only between pointers into the same array. */
static bool r18_3(void)
{
    const int32_t a[ARR_LEN] = { 0 };
    const int32_t *p = &a[1];
    const int32_t *q = &a[2];
    return p < q;
}

/* === Rule 18.4 === */
/* Array indexing instead of pointer arithmetic. */
static int32_t r18_4(const int32_t *data, size_t i)
{
    return data[2U + i];
}

/* === Rule 18.5 === */
/* At most two levels of pointer nesting. */
static int32_t r18_5(int32_t *const *table)
{
    return *table[0];
}

/* === Rule 18.6 === */
/* Return values, or write into storage the caller owns. */
static void r18_6(int32_t *out)
{
    int32_t local = 42;
    *out = local;
}

/* === Rule 18.7 === */
/* A fixed-size buffer with a separate length field. */
#define R18_MAX_PAYLOAD 32U

struct r18_7_packet
{
    uint16_t length;
    uint8_t  payload[R18_MAX_PAYLOAD];
};

static uint16_t r18_7(const struct r18_7_packet *pkt)
{
    return pkt->length;
}

/* === Rule 18.8 === */
/* A compile-time maximum and a run-time check. */
#define R18_MAX_SCRATCH 16U

static int32_t r18_8(size_t n)
{
    int32_t scratch[R18_MAX_SCRATCH] = { 0 };
    int32_t result = -1;
    if ((n > 0U) && (n <= R18_MAX_SCRATCH))
    {
        scratch[0] = 1;
        result = scratch[0];
    }
    return result;
}

void r18_good(void)
{
    int32_t v = 1;
    int32_t *pv = &v;
    int32_t out = 0;
    const int32_t data[ARR_LEN] = { 1, 2, 3, 4 };
    const struct r18_7_packet pkt = { 0 };
    (void)r18_1(2U);
    (void)r18_2();
    (void)r18_3();
    (void)r18_4(data, 1U);
    (void)r18_5(&pv);
    r18_6(&out);
    (void)r18_7(&pkt);
    (void)r18_8(4U);
}
