#include "cpu_internals.h"
#include "mem.h"

void exec_movi(Cpu* cpu, Memory* mem, Instruction* instruction) {
    cpu->r[instruction->reg_x] = (uint32_t)instruction->immediate;
}

void exec_mov(Cpu* cpu, Memory* mem, Instruction* instruction) {
    cpu->r[instruction->reg_x] = cpu->r[instruction->reg_y];
}

void exec_mov_rmem(Cpu* cpu, Memory* mem, Instruction* instruction) {
    bool executing = true;
    uint32_t value = mem_read32(mem, instruction->reg_y, executing);
    cpu->r[instruction->reg_x] = value;
}

void exec_mov_memr(Cpu* cpu, Memory* mem, Instruction* instruction) {
    uint16_t address = (uint16_t)instruction->reg_x;
    uint32_t data = instruction->reg_y;
    mem_write32(mem, address, data);
}