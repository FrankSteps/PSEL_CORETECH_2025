#ifndef CPU_INTERNALS
#define CPU_INTERNALS

#include <stdint.h>
#include "mem.h"

#define REG_COUNT 16

typedef struct Cpu {
    uint32_t pc;
    uint32_t r[REG_COUNT];
    uint8_t flags;
} Cpu;

typedef struct Instruction {
    uint8_t opcode;
    uint8_t reg_x;
    uint8_t reg_y;
    uint16_t immediate;
} Instruction;

uint32_t fetch(Memory* mem, Cpu* cpu);
void decode(uint32_t code, Instruction* instruction);

#endif