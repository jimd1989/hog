#pragma once

#include <stdint.h>

#define VM_STACK_SIZE 32

typedef union Cell {
  void          * p;
  int32_t         i;
  float           f;
  uint8_t         b[4];
} Cell;

typedef struct Stack {
  int8_t        n;
  Cell          cells[VM_STACK_SIZE];
} Stack;

Stack stack(void);
Cell *pop(Stack *);
void pushP(Stack *, void *);
void pushI(Stack *, int32_t i);
void pushF(Stack *, float f);
