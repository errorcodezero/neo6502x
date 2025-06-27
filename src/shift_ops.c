#include "shift_ops.h"
#include "addressing.h"
#include "instructions.h"
#include "status.h"
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
  switch (shift_op) {
  case I_ASL: {
    vm->accum = *op << 1;
    set_status_flag(vm, S_CARRY, *op >> 7);
    if (check_u8_negative(vm->accum)) {
      set_status_flag(vm, S_NEGATIVE, true);
    } else if (vm->accum == 0) {
      set_status_flag(vm, S_ZERO, true);
    }
    break;
  }
  case I_ROL: {
    vm->accum = *op >> 1;
    uint8_t carry_flag = *op << 7;
    set_status_flag(vm, S_CARRY, carry_flag);
    if (check_u8_negative(vm->accum)) {
      set_status_flag(vm, S_NEGATIVE, true);
    } else if (vm->accum == 0) {
      set_status_flag(vm, S_ZERO, true);
    }
    break;
  }
  default: {
    break;
  }
  }
}

void asl_op(VirtualMachine *vm, AddressingMode mode) {
  shift_ops(vm, mode, I_ASL);
}

void rol_op(VirtualMachine *vm, AddressingMode mode) {
  shift_ops(vm, mode, I_ROL);
}
