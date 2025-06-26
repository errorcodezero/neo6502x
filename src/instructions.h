#ifndef INCLUDE_SRC_INSTRUCTIONS_H_
#define INCLUDE_SRC_INSTRUCTIONS_H_

// Sourced from http://www.6502.org/users/obelisk/6502/instructions.html
#include "vm.h"
#include <stdint.h>
typedef enum InstructionNames {
  // Load/Store ops
  I_LDA,
  I_LDX,
  I_LDY,
  I_STA,
  I_STX,
  I_STY,

  // Register transfers
  I_TAX,
  I_TAY,
  I_TXA,
  I_TYA,

  // Stack ops
  I_TSX,
  I_TXS,
  I_PHA,
  I_PLA,
  I_PLP,

  // Logical
  I_AND,
  I_EOR, // they could have just named this one XOR but they chose EOR
  I_ORA,
  I_BIT,

  // Arithmetic
  I_ADC,
  I_SBC,
  I_CMP,
  I_CPX,
  I_CPY,

  // Increments and decrements
  I_INC,
  I_INX,
  I_INY,
  I_DEC,
  I_DEX,
  I_DEY,

  // Branches
  I_BCC,
  I_BCS,
  I_BEQ,
  I_BMI,
  I_BNE,
  I_BPL,
  I_BVC,
  I_BVS,

  // Status flag changes
  I_CLC,
  I_CLD,
  I_CLI,
  I_CLV,
  I_SEC,
  I_SED,
  I_SEI,

  // Extras
  I_BRK,
  I_NOP,
  I_RTI,
} Instructions;

typedef struct Instruction {
  InstructionNames name;
  void (*execute)(VirtualMachine *vm);
  uint8_t cycles;
} Instruction;

#endif // INCLUDE_SRC_INSTRUCTIONS_H_
