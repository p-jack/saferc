#include <saferc/stdlib.h>
#include <saferc/stdio.h>
#include <saferc/string.h>

#define MAX_PATH 4096

int main(int argc, const char* argv[]) {
  SAFER_BEGIN();
  FILE *r = NULL;
  FILE *w = NULL;
  if (argc != 2) {
    fputs("Expected one file argument.\n", stderr);
    exit(1);
  }
  char bak[MAX_PATH];
  snprintf(bak, MAX_PATH, "%s.bak", argv[1]);
  r = fopen(argv[1], "r");
  w = fopen(bak, "w");
  for (int ch = fgetc(r); ch != EOF; ch = fgetc(r)) {
    fputc(ch, w);
  }
  cleanup:
  CATCH(fprintf(stderr, "error %d: %s\n", err, strerror(err)));
  FCLOSE(w);
  FCLOSE(r);
  SAFER_END();
}
