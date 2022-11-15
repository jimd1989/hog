#pragma once

#include <stdint.h>
#include <stdlib.h>

#define BIT_ARRAY_SIZE (size_t)64

struct BitArray {
  uint8_t       data[BIT_ARRAY_SIZE];
};

typedef struct BitArray BitArray;


BitArray bitArray(void);
uint8_t get4Bits(BitArray *, size_t);
void push4Bits(BitArray *, size_t, uint8_t);
