/*
 headers responsável por conter os artifícios de manipulação da CPU

 ele oferece as operações básicas para:
   - alocar e inicializar 
   - execultar os ciclos que:
       - busca a próxima instrução da memória
       - decodifica a instrução
       - executa a instrução decodificada
    - libera a memória que fora usada pela CPU

 O mesmo oferece o suporte para o gabage colector (artifício responsável por liberar a memória quando a mesma não está mais em uso)
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
    execute(cpu, mem, instruction, l);
    
    // Avança para a próxima instrução
    cpu->pc += 4;

    // Para debug, impede que o programa quebre totalmente (por enquanto)
    if (cpu->pc >= 0x0FF) cpu->pc = EXIT;
}

// libera a memória que fora usada pela CPU
void cpu_destroy(Cpu* cpu) {
    free(cpu);
}

bool cpu_simulation_finished(Cpu* cpu) {
    return cpu->pc == EXIT;
}

