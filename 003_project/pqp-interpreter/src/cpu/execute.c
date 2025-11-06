#include "cpu_internals.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "mem.h"

// tabela de instruções. Cada instrução está sendo ligada a um opcode
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

// Função responsável por receber a instrução e chamar a função ligada à mesma respeitando a orientação da tabela acima.
void execute(Cpu* cpu, Memory* mem, Instruction instruction) {
    uint8_t opcode = instruction.opcode;
    void (*handler)(Cpu*, Memory*, Instruction*) = instruction_exec_table[opcode];

    handler(cpu, mem, &instruction);
}
