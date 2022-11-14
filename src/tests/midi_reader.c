#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "../midi/event.h"
#include "../midi/reader.h"
#include "midi_reader.h"

void testMidiReader(void) {
  MidiReader r = midiReader();
  MidiEvent e = {{1, 2, 3}};
  MidiEvent *p = NULL;
  size_t i = 0;
  warnx("midi reader");
  for (; i < r.buffer.blockSize ; i++, r.buffer.size++) {
    r.buffer.data[i] = i + 1;
  }
  warnx("  pop one event from queue");
  p = popEvent(&r, &e);
  if ((!p) || p->gen.status != e.gen.status) {
    errx(-1, "midi buffer pop failure: expected 1; got %u", p->gen.status);
  }
  warnx("  don't pop from empty queue");
  p = popEvent(&r, &e);
  if (p != NULL) {
    errx(-1, "midi buffer pop failure: expected NULL; got %p", (void *)p);
  }
  warnx("  ok");
}
