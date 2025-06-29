#include "utils.h"
#include "addressing.h"
#include "vm.h"

void u16_split(uint16_t value, uint8_t *left, uint8_t *right) {
  *left = value;
  *right = (uint8_t)(value >> 8);
}

uint16_t u16_combine(uint8_t left, uint8_t right) {
  return ((uint16_t)right << 8) | left;
}

bool check_u8_negative(uint8_t value) { return (value & (1 << 7)) != 0; }

void mode_parser(VirtualMachine *vm, uint8_t **op, AddressingMode mode) {
  switch (mode) {
  case AM_IMMEDIATE: {
    *op = &vm->memory[++vm->program_ctr];
    break;
  }
  case AM_ZERO_PAGE: {
    *op = &vm->memory[vm->memory[++vm->program_ctr]];
    break;
  }
  case AM_ZERO_PAGE_X: {
    *op = &vm->memory[vm->memory[++vm->program_ctr] + vm->reg_x];
    break;
  }
  case AM_ZERO_PAGE_Y: {
    *op = &vm->memory[vm->memory[++vm->program_ctr] + vm->reg_y];
    break;
  }
  case AM_ABSOLUTE: {
    uint8_t left = vm->memory[++vm->program_ctr];
    uint8_t right = vm->memory[++vm->program_ctr];
    *op = &vm->memory[u16_combine(left, right)];
    break;
  }
  case AM_ABSOLUTE_X: {
    uint8_t left = vm->memory[++vm->program_ctr];
    uint8_t right = vm->memory[++vm->program_ctr];
    *op = &vm->memory[u16_combine(left, right) + vm->reg_x];
    break;
  }
  case AM_ABSOLUTE_Y: {
    uint8_t left = vm->memory[++vm->program_ctr];
    uint8_t right = vm->memory[++vm->program_ctr];
    *op = &vm->memory[u16_combine(left, right) + vm->reg_y];
    break;
  }
  case AM_INDIRECT: {
    uint8_t left = vm->memory[++vm->program_ctr];
    uint8_t right = vm->memory[++vm->program_ctr];
    uint16_t mem_addr = u16_combine(left, right);
    left = vm->memory[mem_addr];
    right = vm->memory[mem_addr + 1];
    *op = &vm->memory[u16_combine(left, right)];
    break;
  }
  case AM_INDIRECT_X: {
    uint8_t left = vm->memory[++vm->program_ctr];
    uint8_t right = vm->memory[++vm->program_ctr];
    uint16_t mem_addr = u16_combine(left, right);
    left = vm->memory[mem_addr];
    right = vm->memory[mem_addr + 1];
    *op = &vm->memory[u16_combine(left, right) + vm->reg_x];
    break;
  }
  case AM_INDIRECT_Y: {
    uint8_t left = vm->memory[++vm->program_ctr];
    uint8_t right = vm->memory[++vm->program_ctr];
    uint16_t mem_addr = u16_combine(left, right);
    left = vm->memory[mem_addr];
    right = vm->memory[mem_addr + 1];
    *op = &vm->memory[u16_combine(left, right) + vm->reg_y];
    break;
  }
  case AM_ACCUMULATOR: {
    *op = &vm->accum;
    break;
  }
  case AM_IMPLIED: {
    // this one has to be manually dealt with
    break;
  }
  case AM_RELATIVE: {
    // this one has to be manually dealt with
    break;
  }
  }
}
