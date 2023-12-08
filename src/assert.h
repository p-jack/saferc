#pragma once
#include "saferc.h"
#include <assert.h>

#define ASSERT(x) if (!(x)) THROW(EINVAL);
