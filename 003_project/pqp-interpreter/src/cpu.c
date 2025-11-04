#include "cpu.h"
#include "cpu_internals.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mem.h"

Cpu* cpu_create() {
    Cpu* cpu = (Cpu*)calloc(1, sizeof(Cpu));

    if (!cpu) {
        printf("**Erro ao alocar estrutura da cpu.\n");
        return NULL;
    }

    return cpu;
}

void cpu_cycle(Cpu* cpu, Memory* mem) {
    uint32_t machine_code = fetch(mem, cpu);
    Instruction instruction = decode(machine_code);
    execute(instruction);
}

void cpu_destroy(Cpu* cpu) {
    free(cpu);
}
