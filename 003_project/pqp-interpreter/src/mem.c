#include "mem.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct Memory {
    uint8_t* mem8;
    uint32_t size;
} Memory;

Memory* mem_create(uint32_t size) {
    Memory* mem = (Memory*)calloc(1, sizeof(Memory));

    if (!mem) {
        printf("**Erro ao alocar memoria.\n");
        return NULL;
    }

    // Alocando memoria com alinhamento de 1 byte
    mem->size = size;
    mem->mem8 = (uint8_t*)calloc(mem->size, sizeof(uint8_t));

    return mem;
}

void mem_destroy(Memory* mem) {
    free(mem);
}

void mem_load_program(Memory* mem, char* input_path) {
    FILE* input = fopen(input_path, "r");

    if (!mem) {
        printf("**Erro: Necessario alocar memoria para carregar programa.\n");
        exit(EXIT_FAILURE);
    }

    for (uint32_t i = 0; !feof(input); i++) {
        if (fscanf(input, "%hhx ", &mem->mem8[i]) != 1)
            printf("**Warning: Leitura provavelmente falhou.\n");
    }
}
