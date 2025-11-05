#ifndef EXECUTE_HEADER
#define EXECUTE_HEADER

#include "cpu_internals.h" 

//Recebe a CPU e os campos decodificados e realiza a operação
void execute_instruction(Cpu* cpu, const Instruction* instruction);

#endif
