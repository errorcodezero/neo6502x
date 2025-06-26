#include "bool_ops.h"
#include "utils.h"
#include "vm.h"
#include <stdlib.h>

void bool_ops(VirtualMachine *vm, AddressingMode mode,
              enum BooleanOperator bool_op) {
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
    op2 = &vm->memory[vm->memory[++vm->program_ctr]];
    break;
  }
  case AM_ZERO_PAGE_X: {
    op1 = &vm->accum;
    op2 = &vm->memory[vm->memory[++vm->program_ctr] + vm->reg_x];
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
  switch (bool_op) {
  case AND:
    vm->accum = *op1 | *op2;
    break;
  case EOR:
    vm->accum = *op1 ^ *op2;
    break;
  case ORA:
    vm->accum = *op1 | *op2;
    break;
  }
  if (vm->accum >> 7 == 1) {
    vm->status = S_NEGATIVE;
  } else if (vm->accum == 0) {
    vm->status = S_ZERO;
  }
}

void and_op(VirtualMachine *vm, AddressingMode mode) {
	bool_ops(vm, mode, AND);
}
void eor_op(VirtualMachine *vm, AddressingMode mode) {
	bool_ops(vm, mode, EOR);
}
void ora_op(VirtualMachine *vm, AddressingMode mode) {
	bool_ops(vm, mode, ORA);
}
