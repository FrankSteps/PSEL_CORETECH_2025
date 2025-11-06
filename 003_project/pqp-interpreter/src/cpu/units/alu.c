#include "cpu_internals.h"
#include "mem.h"

// Função utilitária para atualizar as flags L (Less), E (Equal), G (Greater)
void cpu_update_flags(Cpu* cpu, flags_t flag) {
    cpu->flags = 0x00;
    switch (flag) {
        case E: cpu->flags |= (1 << E_SHIFT); break; // Zero flag (E)
        case L: cpu->flags |= (1 << L_SHIFT); break; // Less flag (L)
        case G: cpu->flags |= (1 << G_SHIFT); break; // Greater flag (G)
    }
}


// As funções abaixo realizam as operações específicas de cada instrução da CPU. Cada função recebe a CPU, a memória e a instrução decodificada, e executa a operação correspondente.
void exec_cmp(Cpu* cpu, Memory* mem, Instruction* instruction) {
    Instruction* i = instruction;
    uint8_t result = (i->reg_x > i->reg_y ? G : (i->reg_x < i->reg_y ? L : E));
    cpu_update_flags(cpu, result);
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
