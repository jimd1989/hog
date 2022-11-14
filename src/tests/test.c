#include "buffer.h"
#include "midi_reader.h"
#include "queue.h"
#include "stack.h"
#include "test.h"

void test(void) {
  testBuffer();
  testQueue();
  testStack();
  testMidiReader();
}
