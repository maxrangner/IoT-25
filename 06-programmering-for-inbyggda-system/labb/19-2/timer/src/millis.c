#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include "millis.h"

#define BIT_SET(a, b) (a |= (1UL << b))
#define BIT_CLEAR(a, b) (a &= ~(1UL << b))
#define BIT_FLIP(a, b) (a ^= (1UL << b))
#define BIT_CHECK(a, b) (a & (1UL << b))