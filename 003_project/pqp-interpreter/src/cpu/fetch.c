/*
responsável pela primeira etapa do ciclo de execução da CPU.
*/

#include "cpu_internals.h"

#include <stdio.h>

#include "mem.h"

// Função responsável pela busca da próxima instrução da memória para que a CPU para decodificá-la e executá-la.
uint32_t fetch(Memory* mem, Cpu* cpu) {
    bool executing = false;
    uint32_t instruction =  mem_read32(mem, cpu->pc, executing);

    // printf("fetch: 0x%08X\n", instruction);

    return instruction;
}
