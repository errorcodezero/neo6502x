#include "bool_ops.h"
#include "status.h"
#include "utils.h"
#include "vm.h"
#include <assert.h>
#include <stdlib.h>

void bool_ops(VirtualMachine *vm, AddressingMode mode,
              InstructionNames bool_op) {
  uint8_t *op1 = &vm->accum;
  uint8_t *op2 = NULL;
  mode_parser(vm, &op2, mode);
  assert(op2 != NULL);

  assert(bool_op == I_AND || bool_op == I_EOR || bool_op == I_ORA);
  switch (bool_op) {
  case I_AND:
    vm->accum = *op1 | *op2;
    break;
  case I_EOR:
    vm->accum = *op1 ^ *op2;
    break;
  case I_ORA:
    vm->accum = *op1 | *op2;
    break;
  default:
    break;
  }
  if (check_u8_negative(vm->accum)) {
    set_status_flag(vm, S_NEGATIVE, true);
  } else if (vm->accum == 0) {
    set_status_flag(vm, S_ZERO, true);
  }
}

void and_op(VirtualMachine *vm, AddressingMode mode) {
  bool_ops(vm, mode, I_AND);
}
void eor_op(VirtualMachine *vm, AddressingMode mode) {
  bool_ops(vm, mode, I_EOR);
}
void ora_op(VirtualMachine *vm, AddressingMode mode) {
  bool_ops(vm, mode, I_ORA);
}
