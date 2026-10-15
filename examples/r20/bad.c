/*
 * MISRA C:2012 Chapter 20 - Preprocessing directives - BAD examples.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 20.1 === */
/* An #include after code: what this header sees depends on everything
 * declared above it. */
static int32_t r20_1_value = 1;
#include <stddef.h>

/* === Rule 20.2 === */
/* Header names containing ', ", \, or comment markers are undefined
 * behaviour (and break on other operating systems). Hidden behind
 * SHOW_COMPILE_ERRORS because the file does not exist. */
#ifdef SHOW_COMPILE_ERRORS
#include "drivers\uart.h"
#endif

/* === Rule 20.3 === */
/* #include must be followed by <file> or "file" (directly or after
 * macro expansion). */
#ifdef SHOW_COMPILE_ERRORS
#include stdint.h
#endif

/* === Rule 20.4 === */
/* A macro named like a keyword: see the end of this file, where
 * "#define volatile" silently strips volatile from all later code. */

/* === Rule 20.5 === */
/* #undef: the meaning of a macro now depends on where you are in the
 * file. */
#define R20_5_BUFFER_SIZE 16U
#undef R20_5_BUFFER_SIZE
#define R20_5_BUFFER_SIZE 32U

/* === Rule 20.6 === */
/* Directives inside macro arguments: undefined behaviour. cppcheck
 * refuses to analyse a file containing this at all, which would hide
 * every other finding in the file, so it is kept out of its view. */
#define R20_6_MAX(a, b) (((a) > (b)) ? (a) : (b))

#ifndef __CPPCHECK__
static int32_t r20_6(void)
{
    return R20_6_MAX(1,
#ifdef BIG_LIMITS
                     1000
#else
                     10
#endif
                    );
}
#else
static int32_t r20_6(void)
{
    return 0;
}
#endif

/* === Rule 20.7 === */
/* Unparenthesised macro parameters: SQUARE(1 + 2) is 1 + 2 * 1 + 2 = 5. */
#define SQUARE(x) x * x

static int32_t r20_7(void)
{
    return SQUARE(1 + 2);
}

/* === Rule 20.8 === */
/* #if on a value that is not 0 or 1: is LOG_LEVEL a flag or a level? */
#define LOG_LEVEL 2
#if LOG_LEVEL
static const int32_t r20_8_logging = 1;
#endif

/* === Rule 20.9 === */
/* An undefined identifier in #if silently evaluates to 0, so a typo
 * (or a missing config header) quietly disables the feature. */
#if ENABLE_WATCHDGO > 0
static const int32_t r20_9_watchdog = 1;
#endif

/* === Rule 20.10 === */
/* # and ## make code that does not exist in the source, so it cannot be
 * searched, and their evaluation order is unspecified. */
#define R20_10_DECLARE(name) static int32_t var_ ## name = 0
#define R20_10_STR(x) #x
R20_10_DECLARE(speed);

/* === Rule 20.11 === */
/* # immediately followed by ##: unspecified which runs first. */
#define R20_11_LABEL(x) #x ## _label

/* === Rule 20.12 === */
/* "reg" is used both with ## (not expanded) and normally (expanded).
 * If reg is itself a macro, the two uses disagree. */
#define R20_12_ACCESS(reg) (reg + offset_ ## reg)

/* === Rule 20.13 === */
/* An invalid directive in a skipped block: a typo the compiler never
 * reports, until someone turns the block on. */
#if 0
#esle
#endif

/* === Rule 20.14 === */
/* The #endif for this #if lives in bad_unbalanced.h. Hidden behind
 * SHOW_COMPILE_ERRORS to keep the rest of the file readable. */
#ifdef SHOW_COMPILE_ERRORS
#if 1
#include "bad_unbalanced.h"     /* tries to close "#if 1" from inside */
#endif                          /* so which #if does this one close? */
#endif                          /* closes SHOW_COMPILE_ERRORS */

static volatile int32_t r20_4_status = 0;

void r20_bad(void)
{
    (void)r20_1_value;
    (void)r20_6();
    (void)r20_7();
    (void)r20_8_logging;
    (void)var_speed;
    (void)R20_10_STR(text);
    (void)r20_4_status;
}

/* Rule 20.4: from here on "volatile" means nothing. */
#define volatile
