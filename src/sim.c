#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "shell.h"

// headers
void adds_imm(uint32_t instruction);
void adds_reg(uint32_t instruction);
void subs_imm(uint32_t instruction);
void subs_reg(uint32_t instruction);
void hlt(uint32_t instruction);
void cmp_imm(uint32_t instruction);
void b(uint32_t instruction);
void br(uint32_t instruction);

// make a global variable to keep track of the number of instructions
int COUNT = 0;

void process_instruction()
{

  uint32_t instruction = mem_read_32(CURRENT_STATE.PC);
  printf("Instruction: %x ", instruction);
  if (COUNT == 0 ){
    // call adds_imm
    printf("adds_imm\n");
    adds_imm(instruction);
  }
  else if (COUNT == 1){
    // call adds_reg
    printf("adds_reg\n");
    adds_reg(instruction);
  }
  else{
    // call hlt
    printf("hlt\n");
    hlt(instruction);
  }
  
  COUNT++;
  NEXT_STATE.PC += 4;



}

uint32_t get_bits(uint32_t number, int start, int end) {

  if (start < 0 || end < 0 || start > end) {
    return 0;
  }

  uint32_t mask = ((1 << (end - start + 1)) - 1) << start;
  uint32_t extracted_bits = number & mask;

  return extracted_bits >> start;
}


void adds_imm(uint32_t instruction) {


  uint32_t rn = get_bits(instruction, 5, 9);
  uint32_t rd = get_bits(instruction, 0, 4);
  int64_t imm12 = get_bits(instruction, 10, 21);
  uint32_t shift = get_bits(instruction, 22, 23);
  printf("rn: %x\n", rn);
  printf("rd: %x\n", rd);

  if (shift){
    printf("shifting imm12\n");
    imm12 = imm12 << 12;
  }

  NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rn] + imm12;
  NEXT_STATE.FLAG_N = (NEXT_STATE.REGS[rd] < 0) ? 1 : 0;
  NEXT_STATE.FLAG_Z = (NEXT_STATE.REGS[rd] == 0) ? 1 : 0;
}

void adds_reg(uint32_t instruction) {

  uint32_t rd = get_bits(instruction, 0, 4);
  uint32_t rn = get_bits(instruction, 5, 9);
  uint32_t rm = get_bits(instruction, 16, 20);
  

  NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rn] + CURRENT_STATE.REGS[rm];
  NEXT_STATE.FLAG_N = (NEXT_STATE.REGS[rd] < 0) ? 1 : 0;
  NEXT_STATE.FLAG_Z = (NEXT_STATE.REGS[rd] == 0) ? 1 : 0;
}



void subs_imm(uint32_t instruction) {

  uint32_t rd = get_bits(instruction, 0, 4);
  uint32_t rn = get_bits(instruction, 5, 9);
  int64_t imm12 = get_bits(instruction, 10, 21);
  uint32_t shift = get_bits(instruction, 22, 23);
  printf("rn: %x\n", rn);
  printf("rd: %x\n", rd);

  if (shift){
    printf("shifting imm12\n");
    imm12 = imm12 << 12;
  }

  NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rn] - imm12;
  NEXT_STATE.FLAG_N = (NEXT_STATE.REGS[rd] < 0) ? 1 : 0;
  NEXT_STATE.FLAG_Z = (NEXT_STATE.REGS[rd] == 0) ? 1 : 0;
}

void subs_reg(uint32_t instruction) {
  return;
}


void hlt(uint32_t instruction) {
  printf("hlt\n");
  RUN_BIT = 0;
}

void cmp_imm(uint32_t instruction) {
  uint32_t rn = get_bits(instruction, 5, 9);
  int64_t imm12 = get_bits(instruction, 10, 21);
  uint32_t shift = get_bits(instruction, 22, 23);
  printf("rn: %x\n", rn);

  if (shift){
    printf("shifting imm12\n");
    imm12 = imm12 << 12;
  }

  int64_t result = CURRENT_STATE.REGS[rn] - imm12;
  NEXT_STATE.FLAG_N = (result < 0) ? 1 : 0;
  NEXT_STATE.FLAG_Z = (result == 0) ? 1 : 0;
}


void b(uint32_t instruction) {
  int64_t imm26 = get_bits(instruction, 0, 25);
  imm26 = imm26 << 2;
  NEXT_STATE.PC = CURRENT_STATE.PC + imm26;

}

void br(uint32_t instruction) {

}
