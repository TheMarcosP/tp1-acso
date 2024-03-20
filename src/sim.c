#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "sim.h"
#include "sim_utilities.h"
#include "sim_instructions.h"



const InstructionInfo instruction_set[] = {
    {subs_imm, 0xf1, 24},
    {subs_reg, 0x758, 21},
    {adds_imm, 0xb1, 24},
    {adds_reg, 0x558, 21},
    {hlt, 0x6a2, 21},
    {cmp_imm, 0x7d2, 24},
    {cmp_reg, 0x758, 21},
    {b, 0x5, 26},
    {br, 0x3587C0, 10},
    {b_cond, 0x54, 24},
    {MOVZ, 0x1A5, 23},
    {STUR, 0x7C0, 21},
    {STURB, 0x1C0, 21},
    {STURH, 0x3C0, 21},
    {LDUR, 0x7C2, 21},
    {ands, 0xEA, 24},
    {eor, 0xCA, 24},
    {orr, 0xAA, 24},
    {Shifts, 0x34D, 22},
    {add_imm, 0x91, 24},
    {add_reg, 0x458, 21},
    {mul, 0x4D8, 21},
    {cbz, 0xB4, 24},
    {cbnz, 0xB5, 24},
    {LDURB, 0x1C2, 21},
    {LDURH, 0x3C2, 21}
};

const int N = sizeof(instruction_set) / sizeof(instruction_set[0]);

void process_instruction()
{
  uint32_t instruction = mem_read_32(CURRENT_STATE.PC);
  printf("Instruction: %x\n", instruction);
  int flag = 1;

  // Identifica el opcode y llama a la función correspondiente
  for (int i = 0; i < N; i++) {
      uint32_t instruction_opcode = get_bits(instruction, instruction_set[i].start_bit, 32);
      if (instruction_opcode == instruction_set[i].opcode) {
          printf("match found, opcode: %x\n", instruction_set[i].opcode);
          instruction_set[i].instruction(instruction);
          flag = 0;
          break;
      }
  }

  if (flag) {
    printf("no match \n");
    exit(1);
  }

  // las instrucciones de salto (b, br, b.cond, cbz, cbnz) ya modifican el PC en la función, por lo que no hay que actualizarlo acá 
  if(!branch_jump){  
    NEXT_STATE.PC += 4;
  }

  branch_jump = 0;

}

