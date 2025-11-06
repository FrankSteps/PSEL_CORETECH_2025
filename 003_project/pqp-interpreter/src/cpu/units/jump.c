/*
 Implementa as instruções de salto (jump) da CPU, com base nas flags G, L e E.
*/

// incluindo instruções de CPU e memória
#include "cpu_internals.h"
#include "mem.h"

// Faz um jump incondicional
void exec_jmp(Cpu* cpu, Memory* mem, Instruction* instruction) {
    cpu->pc += (uint32_t)instruction->immediate;
}

// Faz um jump condicional se maior
void exec_jg(Cpu* cpu, Memory* mem, Instruction* instruction) {
    if (cpu->flags & (1 << G_SHIFT)) exec_jmp(cpu, mem, instruction); 
}

// Faz um jump condicional se menor
void exec_jl(Cpu* cpu, Memory* mem, Instruction* instruction) {
    if (cpu->flags & (1 << L_SHIFT)) exec_jmp(cpu, mem, instruction); 
}

// Faz um jump condicional se igual
void exec_je(Cpu* cpu, Memory* mem, Instruction* instruction) {
    if (cpu->flags & (1 << E_SHIFT)) exec_jmp(cpu, mem, instruction); 
}
