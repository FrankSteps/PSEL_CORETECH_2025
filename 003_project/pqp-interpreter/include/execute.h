/*
  header responsável por receber a CPU e os campos decodificados e realizar a operação
*/

#ifndef EXECUTE_HEADER
#define EXECUTE_HEADER

#include "cpu_internals.h" 

void execute_instruction(Cpu* cpu, const Instruction* instruction);

#endif
