#ifndef INCLUDE_SRC_UTILS_H_
#define INCLUDE_SRC_UTILS_H_

#include "addressing.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct VirtualMachine VirtualMachine;

void u16_split(uint16_t value, uint8_t *left, uint8_t *right);
uint16_t u16_combine(uint8_t left, uint8_t right);
bool check_u8_negative(uint8_t value);
void mode_parser(VirtualMachine *vm, uint8_t **op, AddressingMode mode);

#endif // INCLUDE_SRC_UTILS_H_
