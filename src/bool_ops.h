#ifndef INCLUDE_SRC_BOOL_OPS_H_
#define INCLUDE_SRC_BOOL_OPS_H_

#include "addressing.h"
#include "vm.h"
enum BooleanOperator { AND, ORA, EOR };

void bool_ops(VirtualMachine *vm, AddressingMode mode,
              enum BooleanOperator bool_op);
void and_op(VirtualMachine *vm, AddressingMode mode);
void eor_op(VirtualMachine *vm, AddressingMode mode);
void ora_op(VirtualMachine *vm, AddressingMode mode);

#endif // INCLUDE_SRC_BOOL_OPS_H_
