#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "mem.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: main /path/to/input /path/to/output\n");
        exit(EXIT_FAILURE);
    }

    Cpu* cpu = cpu_create();

    // Alocando memória de 1kB com alinhamento de 1 byte
    Memory* mem = mem_create(1024);
    
    mem_load_program(mem, argv[1]);

    return 0;
}