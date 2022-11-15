#include <err.h>
#include <stdlib.h>

#include "../utils/ring.h"
#include "test.h"

void testRing(void) {
  Ring q = ring(6);
  void *expected[6] = {0};
  size_t i = 0;
  int x = 100;
  int y = 200;
  warnx("ring");
  warnx("  delete Y from XYXX00 to make XXX000");
  pushRing(&q, (void *)&x);
  pushRing(&q, (void *)&y);
  pushRing(&q, (void *)&x);
  pushRing(&q, (void *)&x);
  deleteFromRing(&q, (void*)&y);
  for (i = 0; i < 3; i++) {
    expected[i] = (void *)&x;
  }
  for (i = 0; i < 6; i++) {
    if (expected[i] != q.data[i]) {
      errx(-1, "expected[%zu] ≠ result[%zu]", i, i);
    }
  }
  warnx("  population of XXX000 is 3");
  if (q.population != 3) {
    errx(-1, "expected 3; got %zu", q.population);
  }
  warnx("  head of XXX000 is fourth index");
  if (q.head != 3) {
    errx(-1, "expected 3; got %zu", q.head);
  }
  warnx("  XXX000 + XXXY = YXXXXX");
  pushRing(&q, (void *)&x);
  pushRing(&q, (void *)&x);
  pushRing(&q, (void *)&x);
  pushRing(&q, (void *)&y);
  if (q.data[0] != &y) {
    errx(-1, "expected Y; got %p", (void *)q.data[0]);
  }
  for (i = 1; i < 6; i++) {
    if (q.data[i] != &x) {
      errx(-1, "expected X; got %p", (void *)q.data[i]);
    }
  }
  warnx("  population of YXXXXX is 6");
  if (q.population != 6) {
    errx(-1, "expected 6; got %zu", q.population);
  }
  warnx("  head of YXXXXX is second index");
  if (q.head != 1) {
    errx(-1, "expected 1; got %zu", q.head);
  }
}
