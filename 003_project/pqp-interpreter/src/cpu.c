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

// incluindo as instruções base da memória
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
void cpu_cycle(Cpu* cpu, Memory* mem) {
    if (cpu->pc == EXIT) return false;

    uint32_t machine_code = fetch(mem, cpu);
    Instruction instruction = decode(machine_code);

    execute(cpu, mem, instruction);

    // Avança para a próxima instrução
    cpu->pc += 4;
    return true;
}

// libera a memória que fora usada pela CPU
void cpu_destroy(Cpu* cpu) {
    free(cpu);
}

