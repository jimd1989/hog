#include <err.h>
#include <stdlib.h>

#include "cell.h"
#include "ring.h"

Ring ring(size_t size) {
  Ring q = {0};
  q.size = size;
  if (size > RING_SIZE) {
    errx(-1, "%zu is greater than max queue size %zu", size, RING_SIZE);
  }
  return q;
}

void deleteFromRing(Ring *q, void *x) {
  size_t i = 0;
  size_t prev = 0;
  void *val = q->data[q->head];
  void *tmp = NULL;
  for (; i < q->population ; i++) {
    prev = (q->head + ((q->size - 1) - i)) % q->size;
    if (q->data[prev] == x) {
      q->data[prev] = val;
      q->head = (q->head + (q->size - 1)) % q->size;
      q->population--;
      return;
    } else {
      tmp = q->data[prev];
      q->data[prev] = val;
      val = tmp;
    }
  }
}

void incrementRing(Ring *q) {
  q->head = (q->head + 1) % q->size;
}

void *popOldest(Ring *q) {
  return q->data[q->head];
}

void pushRing(Ring *q, void *x) {
  q->data[q->head] = x;
  q->population = q->population == q->size ? q->size : q->population + 1;
  incrementRing(q);
}

