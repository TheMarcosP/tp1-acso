#include <stdio.h>
#include <stdint.h>
#include "sim_utilities.h"


void print_binary(uint32_t number) {
  for (int i = 0; i < 32; i++) {
    printf("%d", (number >> (31 - i)) & 1);
  }
  printf("\n");

}

// hace el numero negativo dado la cantidad de bits del numero
int64_t sign_extend(uint32_t number, int bits) {
  //if number is negative extends with ones, else extends with zeros 
  if ((number >> bits - 1)) {
    number |= 0xFFFFFFFFFFFFFFFF << bits;
  }

  return number;
}


uint32_t get_bits(uint32_t number, int start, int end) {

  if (start < 0 || end < 0 || start > end) {
    return 0;
  }

  uint32_t mask = ((1 << (end - start + 1)) - 1) << start;
  uint32_t extracted_bits = number & mask;

  return extracted_bits >> start;
}

uint32_t negate_number(uint32_t number){
  uint32_t temp = number;
  int position = 0;
  while (temp) {
      temp >>= 1;
      position++;
  }
  
  number = ~number;
  
  number = number << 32 - position;
  number = number >> 32 - position;
  
  return number;
  
  
}
