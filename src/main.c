#include <err.h>
#include <stdio.h>

#ifdef TEST
  #include "tests/test.h"
#endif

int main() {
  #ifdef TEST
    test();
  #else
    warnx("prod");
  #endif
  return 0;
}
