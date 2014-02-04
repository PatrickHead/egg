/*!

  @file egg-walker.c

  @brief Source code for grammar specific walking/dumping utility

  @version 0.4.0

  @author Patrick Head mailto:patrickhead@gmail.com

  @copyright Copyright (C) 2013-2014 Patrick Head

  @license
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.@n
  @n
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.@n
  @n
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

static void usage(void);
static void version(void);
static void walk(egg_token *t, int level);

  /*!

     @brief main function for @b egg-walker utility command.

     This is the main function for the @b egg-walker utility.@n
       - Accepts and parses command line arguments
       - Initializes the input source
       - Parses the input using the specified phrase(s)
       - Walks the egg_token tree and displays each egg_token
       - Cleans up input source and other data

     @param argc count of command line arguments
     @param argv array of command line argument strings

     @retval 0 success
     @retval 1 any failure

  */

int main(int argc, char **argv)
{
  int c;
  extern char *optarg;
  extern int optind;
  int long_index;
  struct option long_opts[] =
  {
    { "grammar", 0, 0, 0 },

    { 0, 0, 0, 0 }
  };
  boolean syntax_only = false;
  boolean walk_grammar = false;
  egg_token *t;
  char *input_file;

  while ((c = getopt_long(argc, argv, "svh", long_opts, &long_index)) != -1)
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
      case 'v':
        version();
        return 0;
      case 'h':
      default:
        version();
        usage();
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

  /*!

     @brief Displays usage/help message in conventional format.

     This function displays a help and usage message for the @b egg-walker
     utility in the mostly ubiquitous POSIX/GNU format.

  */

#include "egg-walker-usage.inc"

  /*!

     @brief Display command version.

     This function displays the current version of this command.

  */

static void version(void)
{
  fprintf(stderr, "\n"
       "egg-walker - egg grammar walker.\n"
       "             Version 0.4.0\n"
       "\n");

  return;
}

  /*!

     @brief Walks a egg_token tree.

     This function walks egg_token tree, and displays each egg_token.

     @param t egg_token * to root of egg_token tree
     @param level int depth level of recursion during walk

  */

static void walk(egg_token *t, int level)
{
  if (!t)
    return;

  printf("%*.*s%s@%d.%d\n",
           level, level, " ",
           egg_token_type_to_string(t),
           t->location.line_number,
           t->location.character_offset);

  walk(t->descendant, level+1);

  walk(t->next, level);

  return;
}

