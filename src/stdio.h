#pragma once
#include "saferc.h"
#include <stdio.h>

// Do not use.
// This is only used by the various *scanf macros, to determine whether
// scanf actually produced the expected number of elements in the output.
// Evaluates to the 16th element of the provided arguments.
#define SAFER_16TH(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,...) p16

// Do not use.
// This is only used by the various *scanf macros, to determine whether
// scanf actually produced the expected number of elements in the output.
// Evaluates to the count of the provided __VA_ARGS__.
// EXCEPT, an empty __VA_ARGS__ will evaluate to 1 instead of 0.
// Use SAFER_EMPTY_VA_ARGS to tell the difference.
#define SAFER_COUNT_VA_ARGS(...) SAFER_16TH(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

// Dummy struct. Only used by SAFER_TOO_MANY_VA_ARGS.
typedef struct { } safer_dummy_t;

// NULL cast to safer_dummy_t. Only used by SAFER_TOO_MANY_VA_ARGS.
#define SAFER_DUMMY_NULL ((safer_dummy_t*)0)

// Do not use.
// Evalutes to 0 if the argument is of type safer_dummy_t, or 1 otherwise.
// Only used by SAFER_TOO_MANY_VA_ARGS.
#define SAFER_NOT_DUMMY(x) _Generic((x), safer_dummy_t*: 0, default: 1)

// Evalutes to 1 if there are too many __VA_ARGS__, or 0 otherwise.
#define SAFER_TOO_MANY_VA_ARGS(...) \
  SAFER_NOT_DUMMY(SAFER_16TH(__VA_ARGS__, \
    SAFER_DUMMY_NULL, SAFER_DUMMY_NULL, SAFER_DUMMY_NULL, SAFER_DUMMY_NULL, \
    SAFER_DUMMY_NULL, SAFER_DUMMY_NULL, SAFER_DUMMY_NULL, SAFER_DUMMY_NULL, \
    SAFER_DUMMY_NULL, SAFER_DUMMY_NULL, SAFER_DUMMY_NULL, SAFER_DUMMY_NULL, \
    SAFER_DUMMY_NULL, SAFER_DUMMY_NULL, SAFER_DUMMY_NULL, SAFER_DUMMY_NULL))

// Do not use.
// Evalutes to 1 if the provided __VA_ARGS__ is empty, or 0 otherwise.
#define SAFER_EMPTY_VA_ARGS(...) ( sizeof( (char[]){#__VA_ARGS__} ) == 1 )

#define SAFER_REPORT_IO_ERROR(f) { \
  int $err = ferror(f); \
  clearerr(f); \
  if ($err != 0) THROW($err); \
}

// clearerr
#define FCLOSE(f) { if (f != NULL) fclose(f); }
// fclose
#define fdopen(fd, mode) ERRNO(int $r = fdopen(fd, mode))
// feof
// ferror
#define fflush(file) { int $r = fflush(file); if ($r != 0) THROW(errno); }
#define fgetc(file) ({ \
  FILE* $file = file; \
  int $r = fgetc($file); \
  SAFER_REPORT_IO_ERROR($file); \
  $r; \
})
#define fgets(buf, size, file) ({ \
  char* $buf = buf; \
  int $size = size; \
  FILE* $file = file; \
  char* $r = fgets($buf, $size, $file); \
  SAFER_REPORT_IO_ERROR($file); \
  $r; \
})
#define fgetpos(stream) ({ errno = 0; fpos_t $pos; int $r = fgetpos(stream, &$pos); if ($r < 0) THROW(errno); $pos; })
#define fileno(stream) ({ int $r = fileno(stream); if ($r < 0) THROW(errno); $r; })
#define fopen(path, mode) ERRNO(FILE* $r = fopen(path, mode))
#define fprintf(file, fmt, ...) { \
  FILE* $file = file; \
  int $r = fprintf($file, fmt, __VA_ARGS__); \
  if ($r < 0) SAFER_REPORT_IO_ERROR($file); \
}
#define fpurge(file) { int $r = fpurge(file); if ($r < 0) THROW(errno); }
#define fputc(ch, file) { \
  FILE* $file = file; \
  int $r = fputc(ch, $file); \
  if ($r == EOF) SAFER_REPORT_IO_ERROR($file); \
}
#define fputs(s, file) { \
  FILE* $file = file; \
  int $r = fputs(s, $file); \
  if ($r == EOF) SAFER_REPORT_IO_ERROR($file); \
}
#define freopen(path, mode, stream) ERRNO(FILE $r = freopen(path, mode, stream))
#define fseek(file, ofs, whence) ({ errno = 0; int $r = fseek(file, ofs, whence); if ($r < 0) THROW(errno); $r; })
#define fsetpos(stream, pos) { errno = 0; int $r = fsetpos(stream, pos); if ($r < 0) THROW(errno); }
#define ftell(file) ({ errno = 0; long $r = ftell(file); if ($r < 0) THROW(errno); $r; })

#define fread(buf, size, n, file) ({ \
  void* $buf = buf; \
  size_t $size = size; \
  size_t $n = n; \
  FILE* $file = file; \
  size_t $r = fread($buf, $size, $n, $file); \
  int $err = ferror($file); \
  clearerr($file); \
  if ($err != 0) THROW($err); \
  $r; \
})

#define fscanf(file, fmt, ...) { \
  if (SAFER_EMPTY_VA_ARGS(__VA_ARGS__)) THROW(EINVAL); \
  if (SAFER_TOO_MANY_VA_ARGS(__VA_ARGS__)) THROW(EINVAL); \
  FILE* $file = file; \
  int $r = fscanf($file, fmt, __VA_ARGS__); \
  if ($r == EOF) { \
    int $eof = feof($file); \
    int $err = ferror($file); \
    if ($eof) THROW(ENODATA); \
    if ($err) THROW($err); \
    THROW(EBADMSG); \
  } else if ($r != SAFER_COUNT_VA_ARGS(__VA_ARGS__)) THROW(EPROTO); \
}

#define fwrite(buf, size, n, file) ({ \
  void* $buf = buf; \
  size_t $size = size; \
  size_t $n = n; \
  FILE* $file = file; \
  size_t $r = fwrite($buf, $size, $n, $file); \
  if ($r != $n) { \
    int $err = ferror($file); \
    clearerr($file); \
    THROW($err); \
  } \
})

#define getc(file) fgetc(file)
#define getchar() getc(stdin)
#define gets(s) DEPRECATED use fread instead
#define getw(file) ({ \
  FILE* $file = file; \
  int $r = getw($file); \
  if ($r == EOF) SAFER_REPORT_IO_ERROR($file); \
  $r; \
})

#define mktemp(template) DEPRECATED use stdlib/mkstemp instead

// perror
// printf

#define putc(c, file) fputc(c, file)
// putchar
// puts
#define putw(w, file) { \
  FILE* $file = file; \
  int $r = putw(w, $file); \
  if ($r == EOF) SAFER_REPORT_IO_ERROR($file); \
}

#define remove(path) { int $r = remove(path); if ($r < 0) THROW(errno); }
// rewind

#define scanf(fmt, ...) ({ \
  if (SAFER_EMPTY_VA_ARGS(__VA_ARGS__)) THROW(EINVAL); \
  if (SAFER_TOO_MANY_VA_ARGS(__VA_ARGS__)) THROW(EINVAL); \
  int $r = scanf(fmt, __VA_ARGS__); \
  if ($r == EOF) { \
    int $eof = feof(stdin); \
    int $err = ferror(stdin); \
    if ($eof) THROW(ENODATA); \
    if ($err) THROW($err); \
    THROW(EBADMSG); \
  } else if ($r != SAFER_COUNT_VA_ARGS(__VA_ARGS__)) THROW(EPROTO); \
})

#define setvbuf(file, buf, mode, size) { \
  errno = 0; \
  FILE* $file = file; \
  int $r = setvbuf($file, buf, mode, size); \
  if ($r < 0) { \
    if (errno != 0) THROW(errno); \
    int $err = ferror($file); \
    if ($err != 0) { \
      clearerr($file); \
      THROW($err); \
    } \
    THROW($r); \
  } \
}

#define setbuf(file, buf) setvbuf(file, buf, buf ? _IOFBF : _IONBF, BUFSIZ)
#define setbuffer(file, buf, size) setvbuf(file, buf, buf ? _IOFBF : _IONBF, size)
#define setlinebuf(file) setvbuf(file, NULL, _IOLBF, 0)

#undef sprintf
#define sprintf(str, fmt, ...) UNSAFE use snprintf instead

#undef snprintf
#define snprintf(str, size, fmt, ...) { \
  size_t $size = size; \
  size_t $r = snprintf(str, $size, fmt, __VA_ARGS__); \
  if ($r < 0) THROW($r); \
  if ($r >= $size) THROW(ENOMEM); \
  $r; \
}

#define sscanf(str, fmt, ...) { \
  if (SAFER_EMPTY_VA_ARGS(__VA_ARGS__)) THROW(EINVAL); \
  if (SAFER_TOO_MANY_VA_ARGS(__VA_ARGS__)) THROW(EINVAL); \
  int $r = sscanf(str, fmt, __VA_ARGS__); \
  if ($r == EOF) { THROW(EOF); } \
  else if ($r != SAFER_COUNT_VA_ARGS(__VA_ARGS__)) { THROW(EPROTO); } \
}

// strerror

#define tempnam DEPRECATED use mkstemp or tmpfile instead
#define tmpnam DEPRECATED use mkstemp or tmpfile instead

#define tmpfile() ({ \
  FILE* $r = tmpfile(); \
  if ($r == NULL) THROW(errno); \
  $r; \
})

#define ungetc(ch, file) { \
  int $r = ungetc(ch, file); \
  if ($r == EOF) THROW(ENODATA); \
}

#define vfprintf(file, fmt, va) ({ \
  FILE* $file = file; \
  int $r = fprintf($file, fmt, va); \
  if ($r < 0) SAFER_REPORT_IO_ERROR($file); \
  $r; \
})

// vfscanf
// vprintf
// vscanf
// vsprintf
// vsscanf
