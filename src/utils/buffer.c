#include <stdlib.h>

#include "buffer.h"

Buffer buffer(size_t blockSize) {
  Buffer b = {0};
  b.blockSize = blockSize;
  return b;
}
