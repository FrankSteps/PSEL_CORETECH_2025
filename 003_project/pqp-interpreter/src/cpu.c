#include "cpu.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define REG_COUNT 16

typedef struct Cpu {
    uint16_t pc;
    uint32_t r[REG_COUNT];
    uint8_t flags;
} Cpu;

Cpu* cpu_create() {
    Cpu* cpu = (Cpu*)calloc(1, sizeof(Cpu));

    if (!cpu) {
        printf("**Erro ao alocar estrutura da cpu.\n");
        return NULL;
    }

    return cpu;
}

void cpu_destroy(Cpu* cpu) {
    free(cpu);
}