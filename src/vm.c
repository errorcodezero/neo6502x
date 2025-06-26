#include "vm.h"
#include <stdint.h>
#include <stdlib.h>

void delete_vm(VirtualMachine *vm) {
  free(vm->memory);
  vm->memory = NULL;
}

VirtualMachine init_vm() {
  VirtualMachine vm = {0};
  vm.memory = malloc(sizeof(uint8_t) * VM_MEMORY_SIZE);
  vm.program_ctr = VM_MEMORY_END;
  return vm;
}

void step_vm() { return; }

// dealing with cpu cycles later
// void cycle_vm(VirtualMachine *vm) { return; }
