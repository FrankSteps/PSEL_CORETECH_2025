/*
 headers responsável por conter os artifícios de manipulação da memória da CPU

 ele oferece as operações básicas para:
   - criar e alocar a memória
   - carregar o input na memória

 O mesmo oferece o suporte para o gabage colector (artifício responsável por liberar a memória quando a mesma não está mais em uso)
*/

#ifndef MEM
#define MEM

#include <stdint.h>
#include <stdbool.h>

typedef struct Memory Memory;

Memory* mem_create(uint32_t size);                       
void mem_destroy(Memory* mem);                           
void mem_load_program(Memory* mem, char* file_path);    
uint8_t mem_read8(Memory* mem, uint16_t address);        
uint32_t mem_read32(Memory* mem, uint16_t address, bool executing);
void mem_write8(Memory* mem, uint16_t address, uint8_t data);
void mem_write32(Memory* mem, uint16_t address, uint32_t data);

#endif
