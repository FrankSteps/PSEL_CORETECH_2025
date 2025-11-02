#ifndef MEM_HEADER
#define MEM_HEADER

#include <stdint.h>

typedef struct Memory Memory;

Memory* mem_create(uint32_t size);
void mem_destroy(Memory* mem);
void mem_load_program(Memory* mem, char* file_path);
uint8_t mem_read8(Memory* mem, uint16_t address);
uint32_t mem_read32(Memory* mem, uint16_t address);

#endif