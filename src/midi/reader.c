#include "reader.h"

#include <stdint.h>
#include <stdio.h>

#include "../utils/buffer.h"
#include "event.h"

MidiReader midiReader(void) {
  Buffer b = buffer(3);
  MidiReader r = {{0, 0, 0}, b};
  return r;
}

MidiEvent *popEvent(MidiReader *r, MidiEvent *e) {
  if (popBlock(&r->buffer, r->popped)) {
    e->gen.status = r->popped[0];
    e->gen.b2 = r->popped[1];
    e->gen.b3 = r->popped[2];
    return e;
  } else {
    return NULL;
  }
}
