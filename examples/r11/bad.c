/*
 * MISRA C:2012 Chapter 11 - Pointer type conversions - BAD examples.
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "misra_examples.h"

/* === Rule 11.1 === */
/* A function pointer converted to an object pointer. Code and data may
 * live in different address spaces with different pointer sizes. */
static int32_t r11_1_target(int32_t a)
{
    return a;
}

static void *r11_1(void)
{
    return (void *)&r11_1_target;
}

/* === Rule 11.2 === */
/* A pointer to an incomplete (opaque) type cast to something else: the
 * caller is guessing at a layout it cannot see. */
struct r11_opaque;

static uint8_t r11_2(struct r11_opaque *handle)
{
    const uint8_t *bytes = (const uint8_t *)handle;
    return bytes[0];
}

/* === Rule 11.3 === */
/* A byte buffer reinterpreted as a 32-bit word: may be misaligned (a
 * hardware fault on many CPUs) and breaks strict aliasing. */
static uint32_t r11_3(uint8_t *bytes)
{
    uint32_t *word = (uint32_t *)bytes;
    return *word;
}

/* === Rule 11.4 === */
/* Integers and pointers converted back and forth. */
static uintptr_t r11_4(int32_t *p)
{
    volatile uint32_t *reg = (volatile uint32_t *)0x40021000U;
    *reg = 1U;                      /* magic address */
    return (uintptr_t)p;            /* pointer to integer */
}

/* === Rule 11.5 === */
/* void * silently converted to a typed pointer: no check that the
 * memory really holds uint32_t values. */
static uint32_t r11_5(void *context)
{
    uint32_t *values = context;
    return values[0];
}

/* === Rule 11.6 === */
/* void * converted to and from an arithmetic type. */
static void *r11_6(void *p)
{
    uintptr_t n = (uintptr_t)p;
    return (void *)(n + 4U);
}

/* === Rule 11.7 === */
/* An object pointer cast to a non-integer arithmetic type (here bool). */
static bool r11_7(const int32_t *p)
{
    return (bool)p;
}

/* === Rule 11.8 === */
/* Casting away const: writing to a string literal through it is
 * undefined behaviour. */
static void r11_8(const char *message)
{
    char *writable = (char *)message;
    writable[0] = 'X';
}

/* === Rule 11.9 === */
/* The integer 0 used as a null pointer constant. */
static bool r11_9(int32_t *p)
{
    int32_t *q = 0;
    return (p == 0) && (q == 0);
}

void r11_bad(void)
{
    int32_t x = 0;
    uint8_t bytes[4] = { 0U };
    uint32_t words[1] = { 0U };
    (void)r11_1();
    (void)r11_2(NULL);
    (void)r11_3(bytes);
    (void)r11_4(&x);
    (void)r11_5(words);
    (void)r11_6(&x);
    (void)r11_7(&x);
    r11_8("literal");
    (void)r11_9(&x);
}
