/*
 Implementa as instruções de salto (jump) da CPU, com base nas flags G, L e E.
*/

// incluindo instruções de CPU e memória
#include "cpu_internals.h"
#include "mem.h"

// Faz um jump incondicional
void exec_jmp(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    char log_buffer[LINE_MAX_SIZE];
    uint32_t apriori_pc = cpu->pc;
    
    // Extensão de sinal (feita de forma idêntica nos outros jumps).
    // A cacetada de castings e o código feio abaixo provém como 
    // consequências do caos inerente desse projeto, que não é facil demais.
    cpu->pc = (cpu->pc + ((int32_t)(int16_t)instruction->immediate)) & 0xFFFF;

    log_format_cpu_output(
        log_buffer,
        LINE_MAX_SIZE,
        instruction->opcode,
        apriori_pc,
        "JMP",
        cpu->pc+0x4
    );
    log_add(l, log_buffer);
}

// Faz um jump condicional se maior
void exec_jg(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    char log_buffer[LINE_MAX_SIZE];
    uint32_t apriori_pc = cpu->pc;
    
    if (cpu->flags & (1 << G_SHIFT))
        cpu->pc = (cpu->pc + ((int32_t)(int16_t)instruction->immediate)) & 0xFFFF;

    log_format_cpu_output(
        log_buffer,
        LINE_MAX_SIZE,
        instruction->opcode,
        apriori_pc,
        "JG",
        cpu->pc+0x4
    );
    log_add(l, log_buffer);
}

// Faz um jump condicional se menor
void exec_jl(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    char log_buffer[LINE_MAX_SIZE];
    uint32_t apriori_pc = cpu->pc;
    
    if (cpu->flags & (1 << L_SHIFT))
        cpu->pc = (cpu->pc + ((int32_t)(int16_t)instruction->immediate)) & 0xFFFF;

    log_format_cpu_output(
        log_buffer,
        LINE_MAX_SIZE,
        instruction->opcode,
        apriori_pc,
        "JL",
        cpu->pc+0x4
    );
    log_add(l, log_buffer);
}

// Faz um jump condicional se igual
void exec_je(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    char log_buffer[LINE_MAX_SIZE];
    uint32_t apriori_pc = cpu->pc;
    
    if (cpu->flags & (1 << E_SHIFT))
        cpu->pc = (cpu->pc + ((int32_t)(int16_t)instruction->immediate)) & 0xFFFF;

    log_format_cpu_output(
        log_buffer,
        LINE_MAX_SIZE,
        instruction->opcode,
        apriori_pc,
        "JE",
        cpu->pc+0x4
    );
    log_add(l, log_buffer);
}
