#include "../../src/locale.h"

#define setlocale_test() TRY(setlocale_test1())
static int (setlocale_test1)(void) {
  SAFER_BEGIN();
  setlocale(LC_ALL, "en_US.UTF-8");
  cleanup:
  SAFER_END();
}

#define setlocale_test2() TRY(setlocale_test2())
static int (setlocale_test2)(void) {
  SAFER_BEGIN();
  setlocale(LC_ALL, "???");
  cleanup:
  if (err == EINVAL) {
    // expected error
    err = 0;
  }
  SAFER_END();
}

int main(void) {
  SAFER_BEGIN();
  setlocale_test1();
  setlocale_test2();
  cleanup:
  SAFER_END();
}
