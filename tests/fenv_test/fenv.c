#include "../../src/fenv.h"
#include "../../src/assert.h"
#include <float.h>
#include <math.h>

static double twice(double x) {
  return x * 2;
}

#define fenv_test1() TRY(fenv_test1())
static int (fenv_test1)(void) {
  SAFER_BEGIN();
  fenv_t env;
  feholdexcept(&env);
  double x = twice(DBL_MAX);
  ASSERT(fetestexcept(FE_INEXACT | FE_OVERFLOW));
  (void)x;
  feupdateenv(&env);
  cleanup:
  SAFER_END();
}

#define fenv_test2() TRY(fenv_test2())
static int (fenv_test2)(void) {
  SAFER_BEGIN();
  feclearexcept(FE_ALL_EXCEPT);
  fexcept_t ex;
  fegetexceptflag(&ex, FE_ALL_EXCEPT);
  feraiseexcept(FE_INVALID);
  ASSERT(fetestexcept(FE_INVALID));
  fesetexceptflag(&ex, FE_ALL_EXCEPT);
  ASSERT(!fetestexcept(FE_INVALID));
  cleanup:
  SAFER_END();
}

#define fenv_test3() TRY(fenv_test3())
static int (fenv_test3)(void) {
  SAFER_BEGIN();
  fenv_t fenv;
  fegetenv(&fenv);
  int round = fegetround();
  fesetround(FE_DOWNWARD);
  ASSERT(rint(+12.7) == 12);
  fesetenv(&fenv);
  ASSERT(fegetround() == round);
  cleanup:
  FESETENV(&fenv);
  SAFER_END();
}

int main(void) {
  SAFER_BEGIN();
  fenv_t fenv;
  fegetenv(&fenv);
  fenv_test1();
  fenv_test2();
  fenv_test3();
  cleanup:
  FESETENV(&fenv);
  SAFER_END();
}
