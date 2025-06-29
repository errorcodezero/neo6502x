#include "shift_ops.h"
#include "addressing.h"
#include "instructions.h"
#include "status.h"
#include "utils.h"
#include <stdlib.h>

void shift_ops(VirtualMachine *vm, AddressingMode mode,
               InstructionNames shift_op) {
  uint8_t *op = NULL;
  mode_parser(vm, &op, mode);

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
  case I_LSR: {
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
  case I_ROL: {
    vm->accum = *op << 1;
    vm->accum += get_status_flag(vm, S_CARRY);
    set_status_flag(vm, S_CARRY, *op >> 7);
    if (check_u8_negative(vm->accum)) {
      set_status_flag(vm, S_NEGATIVE, true);
    } else if (vm->accum == 0) {
      set_status_flag(vm, S_ZERO, true);
    }
    break;
  }
  case I_ROR: {
    vm->accum = *op >> 1;
    uint8_t carry_flag = *op << 7;
    vm->accum += get_status_flag(vm, S_CARRY) * 128;
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

void lsr_op(VirtualMachine *vm, AddressingMode mode) {
  shift_ops(vm, mode, I_LSR);
}

void ror_op(VirtualMachine *vm, AddressingMode mode) {
  shift_ops(vm, mode, I_ROR);
}
