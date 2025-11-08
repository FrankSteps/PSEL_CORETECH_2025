#ifndef LOGGER
#define LOGGER

#include <stdint.h>

#define LINE_MAX_SIZE 256
#define OUTPUT_PATH "output/output.txt"

// Define buffer e variáveis auxiliares para armazenamento de strings.
typedef struct Logger Logger;

extern const char* format_table[16];

/*
Desc.: Lida com alocações e atribuições iniciais do logger.

Parâmetros:
    (int) size: Tamanho/Quantidade de linhas salvas no buffer;
    (char*) output_path: Caminho do arquivo de output.

Return: Logger inicializado.
*/
Logger* log_create(int size);

/*
Desc.: Adiciona string no buffer do logger.

Parâmetros:
    (Logger*) l: Estrutura do logger;
    (char*) content: String a ser adicionada.
*/
void log_add(Logger* l, const char* content);


/*
Desc.: Imprime string do buffer.

Parâmetros:
    (Logger*) l: Estrutura do logger;
    (int) index: Índice do buffer a ser impresso.
*/
void log_print(Logger* l, int index);

/*
Desc.: Imprime todas as strings armazenadas no buffer.

Parâmetros:
    (Logger*) l: Estrutura do logger.
*/
void log_print_all(Logger* l);

/*
Desc.: Formata parâmetros da cpu, preenchendo um buffer com a string resultante.

Parâmetros:
    (char) buffer: Buffer que será preenchido;
    (int) buffer_size: Tamanho do buffer;
    (uin8_t) opcode: Código da instrução.
*/
void log_format_cpu_output(char* buffer, int buffer_size, uint8_t opcode, ...);

/*
Desc.: Libera memória do logger.

Parâmetros:
    (Logger*) Estrutura do logger a destruir.
*/
void log_destroy(Logger* l);

#endif