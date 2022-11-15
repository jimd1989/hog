#include "bit_array.h"
#include "buffer.h"
#include "fifo.h"
#include "midi_reader.h"
#include "ring.h"
#include "stack.h"
#include "test.h"
#include "voice.h"

void test(void) {
  testBitArray();
  testBuffer();
  testFifo();
  testMidiReader();
  testRing();
  testStack();
  testVoices();
}
