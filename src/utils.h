#ifndef INCLUDE_SRC_UTILS_H_
#define INCLUDE_SRC_UTILS_H_

#include <stdint.h>
void u16_split(uint16_t value, uint8_t *left, uint8_t *right);
uint16_t u16_combine(uint8_t left, uint8_t right);

#endif // INCLUDE_SRC_UTILS_H_
