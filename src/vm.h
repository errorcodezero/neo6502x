#ifndef INCLUDE_SRC_VM_H_
#define INCLUDE_SRC_VM_H_

#include <stdint.h>

// specs sourced from
// https://en.wikipedia.org/wiki/MOS_Technology_6502#Technical_description
typedef struct VirtualMachine {
  uint8_t accum;
  uint8_t status;
  uint16_t program_ctr;
  uint8_t stack_ptr;
  uint8_t reg_x;
  uint8_t reg_y;
} VirtualMachine;

#endif // INCLUDE_SRC_VM_H_
