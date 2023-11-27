#include "../../src/stdlib.h"
#include "../../src/stdio.h"

#define MAX_PATH 4096
#define BUF_SIZE 4096

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
  CATCH(fprintf(stderr, "error %x", err));
  FCLOSE(r);
  FCLOSE(w);
  SAFER_END();
}
