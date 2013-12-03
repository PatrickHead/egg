#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "input.h"

int main(int argc, char **argv)
{
  FILE *f;
  struct stat st;
  byte *b;

  stat("/etc/passwd", &st);
  f = fopen("/etc/passwd", "r");

  b = (byte *)malloc(st.st_size + 1);
  memset(b, 0, st.st_size + 1);

  fread(b, sizeof(byte), st.st_size, f);

  fclose(f);

  if (!input_initialize((char *)b))
    return -1;

  while (!input_eof())
    fputc((int)input_byte(), stdout);

  input_cleanup();

  free(b);

  return 0;
}

