#ifndef CPU_HEADER
#define CPU_HEADER

#include <stdint.h>

#include "mem.h"

//constantes úteis
#define NUM_REGISTERS 16
#define NUM_OPCODES 16
#define MEMORY_SIZE 256
#define EXIT_PC 0xF0F0 //endereço de término da simulação

typedef struct Cpu Cpu;

Cpu* cpu_create();
void cpu_destroy(Cpu* cpu);
void cpu_cycle(Cpu* cpu, Memory* mem);

#endif