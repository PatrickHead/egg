/*!

  \file egg-walker.c

  \brief Source code for egg-walker.c

  \version 20131210022217

  \author Patrick Head mailto:patrickhead@gmail.com

  \copyright Copyright (C) 2013 Patrick Head

  \license
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.\n
  \n
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.\n
  \n
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see   \<http://www.gnu.org/licenses/\>.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "common.h"
#include "input.h"
#include "egg-token.h"
#include "egg-token-util.h"
#include "egg-parser.h"

void usage(char *program_name);
void walk(egg_token *t, int level);

int main(int argc, char **argv)
{
  int c;
  extern char *optarg;
  extern int optind;
  int long_index;
  struct option long_opts[] =
  {
    { "grammar", 0, 0, 0 }
  };
  boolean syntax_only = false;
  boolean walk_grammar;
  egg_token *t;
  char *input_file;

  while ((c = getopt_long(argc, argv, "sh", long_opts, &long_index)) != -1)
  {
    switch (c)
    {
      case 0:
        switch (long_index)
        {
          case 0:
            walk_grammar = true;
            break;
          default:
            break;
        }
        break;
      case 's':
        syntax_only = true;
        break;
      case 'h':
      default:
        usage(argv[0]);
        return 1;
    }
  }

  input_file = NULL;
  if (optind < argc)
    if (strcmp(argv[optind], "-"))
      input_file = strdup(argv[optind]);

  if (!input_initialize(input_file))
    return 1;

  if (walk_grammar)
  {
    t = grammar();
    if (t)
    {
      if (syntax_only)
        printf("Passed.\n");
      else
        walk(t, 0);
    }
    else
      printf("Failed.\n");
  }

  input_cleanup();

  if (!t)
    return 1;

  return 0;
}

void usage(char *program_name)
{
  if (!program_name)
    program_name = "egg-walker";

  fprintf(stderr, "\n");
  fprintf(stderr, "Usage:  %s\n", program_name);
  fprintf(stderr, "          [--grammar]\n");
  fprintf(stderr, "          [<file name>]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "  where:\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    <file name> = pathname to any file that uses a 'egg' "
                  "grammar.\n");
  fprintf(stderr, "                  NONE or '-' implies input from STDIN.\n");
  fprintf(stderr, "\n");

  return;
}

void walk(egg_token *t, int level)
{
  if (!t)
    return;

  printf("%*.*s%s@%d.%d\n", level, level, " ", egg_token_type_to_string(t), t->loc.line_number, t->loc.character_offset);

  walk(t->d, level+1);

  walk(t->n, level);

  return;
}

