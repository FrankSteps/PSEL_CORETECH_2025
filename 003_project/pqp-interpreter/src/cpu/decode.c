#include "cpu_internals.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Esta função está com a tabela de instruções associa o(s) opcode(s) a um tipo de instrução
const inst_type_t instruction_table[16] = {
    [0x00] = IMMEDIATE,                   // imediata
    [0x01 ... 0x04] = MOV,                // movimento
    [0x05 ... 0x08] = JUMP,               // salto
    [0x09 ... 0x0D] = ARITHMETIC_LOGIC,   // lógica aritmética (or, and, xor...)
    [0x0E ... 0x0F] = SHIFT               // shift
};

// Função responsável por receber a instrução retornar o tipo específico da mesma
inst_type_t decode_instruction_type(uint8_t opcode) {
    return (opcode <= 0x0F ? instruction_table[opcode] : INVALID);
}

/*
A partir do tipo da instrução, aplica máscara de bits de modo a resgatar os operandos
e montar uma instrução pronta para execução.
*/
void decode_operators(Instruction* instruction, inst_type_t type, uint32_t code) {
    uint16_t i16 = 0x0, i5 = 0x0;

    switch (type) {
        case IMMEDIATE:
            i16 = (code & (0xFFFF << 16)) >> 16;

            instruction->reg_x = (code & (0xF << 12)) >> 12;
            instruction->immediate = i16;
            return;
        case MOV:
            instruction->reg_x = (code & (0xF << 12)) >> 12;
            instruction->reg_y = (code & (0xF << 8)) >> 8;
            return;
        case JUMP:
            i16 = (code & (0xFFFF << 16)) >> 16;

            instruction->immediate = i16;
            return;
        case ARITHMETIC_LOGIC:
            instruction->reg_x = (code & (0xF << 12)) >> 12;
            instruction->reg_y = (code & (0xF << 8)) >> 8;
            return;
        case SHIFT:
            i5 = (code & (0x1F << 24)) >> 24;

            instruction->reg_x = (code & (0xF << 12)) >> 12;
            instruction->immediate = i5;
            return;
        case INVALID:
            printf("** Leitura de instrucao invalida.\n");
            return;
    }
}

// Esta função está responsável por decodificar a instrução da memória e 
// transformar em uma estrutura para CPU trabalhar em cima.
Instruction decode(uint32_t code) {
    Instruction instruction = {0};
    instruction.opcode = code & 0xFF;

    // printf("decode (opcode): 0x%02X\n", instruction.opcode);

    inst_type_t type = decode_instruction_type(instruction.opcode);
    decode_operators(&instruction, type, code);

    printf("decode (instruction): x->0x%04X, y->0x%04X, i->0x%X\n",
        instruction.reg_x, 
        instruction.reg_y,
        instruction.immediate
    );

    // retornando a instrução
    return instruction;
}
