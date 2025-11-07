/*
Este arquivo é o núcleo do projeto, pois é responsável por definir a estrutura da CPU, constantes, flags, tipos de intruções e entre 
outros artifícios que serão usados pelos arquivos .c do pqp-interpreter.
*/

#ifndef CPU_INTERNALS
#define CPU_INTERNALS

#include <stdint.h>
#include "mem.h"
#include "logger.h"

#define REG_COUNT 16    // quantidade de registradores
#define NUM_OPCODES 16     // quantidade de instruções possíveis
#define EXIT 0xF0F0     // endereço de término da simulação

// definições para flags da cpu
#define E_SHIFT 0
#define L_SHIFT 1
#define G_SHIFT 2

typedef struct Cpu {
    uint32_t pc;
    uint32_t r[REG_COUNT];
    uint8_t flags;
} Cpu;

typedef struct Instruction {
    uint8_t opcode;
    uint8_t reg_x;
    uint8_t reg_y;
    uint16_t immediate;
} Instruction;

typedef enum inst_type_t { IMMEDIATE, JUMP, MOV, ARITHMETIC_LOGIC, SHIFT, INVALID } inst_type_t;

typedef enum flags_t { G, L, E } flags_t;

extern const inst_type_t instruction_table[16];
extern const void* instruction_exec_table[16];

uint32_t fetch(Memory* mem, Cpu* cpu);
Instruction decode(uint32_t code);
void execute(Cpu* cpu, Memory* mem, Instruction instruction, Logger* l);

// instruções da lsu (load-store unit)
void exec_movi(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);
void exec_mov(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);
void exec_mov_rmem(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);
void exec_mov_memr(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);

// instruções da alu (arithmetic logic unit)
void exec_cmp(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);
void exec_add(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);
void exec_sub(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);
void exec_and(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);
void exec_or(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);
void exec_xor(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);
void exec_sal(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);
void exec_sar(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);

// instruções de desvio/jump
void exec_jmp(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);
void exec_jg(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);
void exec_jl(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);
void exec_je(Cpu* cpu, Memory* mem, Instruction* instruction, Logger* l);

#endif
