#ifndef INCLUDE_SRC_SHIFT_OPS_H_
#define INCLUDE_SRC_SHIFT_OPS_H_

#include "addressing.h"
#include "instructions.h"
#include "vm.h"

void shift_ops(VirtualMachine *vm, AddressingMode mode,
               InstructionNames shift_op);

#endif // INCLUDE_SRC_SHIFT_OPS_H_
