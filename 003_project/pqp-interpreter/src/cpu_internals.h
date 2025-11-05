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

typedef enum inst_type_t { IMMEDIATE, JUMP, MOV, ARITHMETIC_LOGIC, SHIFT, INVALID } inst_type_t;

extern const inst_type_t instruction_table[16];
extern const void* instruction_exec_table[16];

uint32_t fetch(Memory* mem, Cpu* cpu);
Instruction decode(uint32_t code);
void execute(Cpu* cpu, Memory* mem, Instruction instruction);

#endif