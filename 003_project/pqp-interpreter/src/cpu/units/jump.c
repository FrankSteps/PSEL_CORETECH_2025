/*
 Implementa as instruções de salto (jump) da CPU, com base nas flags G, L e E.
*/

// incluindo instruções de CPU e memória
#include "cpu_internals.h"
#include "mem.h"

// Verifica se o endereço para o qual o programa saltará já foi visitado.
bool is_revisitting_address(Logger* l, uint32_t next_pc) {
    return log_get_reached_address(l) >= next_pc + 0x04;
}

// Essa função centraliza a lógica de jumps
void jump(Cpu* cpu, Instruction* instruction, Logger* l) {
    // Extensão de sinal (feita de forma idêntica nos outros jumps).
    // A cacetada de castings e o código feio abaixo provém como 
    // consequências do caos inerente desse projeto, que não é facil demais.
    cpu->pc = (cpu->pc + ((int32_t)(int16_t)instruction->immediate)) & 0xFFFF;
}

void update_logger_enability(Cpu* cpu, Logger* l) {
    // Só usa o logger se acessar um novo endereço
    bool repeating = is_revisitting_address(l, cpu->pc);
    repeating ? log_disable(l) : log_enable(l);
}

// Faz um jump incondicional
void exec_jmp(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    char log_buffer[LINE_MAX_SIZE];
    uint32_t apriori_pc = cpu->pc;
    
    jump(cpu, instruction, l);

    log_format_cpu_output(
        l,
        log_buffer,
        LINE_MAX_SIZE,
        instruction->opcode,
        apriori_pc,
        "JMP",
        cpu->pc+0x4
    );
    log_add(l, log_buffer);
    update_logger_enability(cpu, l);
}

// Faz um jump condicional se maior
void exec_jg(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    char log_buffer[LINE_MAX_SIZE];
    uint32_t apriori_pc = cpu->pc;
    
    if (cpu->flags & (1 << G_SHIFT)) jump(cpu, instruction, l);

    log_format_cpu_output(
        l,
        log_buffer,
        LINE_MAX_SIZE,
        instruction->opcode,
        apriori_pc,
        "JG",
        cpu->pc+0x4
    );
    log_add(l, log_buffer);
    update_logger_enability(cpu, l);
}

// Faz um jump condicional se menor
void exec_jl(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    char log_buffer[LINE_MAX_SIZE];
    uint32_t apriori_pc = cpu->pc;
    
    if (cpu->flags & (1 << L_SHIFT)) jump(cpu, instruction, l);

    log_format_cpu_output(
        l,
        log_buffer,
        LINE_MAX_SIZE,
        instruction->opcode,
        apriori_pc,
        "JL",
        cpu->pc+0x4
    );
    log_add(l, log_buffer);
    update_logger_enability(cpu, l);
}

// Faz um jump condicional se igual
void exec_je(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    char log_buffer[LINE_MAX_SIZE];
    uint32_t apriori_pc = cpu->pc;
    
    if (cpu->flags & (1 << E_SHIFT)) jump(cpu, instruction, l);

    log_format_cpu_output(
        l,
        log_buffer,
        LINE_MAX_SIZE,
        instruction->opcode,
        apriori_pc,
        "JE",
        cpu->pc+0x4
    );
    log_add(l, log_buffer);
    update_logger_enability(cpu, l);
}
