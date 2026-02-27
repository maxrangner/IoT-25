#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#define SET_BIT(reg, bit) ((reg) |= (1UL << bit))
#define CLEAR_BIT(reg, bit) ((reg) &= ~(1UL << bit))
#define FLIP_BIT(reg, bit) ((reg) ^= (1UL << bit))
#define CHECK_BIT(reg, bit) ((reg) & (1UL << bit))

#define IS_BTN_PRESSED(BTN_PIN) (!CHECK_BIT(PINB, BTN_PIN))

#endif
