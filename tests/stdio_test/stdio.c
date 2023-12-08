#include "../../src/stdlib.h"
#include "../../src/stdio.h"
#include <string.h> // TODO

#define macro_empty_test() TRY(macro_empty_test())
static int (macro_empty_test)(void) {
  SAFER_BEGIN();
//body:
  if (!SAFER_EMPTY_VA_ARGS()) THROW(666);
  if (SAFER_EMPTY_VA_ARGS(a)) THROW(666);
  if (SAFER_EMPTY_VA_ARGS(a, b)) THROW(666);
  if (SAFER_EMPTY_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)) THROW(666);
  if (SAFER_EMPTY_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q)) THROW(666);
cleanup:
  SAFER_END();
}

#define macro_too_many_test() TRY(macro_too_many_test())
static int (macro_too_many_test)(void) {
  SAFER_BEGIN();
//body:
  if (SAFER_TOO_MANY_VA_ARGS()) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, b)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, b, c)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, b, c, d)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, c, c, d, e)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, c, c, d, e, f)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, c, c, d, e, f, g)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, c, c, d, e, f, g, h)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, c, c, d, e, f, g, h, i)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, c, c, d, e, f, g, h, i, j)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l, m)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l, m, n)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o)) THROW(666);
  if (SAFER_TOO_MANY_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)) THROW(666);
  if (!SAFER_TOO_MANY_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, "q")) THROW(666);
  if (!SAFER_TOO_MANY_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, "q", "r")) THROW(666);
  if (!SAFER_TOO_MANY_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, "q", "r", "s", "t", "u")) THROW(666);
cleanup:
  SAFER_END();
}

#define macro_count_test() TRY(macro_count_test())
static int (macro_count_test)(void) {
  SAFER_BEGIN();
//body:
  if (SAFER_COUNT_VA_ARGS() != 1) THROW(666); // known issue
  if (SAFER_COUNT_VA_ARGS(a) != 1) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, b) != 2) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, b, c) != 3) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, b, c, d) != 4) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, c, c, d, e) != 5) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, c, c, d, e, f) != 6) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, c, c, d, e, f, g) != 7) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, c, c, d, e, f, g, h) != 8) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, c, c, d, e, f, g, h, i) != 9) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, c, c, d, e, f, g, h, i, j) != 10) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k) != 11) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l) != 12) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l, m) != 13) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l, m, n) != 14) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o) != 15) THROW(666);
  if (SAFER_COUNT_VA_ARGS(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) != 16) THROW(666);
cleanup:
  SAFER_END();
}

#define file_test() TRY(file_test())
static int (file_test)(void) {
  SAFER_BEGIN();
  FILE* f = NULL;
  char* buf = NULL;
// body:
  f = fopen("/tmp/foo", "w");
  fputc('h', f);
  fputs("el", f);
  fwrite("lo", 1, 2, f);
  fclose(f);
  f = fopen("/tmp/foo", "r");
  fpos_t pos = fgetpos(f);
  fseek(f, 0, SEEK_END);
  size_t len = ftell(f);
  if (len != 5) THROW(666);
  buf = calloc(1, len + 1);
  fsetpos(f, &pos);
  fread(buf, 1, len, f);
  if (strcmp(buf, "hello") != 0) THROW(666);
  fsetpos(f, &pos);
  fgets(buf, 6, f);
  if (strcmp(buf, "hello") != 0) THROW(666);
  fsetpos(f, &pos);
  int ch = fgetc(f);
  if (ch != 'h') THROW(666);
  remove("/tmp/foo");
cleanup:
  FREE(buf);
  FCLOSE(f);
  SAFER_END();
}

#define fmt_test() TRY(fmt_test())
static int (fmt_test)(void) {
  SAFER_BEGIN();
  FILE* f = NULL;
//body:
  f = fopen("/tmp/foo", "w");
  fprintf(f, "%s %d\n", "hello", 123);
  fclose(f);
  f = fopen("/tmp/foo", "r");
  int i = 0;
  char buf[64] = {};
  fscanf(f, "%s %d\n", buf, &i);
  if (strcmp("hello", buf) != 0) THROW(666);
  if (i != 123) THROW(666);
cleanup:
  FCLOSE(f);
  SAFER_END();
}

#define fmt_test2() TRY(fmt_test2())
static int (fmt_test2)(void) {
  SAFER_BEGIN();
  FILE* f = NULL;
//body:
  f = fopen("/tmp/foo", "w");
  fprintf(f, "%s,%d\n", "hello", 123);
  fclose(f);
  f = fopen("/tmp/foo", "r");
  int i = 0;
  char buf[64] = {};
  fscanf(f, "%s,%d\n", buf, &i);
  THROW(666);
cleanup:
  if (err == EPROTO) {
    // expected error due to incorrect fscanf usage
    err = 0;
  }
  FCLOSE(f);
  SAFER_END();
}

#define fileno_test() TRY(fileno_test())
static int (fileno_test)(void) {
  SAFER_BEGIN();
  if (fileno(stdout) != 1) THROW(666);
  cleanup:
  SAFER_END();
}

#define sscanf_test() TRY(sscanf_test())
static int (sscanf_test)(void) {
  SAFER_BEGIN();
  //body:
  char* input = "hello 123";
  char s[32];
  int i;
  sscanf(input, "%s %d", s, &i);
  if (strcmp(s, "hello") != 0) THROW(666);
  if (i != 123) THROW(666);
cleanup:
  SAFER_END();
}

#define snprintf_test1() TRY(snprintf_test1())
static int (snprintf_test1)(void) {
  SAFER_BEGIN();
  char buf[13];
  snprintf(buf, sizeof(buf), "Hello, %s", "world!");
cleanup:
  if (err != ENOMEM) {
    printf("got %d", err);
    // Expected failure, the buffer wasn't big enough for the nul.
    err = 66;
  } else {
    err = 0;
  }
  SAFER_END();
}

#define snprintf_test2() TRY(snprintf_test2())
static int (snprintf_test2)(void) {
  SAFER_BEGIN();
  char buf[10];
  snprintf(buf, sizeof(buf), "Hello, %s", "world!");
cleanup:
  if (err != ENOMEM) {
    printf("got %d", err);
    // Expected failure, the buffer wasn't big enough
    err = 66;
  } else {
    err = 0;
  }
  SAFER_END();
}

#define snprintf_test3() TRY(snprintf_test3())
static int (snprintf_test3)(void) {
  SAFER_BEGIN();
  char buf[14];
  snprintf(buf, sizeof(buf), "Hello, %s", "world!");
cleanup:
  SAFER_END();
}

/////
///// These ones are too complicated to test, just making sure the
///// macros expand to something that compiles. (This expand() function
///// is never actually called.)
/////

int expand(void) {
  SAFER_BEGIN();
//body:
  char ch = 0; (void)ch;
  char s[64] = {}; (void)s;
  int i = 0; (void)i;
  ch = getc(stdin);
  ch = getchar();
  i = getw(stdin);
  fpurge(stdout);
  putc('A', stdout);
  putw(12, stdout);
  scanf("%s%d", s, &i);
  FILE* file = tmpfile();
  setvbuf(file, s, _IOFBF, 64);
  setbuf(file, s);
  setbuffer(file, s, 64);
  setlinebuf(file);
  goto cleanup;
cleanup:
  SAFER_END();
}

int main(void) {
  SAFER_BEGIN();
//body:
  macro_empty_test();
  macro_too_many_test();
  macro_count_test();
  file_test();
  fmt_test();
  fmt_test2();
  fileno_test();
  sscanf_test();
  snprintf_test1();
  snprintf_test2();
  snprintf_test3();
cleanup:
  SAFER_END();
}
