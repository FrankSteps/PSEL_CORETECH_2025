/*
Definindo a estrutura básica da CPU
*/

#ifndef CPU
#define CPU

#include <stdint.h>
#include "mem.h"
#include "logger.h"

// declarando a estrutura da cpu -> declaração opaca
typedef struct Cpu Cpu;

// configuração base da CPU (criação, inicialização e execução)
Cpu* cpu_create();
void cpu_destroy(Cpu* cpu);
void cpu_cycle(Cpu* cpu, Memory* mem, Logger* l);
bool cpu_simulation_finished(Cpu* cpu);

#endif
