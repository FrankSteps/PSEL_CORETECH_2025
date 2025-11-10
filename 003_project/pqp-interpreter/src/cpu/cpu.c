/*
 Arquivo central de implementação da interface externa da CPU 

 Ele oferece as operações básicas para:
   - Alocar e inicializar CPU 
   - Executar os ciclos que:
       - Buscam a próxima instrução na memória
       - Decodificam a instrução
       - Executam a instrução decodificada
    - Controla comportamentos do final da simulação
    - Libera a memória que fora usada pela CPU
*/

// incluindo as instruções base da CPU
#include "cpu.h"
#include "cpu_internals.h"

// bibliotecas básicas
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// incluindo as instruções base da memória/logger
#include "mem.h"

// Função responsável pela criação da CPU
Cpu* cpu_create() {
    Cpu* cpu = (Cpu*)calloc(1, sizeof(Cpu));

    if (!cpu) {
        printf("**Erro ao alocar estrutura da cpu.\n");
        return NULL;
    }

    return cpu;
}

// Função responsável pelo ciclo da CPU
void cpu_cycle(Cpu* cpu, Memory* mem, Logger* l) {
    uint32_t machine_code = fetch(mem, cpu);
    Instruction instruction = decode(machine_code);
    log_count_instruction(l, instruction.opcode);
    execute(cpu, mem, instruction, l);
    
    // Avança para a próxima instrução
    cpu->pc += 4;
}

// libera a memória que fora usada pela CPU
void cpu_destroy(Cpu* cpu) {
    free(cpu);
}

// Verifica a cada ciclo se a simulação finalizou
bool cpu_simulation_finished(Cpu* cpu) {
    return cpu->pc == EXIT;
}

// Imprime log de finalização da simulação
void cpu_finishing_simulation_log(Cpu* cpu, Logger* l) {
    const char* finish_msg = "0xF0F0->EXIT";
    log_add(l, finish_msg);
    log_count_final_results(l, cpu->r);
}
