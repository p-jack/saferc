#include "../../src/stdlib.h"

static int a64l_test1(void) {
  SAFER_BEGIN();
  char* ch = NULL;
  ch = l64a(1000);
  if (a64l(ch) != 1000) THROW(666);
  cleanup:
  SAFER_END();
}

static int a64l_test2(void) {
  SAFER_BEGIN();
  a64l(NULL);
  THROW(666);
  cleanup:
  if (err == EFAULT) {
    // expected error
    err = 0;
  }
  SAFER_END();
}

static int ato_tests(void) {
  SAFER_BEGIN();
  if (atof("0.0") != 0.0) THROW(666);
  if (atoi("1000") != 1000) THROW(666);
  if (atol("1000") != 1000l) THROW(666);
  if (atoll("1000") != 1000ll) THROW(666);
  cleanup:
  SAFER_END();
}

static int calloc_test(void) {
  SAFER_BEGIN();
  uint8_t* bytes = NULL;
  bytes = calloc(128, sizeof(uint8_t));
  for (int i = 0; i < 128; i++) {
    bytes[i] = 0xEE;
  }
  cleanup:
  FREE(bytes);
  SAFER_END();
}

static int div_test1(void) {
  SAFER_BEGIN();
  div_t r = div(100, 9);
  if (r.quot != 11) THROW(666);
  if (r.rem != 1) THROW(666);
  cleanup:
  SAFER_END();
}

static int div_test2(void) {
  SAFER_BEGIN();
  div(100, 0);
  THROW(666);
  cleanup:
  if (err == EINVAL) {
    err = 0;
  }
  SAFER_END();
}

static int ldiv_test1(void) {
  SAFER_BEGIN();
  ldiv_t r = ldiv(100l, 9l);
  if (r.quot != 11) THROW(666);
  if (r.rem != 1) THROW(666);
  cleanup:
  SAFER_END();
}

static int ldiv_test2(void) {
  SAFER_BEGIN();
  ldiv(100, 0);
  THROW(666);
  cleanup:
  if (err == EINVAL) {
    err = 0;
  }
  SAFER_END();
}

static int lldiv_test1(void) {
  SAFER_BEGIN();
  lldiv_t r = lldiv(100ll, 9ll);
  if (r.quot != 11) THROW(666);
  if (r.rem != 1) THROW(666);
  cleanup:
  SAFER_END();
}

static int lldiv_test2(void) {
  SAFER_BEGIN();
  ldiv(100ll, 0ll);
  THROW(666);
  cleanup:
  if (err == EINVAL) {
    err = 0;
  }
  SAFER_END();
}

static int malloc_test(void) {
  SAFER_BEGIN();
  uint8_t* bytes = NULL;
  bytes = malloc(128);
  for (int i = 0; i < 128; i++) {
    bytes[i] = 0xEE;
  }
  cleanup:
  FREE(bytes);
  SAFER_END();
}

static int mblen_test(void) {
  SAFER_BEGIN();
  int len = mblen("hello", 5);
  if (len != 1) THROW(666);
  cleanup:
  SAFER_END();
}

static int mbstowcs_test(void) {
  SAFER_BEGIN();
  wchar_t* ws = NULL;
  size_t len = mbstowcs(NULL, "hello", 5);
  ws = malloc(len);
  mbstowcs(ws, "hello", 5);
  if (ws[0] != L'h') THROW(666);
  char mb[5];
  wcstombs(mb, ws, 5);
  if (mb[0] != 'h') THROW(666);
  cleanup:
  SAFER_END();
}

static int mbtowc_test(void) {
  SAFER_BEGIN();
  wchar_t wc = 0;
  size_t len = mbtowc(&wc, "hello", 5);
  if (len != 1) THROW(666);
  if (wc != L'h') THROW(666);
  cleanup:
  SAFER_END();
}

static int putenv_test(void) {
  SAFER_BEGIN();
  putenv("K=V");
  char* v = getenv("K");
  if (v[0] != 'V') THROW(666);
  if (v[1] != 0) THROW(666);
  cleanup:
  SAFER_END();
}

static int realloc_test(void) {
  SAFER_BEGIN();
  uint8_t* bytes = NULL;
  bytes = realloc(NULL, 128);
  for (int i = 0; i < 128; i++) {
    bytes[i] = 0xEE;
  }
  bytes = realloc(bytes, 512);
  for (int i = 128; i < 512; i++) {
    bytes[i] = 0xEE;
  }
  cleanup:
  FREE(bytes);
  SAFER_END();
}

static int setenv_test(void) {
  SAFER_BEGIN();
  setenv("K", "V", 1);
  char* v = getenv("K");
  if (v[0] != 'V') THROW(666);
  if (v[1] != 0) THROW(666);
  cleanup:
  SAFER_END();
}

static int strto_tests(void) {
  SAFER_BEGIN();
  char* s = "1.0 2.0 -3 4.0 -5 6 7";
  double v1 = strtod(s, &s);
  float v2 = strtof(s, &s);
  long v3 = strtol(s, &s, 10);
  long double v4 = strtold(s, &s);
  long long v5 = strtoll(s, &s, 10);
  unsigned long v6 = strtoul(s, &s, 10);
  unsigned long long v7 = strtoull(s, &s, 10);
  if (v1 != 1.0) THROW(666);
  if (v2 != 2.0f) THROW(666);
  if (v3 != -3l) THROW(666);
  if (v4 != 4.0) THROW(666);
  if (v5 != -5ll) THROW(666);
  if (v6 != 6ul) THROW(666);
  if (v7 != 7ull) THROW(666);
  cleanup:
  SAFER_END();
}

/////
///// These ones are too complicated to test, just making sure the
///// macros expand to something that compiles.
/////

static void nop(void) {}

int expand(void) {
  SAFER_BEGIN();
  char* path = NULL; (void)path;
  char buf[64] = {}; (void)buf;
  int i; (void)i;
  atexit(nop);
  grantpt(1);
  initstate(0, buf, 64);
  // path = mkdtemp("fooXXXXXX");
  i = mkstemp("fooXXXXXX");
  path = posix_memalign(sizeof(void*), 256);
  i = posix_openpt(0);
  path = ptsname(i);
  path = realpath(path, NULL);
  setstate(buf);
  unlockpt(i);
  unsetenv("K");
  cleanup:
  SAFER_END();
}


int main(void) {
  SAFER_BEGIN();
  TRY(a64l_test1());
  TRY(a64l_test2());
  TRY(ato_tests());
  TRY(calloc_test());
  TRY(div_test1());
  TRY(div_test2());
  TRY(ldiv_test1());
  TRY(ldiv_test2());
  TRY(lldiv_test1());
  TRY(lldiv_test2());
  TRY(malloc_test());
  TRY(mblen_test());
  TRY(mbstowcs_test());
  TRY(mbtowc_test());
  TRY(putenv_test());
  TRY(realloc_test());
  TRY(setenv_test());
  TRY(strto_tests());
  cleanup:
  SAFER_END();
}
