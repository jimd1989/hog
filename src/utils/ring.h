#pragma once

#include <stdlib.h>

#define RING_SIZE (size_t)16

typedef struct Ring {
  size_t          size;
  size_t          head;
  size_t          population;
  void          * data[RING_SIZE];
} Ring;

Ring ring(size_t);
void deleteFromRing(Ring *, void *);
void incrementRing(Ring *);
void *popOldest(Ring *);
void pushRing(Ring *, void *);
