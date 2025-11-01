#ifndef CPU_HEADER
#define CPU_HEADER

typedef struct Cpu Cpu;

Cpu* cpu_create();
void cpu_destroy(Cpu* cpu);

#endif