#include <err.h>
#include <stdint.h>
#include <stdlib.h>

#include "../utils/bit_array.h"
#include "../utils/fifo.h"
#include "../utils/ring.h"
#include "voice.h"

Voices voices(size_t size) {
  Fifo f = fifo(size);
  Fifo r = fifo(size);
  Ring q = ring(size);
  Voices vs = {0};
  size_t i = 0;
  if (size > VOICES_SIZE) {
    errx(-1, "%zu is greater than max voice count %zu", size, VOICES_SIZE);
  }
  vs.size = size;
  vs.free = f;
  vs.released = r;
  vs.playing = q;
  for (; i < size ; i++) {
    vs.data[i].n = i;
    pushFifo(&vs.free, (void *)&vs.data[i]);
  }
  return vs;
}

void freeVoices(Voices *vs) {
  size_t n = vs->released.population;
  Voice *v = NULL;
  while (n) {
    n--;
    v = (Voice *)popFifo(&vs->released);
    if (v->status == VOICE_OFF) {
      /* kill assignment here */
      pushFifo(&vs->free, (void *)v);
    } else {
      pushFifo(&vs->released, (void *)v);
    }
  }
}

void releaseVoice(Voices *vs, uint8_t note) { 
  uint8_t n = get4Bits(&vs->assignments, note);
  Voice *v = &vs->data[n];
  deleteFromRing(&vs->playing, (void *)v);
  v->status = VOICE_RELEASE;
  pushFifo(&vs->released, (void *)v);
}

void pushVoice(Voices *vs, Voice nv) {
  Ring *q = &vs->playing;
  Fifo *f = &vs->free;
  Fifo *r = &vs->released;
  void *p = f->population > 0 ? popFifo(f) :
            r->population > 0 ? popFifo(r) : popOldest(q);
  Voice *v = (Voice *)p;
  nv.n = v->n;
  nv.status = VOICE_ATTACK;
  *v = nv;
  pushRing(q, (void *)v);
  push4Bits(&vs->assignments, nv.note, nv.n);
}
