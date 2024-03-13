#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "shell.h"

uint32_t get_bits(uint32_t number, int start, int end) {

  if (start < 0 || end < 0 || start > end) {
    return 0;
  }

  uint32_t mask = ((1 << (end - start + 1)) - 1) << start;
  uint32_t extracted_bits = number & mask;
  return extracted_bits >> start;
}

void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. 
     * 
     * Sugerencia: hagan una funcion para decode()
     *             y otra para execute()
     * 
     * */

    uint32_t instruction = mem_read_32(CURRENT_STATE.PC);
    printf("Instruction: %x\n", instruction);

    // decode the instruction using masks 
    // rd is tfrom 0 to 4 bit
    // rn is from 5 to 9
    // rm is from 16 to 20
    // opcode is from 21 to 31
    uint32_t opcode = get_bits(instruction, 24, 31);
    uint32_t rn = get_bits(instruction, 5, 9);
    uint32_t rd = get_bits(instruction, 0, 4);
    uint32_t imm12 = get_bits(instruction, 10, 21);
    // uint32_t rm = get_bits(instruction, 16, 20);

    printf("opcode: %x\n", opcode);
    printf("rn: %x\n", rn);
    printf("rd: %x\n", rd);
    // printf("rm: %x\n", rm);

    // execute the instruction
    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rn] + imm12;




    NEXT_STATE.PC += 4;

    // NEXT_STATE.REGS[0] = 10;
    // printf("flag n:%d\n\n",NEXT_STATE.FLAG_N);

    // /* save to memory */
    // mem_write_32(0x10000000, 10);

}


void adds_imm(uint32_t instruction) {

  uint32_t rn = get_bits(instruction, 5, 9);
  uint32_t rd = get_bits(instruction, 0, 4);
  uint32_t imm12 = get_bits(instruction, 10, 21);

  NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rn] + imm12;
}