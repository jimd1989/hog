#pragma once

#include <stdint.h>

typedef struct MidiGeneric {
  int8_t        status;
  int8_t        b2;
  int8_t        b3;
} MidiGeneric;

typedef struct MidiNote {
  int8_t        status;
  int8_t        pitch;
  int8_t        vel;
} MidiNote;

typedef struct MidiCc {
  int8_t        status;
  int8_t        n;
  int8_t        val;
} MidiCc;

typedef union MidiEvent {
  MidiCc        cc;
  MidiGeneric   gen;
  MidiNote      note;
} MidiEvent;
