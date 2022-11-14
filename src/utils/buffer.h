#pragma once

#include <stdlib.h>
#include <stdint.h>

#define BUFFER_SIZE 4096

typedef struct Buffer {
  size_t        size;
  size_t        head;
  size_t        blockSize;
  uint8_t       data[BUFFER_SIZE];
} Buffer;

Buffer buffer(size_t);
void testBuffer(void);
