#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

const char* format_table[16] = {
    [0x00] = "0x%04X->%s_R%hhd=0x%08X",
    [0x01] = "0x%04X->%s_R%hhd=R%hhd=0x%08X",
    [0x02] = "0x%04X->%s_R%hhd=MEM[0x%02X,0x%02X,0x%02X,0x%02X]=[0x%02X,0x%02X,0x%02X,0x%02X]",
    [0x03] = "0x%04X->%s_MEM[0x%02X,0x%02X,0x%02X,0x%02X]=R%hhd=[0x%02X,0x%02X,0x%02X,0x%02X]",
    [0x04] = "0x%04X->%s_R%hhd<=>R%hhd(G=%x,L=%x,E=%x)",
    [0x05] = "0x%04X->%s_0x%08X",
    [0x06] = "0x%04X->%s_0x%08X",
    [0x07] = "0x%04X->%s_0x%08X",
    [0x08] = "0x%04X->%s_0x%08X",
    [0x09] = "0x%04X->%s_R%hhd+=R%hhd=0x%08X+0x%08X=0x%08X",
    [0x0A] = "0x%04X->%s_R%hhd-=R%hhd=0x%08X-0x%08X=0x%08X",
    [0x0B] = "0x%04X->%s_R%hhd&=R%hhd=0x%08X&0x%08X=0x%08X",
    [0x0C] = "0x%04X->%s_R%hhd|=R%hhd=0x%08X|0x%08X=0x%08X",
    [0x0D] = "0x%04X->%s_R%hhd^=R%hhd=0x%08X^0x%08X=0x%08X",
    [0x0E] = "0x%04X->%s_R%hhd<<=%hd=0x%08X<<%hd=0x%08X",
    [0x0F] = "0x%04X->%s_R%hhd>>=%hd=0x%08X>>%hd=0x%08X"
};

typedef struct Logger {
    int intruction_cnt[16];             // Coleta dados de instruções
    char** buffer;                      // Armazena strings salvass
    FILE* output;                       // Referência para arquivo de saída.
    int buffer_idx;                     // Controla índice de strings armazenadas
    int size;                           // Tamanho do buffer (definido na criação)
} Logger;

Logger* log_create(int size) {
    // O uso de calloc faz com que 'l->instruction_cnt' e outros 
    //não precisem ser inicializados com zeros.
    Logger* l = (Logger*)calloc(1, sizeof(Logger));

    FILE* output = fopen(OUTPUT_PATH, "w");

    if (!output) {
        printf("**Erro ao abrir arquivo de output (%s).\n", OUTPUT_PATH);
        return NULL;
    }

    l->size = size;

    if (!l) {
        printf("**Erro ao alocar estrutura do logger.\n");
        return NULL;
    }

    l->buffer = (char**)malloc(l->size);

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

    return l;
}

void log_add(Logger* l, char* content) {
    // Garante que content tenha \0
    snprintf(l->buffer[l->buffer_idx], LINE_MAX_SIZE, "%s", content);
    l->buffer_idx++;
}

void log_print(Logger* l, int index) {
    fprintf(l->output, "%s\n", l->buffer[index]);
}

void log_print_all(Logger* l) {
    for (int i = 0; i < l->buffer_idx; i++) {
        log_print(l, i);
    }
}

const char* log_get_instruction_format(uint8_t opcode) {
    if (opcode > 16) {
        return "0x%04X->[INVALID]";
    }

    return format_table[opcode];
}

void log_format_cpu_output(char* buffer, int buffer_size, uint8_t opcode, ...) {
    const char* format = log_get_instruction_format(opcode);

    va_list args;                                 // Lista de argumentos não "declarados"
    va_start(args, opcode);                       // Inicialização da lista
    vsnprintf(buffer, buffer_size, format, args); // Formatação
    
    va_end(args);
}

void log_destroy(Logger* l) {
    for (int i = 0; i < l->size; i++) {
        free(l->buffer[i]);
    }

    free(l->buffer);
    fclose(l->output);
}
