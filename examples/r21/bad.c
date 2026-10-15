/*
 * MISRA C:2012 Chapter 21 - Standard libraries - BAD examples.
 */
#include <ctype.h>
#include <fenv.h>
#include <setjmp.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <time.h>
#include "misra_examples.h"

/* === Rule 21.1 === */
/* #define on reserved names: identifiers starting with an underscore
 * plus a capital (or two underscores) belong to the implementation. */
#define _BUFFER_SIZE 64U
#define __DEBUG      1

/* === Rule 21.2 === */
/* Declaring a reserved identifier: file-scope names starting with "_"
 * may clash with the compiler's or library's own. */
static int32_t _counter = 0;

/* === Rule 21.3 === */
/* Heap allocation: may fail, fragment, leak, or take unbounded time. */
static int32_t r21_3(void)
{
    int32_t *data = malloc(10U * sizeof(int32_t));
    data[0] = 1;                    /* no NULL check either */
    free(data);
    return 0;
}

/* === Rule 21.4 === */
/* setjmp / longjmp: jumps that bypass normal function exits and leave
 * local variables in undefined states. */
static jmp_buf r21_4_env;

static int32_t r21_4(void)
{
    int32_t result = 0;
    if (setjmp(r21_4_env) == 0)
    {
        longjmp(r21_4_env, 1);
    }
    else
    {
        result = 1;
    }
    return result;
}

/* === Rule 21.5 === */
/* <signal.h>: handlers run asynchronously with very few guarantees
 * about what they may safely do. */
static void r21_5_handler(int sig)
{
    (void)sig;
}

static void r21_5(void)
{
    (void)signal(SIGINT, &r21_5_handler);
}

/* === Rule 21.6 === */
/* Standard I/O: format strings are unchecked at run time, buffering and
 * error behaviour are implementation-defined. */
static void r21_6(int32_t value)
{
    printf("%d\n", value);
}

/* === Rule 21.7 === */
/* atoi: no way to report an error. "abc" and "0" both give 0, and
 * overflow is undefined behaviour. */
static int32_t r21_7(const char *text)
{
    return atoi(text);
}

/* === Rule 21.8 === */
/* Termination functions: abort and exit end the program without the
 * system getting a chance to reach a safe state. (The original C:2012
 * text also banned getenv and system here.) */
static void r21_8(int32_t error)
{
    if (error != 0)
    {
        exit(1);
    }
    abort();
}

/* === Rule 21.9 === */
/* qsort and bsearch: unspecified behaviour for equal elements, and
 * implementations are often recursive. */
static int r21_9_compare(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;   /* may overflow too */
}

static void r21_9(int *values, size_t n)
{
    qsort(values, n, sizeof(int), &r21_9_compare);
}

/* === Rule 21.10 === */
/* <time.h>: implementation-defined, unspecified and undefined behaviour
 * (time() may return -1, struct tm pointers are shared). */
static time_t r21_10(void)
{
    return time(NULL);
}

/* === Rule 21.11 === */
/* <tgmath.h>: the function actually called depends on the argument
 * type, invisibly. sqrt(2.0F) quietly calls sqrtf. */
static float r21_11(void)
{
    return sqrt(2.0F);
}

/* === Rule 21.12 === */
/* Floating-point exception flags from <fenv.h>: support and behaviour
 * vary between implementations. */
static int r21_12(double a, double b)
{
    double q;
    feclearexcept(FE_ALL_EXCEPT);
    q = a / b;
    (void)q;
    return fetestexcept(FE_DIVBYZERO);
}

/* === Rule 21.13 === */
/* <ctype.h> functions need a value representable as unsigned char (or
 * EOF). A plain char holding a negative value (e.g. 0xE9 on a
 * signed-char platform) is undefined behaviour. */
static int r21_13(char c)
{
    return isdigit(c);
}

/* === Rule 21.14 === */
/* memcmp on strings compares bytes AFTER the terminator too: "abc" and
 * "abc" can compare unequal if the buffers differ beyond the '\0'. */
static int r21_14(const char *a, const char *b)
{
    return memcmp(a, b, 8U);
}

/* === Rule 21.15 === */
/* memcpy between different types: copies bytes, not values. */
static void r21_15(void)
{
    uint32_t words[2] = { 0U, 0U };
    const uint16_t halves[4] = { 1U, 2U, 3U, 4U };
    (void)memcpy(words, halves, sizeof(words));
}

/* === Rule 21.16 === */
/* memcmp on structs compares padding bytes, whose values are
 * unspecified: equal structs may compare unequal. */
struct r21_16_point
{
    uint8_t  tag;               /* padding usually follows */
    uint32_t value;
};

static int r21_16(const struct r21_16_point *a, const struct r21_16_point *b)
{
    return memcmp(a, b, sizeof(*a));
}

/* === Rule 21.17 === */
/* strcpy into a buffer that is too small: a classic buffer overflow. */
static void r21_17(void)
{
    char small[4];
    strcpy(small, "overflow!");
}

/* === Rule 21.18 === */
/* A size argument larger than the object. */
static void r21_18(void)
{
    uint8_t buf[8];
    (void)memset(buf, 0, sizeof(buf) + 1U);
}

/* === Rule 21.19 === */
/* Writing through the pointer returned by strerror: that string belongs
 * to the library. */
static void r21_19(void)
{
    char *msg = strerror(1);
    msg[0] = 'X';
}

/* === Rule 21.20 === */
/* Using a pointer from strerror after calling strerror again: the second
 * call may overwrite the first string. */
static int r21_20(void)
{
    const char *first = strerror(1);
    const char *second = strerror(2);
    return strcmp(first, second);   /* "first" may already be gone */
}

/* === Rule 21.21 === */
/* system(): runs a command through the host shell; behaviour depends on
 * the environment and opens the door to command injection. */
static int r21_21(void)
{
    return system("reboot");
}

void r21_bad(void)
{
    int values[3] = { 3, 1, 2 };
    struct r21_16_point p = { 0U, 0U };
    _counter = (int32_t)_BUFFER_SIZE + __DEBUG;
    (void)r21_3();
    (void)r21_4();
    r21_5();
    r21_6(1);
    (void)r21_7("12");
    r21_8(0);
    r21_9(values, 3U);
    (void)r21_10();
    (void)r21_11();
    (void)r21_12(1.0, 0.0);
    (void)r21_13('7');
    (void)r21_14("abc", "abc");
    r21_15();
    (void)r21_16(&p, &p);
    r21_17();
    r21_18();
    r21_19();
    (void)r21_20();
    (void)r21_21();
}
