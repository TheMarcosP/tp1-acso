#ifndef SIM_UTILITIES_H
#define SIM_UTILITIES_H

void print_binary(uint32_t number);
int32_t sign_extend(uint32_t number, int bits);
uint32_t get_bits(uint32_t number, int start, int end);
uint32_t negate_number(uint32_t number);

#endif // SIM_UTILITIES_H