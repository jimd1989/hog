#include "reader.h"

#include <stdio.h>

#include "../utils/buffer.h"
#include "event.h"

MidiReader midiReader(void) {
  Buffer b = buffer(3);
  MidiReader r = {0};
  r.buffer = b;
  return r;
}

MidiEvent *popEvent(MidiReader *r, MidiEvent *e) {
  Buffer *b = &r->buffer;
  if (b->head + b->blockSize <= b->size) {
    e->gen.status = b->data[0];
    e->gen.b2 = b->data[1];
    e->gen.b3 = b->data[2];
    b->head += b->blockSize;
    return e;
  } else {
    return NULL;
  }
}
