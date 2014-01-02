/*!

  \file egg-mapper.c

  \brief Source code for EGG grammar mapping utility

  \timestamp 20140102052221

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

  // Required system headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

  // Project specific headers

#include "config.h"
#include "common.h"
#include "input.h"
#include "egg-token.h"
#include "egg-token-util.h"
#include "egg-parser.h"
#include "map.h"

  // Function declarations

static void usage(char *program_name);
static void version(void);
static void map(FILE *of, egg_token *t);
static void map_phrases(FILE *of, egg_token *t);
static void map_phrase_usage(FILE *of, egg_token *t);
static void map_top_level_phrases(FILE *of, egg_token *t);
static void emit_item(FILE *of, egg_token *item);
static long convert_integer(egg_token *integer);

  /*!

     \brief main function for \b egg-mapper utility command.

     This is the main function for the \b egg-mapper utility.\n
       - Accepts and parses command line arguments
       - Initializes the input source
       - Maps all the phrases for the EGG input file
       - Outputs map data, based on user options
       - Cleans up input source and other data

     \param argc count of command line arguments
     \param argv array of command line argument strings

     \retval 0 success
     \retval 1 any failure

  */

int main(int argc, char **argv)
{
  int c;
  extern char *optarg;
  extern int optind;
  int long_index;
  struct option long_opts[] =
  {
    { "output", 0, 0, 'o' },
    { "version", 0, 0, 'v' },
    { "help", 0, 0, 'h' },
    { 0, 0, 0, 0 }
  };
  boolean raw_output = false;
  boolean graphviz_output = false;
  boolean c_output = false;
  egg_token *t;
  char *input_file;
  char *output_file = NULL;
  FILE *of = NULL;

  while ((c = getopt_long(argc, argv, "o:vh", long_opts, &long_index)) != -1)
  {
    switch (c)
    {
      case 'o':
        output_file = strdup(optarg);
        break;
      case 'v':
        version();
        return 0;
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

  t = grammar();
  if (!t)
    fprintf(stderr, "Failed to parse grammar.\n");

  input_cleanup();

  if (!t)
    return 1;

  if (output_file)
  {
    of = fopen(output_file, "w");
    if (!of)
    {
      fprintf(stderr, "Failed to open '%s'\n", output_file);
      return 1;
    }
  }
  else
    of = stdout;

  map(of, t);

  return 0;
}

  /*!

     \brief Displays usage/help message in conventional format.

     This function displays a help and usage message for the \b egg-mapper
     utility in the mostly ubiquitous POSIX/GNU format.

     \param program_name string containing the program name used in the
                         usage message

  */

static void usage(char *program_name)
{
  if (!program_name)
    program_name = "egg-mapper";

  fprintf(stderr, "\n");
  fprintf(stderr, "Usage:  %s\n", program_name);
  fprintf(stderr, "          [-o|--output <output file>]\n");
  fprintf(stderr, "          [-v|--version]\n");
  fprintf(stderr, "          [-h|--help]\n");
  fprintf(stderr, "          [<file name>]\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "  where:\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    <file name>   = pathname to any EGG definition file.\n");
  fprintf(stderr, "                    NONE or '-' implies input from STDIN.\n");
  fprintf(stderr, "    <output file> = pathname to generated XML file.\n");
  fprintf(stderr, "\n");

  return;
}

  /*!

     \brief Display command version.
    
     This function displays the current version of this command.
    
  */

static void version(void)
{
  printf("\n"
         "egg-mapper - EGG definition mapper.\n"
         "             Version "
         VERSION
         "\n"
         "\n");

  return;
}

  /*!

     \brief Map the phrases in an egg_token tree.

     This function maps an egg_token tree, and emits phrase map data.
     The data consists of three parts:
       1. A map of each phrase defined in the grammar, including literals.
       2. A map of the phrases that use each phrase in the grammar.
       3. A list of of each top-level phrase.

     \param of point to open file for output
     \param t  egg_token * to root of egg_token tree

  */

static void map(FILE *of, egg_token *t)
{
    // Sanity check parameters

  if (!of)
    return;

  if (!t)
    return;

    // Start of well-formed XML

  fprintf(of, "<?xml version=\"1.0\"?>\n");
  fprintf(of, "\n");

    // Emit root XML node

  fprintf(of, "<egg-map>\n");

  map_phrases(of, t);

  map_phrase_usage(of, t);

  map_top_level_phrases(of, t);

    // Close root XML node

  fprintf(of, "</egg-map>\n");

  return;
}

  /*!

     \brief Map the phrases in an egg_token tree.

     This function maps an egg_token tree, and emits phrase map data.
     The data is a XML representation of containing a map of each phrase
     in an EGG grammar, including literals.  Basically, this is the nearly
     complete XML representation of an EGG grammar definition file.

     \param of point to open file for output
     \param t  egg_token * to root of egg_token tree

  */

static void map_phrases(FILE *of, egg_token *t)
{
  egg_token *ge;
  egg_token *ph;
  egg_token *phn;
  egg_token *def;
  egg_token *seq;
  egg_token *it;
  egg_token *defcon;
  egg_token *seqcon;
  char *sphn = NULL;
  char *s;

    // Sanity check parameters

  if (!of)
    return;

  if (!t)
    return;

    // Emit XML node for the phrase map

  fprintf(of, "  <phrase-map>\n");

    // Search for each grammar-element and emit the phrase map for the
    // phrase that is contained in each grammar-element

    // Get first grammar-element

  ge = egg_token_find(t, egg_token_type_grammar_element);
  while (ge)
  {
      // Get it's phrase

    ph = egg_token_find(ge->descendant, egg_token_type_phrase);
    if (ph)
    {

        // Get the phrase's name

      phn = egg_token_find(ph->descendant, egg_token_type_phrase_name);
      if (phn)
				sphn = egg_token_to_string(phn->descendant, NULL);

        // Get the phrase's definition

      def = egg_token_find(ph->descendant, egg_token_type_definition);
      if (def)
      {
          // Get the first sequence in the definition

				seq = egg_token_find(def->descendant, egg_token_type_sequence);
        if (seq)
        {
            // Emit the XML for the phrase

          fprintf(of, "    <phrase>\n");
          fprintf(of, "      <name>%s</name>\n", sphn);
          fprintf(of, "      <sequence>\n");
          it = egg_token_find(seq->descendant, egg_token_type_item);

					emit_item(of, it);

            // Get any subsequent items in this sequence

          seqcon = egg_token_find(def->descendant,
                                  egg_token_type_sequence_continuation);
          while (seqcon)
          {
						it = egg_token_find(seqcon->descendant, egg_token_type_item);

						emit_item(of, it);

            seqcon = seqcon->next;
          }

            // Emit the closure for this sequence

          fprintf(of, "      </sequence>\n");

            // Look for subsequent sequences in definition

          defcon = egg_token_find(def->descendant,
                                  egg_token_type_definition_continuation);
          while (defcon)
          {
              // Grab the sequence

						seq = egg_token_find(defcon->descendant, egg_token_type_sequence);
						if (seq)
						{
                // Emit the XML for this sequence

							fprintf(of, "      <sequence>\n");
							it = egg_token_find(seq->descendant, egg_token_type_item);

							emit_item(of, it);

                // Get any subsequent items in this sequence

							seqcon = egg_token_find(def->descendant,
                                      egg_token_type_sequence_continuation);
							while (seqcon)
							{
								it = egg_token_find(seqcon->descendant, egg_token_type_item);

                emit_item(of, it);

								seqcon = seqcon->next;
							}

                // Emit the closure for this sequence

							fprintf(of, "      </sequence>\n");
						}
            defcon = defcon->next;
          }

            // Emit the closure for the entire phrase

          fprintf(of, "    </phrase>\n");
        }
      }
    }
    if (sphn)
    {
      free(sphn);
      sphn = NULL;
    }

		ge = ge->next;
  }

    // Emit the closure for the completed phrase-map

  fprintf(of, "  </phrase-map>\n");

  return;
}

  /*!

     \brief Generate the XML associated with any EGG item token type.

     This function outputs the XML fragments that describe an EGG item
     token type.

     \param of point to open file for output
     \param t  egg_token * to root of egg_token tree

  */

static void emit_item(FILE *of, egg_token *item)
{
  char *s;
  egg_token *atom;
  egg_token *phrase_name;
  egg_token *literal;
  egg_token *absolute;
  egg_token *integer;
  egg_token *quoted;
  egg_token *string;
  egg_token *qty;
  egg_token *qty_option;
  egg_token *qty_item;
  egg_token *asterisk;
  long i;

    // Sanity check parameters

  if (!of)
    return;

  if (!item)
    return;

  if (item->type != egg_token_type_item)
    return;

    // Emit XML for this item

  fprintf(of, "%8.8s", " ");
  fprintf(of, "<item>\n");

    // Look for the atom in this item

  if (atom = egg_token_find(item->descendant,
                            egg_token_type_atom))
  {
      // If this atom is a phrase-name, then emit the XML for it

    if (phrase_name = egg_token_find(atom->descendant,
                                     egg_token_type_phrase_name))
    {
			fprintf(of, "%10.10s", " ");
			fprintf(of, "<phrase-name>");
			fprintf(of, "%s", s = egg_token_to_string(phrase_name->descendant, NULL));
			free(s);
			fprintf(of, "</phrase-name>");
			fprintf(of, "\n");
    }

      // If the atom is a literal, then process the literal

		else if (literal = egg_token_find(item->descendant,
                                      egg_token_type_literal))
		{
        // If this is an absolute (integer) literal emit the XML for it

			if (absolute = egg_token_find(literal->descendant,
                                    egg_token_type_absolute_literal))
			{
				if (integer = egg_token_find(absolute->descendant,
                                     egg_token_type_integer))
				{
					fprintf(of, "%10.10s", " ");
					fprintf(of, "<literal type=\"absolute\">");
					fprintf(of, "%ld", convert_integer(integer));
					fprintf(of, "</literal>");
					fprintf(of, "\n");
				}
			}
        // If this is a string literal, then process that

			else if (quoted = egg_token_find(literal->descendant,
                                       egg_token_type_quoted_literal))
			{
          // Emit XML for quoted string

				if (string = egg_token_find(quoted->descendant,
                                    egg_token_type_quoted_character))
				{
					fprintf(of, "%10.10s", " ");
					fprintf(of, "<literal type=\"string\">");
					s = egg_token_to_string(string, NULL);
          if (strrchr(s, '"'))
            *(strrchr(s, '"')) = 0;
					fprintf(of, "%s", s);
					free(s);
					fprintf(of, "</literal>");
					fprintf(of, "\n");
				}
			}
         // Emit XML for single quoted string

			else if (quoted = egg_token_find(literal->descendant,
                                       egg_token_type_single_quoted_literal))
			{
				if (string = egg_token_find(quoted->descendant,
                                    egg_token_type_single_quoted_character))
				{
					fprintf(of, "%10.10s", " ");
					fprintf(of, "<literal type=\"string\">");
					s = egg_token_to_string(string, NULL);
          if (strrchr(s, '\''))
            *(strrchr(s, '\'')) = 0;
					fprintf(of, "%s", s);
					free(s);
					fprintf(of, "</literal>");
					fprintf(of, "\n");
				}
			}
		}
	}

    // Process any quantifier that may exist for this item

  if (qty = egg_token_find(item->descendant,
                           egg_token_type_quantifier))
  {
    if (integer = egg_token_find(qty->descendant,
                                 egg_token_type_integer))
    {
			fprintf(of, "%10.10s", " ");
			fprintf(of, "<quantity>\n");

        // We always have a minimum for any quantifier

      i = convert_integer(integer);
			fprintf(of, "%12.12s", " ");
			fprintf(of, "<minimum>%ld</minimum>\n", i);

      if (qty_option = egg_token_find(qty->descendant,
                                      egg_token_type_quantifier_option))
      {
        if (qty_item = egg_token_find(qty_option->descendant,
                                      egg_token_type_quantifier_item))
        {
            // We may have an optional maximum

					fprintf(of, "%12.12s", " ");
					fprintf(of, "<maximum>");

            // Absolute (integer) maximum

          if (integer = egg_token_find(qty_item->descendant,
                                       egg_token_type_integer))
          {
            fprintf(of, "%ld", convert_integer(integer));
          }

            // Infinite maximum

          else if (asterisk = egg_token_find(qty_item->descendant,
                                             egg_token_type_asterisk))
          {
            fprintf(of, "unlimited");
          }
					fprintf(of, "</maximum>");
          fprintf(of, "\n");
        }
      }

        // Emit quantifier closure

			fprintf(of, "%10.10s", " ");
			fprintf(of, "</quantity>");
			fprintf(of, "\n");
    }
  }

     // Emit item closure

  fprintf(of, "%8.8s", " ");
  fprintf(of, "</item>");
  fprintf(of, "\n");

  return;
}

  /*!

     \brief Converts an EGG integer token type token into an actual integer.

     \param t  egg_token * to integer token

     \retval long integer representation of integer token
  */

static long convert_integer(egg_token *integer)
{
  char *s;
  long i;

    // Sanity check parameters

  if (!integer)
    return;

  if (integer->type != egg_token_type_integer)
    return;

    // Grab integer defining string from the integer token

	s = egg_token_to_string(integer->descendant, NULL);

    // If this is NOT a decimal definition, then process that

	if (*s == '0' && ((strlen(s)) > 2))
	{
		switch (*(s+1))
		{
        // Binary

			case 'b':
			case 'B':
				i = strtol(s+2, NULL, 2);
				break;

        // Octal

			case 'o':
			case 'O':
				i = strtol(s+2, NULL, 8);
				break;

        // Hexadecimal

			case 'x':
			case 'X':
				i = strtol(s+2, NULL, 16);
				break;
		}
	}

    // It is a decimal

	else
		i = strtol(s, NULL, 10);

    // Clean up

	free(s);

    // Return converted value

  return i;
}

  /*!

     \brief Map the usage of each phrase in an EGG grammar.

     This function emits the XML listing every phrase the references each
     phrase in an EGG grammar.

     \param of point to open file for output
     \param t  egg_token * to root of egg_token tree

  */

static void map_phrase_usage(FILE *of, egg_token *t)
{
  phrase_map_item *pml;
  phrase_map_item *pmi;
  phrase_map_item *pmi2;
  phrase_map_item *pmu;

    // Sanity check parameters

  if (!of)
    return;

  if (!t)
    return;

    // Build phrase map

  pml = phrase_map(t);
  if (!pml)
    return;

    // Emit XML phrase map element

  fprintf(of, "  <phrase-usage-map>\n");

    // Emit XML for each phrase in map

  pmi = pml;
  while (pmi)
  {
    fprintf(of, "%4.4s", " ");
    fprintf(of, "<phrase>\n");

    fprintf(of, "%6.6s", " ");
    fprintf(of, "<name>%s</name>\n", pmi->name);

    fprintf(of, "%6.6s", " ");
    fprintf(of, "<used-by>\n");

      // Emit XML for each phrase that references this phrase

    pmi2 = pml;
    while (pmi2)
    {
      pmu = pmi2->uses;
      while (pmu)
      {
        if (!strcmp(pmi->name, pmu->name))
        {
					fprintf(of, "%8.8s", " ");
					fprintf(of, "<reference>%s</reference>\n", pmi2->name);

          break;
        }
        pmu = pmu->next;
      }
      pmi2 = pmi2->next;
    }

      // Emit closure for used-by element

    fprintf(of, "%6.6s", " ");
    fprintf(of, "</used-by>\n");

      // Emit closure for phrase element

    fprintf(of, "%4.4s", " ");
    fprintf(of, "</phrase>\n");

    pmi = pmi->next;
  }

    // Emit closure for entire phrase usage map

  fprintf(of, "  </phrase-usage-map>\n");

  phrase_map_list_delete(pml);

  return;
}

  /*!

     \brief Map the top-level phrases in an EGG grammar.

     This creates the XML that contains a list of all the top-level phrases
     in an EGG grammar.

     A top-level phrase is defined as any phrase in an EGG grammar that is
     not referenced (used) by any other phrase in that grammar.

     \param of point to open file for output
     \param t  egg_token * to root of egg_token tree

  */

static void map_top_level_phrases(FILE *of, egg_token *t)
{
  phrase_map_item *pml;
  phrase_map_item *pmi;

    // Sanity check parameters

  if (!of)
    return;

  if (!t)
    return;

    // Generate phrase map

  pml = phrase_map(t);
  if (!pml)
    return;

    // Prune phrase map down to only top-level phrases

  phrase_map_list_isolate_top_level_phrases(&pml);

    // Emit XML for top-level phrase map element

  fprintf(of, "  <top-level-phrase-map>\n");

    // Emit XML for each top-level phrase

  pmi = pml;
  while (pmi)
  {
    fprintf(of, "%4.4s", " ");
    fprintf(of, "<phrase>\n");

    fprintf(of, "%6.6s", " ");
    fprintf(of, "<name>%s</name>\n", pmi->name);

    fprintf(of, "%4.4s", " ");
    fprintf(of, "</phrase>\n");

    pmi = pmi->next;
  }

    // Emit closure for entire top-level phrase map element

  fprintf(of, "  </top-level-phrase-map>\n");

  phrase_map_list_delete(pml);

  return;
}

