#include <err.h>
#include <stdint.h>
#include <stdlib.h>

#include "../utils/bit_array.h"
#include "../synth/voice.h"
#include "voice.h"

void testVoices(void) {
  Voice v = {0};
  Voices vs = voices(4);
  void *x = NULL;
  uint8_t n = 0;
  size_t i = 0;
  v.note = 60;
  warnx("voices");
  warnx("  initializes with all voices on free stack");
  if (vs.free.population != vs.size) {
    errx(-1, "expected stack size 4; got %zu", vs.free.population);
  }
  warnx("  each voice is assigned its index number");
  for (i = 0 ; i < vs.size ; i++) {
    if (vs.data[i].n != (uint8_t)i) {
      errx(-1, "expected %u; got %zu", vs.data[i].n, i);
    }
  }
  warnx("  playing note 60 takes the last element in a fifo: voice 0");
  pushVoice(&vs, v);
  x = vs.playing.data[0];
  if (((Voice *)x)->n != 0) {
    errx(-1, "expected 0; got %u", ((Voice *)x)->n);
  }
  warnx("  playing note 61 is recorded in assignments array as voice 1"); 
  v.note = 61;
  pushVoice(&vs, v);
  n = get4Bits(&vs.assignments, 61);
  if (n != 1) {
    errx(-1, "expected 1; got %u", n);
  }
  warnx("  killing note 61 then playing note 62 uses voice 2, not 1");
  releaseVoice(&vs, 61);
  if (vs.data[1].status != VOICE_RELEASE) {
    errx(-1, "expected voice 1 to VOICE_RELEASE; got %d", vs.data[1].status);
  }
  v.note = 62;
  pushVoice(&vs, v);
  n = get4Bits(&vs.assignments, 62);
  if (n != 2) {
    errx(-1, "expected 2; got %u", n);
  }
  if (vs.data[1].status != VOICE_RELEASE) {
    errx(-1, "expected voice 1 to VOICE_RELEASE; got %d", vs.data[1].status);
  }
  warnx("  voice 1 should still be in release mode after playing note 63");
  v.note = 63;
  pushVoice(&vs, v);
  if (vs.data[1].status != VOICE_RELEASE) {
    errx(-1, "expected voice 1 to VOICE_RELEASE; got %d", vs.data[1].status);
  }
  warnx("  voice 1 is finally recycled after playing note 64");
  v.note = 64;
  pushVoice(&vs, v);
  if (vs.data[1].status != VOICE_ATTACK) {
    errx(-1, "expected voice 1 to VOICE_ATTACK; got %d", vs.data[1].status);
  }
  warnx("  active voices order is voices 0,2,3,1");
  x = vs.playing.data[0];
  if (((Voice *)x)->n != 0) {
    errx(-1, "expected 0; got %u", ((Voice *)x)->n);
  }
  x = vs.playing.data[1];
  if (((Voice *)x)->n != 2) {
    errx(-1, "expected 2; got %u", ((Voice *)x)->n);
  }
  x = vs.playing.data[2];
  if (((Voice *)x)->n != 3) {
    errx(-1, "expected 3; got %u", ((Voice *)x)->n);
  }
  x = vs.playing.data[3];
  if (((Voice *)x)->n != 1) {
    errx(-1, "expected 1; got %u", ((Voice *)x)->n);
  }
  warnx("  playing note 65 steals oldest voice");
  v.note = 65;
  pushVoice(&vs, v);
  x = vs.playing.data[0];
  if (((Voice *)x)->note != 65) {
    errx(-1, "expected 65; got %u", ((Voice *)x)->note);
  }
  warnx("  active notes order is voices 65,62,63,64");
  x = vs.playing.data[0];
  if (((Voice *)x)->note != 65) {
    errx(-1, "expected 0; got %u", ((Voice *)x)->note);
  }
  x = vs.playing.data[1];
  if (((Voice *)x)->note != 62) {
    errx(-1, "expected 2; got %u", ((Voice *)x)->note);
  }
  x = vs.playing.data[2];
  if (((Voice *)x)->note != 63) {
    errx(-1, "expected 3; got %u", ((Voice *)x)->note);
  }
  x = vs.playing.data[3];
  if (((Voice *)x)->note != 64) {
    errx(-1, "expected 1; got %u", ((Voice *)x)->note);
  }
  warnx("  65,62,63,64 is assigned to voices 0,2,3,1");
  if (get4Bits(&vs.assignments, 65) != 0) {
    errx(-1, "expected 0; got %u", get4Bits(&vs.assignments, 65));
  }
  if (get4Bits(&vs.assignments, 62) != 2) {
    errx(-1, "expected 2; got %u", get4Bits(&vs.assignments, 62));
  }
  if (get4Bits(&vs.assignments, 63) != 3) {
    errx(-1, "expected 3; got %u", get4Bits(&vs.assignments, 63));
  }
  if (get4Bits(&vs.assignments, 64) != 1) {
    errx(-1, "expected 1; got %u", get4Bits(&vs.assignments, 64));
  }
  warnx("  released voices aren't moved to free fifo");
  releaseVoice(&vs, 63);
  releaseVoice(&vs, 64);
  freeVoices(&vs);
  if (vs.released.population != 2 || vs.free.population != 0) {
    errx(-1, "expected 2; got %zu", vs.released.population);
  }
  warnx("  fully expired voices are sent to free fifo");
  vs.data[get4Bits(&vs.assignments, 63)].status = VOICE_OFF;
  freeVoices(&vs);
  if (vs.released.population != 1 || vs.free.population != 1) {
    errx(-1, "expected 1; got %zu", vs.released.population);
  }
  warnx("  free voices are recycled before released ones");
  v.note = 66;
  pushVoice(&vs, v);
  if (vs.released.population != 1 || vs.free.population != 0) {
    errx(-1, "expected 1; got %zu", vs.released.population);
  }
  warnx("  released voices are recycled when there are no free ones");
  v.note = 67;
  pushVoice(&vs, v);
  if (vs.playing.population != 4 || vs.released.population != 0) {
    errx(-1, "expected 0; got %zu", vs.released.population);
  }
}
