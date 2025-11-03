#include "cpu_internals.h"

#include <stdio.h>

#include "mem.h"

uint32_t fetch(Memory* mem, Cpu* cpu) {
    uint32_t instruction =  mem_read32(mem, cpu->pc);

    printf("fetch: 0x%08X\n", instruction);

    return instruction;
}