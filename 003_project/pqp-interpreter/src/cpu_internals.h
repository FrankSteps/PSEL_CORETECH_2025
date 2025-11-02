#ifndef CPU_INTERNALS
#define CPU_INTERNALS

#include <stdint.h>
#include "mem.h"

#define REG_COUNT 16

typedef struct Cpu {
    uint16_t pc;
    uint32_t r[REG_COUNT];
    uint8_t flags;
} Cpu;

uint32_t fetch(Memory* mem, Cpu* cpu);
void decode();
void execute();

#endif