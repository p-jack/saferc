#pragma once
#include "saferc.h"
#include <locale.h>

#define setlocale(category, locale) ({ \
  char* $r = setlocale(category, locale); \
  if ($r == NULL) THROW(EINVAL); \
  $r; \
})

// localeconv
