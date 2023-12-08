#pragma once
#include "saferc.h"
#include <signal.h>

#define SAFER_SIG_ERR 66

#define signal(sig, handler) ({ void(*$r)(int) = signal(sig, handler); if ($r == SIG_ERR) THROW(SAFER_SIG_ERR); $r; })
#define raise(sig) TRY(raise(sig))
