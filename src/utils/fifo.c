#include <err.h>
#include <stdlib.h>

#include "fifo.h"

Fifo fifo(size_t size) {
  Fifo f = {0};
  if (size > FIFO_SIZE) {
    errx(-1, "%zu is greater than max fifo size %zu", size, FIFO_SIZE);
  }
  f.size = size;
  return f;
}

void *popFifo(Fifo *f) {
  void *x = NULL;
  if (f->population > 0) {
    x = f->data[f->head];
    f->head = (f->head + 1) % f->size;
    f->population--;
    return x;
  } else {
    errx(-1, "attempted to pop empty fifo: %p", (void *)f);
    return x;
  }
}

void pushFifo(Fifo *f, void *x) {
  if (f->population < f->size) {
    f->data[(f->head + f->population) % f->size] = x;
    f->population++;
  } else {
    errx(-1, "attempted push to full fifo: %p", (void *)f);
  }
}
