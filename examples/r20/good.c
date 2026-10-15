/*
 * MISRA C:2012 Chapter 20 - Preprocessing directives - GOOD examples.
 */
/* === Rule 20.1 === */
/* All #includes at the top, before any code. */
#include <stddef.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 20.2 === */
/* Header names use plain characters and forward slashes only, e.g.
 * #include "drivers/uart.h". */

/* === Rule 20.3 === */
/* #include is always followed by <file> or "file", as above. */

/* === Rule 20.4 === */
/* Macros never redefine keywords. Configuration that changes a
 * qualifier uses its own name: */
#define R20_VOLATILE_REGISTER volatile

/* === Rule 20.5 === */
/* Each macro is defined once, and keeps its meaning for the whole file. */
#define R20_5_BUFFER_SIZE 32U

/* === Rule 20.6 === */
/* Resolve the configuration first, then use the macro. */
#ifdef BIG_LIMITS
#define R20_6_LIMIT 1000
#else
#define R20_6_LIMIT 10
#endif

#define R20_6_MAX(a, b) (((a) > (b)) ? (a) : (b))

static int32_t r20_6(void)
{
    return R20_6_MAX(1, R20_6_LIMIT);
}

/* === Rule 20.7 === */
/* Every parameter, and the whole expansion, parenthesised. Better
 * still, use a function (Dir 4.9). */
#define SQUARE(x) ((x) * (x))

static int32_t r20_7(void)
{
    return SQUARE(1 + 2);
}

/* === Rule 20.8 === */
/* Flags are 0 or 1; levels are compared explicitly. */
#define LOG_LEVEL 2
#if (LOG_LEVEL >= 2)
#define R20_8_LOGGING 1
#endif

/* === Rule 20.9 === */
/* Check that the macro is defined before testing its value; a missing
 * definition is an error, not a silent 0. */
#define ENABLE_WATCHDOG 1
#if !defined(ENABLE_WATCHDOG)
#error "ENABLE_WATCHDOG must be defined by the configuration"
#endif
#if (ENABLE_WATCHDOG == 1)
#define R20_9_WATCHDOG 1
#endif

/* === Rule 20.10 === */
/* Write the code out: every identifier can be found with a search,
 * e.g. "static int32_t var_speed = 0;" instead of DECLARE(speed). */

/* === Rule 20.11 === */
/* Not needed when # and ## are avoided (Rule 20.10). Where they are
 * used under a deviation, never put # right before ##. */

/* === Rule 20.12 === */
/* A parameter used with # or ## is used only that way, e.g.
 * #define OFFSET_OF(reg) (offset_ ## reg)  -- reg never appears alone.
 * (Shown in a comment because ## itself needs a deviation of 20.10.) */

/* === Rule 20.13 === */
/* Only valid directives, even in skipped blocks. */
#if 0
#else
#endif

/* === Rule 20.14 === */
/* Every #if, #ifdef and #ifndef closes in the same file, like the
 * include guard in misra_examples.h. */

void r20_good(void)
{
    static R20_VOLATILE_REGISTER uint32_t status = R20_5_BUFFER_SIZE;
    static int32_t features = R20_8_LOGGING + R20_9_WATCHDOG;
    (void)r20_6();
    (void)r20_7();
    (void)features;
    (void)status;
}
