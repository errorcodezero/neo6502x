#ifndef INCLUDE_SRC_VM_H_
#define INCLUDE_SRC_VM_H_

#include "status.h"
#include <stdint.h>

#define VM_MEMORY_SIZE 0x10000
#define VM_ZERO_PAGE_START 0x0
#define VM_ZERO_PAGE_END 0xFF
#define VM_STACK_START 0x100
#define VM_STACK_END 0x1FF

// specs sourced from
// https://en.wikipedia.org/wiki/MOS_Technology_6502#Technical_description
typedef struct VirtualMachine {
  uint8_t accum;
  Status status;
  uint16_t program_ctr;
  uint8_t stack_ptr;
  uint8_t reg_x;
  uint8_t reg_y;
  uint8_t *memory;
} VirtualMachine;

VirtualMachine init_vm();

#endif // INCLUDE_SRC_VM_H_
