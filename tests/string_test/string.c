#include "../../src/string.h"
#include "../../src/assert.h"

#define strcat_s_test() TRY(strcat_s_test())
static int (strcat_s_test)(void) {
  SAFER_BEGIN();
  char* s = strcat_s("Hello,", " world!");
  int r = strncmp(s, "Hello, world!", sizeof("Hello, world!"));
  ASSERT(r == 0);
  cleanup:
  SAFER_END();
}

#define strcat_h_test() TRY(strcat_h_test())
static int (strcat_h_test)(void) {
  SAFER_BEGIN();
  char* s = NULL;
  s = strcat_h("Hello,", " world!");
  ASSERT(strlen(s) == 13);
  int r = strncmp(s, "Hello, world!", sizeof("Hello, world!"));
  ASSERT(r == 0);
  cleanup:
  free(s);
  SAFER_END();
}

#define strlcat_test1() TRY(strlcat_test1())
static int (strlcat_test1)(void) {
  SAFER_BEGIN();
  char s[256] = "Hello, ";
  strlcat(s, "world!", sizeof(s));
  ASSERT(strlen(s) == 13);
  int r = strncmp(s, "Hello, world!", sizeof("Hello, world!"));
  ASSERT(r == 0);
  cleanup:
  SAFER_END();
}

#define strlcat_test2() TRY(strlcat_test2())
static int (strlcat_test2)(void) {
  SAFER_BEGIN();
  char s[10] = "Hello, ";
  strlcat(s, "world!", sizeof(s));
  THROW(-1);
  cleanup:
  if (err == E2BIG) {
    // expected error
    err = 0;
  }
  SAFER_END();
}

#define strlcpy_test1() TRY(strlcpy_test1())
static int (strlcpy_test1)(void) {
  SAFER_BEGIN();
  char s[256];
  strlcpy(s, "Hello, world!", sizeof(s));
  ASSERT(strlen(s) == 13);
  int r = strncmp(s, "Hello, world!", sizeof("Hello, world!"));
  ASSERT(r == 0);
  cleanup:
  SAFER_END();
}

#define strlcpy_test2() TRY(strlcpy_test2())
static int (strlcpy_test2)(void) {
  SAFER_BEGIN();
  char s[10];
  strlcpy(s, "Hello, world!", sizeof(s));
  THROW(-1);
  cleanup:
  if (err == E2BIG) {
    // expected error
    err = 0;
  }
  SAFER_END();
}


int main(void) {
  SAFER_BEGIN();
  strcat_s_test();
  strcat_h_test();
  strlcat_test1();
  strlcat_test2();
  strlcpy_test1();
  strlcpy_test2();
  cleanup:
  SAFER_END();
}
