/*
 * MISRA C:2012 Chapter 21 - Standard libraries - GOOD examples.
 */
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "misra_examples.h"

/* === Rule 21.1 === */
/* Project macros use plain, non-reserved names. */
#define BUFFER_SIZE 64U
#define DEBUG_LEVEL 1

/* === Rule 21.2 === */
/* Project identifiers use a module prefix instead of an underscore. */

/* === Rule 21.3 === */
/* A fixed pool sized at compile time replaces malloc/free. */
#define POOL_BLOCKS 4U

static int32_t *pool_take(void)
{
    static int32_t pool[POOL_BLOCKS][10];
    static bool pool_used[POOL_BLOCKS];
    int32_t *block = NULL;
    size_t i;
    for (i = 0U; (i < POOL_BLOCKS) && (block == NULL); i++)
    {
        if (!pool_used[i])
        {
            pool_used[i] = true;
            block = pool[i];
        }
    }
    return block;
}

static int32_t r21_3(void)
{
    int32_t *data = pool_take();
    int32_t status = -1;
    if (data != NULL)
    {
        data[0] = 1;
        status = 0;
    }
    return status;
}

/* === Rule 21.4 === */
/* Errors travel back through return values, not longjmp. */
static int32_t r21_4_step(int32_t input)
{
    int32_t status = 0;
    if (input < 0)
    {
        status = -1;
    }
    return status;
}

static int32_t r21_4(void)
{
    return r21_4_step(1);
}

/* === Rule 21.5 === */
/* No <signal.h>. Asynchronous events are handled by the platform's
 * interrupt mechanism (documented separately) setting a flag that the
 * main loop polls. */
static bool r21_5(void)
{
    static volatile bool event_pending = false;
    bool pending = event_pending;
    event_pending = false;
    return pending;
}

/* === Rule 21.6 === */
/* Output goes through a project driver with a fixed, typed interface,
 * not printf. Here the "driver" just records the last value. */
static int32_t log_value(int32_t value)
{
    static int32_t last_logged = 0;
    int32_t previous = last_logged;
    last_logged = value;
    return previous;
}

/* === Rule 21.7 === */
/* strtol reports errors through errno and the end pointer (and the
 * errno rules 22.8 and 22.9 are followed). */
static bool r21_7(const char *text, int32_t *out)
{
    char *end = NULL;
    long parsed;
    bool ok = false;
    errno = 0;
    parsed = strtol(text, &end, 10);
    if ((errno == 0) && (end != text) && (*end == '\0') &&
        (parsed >= (long)INT32_MIN) && (parsed <= (long)INT32_MAX))
    {
        *out = (int32_t)parsed;
        ok = true;
    }
    return ok;
}

/* === Rule 21.8 === */
/* Report the error to the caller, who moves the system to a safe state. */
static int32_t r21_8(int32_t error)
{
    int32_t status = 0;
    if (error != 0)
    {
        status = -1;
    }
    return status;
}

/* === Rule 21.9 === */
/* A simple, bounded, non-recursive sort written for the job. */
static void r21_9(int32_t *values, size_t n)
{
    size_t i;
    for (i = 1U; i < n; i++)
    {
        int32_t key = values[i];
        size_t j = i;
        while ((j > 0U) && (values[j - 1U] > key))
        {
            values[j] = values[j - 1U];
            j--;
        }
        values[j] = key;
    }
}

/* === Rule 21.10 === */
/* Time comes from a project clock driver with defined behaviour, for
 * example a millisecond tick counter. */
static uint32_t r21_10(void)
{
    static volatile uint32_t tick_ms = 0U;  /* updated by the timer driver */
    return tick_ms;
}

/* === Rule 21.11 === */
/* Call the type-specific function from <math.h> by name. */
static float r21_11(void)
{
    return sqrtf(2.0F);
}

/* === Rule 21.12 === */
/* Prevent the exception rather than testing flags afterwards. */
static double r21_12(double a, double b)
{
    double q = 0.0;
    if (fabs(b) > 1.0e-9)
    {
        q = a / b;
    }
    return q;
}

/* === Rule 21.13 === */
/* Convert to unsigned char before calling <ctype.h> functions. */
static bool r21_13(char c)
{
    return isdigit((unsigned char)c) != 0;
}

/* === Rule 21.14 === */
/* Compare strings with string functions: they stop at the terminator. */
static bool r21_14(const char *a, const char *b)
{
    return strcmp(a, b) == 0;
}

/* === Rule 21.15 === */
/* Source and destination have the same type. */
static void r21_15(void)
{
    uint16_t copy[4] = { 0U, 0U, 0U, 0U };
    const uint16_t halves[4] = { 1U, 2U, 3U, 4U };
    (void)memcpy(copy, halves, sizeof(copy));
}

/* === Rule 21.16 === */
/* Compare structs member by member. */
struct r21_16_point
{
    uint8_t  tag;
    uint32_t value;
};

static bool r21_16(const struct r21_16_point *a, const struct r21_16_point *b)
{
    return (a->tag == b->tag) && (a->value == b->value);
}

/* === Rule 21.17 === */
/* Check the length before copying, and always terminate. */
static bool r21_17(const char *source)
{
    char small[4] = { 0 };
    bool fits = (strlen(source) < sizeof(small));
    if (fits)
    {
        (void)strncpy(small, source, sizeof(small) - 1U);
        small[sizeof(small) - 1U] = '\0';
    }
    return fits;
}

/* === Rule 21.18 === */
/* The size argument is exactly the object's size. */
static void r21_18(void)
{
    uint8_t buf[8];
    (void)memset(buf, 0, sizeof(buf));
}

/* === Rule 21.19 === */
/* Treat library-owned strings as const; copy to modify. */
static char r21_19(void)
{
    const char *msg = strerror(1);
    char copy[16] = { 0 };
    (void)strncpy(copy, msg, sizeof(copy) - 1U);
    copy[0] = 'X';
    return copy[0];
}

/* === Rule 21.20 === */
/* Copy the result before calling the same function again. */
static bool r21_20(void)
{
    char first[32] = { 0 };
    const char *second;
    (void)strncpy(first, strerror(1), sizeof(first) - 1U);
    second = strerror(2);
    return strcmp(first, second) == 0;
}

/* === Rule 21.21 === */
/* Call the needed functionality directly through a project API instead
 * of handing a command string to the shell. */
static int32_t request_restart(void)
{
    return 0;
}

void r21_good(void)
{
    int32_t values[3] = { 3, 1, 2 };
    int32_t parsed = 0;
    const struct r21_16_point p = { 0U, 0U };
    (void)r21_3();
    (void)r21_4();
    (void)r21_5();
    (void)log_value((int32_t)BUFFER_SIZE + DEBUG_LEVEL);
    (void)r21_7("12", &parsed);
    (void)r21_8(0);
    r21_9(values, 3U);
    (void)r21_10();
    (void)r21_11();
    (void)r21_12(1.0, 0.0);
    (void)r21_13('7');
    (void)r21_14("abc", "abc");
    r21_15();
    (void)r21_16(&p, &p);
    (void)r21_17("ok");
    r21_18();
    (void)r21_19();
    (void)r21_20();
    (void)request_restart();
}
