/*
 * MISRA C:2012 Chapter 17 - Functions - BAD examples.
 */
#include <stdarg.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 17.1 === */
/* Variadic functions: no type checking of the extra arguments, and
 * nothing stops a caller passing the wrong count. */
static int32_t r17_1(int32_t count, ...)
{
    va_list args;
    int32_t total = 0;
    int32_t i;
    va_start(args, count);
    for (i = 0; i < count; i++)
    {
        total += va_arg(args, int32_t);
    }
    va_end(args);
    return total;
}

/* === Rule 17.2 === */
/* Recursion: stack use depends on the input and cannot be bounded by
 * static analysis. */
static uint32_t r17_2(uint32_t n)
{
    uint32_t result = 1U;
    if (n > 1U)
    {
        result = n * r17_2(n - 1U);
    }
    return result;
}

/* === Rule 17.3 === */
/* Calling a function with no declaration in scope. C90 assumed it
 * returned int; C99 forbids it. Hidden behind SHOW_COMPILE_ERRORS
 * because modern compilers reject it. */
#ifdef SHOW_COMPILE_ERRORS
static int32_t r17_3(void)
{
    return undeclared_helper(3);
}
#endif

/* === Rule 17.4 === */
/* A non-void function where one path falls off the end: the caller
 * reads an undefined value. */
static int32_t r17_4(int32_t x)
{
    if (x > 0)
    {
        return x;
    }
}

/* === Rule 17.5 === */
/* Passing a 2-element array where the parameter says 4. */
static int32_t r17_5_sum(const int32_t values[4])
{
    return values[0] + values[1] + values[2] + values[3];
}

static int32_t r17_5(void)
{
    const int32_t pair[2] = { 1, 2 };
    return r17_5_sum(pair);         /* reads past the end */
}

/* === Rule 17.6 === */
/* "static" inside [] promises at least 4 elements; breaking that promise
 * is undefined behaviour, and the compiler may optimise on it. */
static int32_t r17_6(const int32_t values[static 4])
{
    return values[3];
}

/* === Rule 17.7 === */
/* The returned status is thrown away. */
static int32_t save_settings(void)
{
    return -1;                      /* failure */
}

static void r17_7(void)
{
    save_settings();
}

/* === Rule 17.8 === */
/* Modifying a parameter: later code that reads "x" no longer sees the
 * caller's value. */
static int32_t r17_8(int32_t x)
{
    x = x * 2;
    return x;
}

void r17_bad(void)
{
    const int32_t four[4] = { 1, 2, 3, 4 };
    (void)r17_1(2, 1, 2);
    (void)r17_2(5U);
    (void)r17_4(1);
    (void)r17_5();
    (void)r17_6(four);
    r17_7();
    (void)r17_8(1);
}
