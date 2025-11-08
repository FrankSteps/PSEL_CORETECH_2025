/*
Responsável por implementar as instruções de movimentação de código (MOV) do CPU. 
Basicamente, o MOV é responsável por movimentar/transferir os valores entre os registradores de memória
*/

// incluindo as instruções de CPU, memória e logger
#include "cpu_internals.h"
#include "mem.h"
#include "logger.h"

// Move um valor imediato (constante) para um registrador
void exec_movi(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    char log_buffer[LINE_MAX_SIZE];
    
    cpu->r[instruction->reg_x] = (uint32_t)instruction->immediate;

    log_format_cpu_output(
        log_buffer,
        LINE_MAX_SIZE,
        instruction->opcode,
        cpu->pc,
        "MOV",
        instruction->reg_x,
        instruction->immediate
    );
    log_add(l, log_buffer);
}

 // Copia o valor de um registrador para outro
void exec_mov(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    char log_buffer[LINE_MAX_SIZE];
    
    cpu->r[instruction->reg_x] = cpu->r[instruction->reg_y];

    log_format_cpu_output(
        log_buffer,
        LINE_MAX_SIZE,
        instruction->opcode,
        cpu->pc,
        "MOV",
        instruction->reg_x,
        instruction->reg_y,
        cpu->r[instruction->reg_y]
    );
    log_add(l, log_buffer);
}

 // Lê um valor da memória e coloca em um registrador
void exec_mov_rmem(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    char log_buffer[LINE_MAX_SIZE];
    
    bool executing = true;
    uint32_t value = mem_read32(mem, cpu->r[instruction->reg_y], executing);
    cpu->r[instruction->reg_x] = value;

    log_format_cpu_output(
        log_buffer,
        LINE_MAX_SIZE,
        instruction->opcode,
        cpu->pc,
        "MOV",
        instruction->reg_x,
        cpu->r[instruction->reg_y]+0x00,
        cpu->r[instruction->reg_y]+0x01,
        cpu->r[instruction->reg_y]+0x02,
        cpu->r[instruction->reg_y]+0x03,
        (value & (0xFF<<24))>>24,
        (value & (0xFF<<16))>>16,
        (value & (0xFF<<8))>>8,
        value & 0xFF
    );
    log_add(l, log_buffer);
}

// Escreve o valor de um registrador em um endereço da memória
void exec_mov_memr(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    char log_buffer[LINE_MAX_SIZE];
    
    uint16_t address = (uint16_t)cpu->r[instruction->reg_x];
    uint32_t data = cpu->r[instruction->reg_y];
    mem_write32(mem, address, data);

    log_format_cpu_output(
        log_buffer,
        LINE_MAX_SIZE,
        instruction->opcode,
        cpu->pc,
        "MOV",
        address+0x00,
        address+0x01,
        address+0x02,
        address+0x03,
        instruction->reg_x,
        (cpu->r[instruction->reg_x] & (0xFF<<24))>>24,
        (cpu->r[instruction->reg_x] & (0xFF<<16))>>16,
        (cpu->r[instruction->reg_x] & (0xFF<<8))>>8,
        cpu->r[instruction->reg_x] & 0xFF
    );
    log_add(l, log_buffer);
}
