#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <inttypes.h>



uint32_t get_bits(uint32_t number, int start, int end) {

  if (start < 0 || end < 0 || start > end) {
    return 0;
  }

  uint32_t mask = ((1 << (end - start + 1)) - 1) << start;
  uint32_t extracted_bits = number & mask;

  return extracted_bits >> start;
}


void print_binary(uint32_t number) {
  for (int i = 0; i < 32; i++) {
    printf("%d", (number >> (31 - i)) & 1);
  }

}

int main() {
  printf("Hello, World!\n");
  uint32_t a = get_bits( 0b11001100,  3,  6);
  print_binary(a);
  return 0;
}

