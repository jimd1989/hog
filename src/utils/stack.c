#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "stack.h"

Stack stack(size_t size) {
  Stack s = {0};
  s.size = size;
  if (size > STACK_SIZE) {
    errx(-1, "%zu is greater than max stack size %zu", size, STACK_SIZE);
  }
  return s;
}

Cell *popStack(Stack *s) {
  if (s->head > 0) {
    return &(s->data[--s->head]);
  } else {
    return NULL;
  }
}

void pushStack(Stack *s, Cell c) {
  if (s->head >= s->size) {
    errx(-1, "stack overflow: %zu", s->size);
  } else {
    s->data[s->head++] = c;
  }
}
