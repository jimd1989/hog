#include <stdint.h>
#include <stdio.h>

#include "cell.h"
#include "stack.h"

Stack stack(void) {
  Stack s = {-1, {{0}}};
  return s;
}

Cell *pop(Stack *s) {
  return s->n >= 0 ? &(s->cells[s->n--]) : NULL;
}

void pushP(Stack *s, void *p) {
  s->cells[++s->n].p = p;
}

void pushI(Stack *s, int64_t n) {
  s->cells[++s->n].i = n; 
}

void pushF(Stack *s, double f) {
  s->cells[++s->n].f = f;
}
