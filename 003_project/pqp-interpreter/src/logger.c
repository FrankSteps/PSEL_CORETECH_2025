#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Logger {
    int intruction_cnt[NUM_OPCODES];    // Coleta dados de instruções
    char** buffer;                      // Armazena strings salvass
    FILE* output;                       // Referência para arquivo de saída.
    int buffer_idx;                     // Controla índice de strings armazenadas
    int size;                           // Tamanho do buffer (definido na criação)
} Logger;

Logger* log_create(int size, char* output_path) {
    // O uso de calloc faz com que 'l->instruction_cnt' e outros 
    //não precisem ser inicializados com zeros.
    Logger* l = (Logger*)calloc(1, sizeof(Logger));

    FILE* output = fopen(output_path, "w");

    if (!output) {
        printf("**Erro ao abrir arquivo de output (%s).\n", output_path);
        return NULL;
    }

    l->size = size;

    if (!l) {
        printf("**Erro ao alocar estrutura do logger.\n");
        return NULL;
    }

    l->buffer = (char*)malloc(l->size);

    if (!l->buffer) {
        printf("**Erro ao alocar buffer do logger.\n");
        return NULL;
    }

    for (int i = 0; i < l->size; i++) {
        l->buffer[i] = (char*)malloc(LINE_MAX_SIZE);
        if (!l->buffer[i]) {
            printf("**Erro ao alocar buffer do logger (idx=%d).\n", i);
            return NULL;
        }
    }
}

void log_add(Logger* l, char* content) {
    // Copia string para content. A responsabilidade de inserir \0
    // no content fica pro chamador.
    strcpy(l->buffer[l->buffer_idx], content);
    l->buffer_idx++;
}

void log_print(Logger* l, int index) {
    fprintf(l->output, l->buffer[index]);
}

void log_print_all(Logger* l) {
    for (int i = 0; i < l->buffer_idx; i++) {
        log_print(l, i);
    }
}

void log_destroy(Logger* l) {
    for (int i = 0; i < l->size; i++) {
        free(l->buffer[i]);
    }

    free(l->buffer);
    fclose(l->output);
}
