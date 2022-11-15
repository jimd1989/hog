#pragma once

#include <stdlib.h>

#define FIFO_SIZE (size_t)16

typedef struct Fifo {
  size_t          size;
  size_t          head;
  size_t          population;
  void          * data[FIFO_SIZE];
} Fifo;

Fifo fifo(size_t);
void *popFifo(Fifo *);
void pushFifo(Fifo *, void *);
