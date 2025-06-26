#include "shift_ops.h"
#include "addressing.h"
#include "utils.h"
#include <stdlib.h>

void shift_ops(VirtualMachine *vm, AddressingMode mode,
               InstructionNames shift_op) {
  uint8_t *op = NULL;

  switch (mode) {
  case AM_ACCUMULATOR: {
    op = &vm->accum;
    break;
  }
  case AM_ZERO_PAGE: {
    op = &vm->memory[++vm->program_ctr];
    break;
  }
  case AM_ZERO_PAGE_X: {
    op = &vm->memory[++vm->program_ctr] + vm->reg_x;
    break;
  }
  case AM_ABSOLUTE: {
    uint8_t left = vm->memory[++vm->program_ctr];
    uint8_t right = vm->memory[++vm->program_ctr];
    op = &vm->memory[u16_combine(left, right)];
    break;
  }
  case AM_ABSOLUTE_X: {
    uint8_t left = vm->memory[++vm->program_ctr];
    uint8_t right = vm->memory[++vm->program_ctr];
    op = &vm->memory[u16_combine(left, right) + vm->reg_x];
    break;
  }
  default: {
    break;
  }
  }
  vm->accum = *op << 1;
  vm->status = *op >> 7;
  if (vm->accum == 0) {
    vm->status = S_ZERO;
  }
}
