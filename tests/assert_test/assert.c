#include "../../src/assert.h"

#define assert_test1() TRY(assert_test1())
static int (assert_test1)(void) {
  assert(1);
  return 0;
}

#define assert_test2() TRY(assert_test2())
static int (assert_test2)(void) {
  SAFER_BEGIN();
  ASSERT(1);
  cleanup:
  SAFER_END();
}

#define assert_test3() TRY(assert_test3())
static int (assert_test3)(void) {
  SAFER_BEGIN();
  ASSERT(0);
  cleanup:
  if (err == EINVAL) {
    // expected error
    err = 0;
  }
  SAFER_END();
}

int main(void) {
  SAFER_BEGIN();
  assert_test1();
  assert_test2();
  assert_test3();
  cleanup:
  SAFER_END();
}
