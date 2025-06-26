#include "bool_ops.h"
#include "status.h"
#include "utils.h"
#include "vm.h"
#include <assert.h>
#include <stdlib.h>

void bool_ops(VirtualMachine *vm, AddressingMode mode,
              InstructionNames bool_op) {
  uint8_t *op1 = NULL;
  uint8_t *op2 = NULL;
  switch (mode) {
  case AM_IMMEDIATE: {
    op1 = &vm->accum;
    op2 = &vm->memory[++vm->program_ctr];
    break;
  }
  case AM_ZERO_PAGE: {
    op1 = &vm->accum;
    op2 = &vm->memory[++vm->program_ctr];
    break;
  }
  case AM_ZERO_PAGE_X: {
    op1 = &vm->accum;
    op2 = &vm->memory[++vm->program_ctr] + vm->reg_x;
    break;
  }
  case AM_ABSOLUTE: {
    op1 = &vm->accum;
    uint8_t left = vm->memory[++vm->program_ctr];
    uint8_t right = vm->memory[++vm->program_ctr];
    op2 = &vm->memory[u16_combine(left, right)];
    break;
  }
  case AM_ABSOLUTE_X: {
    op1 = &vm->accum;
    uint8_t left = vm->memory[++vm->program_ctr];
    uint8_t right = vm->memory[++vm->program_ctr];
    op2 = &vm->memory[u16_combine(left, right) + vm->reg_x];
    break;
  }
  case AM_ABSOLUTE_Y: {
    op1 = &vm->accum;
    uint8_t left = vm->memory[++vm->program_ctr];
    uint8_t right = vm->memory[++vm->program_ctr];
    op2 = &vm->memory[u16_combine(left, right) + vm->reg_y];
    break;
  }
  case AM_INDIRECT_X: {
    op1 = &vm->accum;
    uint8_t left = vm->memory[++vm->program_ctr];
    uint8_t right = vm->memory[++vm->program_ctr];
    uint16_t mem_addr = u16_combine(left, right);
    left = vm->memory[mem_addr];
    right = vm->memory[mem_addr + 1];
    op2 = &vm->memory[u16_combine(left, right) + vm->reg_x];
    break;
  }
  case AM_INDIRECT_Y: {
    op1 = &vm->accum;
    uint8_t left = vm->memory[++vm->program_ctr];
    uint8_t right = vm->memory[++vm->program_ctr];
    uint16_t mem_addr = u16_combine(left, right);
    left = vm->memory[mem_addr];
    right = vm->memory[mem_addr + 1];
    op2 = &vm->memory[u16_combine(left, right) + vm->reg_y];
    break;
  }
  default: {
    break;
  }
  }
  vm->program_ctr++;
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
