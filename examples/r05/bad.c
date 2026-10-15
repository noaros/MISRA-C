/*
 * MISRA C:2012 Chapter 5 - Identifiers - BAD examples.
 */
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 5.1 === */
/* External identifiers that differ only after the 31st character. C99
 * only guarantees 31 significant characters for external names, so a
 * linker may treat these two as the SAME object. */
int32_t engine_exhaust_gas_temperature_sensor_1;
int32_t engine_exhaust_gas_temperature_sensor_2;

/* === Rule 5.2 === */
/* Two names in the same scope that differ only after 63 characters
 * (C99's guaranteed significance for internal identifiers). */
static int32_t r5_2(void)
{
    int32_t battery_management_unit_cell_voltage_measurement_channel_number_a = 1;
    int32_t battery_management_unit_cell_voltage_measurement_channel_number_b = 2;
    return battery_management_unit_cell_voltage_measurement_channel_number_a
         + battery_management_unit_cell_voltage_measurement_channel_number_b;
}

/* === Rule 5.3 === */
/* The inner "count" hides the file-scope "count": which one is updated? */
static int32_t count = 0;

static int32_t r5_3(int32_t n)
{
    int32_t count = n;      /* hides the outer count */
    count++;
    return count;
}

/* === Rule 5.4 === */
/* Macro names that differ only after 63 characters. */
#define BATTERY_MANAGEMENT_UNIT_CELL_VOLTAGE_MEASUREMENT_CHANNEL_NUMBER_A 1
#define BATTERY_MANAGEMENT_UNIT_CELL_VOLTAGE_MEASUREMENT_CHANNEL_NUMBER_B 2

/* === Rule 5.5 === */
/* An identifier with the same name as a macro. "limit" without "(" is
 * not expanded, so both meanings coexist and confuse the reader. */
#define limit(x) (((x) > 10) ? 10 : (x))

static int32_t r5_5(int32_t a)
{
    int32_t limit = a;      /* object named like the macro */
    return limit(limit);
}

/* === Rule 5.6 === */
/* A typedef name reused as an ordinary identifier. */
typedef uint8_t sample_t;

static int32_t r5_6(void)
{
    int32_t sample_t = 3;   /* now "sample_t" means two things */
    return sample_t;
}

/* === Rule 5.7 === */
/* A struct tag reused as a variable name. */
struct point
{
    int32_t x;
};

static int32_t point = 0;

/* === Rule 5.8 === */
/* An external identifier ("init") reused as a local name. */
void init(void);
void init(void)
{
}

static int32_t r5_8(void)
{
    int32_t init = 1;       /* hides the external function init() */
    return init;
}

/* === Rule 5.9 === */
/* An internal-linkage name reused elsewhere: another file in this
 * project also has "static uint32_t error_count", and here a local
 * reuses it too. */
static uint32_t error_count = 0U;

static uint32_t r5_9(void)
{
    uint32_t error_count = 5U;
    return error_count;
}

void r05_bad(void)
{
    struct point p = { 0 };
    (void)r5_2();
    (void)r5_3(1);
    (void)r5_5(1);
    (void)r5_6();
    (void)r5_8();
    (void)r5_9();
    init();
    count = p.x + point + (int32_t)error_count;
}
