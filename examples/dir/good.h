/* Dir 4.10 GOOD: an include guard makes repeated inclusion harmless. */
#ifndef DIR_GOOD_H
#define DIR_GOOD_H

#include <stdint.h>

/* Dir 4.8 GOOD: callers only ever hold a pointer, so the layout of
 * struct motor stays private to good.c (an opaque type). */
struct motor;

struct sensor_reading
{
    uint32_t raw;
};

#endif /* DIR_GOOD_H */
