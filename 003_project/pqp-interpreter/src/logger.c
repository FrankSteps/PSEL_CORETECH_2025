#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#define MAX_INSTRUCTION_COUNT_STR_SIZE 256 
#define MAX_REGISTER_STR_SIZE 512

const char* format_table[16] = {
    [0x00] = "0x%04X->%s_R%hhd=0x%08X",
    [0x01] = "0x%04X->%s_R%hhd=R%hhd=0x%08X",
    [0x02] = "0x%04X->%s_R%hhd=MEM[0x%02X,0x%02X,0x%02X,0x%02X]=[0x%02X,0x%02X,0x%02X,0x%02X]",
    [0x03] = "0x%04X->%s_MEM[0x%02X,0x%02X,0x%02X,0x%02X]=R%hhd=[0x%02X,0x%02X,0x%02X,0x%02X]",
    [0x04] = "0x%04X->%s_R%hhd<=>R%hhd(G=%x,L=%x,E=%x)",
    [0x05] = "0x%04X->%s_0x%04X",
    [0x06] = "0x%04X->%s_0x%04X",
    [0x07] = "0x%04X->%s_0x%04X",
    [0x08] = "0x%04X->%s_0x%04X",
    [0x09] = "0x%04X->%s_R%hhd+=R%hhd=0x%08X+0x%08X=0x%08X",
    [0x0A] = "0x%04X->%s_R%hhd-=R%hhd=0x%08X-0x%08X=0x%08X",
    [0x0B] = "0x%04X->%s_R%hhd&=R%hhd=0x%08X&0x%08X=0x%08X",
    [0x0C] = "0x%04X->%s_R%hhd|=R%hhd=0x%08X|0x%08X=0x%08X",
    [0x0D] = "0x%04X->%s_R%hhd^=R%hhd=0x%08X^0x%08X=0x%08X",
    [0x0E] = "0x%04X->%s_R%hhd<<=%hd=0x%08X<<%hd=0x%08X",
    [0x0F] = "0x%04X->%s_R%hhd>>=%hd=0x%08X>>%hd=0x%08X"
};

typedef struct Buffer {
    char** content;                     // Armazena strings salvas
    int index;                          // Controla índice de strings armazenadas
    int size;                           // Tamanho do buffer (definido na criação)
} Buffer;

typedef struct Logger {
    Buffer buffer;                      // Estrutura de buffer
    bool enabled;                       // Flag de habilitação do logger
    int instruction_cnt[16];            // Coleta dados de instruções
    uint32_t reached_address;           // Indica maior valor de PC já salvo para impressão  
    FILE* output;                       // Referência para arquivo de saída.
} Logger;

Logger* log_create(int size) {
    // O uso de calloc faz com que 'l->instruction_cnt' e outros 
    //não precisem ser inicializados com zeros.
    Logger* l = (Logger*)calloc(1, sizeof(Logger));

    l->output = fopen(OUTPUT_PATH, "w");
    l->enabled = true;

    if (!l->output) {
        printf("**Erro ao abrir arquivo de output (%s).\n", OUTPUT_PATH);
        return NULL;
    }

    l->buffer.size = size;

    if (!l) {
        printf("**Erro ao alocar estrutura do logger.\n");
        return NULL;
    }

    l->buffer.content = (char**)malloc(l->buffer.size*sizeof(char*));

    if (!l->buffer.content) {
        printf("**Erro ao alocar buffer do logger.\n");
        return NULL;
    }

    for (int i = 0; i < l->buffer.size; i++) {
        l->buffer.content[i] = (char*)malloc(LINE_MAX_SIZE);
        if (!l->buffer.content[i]) {
            printf("**Erro ao alocar buffer do logger (idx=%d).\n", i);
            return NULL;
        }
    }

    return l;
}

void log_enable(Logger* l) {
    l->enabled = true;
}

void log_disable(Logger* l) {
    l->enabled = false;
}

void log_count_instruction(Logger* l, uint8_t opcode) {
    // 1. Verificação de segurança: checa se o ponteiro do logger é válido
    if (!l) return;
    
    // 2. Verificação de range
    // O array l->instruction_cnt tem 16 posições (índices 0 a 15)
    if (opcode < 16) { 
       
        l->instruction_cnt[opcode]++;
    }
}

void log_set_reached_address(Logger* l, uint32_t pc) {
    // Condição para salvar maior PC atingido
    if (pc > l->reached_address) l->reached_address = pc;
}

uint32_t log_get_reached_address(Logger* l) {
    return l->reached_address;
}

void log_add(Logger* l, const char* content) {
    if (l->buffer.index == l->buffer.size-1) {
        printf("**Erro: Buffer do logger esta cheio!\n");
        exit(EXIT_FAILURE);
    }

    //printf("log_enabled=%d\n", l->enabled);
    if (l->enabled) {
        // Garante que content tenha \0
        snprintf(l->buffer.content[l->buffer.index], LINE_MAX_SIZE, "%s", content);
        l->buffer.index++;
    }
}

void log_print(Logger* l, int index) {
    fprintf(l->output, "%s\n", l->buffer.content[index]);
}

void log_print_all(Logger* l) {
    for (int i = 0; i < l->buffer.index; i++) {
        log_print(l, i);
    }
}

/*
Desc.: Wrapper "privado" que formata instruções a partir de descrição em
       'format_table'.
Parâmetros:
    (uint8_t) opcode: Código da instrução que será formatada.
Return: String de formatação relativa ao opcode informado.
*/
const char* log_get_instruction_format(uint8_t opcode) {
    if (opcode > 16) {
        return "0x%04X->[INVALID]";
    }

    return format_table[opcode];
}

void log_format_cpu_output(Logger* l, char* buffer, int buffer_size, uint8_t opcode, ...) {
    if (l->enabled) {
        const char* format = log_get_instruction_format(opcode);
    
        va_list args;                                 // Lista de argumentos não "declarados"
        va_start(args, opcode);                       // Inicialização da lista
        vsnprintf(buffer, buffer_size, format, args); // Formatação
        
        va_end(args);
    }
}

void log_count_final_results(Logger* l, uint32_t* cpu_registers) {
 if (!l) return;
    
    printf("** Simulação finalizada.\n");

    // 1. Montar a string de Contagem de Instruções
    char instruction_count_str[MAX_INSTRUCTION_COUNT_STR_SIZE] = "[";
    int current_len = 1;
    int written;

    for (int i = 0; i < 16; i++) {
        written = snprintf(
            instruction_count_str + current_len, 
            MAX_INSTRUCTION_COUNT_STR_SIZE - current_len, 
            "%02X: %d%s", 
            i, 
            l->instruction_cnt[i],
            (i < 15) ? ", " : ""
        );
        current_len += written;
        if (current_len >= MAX_INSTRUCTION_COUNT_STR_SIZE) break;
    }
    
    // Fecha a chave '[' e adiciona a string ao buffer
    snprintf(instruction_count_str + current_len, MAX_INSTRUCTION_COUNT_STR_SIZE - current_len, "]");
    log_add(l, instruction_count_str);

    // 2. Montar a string dos Registradores Finais 
    char register_str[MAX_REGISTER_STR_SIZE] = ""; // Começa vazio
    current_len = 0;

    for (int i = 0; i < 16; i++) {
        written = snprintf(
            register_str + current_len, 
            MAX_REGISTER_STR_SIZE - current_len, 
            "%sR%d=0x%08X", 
            (i == 0) ? "[" : ", ", // Abre com '[' e usa ", " para os demais
            i, 
            cpu_registers[i]
        );
        current_len += written;
        if (current_len >= MAX_REGISTER_STR_SIZE) break;
    }
    
    // Fecha a chave ']' e adiciona a string ao buffer
    snprintf(register_str + current_len, MAX_REGISTER_STR_SIZE - current_len, "]");
    log_add(l, register_str);
}

void log_destroy(Logger* l) {
    for (int i = 0; i < l->buffer.size; i++) {
        free(l->buffer.content[i]);
    }

    free(l->buffer.content);
    fclose(l->output);
    free(l);
}