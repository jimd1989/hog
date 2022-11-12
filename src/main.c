#include <stdio.h>

#include "midi/event.h"
#include "midi/reader.h"
#include "utils/stack.h"

int main() {
  Cell *c = NULL;
  Stack s = stack();
  MidiEvent e = {0};
  MidiReader r = midiReader();
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
  c = pop(&s);
  printf("%p\n", (void *)c);
  printf("%p\n", (void *)popEvent(&r, &e));
  r.buffer.data[0] = 1;
  r.buffer.data[1] = 2;
  r.buffer.data[2] = 3;
  r.buffer.len = 3;
  printf("%p\n", (void *)popEvent(&r, &e));
  return 0;
}
