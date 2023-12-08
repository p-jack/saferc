#include "../../src/wctype.h"
#include "../../src/assert.h"

#define wctype_test() TRY(wctype_test())
static int (wctype_test)(void) {
  SAFER_BEGIN();
  ASSERT(iswalnum(L'a'));
  ASSERT(iswalpha(L'a'));
  ASSERT(iswblank(L' '));
  ASSERT(iswcntrl((wchar_t)0x7F));
  ASSERT(iswdigit(L'0'));
  ASSERT(iswgraph(L'a'));
  ASSERT(iswlower(L'a'));
  ASSERT(iswprint(L'a'));
  ASSERT(iswpunct(L'.'));
  ASSERT(iswupper(L'A'));
  ASSERT(iswxdigit(L'a'));
  ASSERT(towlower(L'A') == L'a');
  ASSERT(towupper(L'a') == L'A');
  wctype_t type = wctype("alpha");
  ASSERT(iswctype(L'a', type));
  wctrans_t trans = wctrans("toupper");
  ASSERT(towctrans(L'a', trans) == L'A');
  cleanup:
  SAFER_END();
}

int main(void) {
  SAFER_BEGIN();
  wctype_test();
  cleanup:
  SAFER_END();
}
