#pragma once

#include <stdint.h>

#include "../utils/buffer.h"
#include "event.h"

typedef struct MidiReader {
  Buffer        buffer;
} MidiReader;

MidiReader midiReader(void);
MidiEvent *popEvent(MidiReader *, MidiEvent *);
void testMidiReader(void);
