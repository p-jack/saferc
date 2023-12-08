#include "../../src/signal.h"
#include "../../src/assert.h"
#include <stddef.h>

_Thread_local int caught = -1;

typedef void(*handler_t)(int);

void handler(int signal) {
  caught = signal;
}

#define signal_test() TRY(signal_test())
int (signal_test)(void) {
  SAFER_BEGIN();
  handler_t old = NULL;
  old = signal(SIGINT, handler);
  raise(SIGINT);
  ASSERT(caught == SIGINT);
  cleanup:
  if (old != NULL) { (signal)(SIGINT, old); }
  SAFER_END();
}

int main(void) {
  SAFER_BEGIN();
  signal_test();
  cleanup:
  SAFER_END();
}
