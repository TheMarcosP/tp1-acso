#include <stdint.h>

#ifndef SIM_INSTRUCTIONS_H
#define SIM_INSTRUCTIONS_H

void adds_imm(uint32_t instruction);
void adds_reg(uint32_t instruction);
void subs_imm(uint32_t instruction);
void subs_reg(uint32_t instruction);
void hlt(uint32_t instruction);
void cmp_imm(uint32_t instruction);
void cmp_reg(uint32_t instruction);
void ands(uint32_t instruction);
void eor(uint32_t instruction);
void orr(uint32_t instruction);
void b(uint32_t instruction);
void br(uint32_t instruction);
void b_cond(uint32_t instruction);
void Shifts(uint32_t instruction);
void MOVZ(uint32_t instruction);
void STUR(uint32_t instruction);
void STURB(uint32_t instruction);
void STURH(uint32_t instruction);
void LDUR(uint32_t instruction);
void LDURB(uint32_t instruction);
void LDURH(uint32_t instruction);

//extras
void add_imm(uint32_t instruction);
void add_reg(uint32_t instruction); 
void mul(uint32_t instruction); 
void cbz(uint32_t instruction); 
void cbnz(uint32_t instruction);

extern int branch_jump;

#endif // SIM_UTILITIES_H