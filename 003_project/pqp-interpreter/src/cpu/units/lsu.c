/*
Responsável por implementar as instruções de movimentação de código (MOV) do CPU. 
Basicamente, o MOV é responsável por movimentar/transferir os valores entre os registradores de memória
*/

// incluindo as instruções de CPU e memória
#include "cpu_internals.h"
#include "mem.h"

// Move um valor imediato (constante) para um registrador
void exec_movi(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    cpu->r[instruction->reg_x] = (uint32_t)instruction->immediate;
}

 // Copia o valor de um registrador para outro
void exec_mov(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    cpu->r[instruction->reg_x] = cpu->r[instruction->reg_y];
}

 // Lê um valor da memória e coloca em um registrador
void exec_mov_rmem(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    bool executing = true;
    uint32_t value = mem_read32(mem, cpu->r[instruction->reg_y], executing);
    cpu->r[instruction->reg_x] = value;
}

// Escreve o valor de um registrador em um endereço da memória
void exec_mov_memr(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l) {
    uint16_t address = (uint16_t)cpu->r[instruction->reg_x];
    uint32_t data = cpu->r[instruction->reg_y];
    mem_write32(mem, address, data);
}
