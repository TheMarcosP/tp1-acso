
#include <inttypes.h>
#include <stdio.h>


#ifndef _SIM_H_
#define _SIM_H_


typedef struct {
    void (*instruction)(uint32_t);
    uint32_t opcode;
    int start_bit; // no hace falta el end_bit porque todos terminan en 32
} InstructionInfo;

void process_instruction();

const InstructionInfo instruction_set[];
const int N;


#endif
