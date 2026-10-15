/*
 * MISRA C:2012 Directives (Dir 1.1 - Dir 4.14) - BAD examples.
 * Each block violates the directive named in its marker.
 */
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "misra_examples.h"
#include "bad.h"

/* === Dir 1.1 === */
/* Relies on implementation-defined behaviour without documenting it:
 * right-shifting a negative value, and the signedness of plain char. */
static int32_t dir1_1(int32_t value, char c)
{
    int32_t half = value >> 1;      /* arithmetic or logical shift? */
    if (c < 0)                      /* is plain char even signed here? */
    {
        half = 0;
    }
    return half;
}

/* === Dir 2.1 === */
/* "It builds with warnings, ship it." Dir 2.1 requires zero compilation
 * errors; this project's bad files only build because errors are hidden
 * behind SHOW_COMPILE_ERRORS. */
#ifdef SHOW_COMPILE_ERRORS
static void dir2_1(void)
{
    undeclared_function_call();
}
#endif

/* === Dir 3.1 === */
/* No link from this code to any requirement: why is the limit 87? */
static uint32_t dir3_1(uint32_t rpm)
{
    return (rpm > 87U) ? 87U : rpm;
}

/* === Dir 4.1 === */
/* Run-time failure not prevented: division by zero when count == 0. */
static uint32_t dir4_1(uint32_t total, uint32_t count)
{
    return total / count;
}

/* === Dir 4.2 === */
/* Undocumented assembly: what is this for? Why here? */
static void dir4_2(void)
{
    __asm__ volatile ("nop");
}

/* === Dir 4.3 === */
/* Assembly mixed directly into C logic instead of being isolated. */
static uint32_t dir4_3(uint32_t x)
{
    uint32_t y = x + 1U;
    __asm__ volatile ("" ::: "memory");
    y = y * 2U;
    __asm__ volatile ("nop");
    return y;
}

/* === Dir 4.4 === */
/* Commented-out code: is it dead, temporary, or a forgotten fix? */
static uint32_t dir4_4(uint32_t x)
{
    /* x = x * 2U; */
    /* if (x > 10U) { x = 10U; } */
    return x;
}

/* === Dir 4.5 === */
/* Identifiers that differ only by easily confused characters. */
static int32_t dir4_5(void)
{
    int32_t l1 = 1;     /* ell-one   */
    int32_t ll = 2;     /* ell-ell   */
    int32_t lI = 3;     /* ell-eye   */
    int32_t O0 = 4;     /* oh-zero   */
    return l1 + ll + lI + O0;
}

/* === Dir 4.6 === */
/* Basic numerical types: their sizes change between compilers. */
static long dir4_6(int a, unsigned short b)
{
    long result = (long)a * (long)b;
    return result;
}

/* === Dir 4.7 === */
/* Error information returned by a function is ignored. */
static int32_t parse_value(const char *text, int32_t *out)
{
    int32_t status = -1;
    if ((text != NULL) && (text[0] != '\0'))
    {
        *out = (int32_t)(text[0] - '0');
        status = 0;
    }
    return status;
}

static int32_t dir4_7(const char *text)
{
    int32_t value;
    parse_value(text, &value);      /* status ignored: value may be garbage */
    return value;
}

/* === Dir 4.8 === */
/* The full struct definition is visible to every user of the module even
 * though callers only pass pointers around: they can (and will) poke at
 * the fields directly. See bad.h: struct sensor_reading is exposed. */
static uint32_t dir4_8(struct sensor_reading *r)
{
    r->raw = 0U;                    /* caller bypasses the module API */
    return r->raw;
}

/* === Dir 4.9 === */
/* Function-like macro where a function would do: no type checking, and
 * the argument is evaluated twice. */
#define SQUARE(x) ((x) * (x))
static int32_t dir4_9(int32_t a)
{
    return SQUARE(a++);             /* a incremented twice: undefined */
}

/* === Dir 4.10 === */
/* bad.h has no include guard; a second #include "bad.h" would fail. */

/* === Dir 4.11 === */
/* Library called with a value outside its domain. */
static double dir4_11(double x)
{
    return sqrt(x);                 /* x may be negative: domain error */
}

/* === Dir 4.12 === */
/* Dynamic memory: allocation can fail, fragment, or leak at run time. */
static uint8_t *dir4_12(size_t n)
{
    return malloc(n);
}

/* === Dir 4.13 === */
/* Resource operations called in the wrong order. */
static uint32_t uart_ready;
static void uart_init(void) { uart_ready = 1U; }
static void uart_send(uint8_t b) { (void)b; }
static void dir4_13(void)
{
    uart_send(0x55U);               /* sent before initialisation */
    uart_init();
}

/* === Dir 4.14 === */
/* Data received from outside (a network message) used as an index
 * without validation. */
static uint32_t lookup_table[8];
static uint32_t dir4_14(const uint8_t *message)
{
    uint8_t index = message[0];     /* attacker controls this byte */
    return lookup_table[index];     /* out of bounds when index >= 8 */
}

void dir_bad(void)
{
    struct sensor_reading r = { 0U };
    uint8_t msg[1] = { 0U };
    (void)dir1_1(-4, 'a');
    (void)dir3_1(100U);
    (void)dir4_1(10U, 0U);
    dir4_2();
    (void)dir4_3(1U);
    (void)dir4_4(1U);
    (void)dir4_5();
    (void)dir4_6(1, 2U);
    (void)dir4_7("7");
    (void)dir4_8(&r);
    (void)dir4_9(3);
    (void)dir4_11(-1.0);
    free(dir4_12(4U));
    dir4_13();
    (void)dir4_14(msg);
}
