#include <err.h>

#include "../utils/fifo.h"
#include "fifo.h"

void testFifo(void) {
  Fifo f = fifo(3);
  void *x = NULL;
  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  warnx("fifo");
  warnx("  population is 3 after adding 1,2,3");
  pushFifo(&f, &a);
  pushFifo(&f, &b);
  pushFifo(&f, &c);
  if (f.population != 3) {
    errx(-1, "expected 3; got %zu", f.population);
  }
  warnx("  1 is first element popped");
  x = popFifo(&f);
  if (*(int *)x != 1) {
    errx(-1, "expected 1; got %zu", f.population);
  }
  warnx("  population is 2 after popping");
  if (f.population != 2) {
    errx(-1, "expected 2; got %zu", f.population);
  }
  warnx("  underlying data is 4,2,3 after pushing 4");
  pushFifo(&f, &d);
  if (*(int *)f.data[0] != 4) {
    errx(-1, "expected 4; got %d", *(int *)f.data[0]);
  }
  if (*(int *)f.data[1] != 2) {
    errx(-1, "expected 2; got %d", *(int *)f.data[0]);
  }
  if (*(int *)f.data[2] != 3) {
    errx(-1, "expected 3; got %d", *(int *)f.data[0]);
  }
  warnx("  2 is second element popped");
  x = popFifo(&f);
  if (*(int *)x != 2) {
    errx(-1, "expected 2; got %zu", f.population);
  }
  warnx("  3 is third element popped");
  x = popFifo(&f);
  if (*(int *)x != 3) {
    errx(-1, "expected 3; got %zu", f.population);
  }
  warnx("  4 is last element popped");
  x = popFifo(&f);
  if (*(int *)x != 4) {
    errx(-1, "expected 4; got %zu", f.population);
  }
  warnx("  population is 0 after popping all");
  if (f.population != 0) {
    errx(-1, "expected 0; got %zu", f.population);
  }
}

