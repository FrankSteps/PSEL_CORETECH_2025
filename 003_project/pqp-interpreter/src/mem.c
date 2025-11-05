/*
    Esta parte do programa implementa um módulo de memória: 
    ele cria, carrega, lê e destrói a memória usada pela CPU simulada.
*/

// implementando o mem.h para usar as operações básicas aqui
#include "mem.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

// struct da memória contendo as variáveis básicas para o funcionamento da mesma
typedef struct Memory {
    uint8_t* mem8; // <- expliquem melhor sobre cada uma, por favor :: ass: Francisco <3
    uint32_t size;
    bool loaded;
} Memory;

// Função responsável pela criação da memória
Memory* mem_create(uint32_t size) {
    Memory* mem = (Memory*)calloc(1, sizeof(Memory));

    if (!mem) {
        printf("**Erro ao alocar memoria.\n");
        return NULL;
    }

    // Alocando memoria com alinhamento de 1 byte;
    // O alinhamento posto desse jeito facilita a leitura.
    mem->size = size;
    mem->mem8 = (uint8_t*)calloc(mem->size, sizeof(uint8_t));
    mem->loaded = false;

    return mem;
}

// Função responsável por evitar o vazamento de memória -> Destruição da mesma
void mem_destroy(Memory* mem) {
    if (!mem) return;
    free(mem->mem8);
    free(mem);
}

// Função para carregar o input para a memória
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

    mem->loaded = true;
}


// Função responsável por ler um byte da memória
uint8_t mem_read8(Memory* mem, uint16_t address) {
    if (!mem || !mem->loaded) {
        printf("**Erro: Necessario alocar memoria/carregar programa para ler.\n");
        exit(EXIT_FAILURE);
    }

    return mem->mem8[address];
}


// Função responsável por ler quatro bytes da memória
uint32_t mem_read32(Memory* mem, uint16_t address) {
    uint8_t buffer[4] = {0};
    uint32_t content = 0x0;

    for (uint16_t i = 0; i < 3; i++) {
        buffer[i] = mem_read8(mem, address + i);
        content |= buffer[i] << 8*(3-i);
    }

    return content;
}

