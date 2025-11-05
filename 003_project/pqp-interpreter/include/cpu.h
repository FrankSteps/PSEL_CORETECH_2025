/*
Definindo a estrutura básica da CPU
*/

#ifndef CPU_HEADER
#define CPU_HEADER

#include <stdint.h>
#include "mem.h"

// constantes úteis
#define NUM_REGISTERS 16   // Número total de registradores totais
#define NUM_OPCODES 16     // quantidade de instruções possíveis
#define MEMORY_SIZE 256    // tamanho da memória do pqp-interpreter
#define EXIT_PC 0xF0F0     // endereço de término da simulação

// declarando a estrutura da cpu -> declaração opaca
typedef struct Cpu Cpu;

// configuração base da CPU (criação, inicialização e execução)
Cpu* cpu_create();
void cpu_destroy(Cpu* cpu);
void cpu_cycle(Cpu* cpu, Memory* mem);

#endif
