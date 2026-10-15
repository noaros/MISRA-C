/*
 * Chapter 8 GOOD: the one header that declares this module's external
 * objects and functions (Rules 8.4, 8.5).
 */
#ifndef R08_GOOD_H
#define R08_GOOD_H

#include <stdint.h>

#define R08_TABLE_SIZE 4U

/* Rule 8.4 / 8.5: declared once, here, and visible where defined. */
extern int32_t r08_counter;

/* Rule 8.11: external arrays carry their size. */
extern const int32_t r08_table[R08_TABLE_SIZE];

#endif /* R08_GOOD_H */
