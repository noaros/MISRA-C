/*
 * MISRA C:2012 Directives (Dir 1.1 - Dir 4.14) - GOOD examples.
 */
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "misra_examples.h"
#include "good.h"
#include "good.h"   /* Dir 4.10: safe to include twice thanks to the guard */

/* === Dir 1.1 === */
/* Implementation-defined behaviour is avoided where possible and
 * documented where not. Here the shift works on an unsigned value, and
 * the compiler assumption is checked at build time.
 *
 * Documented assumption (see the project's compiler manual, section
 * "Integers"): int32_t is exactly 32 bits, two's complement. */
typedef char dir1_1_int32_is_32_bits[(sizeof(int32_t) == 4U) ? 1 : -1];

static uint32_t dir1_1(uint32_t value)
{
    return (value >> 1U) + (uint32_t)sizeof(dir1_1_int32_is_32_bits);
}

/* === Dir 2.1 === */
/* This file compiles with -std=c99 -pedantic-errors -Werror: zero errors
 * and zero warnings. That is the bar Dir 2.1 sets. */

/* === Dir 3.1 === */
/* Every piece of behaviour traces to a requirement.
 * Implements: REQ-ENG-042 "Idle speed limit shall be 870 rpm". */
#define IDLE_RPM_LIMIT  870U    /* REQ-ENG-042 */

static uint32_t dir3_1(uint32_t rpm)
{
    return (rpm > IDLE_RPM_LIMIT) ? IDLE_RPM_LIMIT : rpm;
}

/* === Dir 4.1 === */
/* Prevent the run-time failure instead of hoping it never happens. */
static uint32_t dir4_1(uint32_t total, uint32_t count)
{
    uint32_t average = 0U;
    if (count != 0U)
    {
        average = total / count;
    }
    return average;
}

/* === Dir 4.2 === */
/* No assembly needed here. When assembly is unavoidable, document why
 * (Dir 4.2) and wrap it in one small function (Dir 4.3), e.g.:
 *
 *   static inline void cpu_nop(void)   -- one-cycle delay for the ADC
 *   {                                  -- settling time, see datasheet
 *       __asm__ volatile ("nop");      -- section 12.4
 *   }
 */

/* === Dir 4.3 === */
/* All C, no inline assembly mixed into the logic. Hardware-specific
 * instructions live behind a documented driver function (see Dir 4.2). */
static uint32_t dir4_3(uint32_t x)
{
    return (x + 1U) * 2U;
}

/* === Dir 4.4 === */
/* No commented-out code. Disabled behaviour is deleted (version control
 * keeps the history) or controlled by a documented configuration. */
static uint32_t dir4_4(uint32_t x)
{
    return x;
}

/* === Dir 4.5 === */
/* Names that cannot be misread. */
static int32_t dir4_5(void)
{
    int32_t first_count = 1;
    int32_t second_count = 2;
    return first_count + second_count;
}

/* === Dir 4.6 === */
/* Fixed-width typedefs say exactly how big each value is. */
static int64_t dir4_6(int32_t a, uint16_t b)
{
    return (int64_t)a * (int64_t)b;
}

/* === Dir 4.7 === */
/* Error information is always tested. */
static bool parse_value(const char *text, int32_t *out)
{
    bool ok = false;
    if ((text != NULL) && (out != NULL) && (text[0] >= '0') && (text[0] <= '9'))
    {
        *out = (int32_t)text[0] - (int32_t)'0';
        ok = true;
    }
    return ok;
}

static int32_t dir4_7(const char *text)
{
    int32_t value = 0;
    if (!parse_value(text, &value))
    {
        value = -1;                 /* explicit, documented fallback */
    }
    return value;
}

/* === Dir 4.8 === */
/* good.h only declares "struct motor;". Users get a handle and call
 * functions; only this file knows the layout. */
struct motor
{
    uint32_t speed;
};

static struct motor *motor_get(void)
{
    static struct motor the_motor = { 0U };
    return &the_motor;
}

static uint32_t motor_speed(const struct motor *m)
{
    return m->speed;
}

/* === Dir 4.9 === */
/* A function: type-checked, argument evaluated exactly once. */
static inline int32_t square(int32_t x)
{
    return x * x;
}

/* === Dir 4.10 === */
/* good.h is protected by #ifndef DIR_GOOD_H / #define DIR_GOOD_H. */

/* === Dir 4.11 === */
/* Check the domain before calling the library. */
static double dir4_11(double x)
{
    double result = 0.0;
    if (x >= 0.0)
    {
        result = sqrt(x);
    }
    return result;
}

/* === Dir 4.12 === */
/* Storage is sized at compile time; no malloc, no fragmentation. */
#define BUFFER_SIZE 64U

static uint8_t *dir4_12(void)
{
    static uint8_t buffer[BUFFER_SIZE];
    return buffer;
}

/* === Dir 4.13 === */
/* The API enforces its own sequence: send refuses to run before init. */
static bool uart_ready = false;

static void uart_init(void)
{
    uart_ready = true;
}

static bool uart_send(uint8_t b)
{
    bool sent = false;
    if (uart_ready && (b != 0U))
    {
        sent = true;
    }
    return sent;
}

/* === Dir 4.14 === */
/* External data is validated before use. */
#define TABLE_SIZE 8U

static uint32_t dir4_14(const uint8_t *message)
{
    static const uint32_t lookup_table[TABLE_SIZE] = { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U };
    uint32_t value = 0U;
    uint8_t index = message[0];
    if (index < TABLE_SIZE)
    {
        value = lookup_table[index];
    }
    return value;
}

void dir_good(void)
{
    const uint8_t msg[1] = { 3U };
    struct sensor_reading r = { 0U };
    (void)dir1_1(r.raw);
    (void)dir3_1(1000U);
    (void)dir4_1(10U, 0U);
    (void)dir4_3(1U);
    (void)dir4_4(1U);
    (void)dir4_5();
    (void)dir4_6(1, 2U);
    (void)dir4_7("7");
    (void)motor_speed(motor_get());
    (void)square(3);
    (void)dir4_11(-1.0);
    (void)dir4_12();
    uart_init();
    (void)uart_send(0x55U);
    (void)dir4_14(msg);
}
