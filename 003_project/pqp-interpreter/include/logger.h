#ifndef LOGGER
#define LOGGER

#include "cpu_internals.h"

#define LINE_MAX_SIZE 100

/*
    Define buffer e variáveis auxiliares para armazenamento de strings.
*/ 
typedef struct Logger Logger;

/*
    Desc.: Lida com alocações e atribuições iniciais do logger.
    
    Parâmetros:
        (int) size: Tamanho/Quantidade de linhas salvas no buffer.
        (char*) output_path: Caminho do arquivo de output.
    
    Return: Logger inicializado.
*/
Logger* log_create(int size, char* output_path);

/*
    Desc.: Adiciona string no buffer do logger.

    Parâmetros:
        (Logger*) l: Estrutura do logger.
        (char*) content: String a ser adicionada.
*/
void log_add(Logger* l, char* content);


/*
    Desc.: Imprime string do buffer.

    Parâmetros:
        (Logger*) l: Estrutura do logger.
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
    Desc.: Libera memória do logger.
    
    Parâmetros:
        (Logger*) Estrutura do logger a destruir.
*/
void log_destroy(Logger* l);

#endif