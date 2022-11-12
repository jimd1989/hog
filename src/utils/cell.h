#pragma once

typedef union Cell {
  void          * p;
  int64_t         i;
  double          f;
  uint8_t         b[8];
} Cell;

