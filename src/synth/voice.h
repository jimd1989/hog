#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "../utils/bit_array.h"
#include "../utils/fifo.h"
#include "../utils/ring.h"

typedef enum VoiceStatus {
  VOICE_OFF = 0,
  VOICE_STEAL,
  VOICE_RELEASE,
  VOICE_RETRIGGER,
  VOICE_ATTACK,
  VOICE_DECAY,
  VOICE_SUSTAIN
} VoiceStatus;

typedef struct Voice {
  uint8_t       n;
  uint8_t       note;
  uint8_t       status;
  uint8_t       velocity;
  double        frequency;
  double        increment;
} Voice;

/* Due to 4 bit BitArray used for voice tracking, this can't exceed 16 without
 * writing new push/get functions for other sizes. */
#define VOICES_SIZE (size_t)16

typedef struct Voices {
  size_t        size;
  BitArray      assignments;
  Voice         data[VOICES_SIZE];
  Fifo          free;
  Fifo          released;
  Ring          playing;
} Voices;

Voices voices(size_t);
void freeVoices(Voices *);
void releaseVoice(Voices *, uint8_t);
void pushVoice(Voices *, Voice);
