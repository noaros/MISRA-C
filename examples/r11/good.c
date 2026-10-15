/*
 * MISRA C:2012 Chapter 11 - Pointer type conversions - GOOD examples.
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "misra_examples.h"

/* === Rule 11.1 === */
/* Function pointers stay function pointers, with a typedef. */
typedef int32_t (*r11_handler_t)(int32_t value);

static int32_t r11_1_target(int32_t a)
{
    return a;
}

static r11_handler_t r11_1(void)
{
    return &r11_1_target;
}

/* === Rule 11.2 === */
/* An opaque handle is only passed to the module that owns the type. */
struct r11_device
{
    uint8_t id;
};

static uint8_t r11_device_id(const struct r11_device *dev)
{
    return dev->id;
}

/* === Rule 11.3 === */
/* Build the value from its bytes instead of casting the pointer. As a
 * bonus the byte order is now explicit (little-endian here). */
static uint32_t r11_3(const uint8_t *bytes)
{
    uint32_t word = (uint32_t)bytes[0];
    word |= ((uint32_t)bytes[1] << 8U);
    word |= ((uint32_t)bytes[2] << 16U);
    word |= ((uint32_t)bytes[3] << 24U);
    return word;
}

/* === Rule 11.4 === */
/* Rule 11.4 is advisory: memory-mapped registers usually need an
 * integer-to-pointer conversion. MISRA expects that confined to one
 * documented place (a deviation). Here the "register" is an ordinary
 * object, so no conversion is needed at all. */
static void r11_4(uint32_t value)
{
    static volatile uint32_t simulated_register;
    volatile uint32_t *reg = &simulated_register;
    *reg = value;
}

/* === Rule 11.5 === */
/* Typed interfaces instead of void *. */
static uint32_t r11_5(const uint32_t *values)
{
    return values[0];
}

/* === Rule 11.6 === */
/* Pointer arithmetic on the real element type, no integers involved. */
static const int32_t *r11_6(const int32_t *array)
{
    return &array[1];
}

/* === Rule 11.7 === */
/* Test a pointer by comparing it with NULL. */
static bool r11_7(const int32_t *p)
{
    return p != NULL;
}

/* === Rule 11.8 === */
/* Keep const. To modify text, copy it into writable storage. */
static char r11_8(const char *message)
{
    char buffer[8] = { 0 };
    (void)strncpy(buffer, message, sizeof(buffer) - 1U);
    buffer[0] = 'X';
    return buffer[0];
}

/* === Rule 11.9 === */
/* NULL is the only null pointer constant. */
static bool r11_9(const int32_t *p)
{
    const int32_t *q = NULL;
    return (p == NULL) && (q == NULL);
}

void r11_good(void)
{
    const int32_t pair[2] = { 1, 2 };
    const uint8_t bytes[4] = { 1U, 2U, 3U, 4U };
    const uint32_t words[1] = { 7U };
    const struct r11_device dev = { 3U };
    r11_handler_t handler = r11_1();
    (void)handler(1);
    (void)r11_device_id(&dev);
    (void)r11_3(bytes);
    r11_4(1U);
    (void)r11_5(words);
    (void)r11_6(pair);
    (void)r11_7(pair);
    (void)r11_8("literal");
    (void)r11_9(pair);
}
