#pragma once
#include "saferc.h"
#include "alloca.h"
#include "stdlib.h"
#include <string.h>

// memchr
// memcmp
// memcpy
// memmove
// memset

#define strcat_h(s1,s2) ({ \
  const char* $s1 = s1; \
  const char* $s2 = s2; \
  size_t $len1 = strlen($s1); \
  size_t $len2 = strlen($s2); \
  char* $dst = malloc($len1 + $len2 + 1); \
  memcpy($dst, $s1, $len1); \
  memcpy(&$dst[$len1], $s2, $len2); \
  $dst[$len1 + $len2] = 0; \
  $dst; \
})

#define strcat_s(s1,s2) ({ \
  const char* $s1 = s1; \
  const char* $s2 = s2; \
  size_t $len1 = strlen($s1); \
  size_t $len2 = strlen($s2); \
  char* $dst = alloca($len1 + $len2 + 1); \
  memcpy($dst, $s1, $len1); \
  memcpy(&$dst[$len1], $s2, $len2); \
  $dst[$len1 + $len2] = 0; \
  $dst; \
})

#undef strcat
#define strcat(s1,s2) UNSUPPORTED use strlcat, strcat_h, or strcat_s instead

#undef strncat
#define strncat(s1,s2,n) UNSUPPORTED use strlcat, strcat_h, or strcat_s instead

#undef strlcat
#define strlcat(dest,src,len) ({ \
  size_t $len = len; \
  size_t $r = strlcat(dest,src,$len); \
  if ($r >= len) THROW(E2BIG); \
  $r; \
})

#define strcmp(s1,s2) UNSUPPORTED use strncmp instead
// strncmp
// strcoll

#undef strcpy
#define strcpy(s1,s2) UNSUPPORTED use strlcpy instead

#undef strncpy
#define strncpy(s1,s2,n) UNSUPPORTED use strlcpy instead

#undef strlcpy
#define strlcpy(dest,src,len) ({ \
  size_t $len = len; \
  size_t $r = strlcpy(dest,src,$len); \
  if ($r >= len) THROW(E2BIG); \
  $r; \
})

// strspn
// strcspn

// strerror
// strlen

// strpbrk
// strrchr
// strstr

// strtok

#define strxfrm(dest,src,n) ({ \
  char* $dest = dest; \
  const char* $src = src; \
  size_t $n = n; \
  size_t $r = strxfrm($dest,$src,$n); \
  $r; \
})
