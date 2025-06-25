#include "vm.h"
#include <stdint.h>
#include <stdlib.h>

VirtualMachine init_vm() {
	VirtualMachine vm = {0};
	vm.memory = malloc(sizeof(uint8_t) * VM_MEMORY_SIZE);
	vm.stack_ptr = vm.memory + VM_STACK_START;
	vm.program_ctr = vm.memory + VM_MEMORY_END;
	return vm;
}
