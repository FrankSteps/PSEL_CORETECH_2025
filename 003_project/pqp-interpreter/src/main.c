/*
    Desenvolvedores:
    Data de criação:
    Data de modificação:

    Observações adicionais:
*/

#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "mem.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: main /path/to/input /path/to/output\n");
        exit(EXIT_FAILURE);
    }

    // Declarações iniciais: Alocando memória de 1kB e criando o processador
    Cpu* cpu = cpu_create();
    Memory* mem = mem_create(1024);

    //carregar a entrada do programa
    mem_load_program(mem, argv[1]);
    cpu_cycle(cpu, mem);

    return 0;
}
