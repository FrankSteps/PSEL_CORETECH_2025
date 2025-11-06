#include "cpu_internals.h"
#include "mem.h"

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