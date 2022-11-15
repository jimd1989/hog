#include <err.h>
#include <stdio.h>

#include "../utils/cell.h"
#include "../utils/stack.h"
#include "stack.h"

void testStack(void) {
  Stack s = stack(3);
  Cell c = {0};
  Cell *p = NULL;
  warnx("stack");
  warnx("  push pointer");
  c.p = &s;
  pushStack(&s, c);
  warnx("  push int");
  c.i = 123;
  pushStack(&s, c);
  warnx("  push float");
  c.f = 1917.1917f;
  pushStack(&s, c);
  warnx("  pop float");
  p = popStack(&s);
  if ((!p) || p->f != 1917.1917f) {
    errx(-1, "expected 1917.1917; got %f", p->f);
  }
  warnx("  pop int");
  p = popStack(&s);
  if ((!p) || p->i != 123) {
    errx(-1, "expected 123; got %d", (int)p->f);
  }
  warnx("  pop pointer");
  p = popStack(&s);
  if ((!p) || p->p != &s) {
    errx(-1, "expected pointer; got %p", (void *)p->p);
  }
  warnx("  don't pop empty stack");
  p = popStack(&s);
  if (p != NULL) {
    errx(-1, "expected NULL; got %p", (void *)p);
  }
}
