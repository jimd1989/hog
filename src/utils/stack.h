#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "cell.h"

#define STACK_SIZE (size_t)32

typedef struct Stack {
  size_t          size;
  size_t          head;
  Cell            data[STACK_SIZE];
} Stack;

Stack stack(size_t);
Cell *popStack(Stack *);
void pushStack(Stack *, Cell);
