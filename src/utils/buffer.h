#pragma once

#include <stdint.h>

#define BUFFER_SIZE 4096

typedef struct Buffer {
  uint16_t      head;
  uint16_t      len;
  uint16_t      blockSize;
  uint8_t       data[BUFFER_SIZE];
} Buffer;

Buffer buffer(uint16_t);
uint8_t *popBlock(Buffer *, uint8_t *);
