#pragma once

#include <stdint.h>

#include "cell.h"

#define STACK_SIZE 32

typedef struct Stack {
  int8_t        n;
  Cell          cells[STACK_SIZE];
} Stack;

Stack stack(void);
Cell *pop(Stack *);
void pushP(Stack *, void *);
void pushI(Stack *, int64_t i);
void pushF(Stack *, double f);
