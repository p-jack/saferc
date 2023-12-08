#pragma once
#include "saferc.h"
#include <fenv.h>

#define feclearexcept(mask) TRY(feclearexcept(mask))
#define fegetenv(envp) TRY(fegetenv(envp));
#define fegetexceptflag(flagp, mask) TRY(fegetexceptflag(flagp, mask))
// fegetround
#define feholdexcept(envp) TRY(feholdexcept(envp))
#define feraiseexcept(mask) TRY(feraiseexcept(mask))
#define fesetenv(envp) TRY(fesetenv(envp))
#define fesetexceptflag(flagp, mask) TRY(fesetexceptflag(flagp, mask))
#define fesetround(round) TRY(fesetround(round))
// fetestexcept
#define feupdateenv(envp) TRY(feupdateenv(envp))

#define FESETENV(envp) (fesetenv)(envp);
#define FEUPDATEENV(envp) (feupdateenv)(envp);
