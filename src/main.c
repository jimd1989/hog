#include <stdio.h>

#include "vm/stack.h"

int main() {
  Cell *c = NULL;
  Stack s = stack();
  pushI(&s, 128);
  pushF(&s, 128.0f);
  pushP(&s, (void *)&s);
  c = pop(&s);
  printf("%p\n", c->p);
  c = pop(&s);
  printf("%f\n", c->f);
  c = pop(&s);
  printf("%d\n", c->i);
  c = pop(&s);
  printf("%p\n", (void *)c);
  return 0;
}
