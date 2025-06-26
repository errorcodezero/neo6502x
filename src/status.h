#ifndef INCLUDE_SRC_STATUS_H_
#define INCLUDE_SRC_STATUS_H_

#include <stdbool.h>

typedef struct VirtualMachine VirtualMachine;

// 7  bit  0
// ---- ----
// NV1B DIZC
// |||| ||||
// |||| |||+- Carry
// |||| ||+-- Zero
// |||| |+--- Interrupt Disable
// |||| +---- Decimal
// |||+------ (No CPU effect; see: the B flag)
// ||+------- (No CPU effect; always pushed as 1)
// |+-------- Overflow
// +--------- Negative
// shamelessly borrowed from https://www.nesdev.org/wiki/Status_flags
typedef enum Status {
  S_NEGATIVE = 7,
  S_OVERFLOW = 6,
  S_NO_EFF = 5,
  S_B_FLAG = 4,
  S_DECIMAL = 3,
  S_INTERRUPT_DISABLE = 2,
  S_ZERO = 1,
  S_CARRY = 0
} Status;

void set_status_flag(VirtualMachine *vm, Status status, bool value);
void reset_status_flag(VirtualMachine *vm);
bool get_status_flag(VirtualMachine *vm, Status status);

#endif // INCLUDE_SRC_STATUS_H_
