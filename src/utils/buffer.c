#include <stdint.h>
#include <stdio.h>

#include "buffer.h"

Buffer buffer(uint16_t blockSize) {
  Buffer b = {0, 0, blockSize, {0}};
  return b;
}

uint8_t *popBlock(Buffer *b, uint8_t *xs) {
  int i = 0;
  if(b->head + b->blockSize <= b->len) {
    for(; i < b->blockSize ; i++, b->head++) {
      xs[i] = b->data[b->head];
    }
    return xs;
  } else {
    return NULL;
  }
}
