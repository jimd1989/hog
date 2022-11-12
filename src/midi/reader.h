#pragma once

#include <stdint.h>

#include "../utils/buffer.h"
#include "event.h"

typedef struct MidiReader {
  uint8_t       popped[3];
  Buffer        buffer;
} MidiReader;

MidiReader midiReader(void);
MidiEvent *popEvent(MidiReader *, MidiEvent *);
