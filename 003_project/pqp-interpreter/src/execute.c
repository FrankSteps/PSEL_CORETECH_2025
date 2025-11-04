#include "execute.h"
#include "mem.h" 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define HALT_PC 0xFFFFFFFF

// Função utilitária para atualizar as flags L (Less), E (Equal), G (Greater)
void update_flags(Cpu* cpu, int32_t result) {
    // Zero flag (E)
    cpu->flags &= ~(1 << 0); 
    if (result == 0) {
        cpu->flags |= (1 << 0); 
    }

    // Less flag (L)
    cpu->flags &= ~(1 << 1); 
    if (result < 0) {
        cpu->flags |= (1 << 1); 
    }

    // Greater flag (G)
    cpu->flags &= ~(1 << 2); 
    if (result > 0) {
        cpu->flags |= (1 << 2); 
    }
}

// A função principal de execução.
void execute_instruction(Cpu* cpu, const Instruction* instruction) {
    int32_t val_rx = (int32_t)cpu->r[instruction->reg_x];
    int32_t val_ry = (int32_t)cpu->r[instruction->reg_y];
    int32_t result = 0; 

    switch (instruction->opcode) {
        
       
        case 0x00: // mov rx, i16 (Move imediato para registrador Rx)
            cpu->r[instruction->reg_x] = (uint32_t)((int16_t)instruction->immediate);
            break;

        case 0x01: // mov rx, ry (Cópia de registrador: Rx = Ry)
            cpu->r[instruction->reg_x] = cpu->r[instruction->reg_y];
            break;
        
        case 0x02: 
        case 0x03: 
            printf("Instrucao 0x%02X (Memoria) ainda nao implementada.\n", instruction->opcode);
            goto unimplemented;
        
       
        case 0x08: 
            result = val_rx + val_ry;
            cpu->r[instruction->reg_x] = (uint32_t)result;
            break;
            
        
        case 0x09: 
            printf("Instrucao 0x%02X (SUB) ainda nao implementada.\n", instruction->opcode);
            goto unimplemented;
        
        case 0x0A: 
            result = val_rx - val_ry; 
            update_flags(cpu, result);
            break;


        case 0x04: 
            printf("Instrucao 0x%02X (JMP) ainda nao implementada.\n", instruction->opcode);
            goto unimplemented;
            

        case 0x07: 
            if (cpu->flags & (1 << 0)) { 
                cpu->pc = (cpu->pc - 4) + (uint32_t)((int16_t)instruction->immediate);
            }
            break;

      
        case 0x05: 
        case 0x06: 
            printf("Instrucao 0x%02X (Jump Condicional) ainda nao implementada.\n", instruction->opcode);
            goto unimplemented;

            
        case 0x0B: 
        case 0x0C: 
        case 0x0D: 
        case 0x0E: 
        case 0x0F: 
            printf("Instrucao 0x%02X (Logica/Shift) ainda nao implementada.\n", instruction->opcode);
            goto unimplemented;
            
        default:
            printf("**Erro de Execucao: Opcode 0x%02X invalido ou nao implementado. PC=0x%04X\n", 
                   instruction->opcode, cpu->pc - 4);
           
            
        unimplemented:
            cpu->pc = HALT_PC; 
            break;
    }
}