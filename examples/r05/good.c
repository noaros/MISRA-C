/*
 * MISRA C:2012 Chapter 5 - Identifiers - GOOD examples.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 5.1 === */
/* External names are distinct within the first 31 characters. Prefer
 * short, module-prefixed names: egt_sensor1, egt_sensor2. (Shown as
 * static locals here to keep the example self-contained.) */
static int32_t r5_1(void)
{
    static int32_t egt_sensor1 = 0;
    static int32_t egt_sensor2 = 0;
    return egt_sensor1 + egt_sensor2;
}

/* === Rule 5.2 === */
/* Short names that differ early. */
static int32_t r5_2(void)
{
    int32_t cell_voltage_a = 1;
    int32_t cell_voltage_b = 2;
    return cell_voltage_a + cell_voltage_b;
}

/* === Rule 5.3 === */
/* Inner names never hide outer ones. */
static int32_t r5_3(int32_t n)
{
    static int32_t total_count = 0;
    int32_t local_count = n;
    local_count++;
    total_count = local_count;
    return total_count;
}

/* === Rule 5.4 === */
/* Macro names that differ early. */
#define CELL_CHANNEL_A  1
#define CELL_CHANNEL_B  2

/* === Rule 5.5 === */
/* Macros and identifiers never share a name. */
#define LIMIT_TO_TEN(x) (((x) > 10) ? 10 : (x))

static int32_t r5_5(int32_t a)
{
    int32_t value = a;
    return LIMIT_TO_TEN(value) + CELL_CHANNEL_A + CELL_CHANNEL_B;
}

/* === Rule 5.6 === */
/* A typedef name is used only as a type. */
typedef uint8_t sample_t;

static sample_t r5_6(void)
{
    sample_t reading = 3U;
    return reading;
}

/* === Rule 5.7 === */
/* A tag name is used only as a tag. */
struct point
{
    int32_t x;
};

static int32_t r5_7(void)
{
    struct point origin = { 0 };
    return origin.x;
}

/* === Rule 5.8 === */
/* External names are unique across the whole program. Here the module
 * prefix keeps the entry point "r05_good" unique. */
static int32_t r5_8(void)
{
    int32_t init_value = 1;
    return init_value;
}

/* === Rule 5.9 === */
/* Internal names are unique too: module prefixes again. */
static uint32_t r5_9(void)
{
    static uint32_t r5_error_count = 0U;
    uint32_t new_errors = 5U;
    r5_error_count += new_errors;
    return r5_error_count;
}

void r05_good(void)
{
    (void)r5_1();
    (void)r5_2();
    (void)r5_3(1);
    (void)r5_5(1);
    (void)r5_6();
    (void)r5_7();
    (void)r5_8();
    (void)r5_9();
}
