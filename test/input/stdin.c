#include <stdio.h>

#include "input.h"

int main(int argc, char **argv)
{
  if (!input_initialize(NULL))
    return -1;

  while (!input_eof())
    fputc((int)input_byte(), stdout);

  input_cleanup();

  return 0;
}

