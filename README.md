# neo6502x

An emulator for the MOS Technology 6502 processor.

## Specifications

- 16-bit
- Two "index" registers x and y.
- Little-endian
- 256 bytes of memory in zero page between 0x0 and 0xFF.
- 0x10000 bytes of memory total.
- 256 bytes of stack memory(tiny stack) meaning 8-bit stack pointer stored between 0x100 and 0x1FF. Small stack is interesting since it means the stack isn't used in the same way that we use it today.
- Memory indexing system that is actually pretty cool and allows for fast array ops and other interesting things:
    - Essentially, memory address after instruction plus value in index register and that's the memory address used in a memory indexed command.
    - Zero-page uses add without carry and full memory uses add with carry.
