#pragma once
#include "saferc.h"
#include <wctype.h>

#define wctype(str) ({ wctype_t $r = wctype(str); if ($r == 0) THROW(EINVAL); $r; })
#define wctrans(str) ({ wctrans_t $r = wctrans(str); if ($r == 0) THROW(EINVAL); $r; })
