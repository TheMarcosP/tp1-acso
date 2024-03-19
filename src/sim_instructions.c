#include <stdio.h>
#include <stdint.h>
#include "shell.h"
#include "sim_instructions.h"
#include "sim_utilities.h"

void adds_imm(uint32_t instruction) {
  printf("adds_imm function enter\n");


  uint32_t rn = get_bits(instruction, 5, 9);
  uint32_t rd = get_bits(instruction, 0, 4);
  uint32_t imm12 = get_bits(instruction, 10, 21); // no hace falta sign extend porque si es negativo se llama a subs
  uint32_t shift = get_bits(instruction, 22, 23);


  if (shift){
    printf("shifting imm12\n");
    imm12 = imm12 << 12;
  }

  NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rn] + imm12;
  NEXT_STATE.FLAG_N = (NEXT_STATE.REGS[rd] < 0) ? 1 : 0;
  NEXT_STATE.FLAG_Z = (NEXT_STATE.REGS[rd] == 0) ? 1 : 0;
}

void adds_reg(uint32_t instruction) {
  printf("adds_reg function enter\n");

  uint32_t rd = get_bits(instruction, 0, 4);
  uint32_t rn = get_bits(instruction, 5, 9);
  uint32_t rm = get_bits(instruction, 16, 20);
  

  NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rn] + CURRENT_STATE.REGS[rm];
  NEXT_STATE.FLAG_N = (NEXT_STATE.REGS[rd] < 0) ? 1 : 0;
  NEXT_STATE.FLAG_Z = (NEXT_STATE.REGS[rd] == 0) ? 1 : 0;
}



void subs_imm(uint32_t instruction) {
  printf("subs_imm function enter\n");

  uint32_t rd = get_bits(instruction, 0, 4);
  uint32_t rn = get_bits(instruction, 5, 9);
  int64_t imm12 = get_bits(instruction, 10, 21); // lo mismo que en adds_imm
  uint32_t shift = get_bits(instruction, 22, 23);

  if (shift){
    printf("shifting imm12\n");
    imm12 = imm12 << 12;
  }

  NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rn] - imm12;
  NEXT_STATE.FLAG_N = (NEXT_STATE.REGS[rd] < 0) ? 1 : 0;
  NEXT_STATE.FLAG_Z = (NEXT_STATE.REGS[rd] == 0) ? 1 : 0;
}

void subs_reg(uint32_t instruction) {
  printf("subs_reg function enter\n");

  uint32_t rd = get_bits(instruction, 0, 4);
  uint32_t rn = get_bits(instruction, 5, 9);
  uint32_t rm = get_bits(instruction, 16, 20);


  printf("rn: %x\n", rn);
  printf("rd: %x\n", rd);

  int64_t temp = CURRENT_STATE.REGS[rm] - CURRENT_STATE.REGS[rn];

  NEXT_STATE.FLAG_N = (temp < 0) ? 1 : 0;
  NEXT_STATE.FLAG_Z = (temp == 0) ? 1 : 0;

  if (rd == 31) {
    printf("rd is xzr\n");
    return;
  }

  NEXT_STATE.REGS[rd] = temp;

}


void hlt(uint32_t instruction) {
  printf("HLT function enter\n");
  RUN_BIT = 0;
}

void cmp_imm(uint32_t instruction) {
  printf("cmp_imm function enter\n");
  uint32_t rn = get_bits(instruction, 5, 9);
  int64_t imm12 = get_bits(instruction, 10, 21); // del manual: <Imm> Is an unsigned immediate, in the range 0 to 4095, encoded in the "imm12" field.
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

void cmp_reg(uint32_t instruction) {
  printf("cmp_reg function enter\n");
  uint32_t rn = get_bits(instruction, 5, 9);
  uint32_t rm = get_bits(instruction, 16, 20);
  printf("rn: %x\n", rn);

  int64_t result = CURRENT_STATE.REGS[rn] - CURRENT_STATE.REGS[rm];
  NEXT_STATE.FLAG_N = (result < 0) ? 1 : 0;
  NEXT_STATE.FLAG_Z = (result == 0) ? 1 : 0;
}


void ands(uint32_t instruction){
  uint32_t rd = get_bits(instruction, 0, 4); 
  uint32_t rn = get_bits(instruction, 5, 9); 
  uint32_t imm6 = get_bits(instruction, 10, 15); 
  uint32_t rm = get_bits(instruction, 16, 20); 
  uint32_t shift = get_bits(instruction, 22, 23);


  NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rm] & CURRENT_STATE.REGS[rn];
  NEXT_STATE.FLAG_Z = (CURRENT_STATE.REGS[rd] == 0) ? 1 : 0;
}




void eor(uint32_t instruction){
  uint32_t rd = get_bits(instruction, 0, 4); 
  uint32_t rn = get_bits(instruction, 5, 9); 
  uint32_t imm6 = get_bits(instruction, 10, 15); 
  uint32_t rm = get_bits(instruction, 16, 20); 
  uint32_t shift = get_bits(instruction, 22, 23);

  NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rm] ^ CURRENT_STATE.REGS[rn];

}



void orr(uint32_t instruction){
  uint32_t rd = get_bits(instruction, 0, 4); 
  uint32_t rn = get_bits(instruction, 5, 9); 
  uint32_t imm6 = get_bits(instruction, 10, 15); 
  uint32_t rm = get_bits(instruction, 16, 20); 
  uint32_t shift = get_bits(instruction, 22, 23);

  NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rm] | CURRENT_STATE.REGS[rn];
}

void b(uint32_t instruction) {
  printf("b function enter\n");
  uint32_t imm26 = get_bits(instruction, 0, 25); 
  int32_t offset = sign_extend(imm26, 26) << 2;
  
  NEXT_STATE.PC = CURRENT_STATE.PC + offset;
}


void br(uint32_t instruction) {
  printf("br function enter\n");
  uint32_t rn = get_bits(instruction, 5, 9); 
  uint64_t direction = CURRENT_STATE.REGS[rn];
  NEXT_STATE.PC = direction;
  // falta verificar que ande pero para eso hay que hacer load.
}

void b_cond(uint32_t instruction){
  printf("b_cond function enter\n");
  uint32_t cond = get_bits(instruction, 0, 3); 
  uint32_t imm19 = get_bits(instruction, 5, 23);
  int32_t offset = sign_extend(imm19, 19) << 2;


  if ((cond == 0 && CURRENT_STATE.FLAG_Z)  ||
     (cond == 1 && !CURRENT_STATE.FLAG_Z) ||
     (cond == 12 && (!CURRENT_STATE.FLAG_Z && !CURRENT_STATE.FLAG_N)) ||
     (cond == 11 && CURRENT_STATE.FLAG_N) || 
     (cond == 10 && !CURRENT_STATE.FLAG_N)||
     (cond == 13 && !(!CURRENT_STATE.FLAG_Z && !CURRENT_STATE.FLAG_N))){

    NEXT_STATE.PC = CURRENT_STATE.PC + offset;


//Falta testear
  } 
}


// esta funcion hace lsl y lsr
void Shifts(uint32_t instruction){
  printf("Shifts function enter\n");
  uint32_t rd = get_bits(instruction, 0, 4);
  uint32_t rn = get_bits(instruction, 5, 9);
  uint32_t imms = get_bits(instruction, 10, 15); 
  uint32_t immr = get_bits(instruction, 16, 21); 

  if(imms == 63){
    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rn] >> immr; 
  }
  else{
    uint32_t result = negate_number(imms);
    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rn] << result;
    printf("Valor de result: %d\n", result);
    printf("Valor de imms: %d\n", imms);
  }

}


// preguntar si hay que hacer lo de checkSPAlignment y adress = sp[]
void STUR(uint32_t instruction){
  printf("STUR function enter\n");
  uint32_t rt = get_bits(instruction, 0, 4);
  uint32_t rn = get_bits(instruction, 5, 9);
  int32_t offset = sign_extend(get_bits(instruction, 12, 20), 9);


  uint64_t address = CURRENT_STATE.REGS[rn] + offset;
  uint64_t data = CURRENT_STATE.REGS[rt];

  // data ocupa 64 bits y la memoria es de 32-bits word. hay que partir data en 2 y guardar las partes en la memoria
  uint32_t data1 = data & 0xFFFFFFFF; // primeros 4 bytes
  uint32_t data2 = (data >> 32) & 0xFFFFFFFF; // ultimos 4 bytes

  // printf("address: %lx\n", address);
  // printf("data: %lx\n", data);
  // printf("data1: %x\n", data1);
  // printf("data2: %x\n", data2);

  mem_write_32(address, data1);
  mem_write_32(address + 4, data2);

}

void STURB(uint32_t instruction){
  uint32_t rt = get_bits(instruction, 0, 4);
  uint32_t rn = get_bits(instruction, 5, 9);
  int32_t offset = sign_extend(get_bits(instruction, 12, 20), 9);

  uint64_t address = CURRENT_STATE.REGS[rn] + offset; 

  uint32_t data = CURRENT_STATE.REGS[rt] & 0xFF; // me quedo con el primer byte

  // como solo tenemos que modificar un byte, primero leo la palabra de 4 bytes, modifico el byte y la vuelvo a escribir

  uint32_t word = mem_read_32(address);

  // sobre escribo el primer byte de la palabra con data
  word = (word & 0xFFFFFF00) | data;

  mem_write_32(address, word); // escribo la palabra modificada
}

void STURH(uint32_t instruction){
  uint32_t rt = get_bits(instruction, 0, 4);
  uint32_t rn = get_bits(instruction, 5, 9);
  int32_t offset = sign_extend(get_bits(instruction, 12, 20), 9);

  uint64_t address = CURRENT_STATE.REGS[rn] + offset;

  uint32_t data = CURRENT_STATE.REGS[rt] & 0xFFFF;

  uint32_t word = mem_read_32(address);

  word = (word & 0xFFFF0000) | data;

  mem_write_32(address, word); 

}

void LDUR(uint32_t instruction){
  uint32_t rt = get_bits(instruction, 0, 4);
  uint32_t rn = get_bits(instruction, 5, 9);
  int32_t offset = sign_extend(get_bits(instruction, 12, 20), 9);

  uint64_t address = CURRENT_STATE.REGS[rn] + offset;


  uint64_t data = mem_read_32(address+4); 
  data = data << 32;
  data = data | mem_read_32(address);

  NEXT_STATE.REGS[rt] = data;
}

void LDURB(uint32_t instruction){
  uint32_t rt = get_bits(instruction, 0, 4);
  uint32_t rn = get_bits(instruction, 5, 9);
  int32_t offset = sign_extend(get_bits(instruction, 12, 20), 9);

  uint64_t address = CURRENT_STATE.REGS[rn] + offset;

  uint32_t word = mem_read_32(address);
  uint32_t data = word & 0xFF;

  NEXT_STATE.REGS[rt] = data;
}

void LDURH(uint32_t instruction){
  uint32_t rt = get_bits(instruction, 0, 4);
  uint32_t rn = get_bits(instruction, 5, 9);
  int32_t offset = sign_extend(get_bits(instruction, 12, 20), 9);

  uint64_t address = CURRENT_STATE.REGS[rn] + offset;

  uint32_t word = mem_read_32(address);
  uint32_t data = word & 0xFFFF;

  NEXT_STATE.REGS[rt] = data;
}

void MOVZ(uint32_t instruction){
  uint32_t rd = get_bits(instruction, 0, 4);
  uint32_t imm16 = get_bits(instruction, 5, 20);
  
  NEXT_STATE.REGS[rd] = imm16;
}

// EXTRAS

void add_imm(uint32_t instruction){
  uint32_t rn = get_bits(instruction, 5, 9);
  uint32_t rd = get_bits(instruction, 0, 4);
  int64_t imm12 = get_bits(instruction, 10, 21);
  uint32_t shift = get_bits(instruction, 22, 23);


  if (shift){
    printf("shifting imm12\n");
    imm12 = imm12 << 12;
  }

  NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rn] + imm12;

  // la unica diferencia con ADDS es que no actualiza las banderas?
}

void add_reg(uint32_t instruction){
  uint32_t rd = get_bits(instruction, 0, 4);
  uint32_t rn = get_bits(instruction, 5, 9);
  uint32_t rm = get_bits(instruction, 16, 20);
  

  NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rn] + CURRENT_STATE.REGS[rm];

}



void mul(uint32_t instruction){
  uint32_t rd = get_bits(instruction, 0, 4); 
  uint32_t rn = get_bits(instruction, 5, 9); 
  uint32_t rm = get_bits(instruction, 16, 20); 
  uint32_t ra = get_bits(instruction, 10, 14); 

  NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[ra] + (CURRENT_STATE.REGS[rn] * CURRENT_STATE.REGS[rm]); 

}


void cbz(uint32_t instruction){
  uint32_t rt = get_bits(instruction, 0, 4); 
  uint32_t imm19 = get_bits(instruction, 5, 23); 

  // necesita el sign extend
  // int64_t offset = sign_extend(imm19, 19);
  // if(NEXT_STATE.FLAG_Z[rt]){
  //   NEXT_STATE.PC = CURRENT_STATE.PC + offset; 
  // }

}


void cbnz(uint32_t instruction){
  uint32_t rt = get_bits(instruction, 0, 4); 
  uint32_t imm19 = get_bits(instruction, 5, 23); 

  // necesita el sign extend
  // int64_t offset = sign_extend(imm19, 19);
  // if(!NEXT_STATE.FLAG_Z[rt]){
  //   NEXT_STATE.PC = CURRENT_STATE.PC + offset;
  // }
}