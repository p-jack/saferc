#pragma once
#include "saferc.h"
#include <stdlib.h>

// _Exit
#define a64l(s) ({ const char* $s = s; if ($s == NULL) THROW(EFAULT); long $l = a64l($s); $l; })
// abort
// abs
#define atexit(f) TRY(atexit(f))
#define atof(s) ({ char* end; double $rr = strtod(s, &end); if (*end != 0) THROW(EINVAL); $rr; })
#define atoi(s) ({ char* end; int $rr = (int)strtol(s, &end, 10); if (*end != 0) THROW(EINVAL); $rr; })
#define atol(s) ({ char* end; long $rr = strtol(s, &end, 10); if (*end != 0) THROW(EINVAL); $rr; })
#define atoll(s) ({ char* end; long long $rr = strtoll(s, &end, 10); if (*end != 0) THROW(EINVAL); $rr; })
// bsearch
#define calloc(n, e) ({ size_t $n = n; size_t $e = e; if ($n == 0) THROW(EINVAL); if (e == 0) THROW(EINVAL); errno = 0; void* $r = calloc($n, $e); if ($r == NULL) THROW(errno); $r; })
#define div(n, d) ({ int $n = n; int $d = d; if ($d == 0) THROW(EINVAL); div($n, $d); })
// drand48
// erand48
// exit
// free
// getenv
// getsubopt
#define grantpt(v) ({ int $r = grantpt(v); if ($r != 0) THROW(errno); $r; })
#define initstate(seed, state, n) MUST(initstate(seed, state, n))
// jrand48
// l64a
// labs
// lcong48
#define ldiv(n, d) ({ long $n = n; long $d = d; if ($d == 0) THROW(EINVAL); ldiv($n, $d); })
// llabs
#define lldiv(n, d) ({ long long $n = n; long long $d = d; if ($d == 0) THROW(EINVAL); lldiv($n, $d); })
// lrand48
#define malloc(n) ({ size_t $n = n; if ($n == 0) THROW(EINVAL); void* $r = malloc($n); if ($r == NULL) THROW(errno); $r; })
#define mblen(s, n) ({ const char* $s = s; size_t $n = n; if (($s == NULL) && ($n != 0)) THROW(EINVAL); int $r = mblen($s, $n); if (($s != NULL) && ($r < 0)) THROW(EILSEQ); $r; })
#define mbstowcs(dest, src, n) ERRNO(size_t $r = mbstowcs(dest, src, n));
#define mbtowc(dest, src, n) ({ const char* $src = src; size_t $n = n; if (($src == NULL) && ($n != 0)) THROW(EINVAL); int $r = mbtowc(dest, $src, $n); if (($src != NULL) && ($r < 0)) THROW(EILSEQ); $r; })
#define mkdtemp(s) ERRNO(char* $r = mkdtemp(s))
#define mkstemp(s) ERRNO(int $r = mkstemp(s))
// mrand48
// nrand48
#define posix_memalign(alignment, size) ({ size_t $a = alignment; size_t $n = size; if ($n == 0) THROW(EINVAL); void* $out = NULL; TRY(posix_memalign($out, $a, $n)); $out; })
#define posix_openpt(flag) ERRNO(int $r = posix_openpt(flag))
#define ptsname(fd) ERRNO(char* $r = ptsname(fd))
#define putenv(s) { errno = 0; putenv(s); if (errno != 0) THROW(errno); }
// qsort
// rand
// rand_r
// random
#define realloc(ptr, n) ({ size_t $n = n; void* $r; if ($n == 0) { FREE(ptr); $r = NULL; } else { errno = 0; $r = realloc(ptr, n); if (errno != 0) THROW(errno); } $r; })
#define realpath(fn, rn) ERRNO(char* $r = realpath(fn, rn));
// seed48
#define setenv(k,v,flag) { errno = 0; setenv(k,v,flag); if (errno != 0) THROW(errno); }
// setkey
#define setstate(s) MUST(setstate(s))
// srand
// srand48
// srandom
#define strtod(s, end) ERRNO(double $r = strtod(s, end))
#define strtof(s, end) ERRNO(float $r = strtof(s, end))
#define strtol(s, end, base) ERRNO(long $r = strtol(s, end, base))
#define strtold(s, end) ERRNO(long double $r = strtold(s, end))
#define strtoll(s, end, base) ERRNO(long long $r = strtoll(s, end, base))
#define strtoul(s, end, base) ERRNO(unsigned long $r = strtoul(s, end, base))
#define strtoull(s, end, base) ERRNO(unsigned long long $r = strtoull(s, end, base))
// system
#define unlockpt(fd) { errno = 0; unlockpt(fd); if (errno != 0) THROW(errno); }
#define unsetenv(k) { errno = 0; unsetenv(k); if (errno != 0) THROW(errno); }
#define wcstombs(s, wcs, n) ({ size_t $r = wcstombs(s, wcs, n); if ($r == (size_t)-1) THROW(EILSEQ); $r; })
#define wctomb(s, wch) ({ char* $s = s; wchar_t $wch = wch; if (($s == NULL) && ($wch != 0)) THROW(EINVAL); int $r = wctomb($s, $wch); if ($r < 0) THROW(EILSEQ); $r; })
