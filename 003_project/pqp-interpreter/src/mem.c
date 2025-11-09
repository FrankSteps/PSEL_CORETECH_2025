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
#include <stddef.h>

// struct da memória contendo as variáveis básicas para o funcionamento da mesma
typedef struct Memory {
    uint8_t* mem8; // definição de vetor de dados em RAM com alinhamento byte a byte
    uint32_t size; // tamanho da memória definido na inicialização
    bool loaded; // flag para verificação de programa disponível na memória
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

    if (!mem->mem8) {
        printf("**Erro ao alocar memoria (dados).\n");
        return NULL;
    }

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


// Transforma bytes big endian em little endian e vice-versa.
uint32_t mem_endianess_transform(uint32_t value, size_t size) {
    uint32_t* buffer = (uint32_t*)calloc(4, size);
    uint32_t content = 0x0;

    for (uint8_t i = 0; i < size; i++) {
        buffer[i] = (value & (0XFF << 8*i)) >> 8;
        content |= (buffer[i] << 8*(size-1-i));
    }

    return content;
}


// Função responsável por ler um byte da memória
uint8_t mem_read8(Memory* mem, uint16_t address) {
    if (!mem || !mem->loaded) {
        printf("**Erro: Necessario alocar memoria/carregar programa para ler.\n");
        exit(EXIT_FAILURE);
    }

    return mem->mem8[address];
}


/*
    Função responsável por ler (load) quatro bytes da memória.
    Utiliza convenção big endian para carregamento do programa e
    little endian para a leitura em tempo de execução.
*/
uint32_t mem_read32(Memory* mem, uint16_t address, bool executing) {
    uint8_t buffer[4] = {0};
    uint32_t content = 0x0;

    for (uint16_t i = 0; i < 4; i++) {
        buffer[i] = mem_read8(mem, address + i);
        // O parâmetro 'executing' define endianess da leitura
        content |= buffer[i] << (executing ? 8*i : 8*(3-i));
    }

    return content;
}


// Função auxiliar que lê um byte da memória
void mem_write8(Memory* mem, uint16_t address, uint8_t data) {
    mem->mem8[address] = data;
}


/*
    Função responsável por escrever (store) quatro bytes na memória
    Realiza a escrita conforme convenção little endian
*/ 
void mem_write32(Memory* mem, uint16_t address, uint32_t data) {
    uint8_t buffer[4] = {0};

    for (uint8_t i = 0; i < 4; i++) {
        // Itera de modo a pôr o byte mais sig. de 'data' no final
        buffer[i] = (uint8_t)(data & (0xFF << 8*i));
        mem_write8(mem, address + i, buffer[i]);
    }
}
