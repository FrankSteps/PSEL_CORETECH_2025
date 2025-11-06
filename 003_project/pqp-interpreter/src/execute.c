#include "cpu_internals.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "mem.h"

#define E_SHIFT 0
#define L_SHIFT 1
#define G_SHIFT 2

typedef enum flags_t { G, L, E } flags_t;

// Função utilitária para atualizar as flags L (Less), E (Equal), G (Greater)
void cpu_update_flags(Cpu* cpu, flags_t flag) {
    cpu->flags = 0x00;
    switch (flag) {
        case E: cpu->flags |= (1 << E_SHIFT); break; // Zero flag (E)
        case L: cpu->flags |= (1 << L_SHIFT); break; // Less flag (L)
        case G: cpu->flags |= (1 << G_SHIFT); break; // Greater flag (G)
    }
}

void exec_movi(Cpu* cpu, Memory* mem, Instruction* instruction) {
    cpu->r[instruction->reg_x] = (uint32_t)((int16_t)instruction->immediate);
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

void exec_cmp(Cpu* cpu, Memory* mem, Instruction* instruction) {
    Instruction* i = instruction;
    uint8_t result = (i->reg_x > i->reg_y ? G : (i->reg_x < i->reg_y ? L : E));
    cpu_update_flags(cpu, result);
}

void exec_jmp(Cpu* cpu, Memory* mem, Instruction* instruction) {
    cpu->pc += (uint32_t)instruction->immediate;
}

void exec_jg(Cpu* cpu, Memory* mem, Instruction* instruction) {
    if (cpu->flags & (1 << G_SHIFT)) exec_jmp(cpu, mem, instruction); 
}

void exec_jl(Cpu* cpu, Memory* mem, Instruction* instruction) {
    if (cpu->flags & (1 << L_SHIFT)) exec_jmp(cpu, mem, instruction); 
}

void exec_je(Cpu* cpu, Memory* mem, Instruction* instruction) {
    if (cpu->flags & (1 << E_SHIFT)) exec_jmp(cpu, mem, instruction); 
}

void exec_add(Cpu* cpu, Memory* mem, Instruction* instruction) {
    uint32_t add = (uint32_t)instruction->reg_x + (uint32_t)instruction->reg_y;
    cpu->r[instruction->reg_x] = (uint32_t)add;
}

void exec_sub(Cpu* cpu, Memory* mem, Instruction* instruction) {
    uint32_t sub = (uint32_t)instruction->reg_x - (uint32_t)instruction->reg_y;
    cpu->r[instruction->reg_x] = (uint32_t)sub;
}

void exec_and(Cpu* cpu, Memory* mem, Instruction* instruction) {
    cpu->r[instruction->reg_x] &= (uint32_t)instruction->reg_y;
}

void exec_or(Cpu* cpu, Memory* mem, Instruction* instruction) {
    cpu->r[instruction->reg_x] |= (uint32_t)instruction->reg_y;
}

void exec_xor(Cpu* cpu, Memory* mem, Instruction* instruction) {
    cpu->r[instruction->reg_x] ^= (uint32_t)instruction->reg_y;
}

void exec_sal(Cpu* cpu, Memory* mem, Instruction* instruction) {
    cpu->r[instruction->reg_x] <<= (uint32_t)instruction->immediate;
}

void exec_sar(Cpu* cpu, Memory* mem, Instruction* instruction) {
    cpu->r[instruction->reg_x] >>= (uint32_t)instruction->immediate;
}

const void* instruction_exec_table[16] = {
    [0x00] = exec_movi,
    [0x01] = exec_mov,
    [0x02] = exec_mov_rmem,
    [0x03] = exec_mov_memr,
    [0x04] = exec_cmp,
    [0x05] = exec_jmp,
    [0x06] = exec_jg,
    [0x07] = exec_jl,
    [0x08] = exec_je,
    [0x09] = exec_add,
    [0x0A] = exec_sub,
    [0x0B] = exec_and,
    [0x0C] = exec_or,
    [0x0D] = exec_xor,
    [0x0E] = exec_sal,
    [0x0F] = exec_sar
};

void execute(Cpu* cpu, Memory* mem, Instruction instruction) {
    uint8_t opcode = instruction.opcode;
    void (*handler)(Cpu*, Memory*, Instruction*) = instruction_exec_table[opcode];

    handler(cpu, mem, &instruction);
}
