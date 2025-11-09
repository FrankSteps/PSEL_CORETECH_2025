/*
    Desenvolvedores:        Francisco Passos & João Vinícius & Guilherme Ferreira
    Data de criação:        05/11/2025     
    Data de modificação:    05/11/2025

    Observações adicionais: 
        Este é o arquivo principal. O mesmo se encontra encarregado por carregar o programa na memória e iniciar a simulação do processador.

    Execução:
    ./main input.txt output.txt
*/

// incluindo as bibliotecas base
#include <stdio.h>
#include <stdlib.h>

// chamando os headers do processador, memória e logger
#include "cpu.h"
#include "mem.h"
#include "logger.h"

int main(int argc, char* argv[]) {
    // confirmando se o usuário passou o caminho para os arquivos da forma devida. 
    // (caminho para o input e para o output)
    if (argc < 2) {
        printf("Usage: main /path/to/input\n");
        exit(EXIT_FAILURE);
    }

    // Declarações iniciais: Alocando memória de 256 bytes, 
    // criando o processador e logger
    Cpu* cpu = cpu_create();
    Memory* mem = mem_create(256);
    Logger* l = log_create(200);

    //carregar a entrada do programa
    mem_load_program(mem, argv[1]);

    // Lógica de execução do programa
    bool run = true;

    // Impedir estouro do logger (temporario)
    int i = 0;
    while (run) {
        i++;
        cpu_cycle(cpu, mem, l);
        run = !cpu_simulation_finished(cpu);
        if (i > 190) break;
    }

    log_print_all(l);

    cpu_destroy(cpu);
    mem_destroy(mem);
    log_destroy(l);

    // encerrando o programa
    return 0;
}
