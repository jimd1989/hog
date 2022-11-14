#pragma once

#include <stdlib.h>

#define QUEUE_SIZE (size_t)8

typedef struct Queue {
  size_t          size;
  size_t          head;
  size_t          population;
  void          * data[QUEUE_SIZE];
} Queue;

Queue queue(size_t);
void deleteFromQueue(Queue *, void *);
void incrementQueue(Queue *);
void pushQueue(Queue *, void *);
