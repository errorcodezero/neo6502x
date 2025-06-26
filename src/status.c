#include "status.h"
#include "vm.h"

void set_status_flag(VirtualMachine *vm, Status status, bool value) {
  vm->status |= value << status;
}

bool get_status_flag(VirtualMachine *vm, Status status) {
  return (vm->status & (1 << status)) >> status;
}

void reset_status_flag(VirtualMachine *vm) {
  vm->status = 0;
}
