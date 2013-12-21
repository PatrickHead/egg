/*!
    \file generator.c

    \brief Source code for parser code generation routines for EGG grammars.

    \version 20131221055452

    \author Patrick Head   mailto:patrickhead@gmail.com

    \copyright Copyright (C) 2013  Patrick Head

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
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

  /*!

    \file generator.c

    This is the source code file for the embryo project source code generation
    function module.

    An individual generation function exists for each source code file that
    can be generated.

    \note Several internal settings used by the generator are available.  Each
          setting can be managed with its own getter/setter function pairs.\n
          \n
          Currently, all of these internal settings are related to the
          source code annotations that are generated within the source file
          files.

  */

  // Require system headers

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

  // Project specific headers

#include "egg-token.h"
#include "egg-token-util.h"
#include "strapp.h"
#include "map.h"

  // Module specific header

#include "generator.h"

  // Module function declarations

static void generate_grammar(FILE *of,
                             char *parser_name,
                             egg_token *t,
                             int level);
static void generate_phrase(FILE *of,
                            char *parser_name,
                            egg_token *t);
static void generate_definition(FILE *of,
                                char *parser_name,
                                egg_token *t);
static void generate_sequence(FILE *of,
                              char *parser_name,
                              egg_token *t);
static void generate_item(FILE *of,
                          char *parser_name,
                          egg_token *t);
static void generate_atom(FILE *of,
                          char *parser_name,
                          egg_token *t);
static void generate_literal(FILE *of,
                             char *parser_name,
                             egg_token *t);
static void generate_phrase_name(FILE *of,
                                char *parser_name,
                                egg_token *t);
static int get_minimum(egg_token *t);
static int get_maximum(egg_token *t);
static char *fix_identifier(char *pn);
static char *fix_quotes(char *s);
static char *str_toupper(char *s);
static char *build_literal(egg_token *t);
static char *literal_or_phrase_name(egg_token *t);
static char *long_to_bytes(unsigned long l);
static int get_year(void);
static void emit_indent(FILE *of);
static void emit_phrase_comment_lines(FILE *of, char *s);
static void emit_source_comment_header(FILE *of);
static char * make_file_name(char *project, char *file_name);

  // Module global values

static phrase_map_item *_pml = NULL;
static int _current_level = 0;
static char *_pns = NULL;
static char *_pns_f = NULL;
static boolean _use_doxygen = false;
static char * _file_name = "Unknown";
static char * _project_brief = "";
static char * _version = "0";
static char * _author = "Anonymous";
static char * _email = "";
static int _first_year = 2013;
static char * _license =
    "This program is free software: you can redistribute it and/or modify\n"
    "  it under the terms of the GNU General Public License as published by\n"
    "  the Free Software Foundation, either version 3 of the License, or\n"
    "  (at your option) any later version.\n"
    "\n"
    "  This program is distributed in the hope that it will be useful,\n"
    "  but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    "  GNU General Public License for more details.\n"
    "\n"
    "  You should have received a copy of the GNU General Public License\n"
    "  along with this program.  If not, see <http://www.gnu.org/licenses/>.";
static char * _license_with_doxygen =
    "\\license\n"
    "  This program is free software: you can redistribute it and/or modify\n"
    "  it under the terms of the GNU General Public License as published by\n"
    "  the Free Software Foundation, either version 3 of the License, or\n"
    "  (at your option) any later version.\\n\n"
    "  \\n\n"
    "  This program is distributed in the hope that it will be useful,\n"
    "  but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    "  GNU General Public License for more details.\\n\n"
    "  \\n\n"
    "  You should have received a copy of the GNU General Public License\n"
    "  along with this program.  If not, see "
    "  \\<http://www.gnu.org/licenses/\\>.";

  /*!

     \brief Generates \<PROJECT\>-parser.c source code file.
    
     This function generates the source code for \<PROJECT\>-parser.c\n
     \n
     The parser source file contains exactly one function for each phrase
     in the supplied EGG grammar.  Also, a the parser source includes a
     static \e callback_table with one entry per phrase, and a utility
     getter function named \<PROJECT\>_get_callback_table.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)
     \param t           \e egg_token * containing the root token from which
                        the source code is generated
    
  */

void generate_parser_source(FILE *of,
                            char *parser_name,
                            egg_token *t)
{
  phrase_map_item *pmi;  // Generic phrase map item pointer
  char *fn;              // A generated file name for emitted documentation

    // Sanity check parameters

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  if (!t)
    return;

    // Create a top level phrase map of all grammar phrases

  _pml = phrase_map(t);
  if (!_pml)
    return;

    // Emit the file level comment block

  fn = make_file_name(parser_name, "parser.c");
  generator_set_file_name(fn);
  emit_source_comment_header(of);

    // Emit file description comment block

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  if (_use_doxygen)
  {
    fprintf(of, "    \\file %s-parser.c\n", parser_name);
    fprintf(of, "\n");
  }
  fprintf(of, "    This is the source code file for the %s grammar phrase "
              "parsing\n",
                parser_name);
  fprintf(of, "    functions module.\n");
  fprintf(of, "\n");
  fprintf(of, "    An individual phrase parsing function exists for each\n");
  fprintf(of, "    %s grammar phrase.\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "    Also the %s_get_callback_table function is defined in\n",
                parser_name);
  fprintf(of, "    this module.\n");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit documentation to explain the standard phrase parsing functions

  fprintf(of, "\n");
  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %s%s%s",
                (_use_doxygen) ? "\\file " : "",
                (_use_doxygen) ? fn : "",
                (_use_doxygen) ? "\n\n" : "");
  fprintf(of, "    %s%s",
                (_use_doxygen) ?
                  "\\par \"Description of Parsing Functions\"" :
                  "",
                (_use_doxygen) ? "\n" : "");
  fprintf(of, "    With the exception of the %s_get_callback_table() "
              "function,\n", parser_name);
  fprintf(of, "    every function in this parser has the same calling "
              "signature and \n");
  fprintf(of, "    return value pattern:\n");
  fprintf(of, "    %s\n", (_use_doxygen) ? "\\n\\n" : "");
  fprintf(of, "      %s_token * <phrase-name>(void);\n", parser_name);
  fprintf(of, "    %s\n", (_use_doxygen) ? "\\n\\n" : "");
  fprintf(of, "    Each function returns a pointer to a struct of type "
              "%s_token,\n", parser_name);
  fprintf(of, "    which is set to the %s_<phrase-name>_token_type type, "
              "and possibly\n", parser_name);
  fprintf(of, "    contains a child hierarchy of related tokens.\n");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for included header files

  fprintf(of, "#include <stdlib.h>\n");
  fprintf(of, "\n");
  fprintf(of, "#include \"%s-token.h\"\n", parser_name);
  fprintf(of, "#include \"%s-parser.h\"\n", parser_name);
  fprintf(of, "\n");

    // Emit code for array of callback entries

  fprintf(of, "static callback_entry _callbacks[] =\n");
  fprintf(of, "{\n");
  pmi = _pml;
  while (pmi)
  {
    fprintf(of, "  { \"%s\", NULL, NULL, NULL }", pmi->name);
    if (pmi->next)
      fprintf(of, ",");
    fprintf(of, "\n");
    pmi = pmi->next;
  }
  fprintf(of, "};\n");
  fprintf(of, "\n");

    // Emit code for actual callback table structure

  fprintf(of, "static callback_table _cbt = { %d, _callbacks };\n",
              phrase_map_list_count_items(_pml));
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_get_callback_table()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sReturns pointer to callback table.\n",
                (_use_doxygen) ? "\\brief " : "");
  fprintf(of, "\n");
  fprintf(of, "    This function returns a pointer to the parser's callback "
              "table.  The\n");
  fprintf(of, "    caller can use this to register its own callback functions "
              "for additional\n");
  fprintf(of, "    parsing actions.\n");
  fprintf(of, "\n");
  fprintf(of, "    %s\"callback_table *\" pointer to head of parser "
              "callback table\n",
                (_use_doxygen) ? "\\retval " : "Returns: ");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_get_callback_table()

  fprintf(of, "callback_table *%s_get_callback_table(void)\n", parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  return &_cbt;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit code for each phrase parsing function

  generate_grammar(of, parser_name, t, 0);

    // Clean up and return

  phrase_map_list_delete(_pml);
  free(fn);

  return;
}

  /*!

     \brief Generates \<PROJECT\>-parser.h source code file.
    
     This function generates the source code for \<PROJECT\>-parser.h\n
     \n
     The parser header file contains exactly one function declaration for each
     phrase in the supplied EGG grammar.  Also, a function declartion for the
     utility getter function named \<PROJECT\>_get_callback_table is included.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)
     \param t           \e egg_token * containing the root token from which
                        the source code is generated

  */

void generate_parser_header(FILE *of,
                            char *parser_name,
                            egg_token *t)
{
  egg_token *ge, *p, *pn;
  char *hn;
  int hnl;
  char *pns;
  char *fn;

    // Sanity check parameters

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  if (!t)
    return;

    // Create header include guard name

  hnl = strlen(parser_name) + strlen("_parser_h") + 1;
  hn = malloc(hnl);
  memset(hn, 0, hnl);

  sprintf(hn, "%s_parser_h", parser_name);

  hn = str_toupper(hn);

    // Emit the file level comment block

  fn = make_file_name(parser_name, "parser.h");
  generator_set_file_name(fn);
  emit_source_comment_header(of);
  free(fn);

    // Emit file description comment block

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  if (_use_doxygen)
  {
    fprintf(of, "    \\file %s-parser.h\n", parser_name);
    fprintf(of, "\n");
  }
  fprintf(of, "    This is the header file for the %s grammar phrase parsing\n",
                parser_name);
  fprintf(of, "    functions module.\n");
  fprintf(of, "\n");
  fprintf(of, "    An individual phrase parsing function exists for each\n");
  fprintf(of, "    %s grammar phrase.\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "    Also the %s_get_callback_table function is defined in\n",
                parser_name);
  fprintf(of, "    this module.\n");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit header include guard

  fprintf(of, "#ifndef %s\n", hn);
  fprintf(of, "#define %s\n", hn);
  fprintf(of, "\n");

     // Emit includes

  fprintf(of, "#include \"callback.h\"\n");
  fprintf(of, "\n");

    // Emit function declaration for utility functions

  fprintf(of, "callback_table *%s_get_callback_table(void);\n", parser_name);
  fprintf(of, "\n");

    // Emit function declarations for each phrase parsing function

  if ((ge = egg_token_find(t->descendant, egg_token_type_grammar_element)))
  {
    while (ge)
    {
      if ((p = egg_token_find(ge->descendant, egg_token_type_phrase)))
      {
        if ((pn = egg_token_find(p->descendant, egg_token_type_phrase_name)))
        {
          pns = NULL;
          pns = egg_token_to_string(pn->descendant, pns);
          pns = fix_identifier(pns);

          fprintf(of, "%s_token *%s(void);\n",
                        parser_name, pns);

          free(pns);
        }
      }
      ge = ge->next;
    }
  }

    // Emit close-out for header include guard

  fprintf(of, "\n");
  fprintf(of, "#endif // %s\n", hn);

    // Clean up

  free(hn);

  return;
}

  /*!

     \brief Generates \<PROJECT\>-token.h source code file.
    
     This function generates the source code for \<PROJECT\>-token.h\n
     \n
     The token header file contains:
       - an enum typedef for the \<PROJECT\>_token_direction values
       - a struct typedef for the \<PROJECT\>_token structure
       - the declaration for several \<PROJECT\>_token management functions
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)

  */

void generate_token_header(FILE *of,
                           char *parser_name)
{
  char *u_parser_name;
  char *fn;

    // Sanity check parameters

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

    // Force parser name to upper case

  u_parser_name = str_toupper(strdup(parser_name));

    // Emit the file level comment block

  fn = make_file_name(parser_name, "token.h");
  generator_set_file_name(fn);
  emit_source_comment_header(of);
  free(fn);

    // Emit file description comment block

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  if (_use_doxygen)
  {
    fprintf(of, "    \\file %s-token.h\n", parser_name);
    fprintf(of, "\n");
  }
  fprintf(of, "    This is the header file for the %s grammar token and\n",
                parser_name);
  fprintf(of, "    token tree management functions module.\n");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit header include guard

  fprintf(of, "#ifndef %s_TOKEN_H\n", u_parser_name);
  fprintf(of, "#define %s_TOKEN_H\n", u_parser_name);
  fprintf(of, "\n");

    // Emit project related includes

  fprintf(of, "#include \"common.h\"\n");
  fprintf(of, "#include \"input.h\"\n");
  fprintf(of, "\n");

    // Emit module related includes

  fprintf(of, "#include \"%s-token-type.h\"\n", parser_name);
  fprintf(of, "\n");

    // Emit <PROJECT>_token_direction annotation

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "    %sDefinition of allowed directions for %s_token_add "
              "function.\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name);
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit <PROJECT>_token_direction enum

  fprintf(of, "typedef enum\n");
  fprintf(of, "{\n");
  fprintf(of, "    /*%s %sAdd new token before token (as sibling) */\n",
                (_use_doxygen) ? "!" : "",
                (_use_doxygen) ? "\\brief " : "");
  fprintf(of, "  %s_token_before,\n", parser_name);
  fprintf(of, "    /*%s %sAdd new token after token (as sibling) */\n",
                (_use_doxygen) ? "!" : "",
                (_use_doxygen) ? "\\brief " : "");
  fprintf(of, "  %s_token_after,\n", parser_name);
  fprintf(of, "    /*%s %sAdd new token below token (as descendant) */\n",
                (_use_doxygen) ? "!" : "",
                (_use_doxygen) ? "\\brief " : "");
  fprintf(of, "  %s_token_below\n", parser_name);
  fprintf(of, "} %s_token_direction;\n", parser_name);
  fprintf(of, "\n");

    // Emit <PROJECT>_token annotation

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "    %sDefinition of %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name);
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit <PROJECT>_token typedef

  fprintf(of, "typedef struct %s_token\n", parser_name);
  fprintf(of, "{\n");
  fprintf(of, "    /*%s %sType of token */\n",
                (_use_doxygen) ? "!" : "",
                (_use_doxygen) ? "\\brief " : "");
  fprintf(of, "  %s_token_type type;\n", parser_name);
  fprintf(of, "    /*%s %sPointer to ascendant (parent) token */\n",
                (_use_doxygen) ? "!" : "",
                (_use_doxygen) ? "\\brief " : "");
  fprintf(of, "  struct %s_token *ascendant;\n", parser_name);
  fprintf(of, "    /*%s %sPointer to descendant (child) token */\n",
                (_use_doxygen) ? "!" : "",
                (_use_doxygen) ? "\\brief " : "");
  fprintf(of, "  struct %s_token *descendant;\n", parser_name);
  fprintf(of, "    /*%s %sPointer to previous (sibling) token */\n",
                (_use_doxygen) ? "!" : "",
                (_use_doxygen) ? "\\brief " : "");
  fprintf(of, "  struct %s_token *previous;\n", parser_name);
  fprintf(of, "    /*%s %sPointer to next (sibling) token */\n",
                (_use_doxygen) ? "!" : "",
                (_use_doxygen) ? "\\brief " : "");
  fprintf(of, "  struct %s_token *next;\n", parser_name);
  fprintf(of, "    /*%s %sLine + offset location of token in input source */\n",
                (_use_doxygen) ? "!" : "",
                (_use_doxygen) ? "\\brief " : "");
  fprintf(of, "  input_location location;\n");
  fprintf(of, "} %s_token;\n", parser_name);
  fprintf(of, "\n");

    // Emit function declarations

  fprintf(of, "%s_token *%s_token_new(%s_token_type type);\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "\n");

  fprintf(of, "void %s_token_free(%s_token *t);\n",
                parser_name, parser_name);
  fprintf(of, "\n");

  fprintf(of, "boolean %s_token_add(%s_token *t,\n",
                parser_name, parser_name);
  fprintf(of, "  %s_token_direction dir,\n", parser_name);
  fprintf(of, "  %s_token *n);\n", parser_name);
  fprintf(of, "\n");

  fprintf(of, "void %s_token_delete(%s_token *t);\n",
                parser_name, parser_name);
  fprintf(of, "\n");

  fprintf(of, "void %s_token_unlink(%s_token *t);\n",
                parser_name, parser_name);
  fprintf(of, "\n");

  fprintf(of, "%s_token_type %s_token_get_type(%s_token *t);\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "void %s_token_set_type(%s_token *t, %s_token_type type);\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "\n");

  fprintf(of, "%s_token *%s_token_get_ascendant(%s_token *t);\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "void %s_token_set_ascendant(%s_token *t, %s_token *a);\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "\n");

  fprintf(of, "%s_token *%s_token_get_descendant(%s_token *t);\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "void %s_token_set_descendant(%s_token *t, %s_token *d);\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "\n");

  fprintf(of, "%s_token *%s_token_get_previous(%s_token *t);\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "void %s_token_set_previous(%s_token *t, %s_token *p);\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "\n");

  fprintf(of, "%s_token *%s_token_get_next(%s_token *t);\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "void %s_token_set_next(%s_token *t, %s_token *n);\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "\n");

  fprintf(of, "%s_token *%s_token_find(%s_token *t, %s_token_type type);\n",
                parser_name, parser_name, parser_name, parser_name);
  fprintf(of, "\n");

  fprintf(of, "char *%s_token_to_string(%s_token *t, char *s);\n",
                parser_name, parser_name);
  fprintf(of, "\n");

    // Emit close-out for header include guard

  fprintf(of, "#endif // %s_TOKEN_H\n", u_parser_name);
  fprintf(of, "\n");

    // Clean up

  free(u_parser_name);

  return;
}

  /*!

     \brief Generates \<PROJECT\>-token.c source code file.
    
     This function generates the source code for \<PROJECT\>-token.c\n
     \n
     The token source file contains:
       - the definitions for several \<PROJECT\>_token management functions
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)

  */

void generate_token_source(FILE *of,
                           char *parser_name)
{
  char *fn;              // A generated file name for emitted documentation

    // Sanity check parameters

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

    // Emit the file level comment block

  fn = make_file_name(parser_name, "token.c");
  generator_set_file_name(fn);
  emit_source_comment_header(of);
  free(fn);

    // Emit file description comment block

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  if (_use_doxygen)
  {
    fprintf(of, "    \\file %s-token.c\n", parser_name);
    fprintf(of, "\n");
  }
  fprintf(of, "    This is the source code file for the %s grammar token and\n",
                parser_name);
  fprintf(of, "    token tree management functions module.\n");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for included header files

  fprintf(of, "#include <stdlib.h>\n");
  fprintf(of, "#include <string.h>\n");
  fprintf(of, "\n");
  fprintf(of, "#include \"strapp.h\"\n");
  fprintf(of, "\n");
  fprintf(of, "#include \"%s-token.h\"\n", parser_name);
  fprintf(of, "#include \"%s-token-util.h\"\n", parser_name);
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_new()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sCreate a new %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %sThis function returns a pointer to dynamically "
              "allocated memory.\n",
                (_use_doxygen) ? "\\warning " : "Warning: ");
  fprintf(of, "             It is the caller's responsibility to free this "
              "memory when \n");
  fprintf(of, "             appropriate.\n");
  fprintf(of, "\n");
  fprintf(of, "    %stype %s_token_type\n",
                (_use_doxygen) ? "\\param " : "Parameters: ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %s%s%s_token *%s new %s_token\n",
                (_use_doxygen) ? "\\retval " : "Returns: ",
                (_use_doxygen) ? "\"" : "",
                parser_name,
                (_use_doxygen) ? "\"" : "",
                parser_name);
  fprintf(of, "    %sNULL failure\n",
                (_use_doxygen) ? "\\retval " : "         ");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_new()

  fprintf(of, "%s_token *%s_token_new(%s_token_type type)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  %s_token *new = NULL;\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  new = malloc(sizeof(%s_token));\n",
                parser_name);
  fprintf(of, "  if (!new)\n");
  fprintf(of, "    return NULL;\n");
  fprintf(of, "\n");
  fprintf(of, "  memset(new, 0, sizeof(%s_token));\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  new->type = type;\n");
  fprintf(of, "\n");
  fprintf(of, "  input_get_location(&(new->location));\n");
  fprintf(of, "\n");
  fprintf(of, "  return new;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_free()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sFree the memory associated with %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %sThis function does NOT perform any unlinking of "
              "the freed token.\n",
                (_use_doxygen) ? "\\warning " : "Warning: ");
  fprintf(of, "    %s%s_token_unlink()\n",
                (_use_doxygen) ? "\\sa " : "See: ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_free()

  fprintf(of, "void %s_token_free(%s_token *t)\n",
                parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  free(t);\n");
  fprintf(of, "\n");
  fprintf(of, "  return;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_add()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sLink %s_token into an existing token tree\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st   existing %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "    %sdir %s_token_direction\n",
                (_use_doxygen) ? "\\param " : "       ",
                parser_name);
  fprintf(of, "    %sn   %s_token * to link\n",
                (_use_doxygen) ? "\\param " : "       ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %strue  success\n",
                (_use_doxygen) ? "\\retval " : "Returns: ");
  fprintf(of, "    %sfalse failure\n",
                (_use_doxygen) ? "\\retval " : "         ");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_add()

  fprintf(of, "boolean %s_token_add(%s_token *t, "
              "%s_token_direction dir, "
              "%s_token *n)\n",
                parser_name, parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return false;\n");
  fprintf(of, "\n");
  fprintf(of, "  if (!n)\n");
  fprintf(of, "    return false;\n");
  fprintf(of, "\n");
  fprintf(of, "  switch (dir)\n");
  fprintf(of, "  {\n");
  fprintf(of, "    case %s_token_before:\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "      n->previous = t->previous;\n");
  fprintf(of, "      n->next = t;\n");
  fprintf(of, "      if (t->previous)\n");
  fprintf(of, "        t->previous->next = n;\n");
  fprintf(of, "      t->previous = n;\n");
  fprintf(of, "      n->ascendant = t->ascendant;\n");
  fprintf(of, "\n");
  fprintf(of, "        // Fix ascendant's descendant pointer, if it is t.\n");
  fprintf(of, "        // We always want the ascendant's descendent pointer to "
              "point to\n");
  fprintf(of, "        //   the beginning of the list of descendents.\n");
  fprintf(of, "\n");
  fprintf(of, "      if (t->ascendant)\n");
  fprintf(of, "        if (t->ascendant->descendant == t)\n");
  fprintf(of, "          t->ascendant->descendant = n;\n");
  fprintf(of, "\n");
  fprintf(of, "      break;\n");
  fprintf(of, "\n");
  fprintf(of, "    case %s_token_after:\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "      n->previous = t;\n");
  fprintf(of, "      n->next = t->next;\n");
  fprintf(of, "      if (t->next)\n");
  fprintf(of, "        t->next->previous = n;\n");
  fprintf(of, "      t->next = n;\n");
  fprintf(of, "      n->ascendant = t->ascendant;\n");
  fprintf(of, "\n");
  fprintf(of, "      break;\n");
  fprintf(of, "\n");
  fprintf(of, "    case %s_token_below:\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "      if (t->descendant)\n");
  fprintf(of, "        return false;\n");
  fprintf(of, "      t->descendant = n;\n");
  fprintf(of, "      n->ascendant = t;\n");
  fprintf(of, "\n");
  fprintf(of, "      break;\n");
  fprintf(of, "  }\n");
  fprintf(of, "\n");
  fprintf(of, "  return true;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_delete()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sDelete %s_token from an existing token tree, if any\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    This function unlinks %s_token from an existing token \n"
              "    tree, if required.\n",
                parser_name);
  fprintf(of, "    Also, the memory associated with %s_token is freed.\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_delete()

  fprintf(of, "void %s_token_delete(%s_token *t)\n",
                parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  while (t->descendant)\n");
  fprintf(of, "    %s_token_delete(t->descendant);\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  %s_token_unlink(t);\n",
                parser_name);
  fprintf(of, "  %s_token_free(t);\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  return;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_unlink()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sUnlink %s_token from an existing token tree\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %sThis function does NOT perform any freeing of "
              "the unlinked token.\n",
                (_use_doxygen) ? "\\warning " : "Warning: ");
  fprintf(of, "    %s%s_token_free()\n",
                (_use_doxygen) ? "\\sa " : "See: ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_unlink()

  fprintf(of, "void %s_token_unlink(%s_token *t)\n",
                parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  if (t->ascendant)\n");
  fprintf(of, "    if (t->ascendant->descendant == t)\n");
  fprintf(of, "      t->ascendant->descendant = t->next;\n");
  fprintf(of, "\n");
  fprintf(of, "  if (t->previous)\n");
  fprintf(of, "    t->previous->next = t->next;\n");
  fprintf(of, "\n");
  fprintf(of, "  if (t->next)\n");
  fprintf(of, "    t->next->previous = t->previous;\n");
  fprintf(of, "\n");
  fprintf(of, "  return;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_get_type()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sReturns %s_token_type of %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %s%s_token_type\n",
                (_use_doxygen) ? "\\retval " : "Returns: ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_get_type()

  fprintf(of, "%s_token_type %s_token_get_type(%s_token *t)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return %s_token_type_none;\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  return t->type;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_set_type()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sSets %s_token_type of %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st    %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "    %stype %s_token_type\n",
                (_use_doxygen) ? "\\param " : "       ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_set_type()

  fprintf(of, "void %s_token_set_type(%s_token *t, %s_token_type type)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  t->type = type;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_get_ascendant()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sReturns pointer to ascendant of %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %s%s%s_token *%s\n",
                (_use_doxygen) ? "\\retval " : "Returns: ",
                (_use_doxygen) ? "\"" : "",
                parser_name,
                (_use_doxygen) ? "\"" : "");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_get_ascendant()

  fprintf(of, "%s_token *%s_token_get_ascendant(%s_token *t)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return NULL;\n");
  fprintf(of, "\n");
  fprintf(of, "  return t->ascendant;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_set_ascendant()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sSets pointer to ascendant of %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st existing %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "    %sa ascendant of %s_token *\n",
                (_use_doxygen) ? "\\param " : "       ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_set_ascendant()

  fprintf(of, "void %s_token_set_ascendant(%s_token *t, %s_token *a)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  t->ascendant = a;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_get_descendant()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sReturns pointer to descendant of %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %s%s%s_token *%s\n",
                (_use_doxygen) ? "\\retval " : "Returns: ",
                (_use_doxygen) ? "\"" : "",
                parser_name,
                (_use_doxygen) ? "\"" : "");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_get_descendant()

  fprintf(of, "%s_token *%s_token_get_descendant(%s_token *t)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return NULL;\n");
  fprintf(of, "\n");
  fprintf(of, "  return t->descendant;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_set_descendant()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sSets pointer to descendant of %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st existing %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "    %sd descendant of %s_token *\n",
                (_use_doxygen) ? "\\param " : "       ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_set_descendant()

  fprintf(of, "void %s_token_set_descendant(%s_token *t, %s_token *d)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  t->descendant = d;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_get_previous()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sReturns pointer to previous %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %s%s%s_token *%s\n",
                (_use_doxygen) ? "\\retval " : "Returns: ",
                (_use_doxygen) ? "\"" : "",
                parser_name,
                (_use_doxygen) ? "\"" : "");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_get_previous()

  fprintf(of, "%s_token *%s_token_get_previous(%s_token *t)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return NULL;\n");
  fprintf(of, "\n");
  fprintf(of, "  return t->previous;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_set_previous()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sSets pointer to previous %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st existing %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "    %sp previous %s_token *\n",
                (_use_doxygen) ? "\\param " : "       ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_set_previous()

  fprintf(of, "void %s_token_set_previous(%s_token *t, %s_token *p)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  t->previous = p;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_get_next()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sReturns pointer to next %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %s%s%s_token *%s\n",
                (_use_doxygen) ? "\\retval " : "Returns: ",
                (_use_doxygen) ? "\"" : "",
                parser_name,
                (_use_doxygen) ? "\"" : "");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_get_next()

  fprintf(of, "%s_token *%s_token_get_next(%s_token *t)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return NULL;\n");
  fprintf(of, "\n");
  fprintf(of, "  return t->next;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_set_next()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sSets pointer to next %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st existing %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "    %sn next %s_token *\n",
                (_use_doxygen) ? "\\param " : "       ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_set_next()

  fprintf(of, "void %s_token_set_next(%s_token *t, %s_token *n)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  t->next = n;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_find_next()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sFind next %s_token of specified %s_token_type\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %st    existing %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "    %stype %s_token_type\n",
                (_use_doxygen) ? "\\param " : "       ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %s%s%s_token *%s found %s_token\n",
                (_use_doxygen) ? "\\retval " : "Returns: ",
                (_use_doxygen) ? "\"" : "",
                parser_name,
                (_use_doxygen) ? "\"" : "",
                parser_name);
  fprintf(of, "    %sNULL failure, including NOT FOUND\n",
                (_use_doxygen) ? "\\retval " : "         ");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_find_next()

  fprintf(of, "%s_token *%s_token_find(%s_token *t, %s_token_type type)\n",
                parser_name, parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  %s_token *f;\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return NULL;\n");
  fprintf(of, "\n");
  fprintf(of, "  if (t->type == type)\n");
  fprintf(of, "    return t;\n");
  fprintf(of, "\n");
  fprintf(of, "  f = %s_token_find(t->descendant, type);\n", parser_name);
  fprintf(of, "  if (f)\n");
  fprintf(of, "    return f;\n");
  fprintf(of, "\n");
  fprintf(of, "  f = %s_token_find(t->next, type);\n", parser_name);
  fprintf(of, "  if (f)\n");
  fprintf(of, "    return f;\n");
  fprintf(of, "\n");
  fprintf(of, "  return NULL;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_to_string()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sReturns string representation of %s_token\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %sThis is a recursive function, therefore parameter s can "
              "NOT point to static\n",
                (_use_doxygen) ? "\\warning " : "Warning: ");
  fprintf(of, "              memory.\n");
  fprintf(of, "\n");
  fprintf(of, "    %sThis function returns a pointer to dynamically "
              "allocated memory.\n",
                (_use_doxygen) ? "\\warning " : "Warning: ");
  fprintf(of, "             It is the caller's responsibility to free this "
              "memory when\n");
  fprintf(of, "             appropriate.\n");
  fprintf(of, "\n");
  fprintf(of, "    %st existing %s_token *\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name);
  fprintf(of, "    %ss char * of existing string, can be NULL\n",
                (_use_doxygen) ? "\\param " : "       ",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %s%schar *%s string, can be NULL if s is NULL\n",
                (_use_doxygen) ? "\\retval " : "Returns: ",
                (_use_doxygen) ? "\"" : "",
                (_use_doxygen) ? "\"" : "");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_to_string()

  fprintf(of, "char *%s_token_to_string(%s_token *t, char *s)\n",
               parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return s;\n");
  fprintf(of, "\n");
  fprintf(of, "  if (!t->descendant)\n");
  fprintf(of, "    s = strapp(s , %s_token_type_to_string(t));\n", parser_name);
  fprintf(of, "  else\n");
  fprintf(of, "    s = %s_token_to_string(t->descendant, s);\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "  s = %s_token_to_string(t->next, s);\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "  return s;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

  return;
}

  /*!

     \brief Generates \<PROJECT\>-token-type.h source code file.
    
     This function generates the source code for \<PROJECT\>-token-type.h\n
     \n
     The token type header file contains an enum typedef for the
     \<PROJECT\>_token_type values.  A token type is defined for each phrase
     defined in the parsed EGG grammar.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)
     \param t           \e egg_token * containing the root token from which
                        the source code is generated

  */

void generate_token_type_header(FILE *of,
                                char *parser_name,
                                egg_token *t)
{
  egg_token *ge, *p, *pn;
  char *hn;
  int hnl;
  char *pns;
  char *fn;

    // Sanity check parameters

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  if (!t)
    return;

    // Create header guard macro name

  hnl = strlen(parser_name) + strlen("_token_type_h") + 1;
  hn = malloc(hnl);
  memset(hn, 0, hnl);

  sprintf(hn, "%s_token_type_h", parser_name);

    // Force header guard macro to uppercase

  hn = str_toupper(hn);

    // Emit the file level comment block

  fn = make_file_name(parser_name, "token-type.h");
  generator_set_file_name(fn);
  emit_source_comment_header(of);
  free(fn);

    // Emit file description comment block

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  if (_use_doxygen)
  {
    fprintf(of, "    \\file %s-token-type.h\n", parser_name);
    fprintf(of, "\n");
  }
  fprintf(of, "    This is the header file for the %s grammar token type "
              "definitions\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    Each %s grammar phrase has an associated token type\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit header include guard

  fprintf(of, "#ifndef %s\n", hn);
  fprintf(of, "#define %s\n", hn);
  fprintf(of, "\n");

    // Emit <PROJECT>_token_type annotation

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "    %sDefinition of allowed token types for %s_token.\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name);
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit <PROJECT>_token_direction enum

  fprintf(of, "typedef enum\n");
  fprintf(of, "{\n");

  if ((ge = egg_token_find(t->descendant, egg_token_type_grammar_element)))
  {
      // Emit special token type, none

    fprintf(of, "    /*%s %sSpecial token type for unknown tokens */\n",
                  (_use_doxygen) ? "!" : "",
                  (_use_doxygen) ? "\\brief " : "");
    fprintf(of, "  %s_token_type_none%s\n",
                  parser_name,
                  ge->next ? "," : "");

    while (ge)
    {
      if ((p = egg_token_find(ge->descendant, egg_token_type_phrase)))
      {
        if ((pn = egg_token_find(p->descendant, egg_token_type_phrase_name)))
        {
          pns = NULL;
          pns = egg_token_to_string(pn->descendant, pns);

          fprintf(of, "    /*%s %sToken type for %s phrase*/\n",
                        (_use_doxygen) ? "!" : "",
                        (_use_doxygen) ? "\\brief " : "",
                        pns);

          pns = fix_identifier(pns);

          fprintf(of, "  %s_token_type_%s%s\n",
                        parser_name,
                        pns,
                        ge->next ? "," : ""
                 );

          free(pns);
        }
      }
      ge = ge->next;
    }
  }

  fprintf(of, "} %s_token_type;\n", parser_name);
  fprintf(of, "\n");

    // Emit close-out for header include guard

  fprintf(of, "#endif // %s\n", hn);
  fprintf(of, "\n");

  free(hn);

  return;
}

  /*!

     \brief Generates \<PROJECT\>-token-util.c source code file.
    
     This function generates the source code for \<PROJECT\>-token-util.c\n
     \n
     The token utility source file contains the \<PROJECT\>_token_type_to_string
     function definition.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)
     \param t           \e egg_token * containing the root token from which
                        the source code is generated

  */

void generate_token_util_source(FILE *of,
                                char *parser_name,
                                egg_token *t)
{
  egg_token *ge, *p, *pn;
  char *pns;
  char *val;
  char *fn;

    // Sanity check parameters

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  if (!t)
    return;

    // Emit the file level comment block

  fn = make_file_name(parser_name, "token-util.c");
  generator_set_file_name(fn);
  emit_source_comment_header(of);
  free(fn);

    // Emit file description comment block

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  if (_use_doxygen)
  {
    fprintf(of, "    \\file %s-token-util.c\n", parser_name);
    fprintf(of, "\n");
  }
  fprintf(of, "    This is the source code file for the %s grammar token "
              "utility\n",
                parser_name);
  fprintf(of, "    functions module.\n");
  fprintf(of, "\n");
  fprintf(of, "    The %s_token_type_to_string function is defined in\n",
                parser_name);
  fprintf(of, "    this module.\n");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for included header files

  fprintf(of, "#include <stdlib.h>\n");
  fprintf(of, "#include <string.h>\n");
  fprintf(of, "\n");
  fprintf(of, "#include \"%s-token.h\"\n", parser_name);
  fprintf(of, "#include \"%s-token-util.h\"\n", parser_name);
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>_token_type_to_string()

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %sReturns a string representation of %s_token.\n",
                (_use_doxygen) ? "\\brief " : "",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "    %sThis function returns a pointer to dynamically allocated "
              "memory.\n",
                (_use_doxygen) ? "\\warning " : "Warning: ");
  fprintf(of, "    %sIt is the caller's responsibility to free this memory "
              "when\n",
                (_use_doxygen) ? "      " : "         ");
  fprintf(of, "    %sappropriate.\n",
                (_use_doxygen) ? "      " : "         ");
  fprintf(of, "\n");
  fprintf(of, "    %st %s_token * to %s_token to string-ize\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>_token_type_to_string()

  fprintf(of, "char *%s_token_type_to_string(%s_token *t)\n",
                parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  char *s;\n");
  fprintf(of, "\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return NULL;\n");
  fprintf(of, "\n");
  fprintf(of, "  switch (t->type)\n");
  fprintf(of, "  {\n");
  fprintf(of, "    case %s_token_type_none:\n", parser_name);
  fprintf(of, "      s = \"<none>\";\n");
  fprintf(of, "      break;\n");

  if ((ge = egg_token_find(t->descendant, egg_token_type_grammar_element)))
  {

    while (ge)
    {
      if ((p = egg_token_find(ge->descendant, egg_token_type_phrase)))
      {
        if ((pn = egg_token_find(p->descendant, egg_token_type_phrase_name)))
        {
          pns = NULL;
          pns = egg_token_to_string(pn->descendant, pns);
          pns = fix_identifier(pns);

          fprintf(of, "    case %s_token_type_%s:\n",
                        parser_name, pns);
          fprintf(of, "      s = \"%s\";\n",
                      val = literal_or_phrase_name(p));
          fprintf(of, "      break;\n");

          free(val);
          free(pns);
        }
      }
      ge = ge->next;
    }
  }

  fprintf(of, "  }\n");
  fprintf(of, "\n");
  fprintf(of, "  return s;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

  return;
}

  /*!

     \brief Generates \<PROJECT\>-token-util.h source code file.
    
     This function generates the source code for \<PROJECT\>-token-util.h\n
     \n
     The token utility header file contains the \<PROJECT\>_token_type_to_string
     function declaration.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)

  */

void generate_token_util_header(FILE *of,
                                char *parser_name)
{
  char *hn;
  int hnl;
  char *fn;

    // Sanity check parameters

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

    // Create header guard macro name

  hnl = strlen(parser_name) + strlen("_token_util_h") + 1;
  hn = malloc(hnl);
  memset(hn, 0, hnl);

  sprintf(hn, "%s_token_util_h", parser_name);

    // Force header guard macro name to uppercase 

  hn = str_toupper(hn);

    // Emit the file level comment block

  fn = make_file_name(parser_name, "token-util.h");
  generator_set_file_name(fn);
  emit_source_comment_header(of);
  free(fn);

    // Emit file description comment block

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  if (_use_doxygen)
  {
    fprintf(of, "    \\file %s-token-util.h\n", parser_name);
    fprintf(of, "\n");
  }
  fprintf(of, "    This is the header file for the %s grammar token utility\n",
                parser_name);
  fprintf(of, "    functions module.\n");
  fprintf(of, "\n");
  fprintf(of, "    The %s_token_type_to_string function is defined in\n",
                parser_name);
  fprintf(of, "    this module.\n");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit header include guard

  fprintf(of, "#ifndef %s\n", hn);
  fprintf(of, "#define %s\n", hn);
  fprintf(of, "\n");

    // Emit function declarations

  fprintf(of, "char *%s_token_type_to_string(%s_token *t);\n",
                parser_name, parser_name);
  fprintf(of, "\n");

    // Emit close-out for header include guard

  fprintf(of, "#endif // %s\n", hn);

    // Clean up

  free(hn);

  return;
}

  /*!

     \brief Generates \<PROJECT\>-walker.c source code file.
    
     This function generates the source code for \<PROJECT\>-walker.c\n
     \n
     The walker source file contains the code for a generic grammar walking
     utility command.  The walker utility will walk any given file and apply
     the \<PROJECT\> grammar rules to the file.  On success, the walker will
     dump all the parsed phrases in the input file to \b stdout.  This
     utility can optionally just check for correct grammar structure of the
     input file.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)
     \param t           \e egg_token * containing the root token from which
                        the source code is generated

  */

void generate_walker_source(FILE *of,
                            char *parser_name,
                            egg_token *t)
{
  phrase_map_item *pml;
  phrase_map_item *pmi;
  char *phrase_name;
  int opt_count = 0;
  char *fn;

    // Sanity check parameters

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  if (!t)
    return;

    // Create a top level phrase map of all grammar phrases

  pml = phrase_map(t);
  phrase_map_list_isolate_top_level_phrases(&pml);

    // Emit the file level comment block

  fn = make_file_name(parser_name, "walker.c");
  generator_set_file_name(fn);
  emit_source_comment_header(of);
  free(fn);

    // Emit code for included header files

  fprintf(of, "#include <stdio.h>\n");
  fprintf(of, "#include <stdlib.h>\n");
  fprintf(of, "#include <string.h>\n");
  fprintf(of, "#include <getopt.h>\n");
  fprintf(of, "\n");
  fprintf(of, "#include \"common.h\"\n");
  fprintf(of, "#include \"input.h\"\n");
  fprintf(of, "#include \"%s-token.h\"\n", parser_name);
  fprintf(of, "#include \"%s-token-util.h\"\n", parser_name);
  fprintf(of, "#include \"%s-parser.h\"\n", parser_name);
  fprintf(of, "\n");

    // Emit code for function declarations

  fprintf(of, "static void usage(char *program_name);\n");
  fprintf(of, "static void walk(%s_token *t, int level);\n", parser_name);
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>-walker's main() function

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "     %smain function for %s %s-walker utility command.\n",
                (_use_doxygen) ? "\\brief " : "",
                (_use_doxygen) ? "\\b" : "",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "     This is the main function for the %s %s-walker "
              "utility.%s\n",
                (_use_doxygen) ? "\\b" : "",
                parser_name,
                (_use_doxygen) ? "\\n" : "");
  fprintf(of, "       - Accepts and parses command line arguments\n");
  fprintf(of, "       - Initializes the input source\n");
  fprintf(of, "       - Parses the input using the specified phrase(s)\n");
  fprintf(of, "       - Walks the %s_token tree and displays each %s_token\n",
                parser_name,
                parser_name);
  fprintf(of, "       - Cleans up input source and other data\n");
  fprintf(of, "\n");
  fprintf(of, "     \\param argc count of command line arguments\n");
  fprintf(of, "     \\param argv array of command line argument strings\n");
  fprintf(of, "\n");
  fprintf(of, "     \\retval 0 success\n");
  fprintf(of, "     \\retval 1 any failure\n");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>-walker's main() function

  fprintf(of, "int main(int argc, char **argv)\n");
  fprintf(of, "{\n");
  fprintf(of, "  int c;\n");
  fprintf(of, "  extern char *optarg;\n");
  fprintf(of, "  extern int optind;\n");
  fprintf(of, "  int long_index;\n");
  fprintf(of, "  struct option long_opts[] =\n");
  fprintf(of, "  {\n");
  pmi = pml;
  while (pmi)
  {
    fprintf(of, "    { \"");
    fprintf(of, "%s", pmi->name);
    fprintf(of, "\", 0, 0, 0 }");
    if (pmi->next)
      fprintf(of, ",");
    fprintf(of, "\n");
    pmi = pmi->next;
  }
  fprintf(of, "  };\n");
  fprintf(of, "  boolean syntax_only = false;\n");
  pmi = pml;
  while (pmi)
  {
    phrase_name = fix_identifier(strdup(pmi->name));
    fprintf(of, "  boolean walk_%s = false;\n", phrase_name);
    free(phrase_name);
    pmi = pmi->next;
  }
  fprintf(of, "  %s_token *t;\n", parser_name);
  fprintf(of, "  char *input_file;\n");
  fprintf(of, "\n");
  fprintf(of, "  while ((c = getopt_long(argc, argv, \"sh\", long_opts, "
              "&long_index)) != -1)\n");
  fprintf(of, "  {\n");
  fprintf(of, "    switch (c)\n");
  fprintf(of, "    {\n");
  fprintf(of, "      case 0:\n");
  fprintf(of, "        switch (long_index)\n");
  fprintf(of, "        {\n");
  pmi = pml;
  opt_count = 0;
  while (pmi)
  {
    phrase_name = fix_identifier(strdup(pmi->name));
    fprintf(of, "          case %d:\n", opt_count);
    fprintf(of, "            walk_%s = true;\n", phrase_name);
    fprintf(of, "            break;\n");
    free(phrase_name);
    pmi = pmi->next;
    ++opt_count;
  }
  fprintf(of, "          default:\n");
  fprintf(of, "            break;\n");
  fprintf(of, "        }\n");
  fprintf(of, "        break;\n");
  fprintf(of, "      case 's':\n");
  fprintf(of, "        syntax_only = true;\n");
  fprintf(of, "        break;\n");
  fprintf(of, "      case 'h':\n");
  fprintf(of, "      default:\n");
  fprintf(of, "        usage(argv[0]);\n");
  fprintf(of, "        return 1;\n");
  fprintf(of, "    }\n");
  fprintf(of, "  }\n");
  fprintf(of, "\n");
  fprintf(of, "  input_file = NULL;\n");
  fprintf(of, "  if (optind < argc)\n");
  fprintf(of, "    if (strcmp(argv[optind], \"-\"))\n");
  fprintf(of, "      input_file = strdup(argv[optind]);\n");
  fprintf(of, "\n");
  fprintf(of, "  if (!input_initialize(input_file))\n");
  fprintf(of, "    return 1;\n");
  fprintf(of, "\n");
  pmi = pml;
  while (pmi)
  {
    phrase_name = fix_identifier(strdup(pmi->name));
    fprintf(of, "  if (walk_%s)\n", phrase_name);
    fprintf(of, "  {\n");
    fprintf(of, "    t = %s();\n", phrase_name);
    free(phrase_name);
    fprintf(of, "    if (t)\n");
    fprintf(of, "    {\n");
    fprintf(of, "      if (syntax_only)\n");
    fprintf(of, "        printf(\"Passed.\\n\");\n");
    fprintf(of, "      else\n");
    fprintf(of, "        walk(t, 0);\n");
    fprintf(of, "    }\n");
    fprintf(of, "    else\n");
    fprintf(of, "      printf(\"Failed.\\n\");\n");
    fprintf(of, "  }\n");
    fprintf(of, "\n");
    pmi = pmi->next;
  }
  fprintf(of, "  input_cleanup();\n");
  fprintf(of, "\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return 1;\n");
  fprintf(of, "\n");
  fprintf(of, "  return 0;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>-walker's usage() function

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "     %s Displays usage/help message in conventional format.\n",
                (_use_doxygen) ? "\\brief" : "");
  fprintf(of, "\n");
  fprintf(of, "     This function displays a help and usage message for the "
              "%s %s-walker\n",
                (_use_doxygen) ? "\\b" : "",
                parser_name);
  fprintf(of, "     utility in the mostly ubiquitous POSIX/GNU format.\n");
  fprintf(of, "\n");
  fprintf(of, "     %sprogram_name string containing the program name used "
              "in the\n",
                (_use_doxygen) ? "\\param " : "Param: ");
  fprintf(of, "                         usage message\n");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>-walker's usage() function

  fprintf(of, "static void usage(char *program_name)\n");
  fprintf(of, "{\n");
  fprintf(of, "  if (!program_name)\n");
  fprintf(of, "    program_name = \"%s-walker\";\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "  fprintf(stderr, \"\\n\");\n");
  fprintf(of, "  fprintf(stderr, \"Usage:  %%s\\n\", program_name);\n");
  pmi = pml;
  while (pmi)
  {
    fprintf(of, "  fprintf(stderr, \"          [--%s]\\n\");\n", pmi->name);
    pmi = pmi->next;
  }
  fprintf(of, "  fprintf(stderr, \"          [<file name>]\\n\");\n");
  fprintf(of, "  fprintf(stderr, \"\\n\");\n");
  fprintf(of, "  fprintf(stderr, \"  where:\\n\");\n");
  fprintf(of, "  fprintf(stderr, \"\\n\");\n");
  fprintf(of, "  fprintf(stderr, \"    <file name> = pathname to any file that "
              "uses a '%s' \"\n", parser_name);
  fprintf(of, "                  \"grammar.\\n\");\n");
  fprintf(of, "  fprintf(stderr, \"                  NONE or '-' implies input "
              "from STDIN.\\n\");\n");
  fprintf(of, "  fprintf(stderr, \"\\n\");\n");
  fprintf(of, "\n");
  fprintf(of, "  return;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

    // Emit comment block for <PROJECT>-walker's walk() function

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "     %s Walks a %s_token tree.\n",
                (_use_doxygen) ? "\\brief" : "",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "     This function walks %s_token tree, and displays each "
              "%s_token.\n",
                parser_name,
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "     %st %s_token * to root of %s_token tree\n",
                (_use_doxygen) ? "\\param " : "Param: ",
                parser_name,
                parser_name);
  fprintf(of, "     %slevel int depth level of recursion during walk\n",
                (_use_doxygen) ? "\\param " : "Param: ");
  fprintf(of, "\n");
  fprintf(of, "  */\n");
  fprintf(of, "\n");

    // Emit code for <PROJECT>-walker's walk() function

  fprintf(of, "static void walk(%s_token *t, int level)\n", parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  printf(\"%%*.*s%%s@%%d.%%d\\n\",\n"
              "           level, level, \" \",\n"
              "           %s_token_type_to_string(t),\n"
              "           t->location.line_number,\n"
              "           t->location.character_offset);\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  walk(t->descendant, level+1);\n");
  fprintf(of, "\n");
  fprintf(of, "  walk(t->next, level);\n");
  fprintf(of, "\n");
  fprintf(of, "  return;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

  return;
}

  /*!

     \brief Generates Makefile for \<PROJECT\> parser project.
    
     This function generates the Makefile for \<PROJECT\>\n
     \n
     The \<PROJECT\> Makefile contains all the make rules necessary to compile
     and link all the generated source code from embryo and associated
     utility actions, such as building a linkable library for the \<PROJECT\>
     parsing modules, installation scripts for the library, header files,
     and associated documention.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)

  */

void generate_makefile(FILE *of,
                       char *parser_name)
{
  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  fprintf(of, "CC = gcc\n");

  fprintf(of, "CFLAGS = -g -Wall -Wno-unused-but-set-variable -O0 \\\n"
              "\t\t-I include \\\n"
              "\t\t-I /usr/local/include/egg \\\n"
              "\t\t-I /usr/include/egg \\\n"
              "\t\t-L /usr/local/lib/egg \\\n"
              "\t\t-L ./lib\n");
  fprintf(of, "\n");

  fprintf(of, "CFLAGS_ALL = $(CFLAGS)\n");
  fprintf(of, "\n");

  fprintf(of, "ifdef EGG_LIBRARY_PATH\n");
  fprintf(of, "\tCFLAGS_ALL += -L $(EGG_LIBRARY_PATH)\n");
  fprintf(of, "endif\n");
  fprintf(of, "\n");

  fprintf(of, "ifdef EGG_INCLUDE_PATH\n");
  fprintf(of, "\tCFLAGS_ALL += -I $(EGG_INCLUDE_PATH)\n");
  fprintf(of, "endif\n");
  fprintf(of, "\n");

  fprintf(of, "all: %s-walker\n", parser_name);
  fprintf(of, "\n");

  fprintf(of, "%s-walker: bin/%s-walker\n",
                parser_name, parser_name);
  fprintf(of, "\n");

  fprintf(of, "bin/%s-walker: obj/%s-walker.o \\\n",
                parser_name, parser_name);
  fprintf(of, "\t\tlib/lib%s-parser.so.1.0\n", parser_name);
  fprintf(of, "\t$(CC) $(CFLAGS_ALL) \\\n");
  fprintf(of, "\t\t-o bin/%s-walker \\\n", parser_name);
  fprintf(of, "\t\tobj/%s-walker.o \\\n", parser_name);
  fprintf(of, "\t\t-legg-common \\\n");
  fprintf(of, "\t\t-legg-parser\n");
  fprintf(of, "\n");

  fprintf(of, "lib%s-parser: lib/lib%s-parser.a lib/lib%s-parser.so.1.0\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "\n");
  fprintf(of, "lib/lib%s-parser.so.1.0: obj/%s-parser.o \\\n",
                parser_name, parser_name);
  fprintf(of, "		obj/%s-token.o \\\n", parser_name);
  fprintf(of, "		obj/%s-token-util.o\n", parser_name);
  fprintf(of, "	$(CC) $(COPTS) --shared -Wl,-soname,lib%s-parser.so.1 \\\n",
                parser_name);
  fprintf(of, "		-o lib/lib%s-parser.so.1.0 \\\n", parser_name);
  fprintf(of, "		obj/%s-parser.o \\\n", parser_name);
  fprintf(of, "		obj/%s-token.o \\\n", parser_name);
  fprintf(of, "		obj/%s-token-util.o\n", parser_name);
  fprintf(of, "	@(cd lib; ln -sf lib%s-parser.so.1.0 lib%s-parser.so.1)\n",
                parser_name, parser_name);
  fprintf(of, "	@(cd lib; ln -sf lib%s-parser.so.1 lib%s-parser.so)\n",
                parser_name, parser_name);
  fprintf(of, "\n");
  fprintf(of, "lib/lib%s-parser.a: obj/%s-parser.o \\\n",
                parser_name, parser_name);
  fprintf(of, "		obj/%s-token.o \\\n", parser_name);
  fprintf(of, "		obj/%s-token-util.o\n", parser_name);
  fprintf(of, "	ar crD lib/lib%s-parser.a \\\n", parser_name);
  fprintf(of, "		obj/%s-parser.o \\\n", parser_name);
  fprintf(of, "		obj/%s-token.o \\\n", parser_name);
  fprintf(of, "		obj/%s-token-util.o\n", parser_name);
  fprintf(of, "\n");

  fprintf(of, "obj/%s-walker.o: src/%s-walker.c \\\n",
                parser_name, parser_name);
  fprintf(of, "\t\tinclude/%s-token.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-type.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-util.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-parser.h\n", parser_name);
  fprintf(of, "\t$(CC) $(CFLAGS_ALL) \\\n");
  fprintf(of, "\t\t-o obj/%s-walker.o \\\n", parser_name);
  fprintf(of, "\t\t-c src/%s-walker.c\n", parser_name);
  fprintf(of, "\n");

  fprintf(of, "obj/%s-parser.o: "
              "src/%s-parser.c \\\n",
                parser_name, parser_name);
  fprintf(of, "\t\tinclude/%s-parser.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-type.h\n", parser_name);
  fprintf(of, "\t$(CC) $(CFLAGS_ALL) -fPIC\\\n");
  fprintf(of, "\t\t-o obj/%s-parser.o \\\n", parser_name);
  fprintf(of, "\t\t-c src/%s-parser.c\n", parser_name);
  fprintf(of, "\n");

  fprintf(of, "obj/%s-token.o: "
              "src/%s-token.c \\\n",
                parser_name, parser_name);
  fprintf(of, "\t\tinclude/%s-token.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-type.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-util.h\n", parser_name);
  fprintf(of, "\t$(CC) $(CFLAGS_ALL) -fPIC\\\n");
  fprintf(of, "\t\t-o obj/%s-token.o \\\n", parser_name);
  fprintf(of, "\t\t-c src/%s-token.c\n", parser_name);
  fprintf(of, "\n");

  fprintf(of, "obj/%s-token-util.o: "
              "src/%s-token-util.c \\\n",
                parser_name, parser_name);
  fprintf(of, "\t\tinclude/%s-token.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-type.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-util.h\n", parser_name);
  fprintf(of, "\t$(CC) $(CFLAGS_ALL) -fPIC\\\n");
  fprintf(of, "\t\t-o obj/%s-token-util.o \\\n", parser_name);
  fprintf(of, "\t\t-c src/%s-token-util.c\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "clean:\n");
  fprintf(of, "\t@rm -f obj/*.o\n");
  fprintf(of, "\t@rm -f lib/*\n");
  fprintf(of, "\t@rm -f bin/%s-walker\n", parser_name);
  fprintf(of, "\n");

  return;
}

  /*!

     \brief Helper function for \e generate_parser_source function.
    
     This function is the highest level helper function for generating the
     parser for \<PROJECT\>.\n
     \n
     This function basically scans each individual phrase in the token tree
     of the parsed EGG file for \<PROJECT\>'s grammar and kicks off the
     subsequent calls to lower level generator functions.
    
     \warning This function is recursive.

     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)
     \param t           \e egg_token * containing the root token from which
                        the source code is generated
     \param level       the current indentation level for generated code

  */

static void generate_grammar(FILE *of,
                             char *parser_name,
                             egg_token *t,
                             int level)
{
  if (!t) return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  switch (t->type)
  {
    case egg_token_type_phrase:
      generate_phrase(of, parser_name, t);
      break;
    default:
      break;
  }

  generate_grammar(of, parser_name, t->descendant, level+1);

  generate_grammar(of, parser_name, t->next, level);

  return;
}

  /*!

     \brief Helper function for \e generate_parser_source function.
    
     This function parses a phrase token and generates the appropriate
     code for the phrase parsing function.\n
     \n
     A phrase consists of a phrase-name and a definition.  This function
     directly generates the source for the phrase parsing function pre-amble
     code, calls the subsequent definition code generating function, and then
     closes out the code for the phrase parsing function.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)
     \param t           \e egg_token * containing the phrase token from which
                        the source code is generated

  */

static void generate_phrase(FILE *of,
                            char *parser_name,
                            egg_token *t)
{
  egg_token *pn;
  egg_token *def;
  char *ds = NULL;

  if (!t)
    return;

  if (t->type != egg_token_type_phrase)
    return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  _pns = _pns_f = NULL;

  t = t->descendant;

  fprintf(of, "  /*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");
  fprintf(of, "    %s%sEGG Phrase Definition%s\n",
                (_use_doxygen) ? "\\par " : "",
                (_use_doxygen) ? "\"" : "",
                (_use_doxygen) ? "\"" : ":");
  if (_use_doxygen)
    fprintf(of, "    \\verbatim\n");
  ds = egg_token_to_string(t, ds);
  if (ds)
  {
    emit_phrase_comment_lines(of, ds);
    free(ds);
  }
  if (_use_doxygen)
    fprintf(of, "    \\endverbatim\n");
  fprintf(of, "\n");
  fprintf(of, "    %s %s%s_token *%s on synctactical match of phrase\n",
                (_use_doxygen) ? "\\retval" : "Returns:",
                (_use_doxygen) ? "\"" : "",
                parser_name,
                (_use_doxygen) ? "\"" : "");
  fprintf(of, "    %s NULL on error including NO MATCH\n",
                (_use_doxygen) ? "\\retval" : "        ");
  fprintf(of, "\n");
  fprintf(of, " */\n");
  fprintf(of, "\n");

  pn = egg_token_find(t, egg_token_type_phrase_name);
  if (pn)
  {
    _pns = egg_token_to_string(pn->descendant, _pns);
    if (_pns)
    {
      _pns_f = fix_identifier(strdup(_pns));

      fprintf(of, "%s_token *", parser_name);
      fprintf(of, "%s", _pns_f);
      fprintf(of, "(void)\n");
      fprintf(of, "{\n");
      fprintf(of, "  long pos = input_get_position();\n");
      fprintf(of, "  %s_token *nt, *t1, *t2;\n", parser_name);
      fprintf(of, "  int count;\n");
      fprintf(of, "  %s_token_direction dir;\n", parser_name);
      fprintf(of, "\n");
      fprintf(of, "  callback_by_index(&_cbt,\n"
                  "                    %d,\n"
                  "                    entry,\n"
                  "                    (void *)%s_token_type_%s);\n",
                    phrase_map_list_get_item_index(_pml, _pns),
                    parser_name, _pns_f);
      fprintf(of, "\n");
      fprintf(of, "  if (input_eof())\n");
      fprintf(of, "    return NULL;\n");
      fprintf(of, "\n");
      fprintf(of, "  count = 0;\n");
      fprintf(of, "\n");
      fprintf(of, "  nt = t1 = t2 = NULL;\n");
      fprintf(of, "\n");
      fprintf(of, "  nt = %s_token_new(%s_token_type_%s);\n",
                    parser_name, parser_name, _pns_f);
      fprintf(of, "  if (!nt)\n");
      fprintf(of, "  {\n");
      fprintf(of, "    callback_by_index(&_cbt,\n"
                  "                      %d,\n"
                  "                      fail,\n"
                  "                      (void *)%s_token_type_%s);\n",
                    phrase_map_list_get_item_index(_pml, _pns),
                    parser_name, _pns_f);
      fprintf(of, "    return NULL;\n");
      fprintf(of, "  }\n");
      fprintf(of, "\n");
      fprintf(of, "  t1 = nt;\n");
      fprintf(of, "\n");

      def = egg_token_find(t, egg_token_type_definition);
      generate_definition(of, parser_name, def);
    }
  }

  fprintf(of, "  callback_by_index(&_cbt,\n"
              "                    %d,\n"
              "                    fail,\n"
              "                    (void *)%s_token_type_%s);\n",
                phrase_map_list_get_item_index(_pml, _pns),
                parser_name, _pns_f);
  fprintf(of, "\n");

  fprintf(of, "  return NULL;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

  if (_pns)
    free(_pns);
  if (_pns_f)
    free(_pns_f);

  return;
}

  /*!

     \brief Helper function for \e generate_parser_source function.
    
     This function parses a definition token and generates the appropriate
     code for all contents of the phrase definition.\n
     \n
     A definition consists of a sequence of definition elements.  This function
     directly generates the source for the definition pre-amble code, calls the
     subsequent sequence code generating function, and then closes out the code
     for the definition.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)
     \param t           \e egg_token * containing the definition token from
                        which the source code is generated

  */

static void generate_definition(FILE *of,
                                char *parser_name,
                                egg_token *t)
{
  egg_token *seq;
  egg_token *cont;

  if (!t)
    return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  t = t->descendant;

  seq = egg_token_find(t, egg_token_type_sequence);
  if (seq)
  {
    emit_indent(of);
    fprintf(of, "  dir = %s_token_below;\n", parser_name);
    generate_sequence(of, parser_name, seq);
    fprintf(of, "\n");

    cont = seq->next;

    while (cont)
    {
      if (cont->type == egg_token_type_definition_continuation)
      {
        t = cont->descendant;
        seq = egg_token_find(t, egg_token_type_sequence);
        if (seq)
        {
          emit_indent(of);
          fprintf(of, "  dir = %s_token_below;\n", parser_name);
          generate_sequence(of, parser_name, seq);
          fprintf(of, "\n");
        }
      }
      cont = cont->next;
    }

    fprintf(of, "  %s_token_delete(nt);\n", parser_name);
    fprintf(of, "  input_set_position(pos);\n");
    fprintf(of, "\n");
  }

  return;
}

  /*!

     \brief Helper function for \e generate_parser_source function.
    
     This function parses a sequence token and generates the appropriate
     code for all contents of the sequence.\n
     \n
     A sequence consists of a list of grammar items.  This function calls
     the item generation function, and directly generates the source for the
     definition close-out code.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)
     \param t           \e egg_token * containing the sequence token from which
                        the source code is generated

  */

static void generate_sequence(FILE *of,
                              char *parser_name,
                              egg_token *t)
{
  egg_token *itm;
  egg_token *cont;
  int level_in = _current_level;

  if (!t)
    return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  t = t->descendant;

  itm = egg_token_find(t, egg_token_type_item);
  if (itm)
  {
    ++_current_level;

    generate_item(of, parser_name, itm);

    cont = itm->next;
    while (cont)
    {
      if (cont->type == egg_token_type_sequence_continuation)
      {
        t = cont->descendant;
        itm = egg_token_find(t, egg_token_type_item);
        if (itm)
        {
           ++_current_level;
           generate_item(of, parser_name, itm);
        }
      }
      cont = cont->next;
    }

    emit_indent(of);
    fprintf(of, "  callback_by_index(&_cbt,\n");
    emit_indent(of);
    fprintf(of, "                    %d,\n",
                  phrase_map_list_get_item_index(_pml, _pns));
    emit_indent(of);
    fprintf(of, "                    success,\n");
    emit_indent(of);
    fprintf(of, "                    (void *)%s_token_type_%s);\n",
                  parser_name, _pns_f);
    fprintf(of, "\n");
    emit_indent(of);
    fprintf(of, "  return nt;\n");

    while (_current_level > level_in)
    {
      emit_indent(of);
      fprintf(of, "}\n");
      --_current_level;
    }
  }

  _current_level = 0;

  return;
}

  /*!

     \brief Helper function for \e generate_parser_source function.
    
     This function parses an item token and generates the appropriate
     code for all contents of the item.\n
     \n
     An item consists of an atom which is possibly quantified.  This function
     directly generates the item and quantifier pre-amble code, calls the atom
     generation function, and directly generates the source for the
     item close-out code.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)
     \param t           \e egg_token * containing the item token from which
                        the source code is generated

  */

static void generate_item(FILE *of,
                          char *parser_name,
                          egg_token *t)
{
  egg_token *atm;
  egg_token *qty;
  int min = 1;
  int max = 1;

  if (!t)
    return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  t = t->descendant;

  atm = egg_token_find(t, egg_token_type_atom);
  if (atm)
  {
    qty = egg_token_find(atm->next, egg_token_type_quantifier);
    if (qty)
    {
      min = get_minimum(qty);
      max = get_maximum(qty);
      emit_indent(of);
      fprintf(of, "count=0;\n");
      if (max >= 0)
      {
        emit_indent(of);
        fprintf(of, "while(count < %d)\n", max);
      }
      else
      {
        emit_indent(of);
        fprintf(of, "while(true)\n");
      }
      emit_indent(of);
      fprintf(of, "{\n");
      ++_current_level;
    }
    generate_atom(of, parser_name, atm);
    if (qty)
    {
      --_current_level;
      emit_indent(of);
      fprintf(of, "    ++count;\n");
      emit_indent(of);
      fprintf(of, "  }\n");
      emit_indent(of);
      fprintf(of, "  else\n");
      emit_indent(of);
      fprintf(of, "    break;\n");
      emit_indent(of);
      fprintf(of, "}\n");
      if (max >= 0)
      {
        emit_indent(of);
        fprintf(of, "if ((count >= %d) && (count <= %d))\n", min, max);
      }
      else
      {
        emit_indent(of);
        fprintf(of, "if ((count >= %d))\n", min);
      }
      emit_indent(of);
      fprintf(of, "{\n");
    }
  }

  return;
}

  /*!

     \brief Helper function for \e generate_parser_source function.
    
     This function parses an atom token and generates the appropriate
     code for all contents of the atom.\n
     \n
     An atom contains either a literal or a phrase-name.  This function calls
     the appropriate code generation function for a literal or a phrase name.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)
     \param t           \e egg_token * containing the atom token from which
                        the source code is generated

  */

static void generate_atom(FILE *of,
                          char *parser_name,
                          egg_token *t)
{
  egg_token *lit;
  egg_token *pn;

  if (!t)
    return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  t = t->descendant;

  lit = egg_token_find(t, egg_token_type_literal);
  if (lit)
  {
    generate_literal(of, parser_name, lit);
  }
  else
  {
    pn = egg_token_find(t, egg_token_type_phrase_name);
    if (pn)
    {
      generate_phrase_name(of, parser_name, pn);
    }
  }

  return;
}

  /*!

     \brief Helper function for \e generate_parser_source function.
    
     This function parses a literal token and generates the appropriate
     code for all contents of the literal.\n
     \n
     An literal contains either a string or integer.  This function directly
     generates the code for all types of literals.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)
     \param t           \e egg_token * containing the literal token from which
                        the source code is generated

  */

static void generate_literal(FILE *of,
                             char *parser_name,
                             egg_token *t)
{
  egg_token *lit;
  char *s;
  char *s2;

  if (!t)
    return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  t = t->descendant;

  lit = egg_token_find(t, egg_token_type_absolute_literal);
  if (lit)
  {
    s = egg_token_to_string(lit->descendant, s = NULL);
    ++s;
    s[strlen(s)-1] = 0;
    emit_indent(of);
    fprintf(of, "if ((input_byte()) == %s)\n", s);
    emit_indent(of);
    fprintf(of, "{\n");
    free(s-1);
    return;
  }

  lit = egg_token_find(t, egg_token_type_quoted_literal);
  if (lit)
  {
    s = egg_token_to_string(lit->descendant, s = NULL);
    ++s;
    s[strlen(s)-1] = 0;
    emit_indent(of);
    fprintf(of, "for (s = \"%s\"; *s && ((input_byte()) == *s); ++s) ;\n", s);
    emit_indent(of);
    fprintf(of, "if (!*s)\n");
    emit_indent(of);
    fprintf(of, "{\n");
    free(s-1);
    return;
  }

  lit = egg_token_find(t, egg_token_type_single_quoted_literal);
  if (lit)
  {
    s = egg_token_to_string(lit->descendant, s = NULL);
    ++s;
    s[strlen(s)-1] = 0;
    s2 = fix_quotes(s);
    emit_indent(of);
    fprintf(of, "for (s = \"%s\"; *s && ((input_byte()) == *s); ++s) ;\n", s2);
    emit_indent(of);
    fprintf(of, "if (!*s)\n");
    emit_indent(of);
    fprintf(of, "{\n");
    free(s-1);
    free(s2);
    return;
  }

  return;
}

  /*!

     \brief Helper function for \e generate_parser_source function.
    
     This function parses a phrase-name token and generates the appropriate
     code for all contents of the phrase-name.\n
     \n
     A phrase-name contains is a literal EGG grammer name of a phrase.  This
     function directly generates the code for a phrase-name.
    
     \param of          FILE * of open output file to write source code
     \param parser_name string containing name of parser (ie. \<PROJECT\>)
     \param t           \e egg_token * containing the phrase-name token from
                        which the source code is generated

  */

static void generate_phrase_name(FILE *of, char *parser_name, egg_token *t)
{
  char *pns = NULL;

  if (!t)
    return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  t = t->descendant;

  pns = egg_token_to_string(t, pns);
  pns = fix_identifier(pns);

  if (pns)
  {
    emit_indent(of);
    fprintf(of, "if (%s_token_add(t1, dir, t2 = %s()))\n",
                  parser_name, pns);
    emit_indent(of);
    fprintf(of, "{\n");
    emit_indent(of);
    fprintf(of, "  dir = %s_token_after;\n", parser_name);
    emit_indent(of);
    fprintf(of, "  t1 = t2;\n");

    free(pns);
  }

  return;
}

  /*!

     \brief Helper function for \e generate_parser_source function.
    
     This function finds the minimum range value in a quantifier.
    
     \param t           \e egg_token * containing the quantifier token

     \retval int value of quantifier range minimum
             1   on any error

  */

static int get_minimum(egg_token *t)
{
  egg_token *in;
  char *ins = NULL;
  int i;

  if (!t)
    return 1;

  if (t->type != egg_token_type_quantifier)
    return 1;

  in = egg_token_find(t->descendant, egg_token_type_integer);
  if (in)
  {
    ins = egg_token_to_string(in->descendant, ins);
    if (ins)
    {
      i = atoi(ins);
      free(ins);
      return i;
    }
  }

  return 1;
}

  /*!

     \brief Helper function for \e generate_parser_source function.
    
     This function finds the maximum range value in a quantifier.
    
     \param t           \e egg_token * containing the quantifier token

     \retval int value of quantifier range maximum
             -1  when range maximum is unlimited (ie. asterisk)
              1  on any error

  */

static int get_maximum(egg_token *t)
{
  egg_token *opt;
  egg_token *in;
  egg_token *as;
  char *ins = NULL;
  int min = 1;
  int i;

  if (!t)
    return 1;

  if (t->type != egg_token_type_quantifier)
    return 1;

  min = get_minimum(t);

  opt = egg_token_find(t->descendant, egg_token_type_quantifier_option);
  if (opt)
  {
    in = egg_token_find(opt->descendant, egg_token_type_integer);
    if (in)
    {
      ins = egg_token_to_string(in->descendant, ins);
      if (ins)
      {
        i = atoi(ins);
        free(ins);
        return i;
      }
    }
    else
    {
      as = egg_token_find(opt->descendant, egg_token_type_asterisk);
      if (as)
        return -1;
    }
  }
  else
    return min;

  return 1;
}

  /*!

     \brief Generic helper function for code generation functions.
    
     This function converts all EGG grammar identifiers (ie. phrase-name) to
     C language identifiers.  Specifically all '-' (minus) characters are
     converted to '_' (underscore) characters.
    
     \param pn string containing EGG phrase-name
    
     \retval "char *" string containing C language equivalent identifier

  */

static char *fix_identifier(char *pn)
{
  char *t;

  if (!pn)
    return NULL;

  t = pn;

  while (*t)
  {
    if (*t == '-')
      *t = '_';
    ++t;
  }

  return pn;
}

  /*!

     \brief Generic helper function for code generation functions.
    
     This function converts all EGG grammar quoted literals to C language
     compatible strings.  All single-quoted-literals are converted to double
     quoted strings, including preceding any double-quotes contained within
     the single-quoted-literal with a C string '\' (backslash) character.
    
     \warning This function returns a pointer to dynamically allocated memory.
              It is the caller's responsibility to free this memory when
              appropriate.

     \param s string containing single quoted literal
    
     \retval "char *" string containing C language compatible double quoted
                      string

  */

static char *fix_quotes(char *s)
{
  char *t;
  char *n;
  int nq = 0;

  if (!s)
    return NULL;

  for (t = s; *t; t++)
    if (*t == '"')
      ++nq;

  n = malloc(strlen(s) + nq + 1);

  for (t = n; *s; ++s, ++t)
  {
    if (*s == '"')
    {
      *t = '\\';
      ++t;
    }
    *t = *s;
  }

  *t = 0;

  return n;
}

  /*!

     \brief Generic helper function for code generation functions.
    
     This function builds a C language compatible literal value.
    
     \warning This function returns a pointer to dynamically allocated memory.
              It is the caller's responsibility to free this memory when
              appropriate.

     \param t           \e egg_token * containing the literal token

     \retval "char *" string containing the C language literal code.
             NULL     on any error

  */

static char *build_literal(egg_token *t)
{
  char *s = NULL;
  char *sp1, *sp2;
  egg_token *tm;
  long l;

  if (!t)
    return NULL;

  if (t->type != egg_token_type_literal)
    return NULL;

  tm = egg_token_find(t->descendant, egg_token_type_absolute_literal);
  if (tm)
  {
    tm = egg_token_find(tm->descendant, egg_token_type_integer);
    if (tm)
    {
      s = egg_token_to_string(tm->descendant, s);

      switch (tm->descendant->type)
      {
        case egg_token_type_binary_integer:
          l = strtol(s+2, NULL, 2);
          break;
        case egg_token_type_octal_integer:
          l = strtol(s+2, NULL, 8);
          break;
        case egg_token_type_hexadecimal_integer:
          l = strtol(s+2, NULL, 16);
          break;
        case egg_token_type_decimal_integer:
        default:
          l = strtol(s, NULL, 10);
          break;
      }

      free(s);

      s = long_to_bytes(l);

      return s;
    }

    return NULL;
  }

  tm = egg_token_find(t->descendant, egg_token_type_quoted_literal);
  if (tm)
  {
    s = egg_token_to_string(tm->descendant, s);
    for (sp1 = s+1, sp2 = s; *sp1; ++sp2, ++sp1)
      *sp2 = *sp1; 
    *(strchr(s, '"')) = 0;
    return s;
  }

  tm = egg_token_find(t->descendant, egg_token_type_single_quoted_literal);
  if (tm)
  {
    s = egg_token_to_string(tm->descendant, s);
    for (sp1 = s+1, sp2 = s; *sp1; ++sp2, ++sp1)
      *sp2 = *sp1; 
    *(strchr(s, '\'')) = 0;
    sp1 = fix_quotes(s);
    free(s);
    return sp1;
  }

  return NULL;
}

  /*!

     \brief Generic helper function for code generation functions.
    
     This function converts all alpha characters in a string to upper case.
    
     \warning This function modifies the passed string, therefore a copy must be
              made by the caller if the original string contents are to be
              preserved.

     \param s string

     \retval "char *" string with all upper case alpha characters
             NULL     on any error

  */

static char *str_toupper(char *s)
{
  char *t = s;

  if (!s)
    return NULL;

  while (*t)
  {
    *t = toupper(*t);
    ++t;
  }

  return s;
}

  /*!

     \brief Helper function for \e generate_token_util_source function.
    
     This function determines if a given phrase contains only literals.  If so,
     then a C language compatible literal is returned, else a C language
     compatible string containing a phrase's phrase-name is returned.
    
     \param t           \e egg_token * containing the phrase token

     \retval "char *" string containing either literal or phrase name in C
                      language compatible form
     \retval NULL     on any error

  */

static char *literal_or_phrase_name(egg_token *t)
{
  egg_token *pn;
  egg_token *def;
  egg_token *tm;
  char *pns;

  if (!t)
    return NULL;

  if (t->type != egg_token_type_phrase)
    return NULL;

  pn = egg_token_find(t->descendant, egg_token_type_phrase_name);
  if (!pn)
    return NULL;

  def = egg_token_find(t->descendant, egg_token_type_definition);
  if (!def)
    return NULL;

  if (!(tm = egg_token_find(def->descendant, egg_token_type_definition_continuation)))
  {
    tm = egg_token_find(def->descendant, egg_token_type_sequence);
    if (tm)
    {
      if (!egg_token_find(tm->descendant, egg_token_type_sequence_continuation))
      {
        tm = egg_token_find(tm->descendant, egg_token_type_item);
        if (tm)
        {
          if (!egg_token_find(tm->next, egg_token_type_quantifier))
          {
            tm = egg_token_find(tm->descendant, egg_token_type_literal);
            if (tm)
              return build_literal(tm);
          }
        }
      }
    }
  }

  pns = NULL;
  return egg_token_to_string(pn->descendant, pns);
}

  /*!

     \brief Generic helper function for code generation functions.
    
     This function any long to a C language compatible hexadecimal literal.
    
     \warning This function returns a pointer to dynamically allocated memory.
              It is the caller's responsibility to free this memory when
              appropriate.

     \param l long to convert

     \retval "char *" string containing C language compatible hexadecimal
                      literal

  */

static char *long_to_bytes(unsigned long l)
{
  char *s = NULL;
  char hex[3];
  unsigned char bytes[sizeof(long)];
  int i;

  for (i = 0, bytes[0] = l % 0x100, l /= 0x100; l; l /= 0x100)
    bytes[++i] = l % 0x100;

  for (; i >= 0; --i)
  {
    s = strapp(s, "\\x");
    sprintf(hex, "%02x", bytes[i]);
    s = strapp(s, hex);
  }

  return s;
}

  /*!

     \brief Generic helper function for code generation functions.
    
     This function the current year as an integer
    
     \retval int current year

  */

int get_year(void)
{
  time_t now;
  struct tm *stm;

  now = time(NULL);
  stm = localtime(&now);

  return stm->tm_year + 1900;
}

  /*!

     \brief Generic helper function for code generation functions.
    
     This emits an appropriate number of spaces to an open output file based
     on value in global \e _current_level variable.
    
     \param of file * to open file for writing

  */

static void emit_indent(FILE *of)
{
  int i;

  if (!of)
    return;

  for (i = 0; i < _current_level; i++)
    fprintf(of, "  ");

  return;
}

  /*!

     \brief Generic helper function for code generation functions.
    
     This function emits a comment string adorned with a 4 space indentation
     preceeding each line.
    
     \param of file * to open file for writing
     \param s  string containing unadorned comment string

  */

static void emit_phrase_comment_lines(FILE *of, char *s)
{
  char *t = s;

  if (!of)
    return;

  if (!s)
    return;

  while (*s)
  {
    while (*t && (*t != '\n'))
      ++t;
    if (!*t)
      break;
    *t = 0;
    fprintf(of, "    %s\n", s);
    s = t+1;
    t = s;
  }

  fprintf(of, "    %s\n", s);

  return;
}

  /*!
     \brief Get doxygen use flag from code generator.
     \retval boolean doxygen use flag
  */

boolean generator_get_doxygen_flag(void)
{
  return _use_doxygen;
}

  /*!
     \brief Set doxygen use flag for code generator.
     \param flag true or false
  */

void generator_set_doxygen_flag(boolean flag)
{
  _use_doxygen = flag;
}

  /*!
     \brief Get current file name for code documenation from code generator.
     \retval "char *" string containing current file name
  */

char * generator_get_file_name(void)
{
  return _file_name;
}

  /*!
     \brief Set file name for code documenation for code generator.
     \param file_name string containing file name for generated code documents
  */

void generator_set_file_name(char *file_name)
{
  _file_name = file_name;
}

  /*!
     \brief Get current project brief name for code documentation from code
            generator.
     \retval "char *" string containing current project brief name
  */

char * generator_get_project_brief(void)
{
  return _project_brief;
}

  /*!
     \brief Set brief project name for code documenation for code generator.
     \param brief string containing brief project name
  */

void generator_set_project_brief(char *brief)
{
  _project_brief = brief;
}

  /*!
     \brief Get current version for code documention from code generator.
     \retval "char *" string containing current version
  */

char * generator_get_version(void)
{
  return _version;
}

  /*!
     \brief Set version for code documenation for code generator.
     \param version string containing version
  */

void generator_set_version(char *version)
{
  _version = version;
}

  /*!
     \brief Get current author for code documention from code generator.
     \retval "char *" string containing current author
  */

char * generator_get_author(void)
{
  return _author;
}

  /*!
     \brief Set author for code documenation for code generator.
     \param author string containing author
  */

void generator_set_author(char *author)
{
  _author = author;
}

  /*!
     \brief Get current email for code documention from code generator.
     \retval "char *" string containing current email
  */

char * generator_get_email(void)
{
  return _email;
}

  /*!
     \brief Set email for code documenation for code generator.
     \param email string containing email address of author
  */

void generator_set_email(char *email)
{
  _email = email;
}

  /*!
     \brief Get current first copyright year for code documention from code
            generator.
     \retval int first year used for copyright range
  */

int generator_get_first_year(void)
{
  return _first_year;
}

  /*!
     \brief Set first copyright year for code documenation for code generator.
     \param year integer first copyright year
  */

void generator_set_first_year(int year)
{
  _first_year = year;
}

  /*!
     \brief Get current license text for code documention from code generator.
     \note The current license text depends on the doxygen use flag.
           There are two complete license texts used by the code generator.
           One for doxygen markup, and one for plain text.
     \retval "char *" string containing current license text
  */

char * generator_get_license(void)
{
  if (_use_doxygen)
    return _license_with_doxygen;
  else
    return _license;
}

  /*!
     \brief Set license text for code documenation for code generator.
     \param license string containing license text
  */

void generator_set_license(char *license)
{
  if (_use_doxygen)
    _license_with_doxygen = license;
  else
    _license = license;
}

  /*!

     \brief Generic helper function for code generation functions.
    
     This functions emits a source code file level comment block which
     describes the source code file itself.  The comment block contains:
       - The base file name of the source code file (no default)
       - The a brief description of the source code file
         (default uses the base file name)
       - The version of the source code file (default is "0")
       - The name of the author of the source code file. (default is "Unknown")
       - The email address of the author (default is \<none\>)
       - The copyright notice (default uses current year and author)
       - The license that applies to the source code file (default is GNU)

     \param of FILE * to open file for writing

  */

static void emit_source_comment_header(FILE *of)
{
  if (!of)
    of = stdout;

    // open comment block
  fprintf(of, "/*%s\n", (_use_doxygen) ? "!" : "");
  fprintf(of, "\n");

    // emit file name
  fprintf(of, "  %s%s\n", (_use_doxygen) ? "\\file " : "", _file_name);
  fprintf(of, "\n");

    // emit brief description
  fprintf(of, "  %sSource code for %s\n",
                (_use_doxygen) ? "\\brief " : "",
                (_project_brief && strlen(_project_brief))
                  ? _project_brief
                  : _file_name);
  fprintf(of, "\n");

    // emit version
  fprintf(of, "  %s%s\n",
                (_use_doxygen) ? "\\version " : "Version: ",
                (_version) ? _version : "0");
  fprintf(of, "\n");

    // emit author
  fprintf(of, "  %s%s%s%s\n",
                (_use_doxygen) ? "\\author " : "Author: ",
                (_author) ? _author : "Unknown",
                (_email && strlen(_email)) ? " mailto:": "",
                (_email) ? _email : "");
  fprintf(of, "\n");

    // emit author
  if (_first_year != get_year())
    fprintf(of, "  %sCopyright (C) %4.4d-%4.4d %s\n",
                  (_use_doxygen) ? "\\copyright " : "",
                  _first_year,
                  get_year(),
                  _author);
  else
    fprintf(of, "  %sCopyright (C) %4.4d %s\n",
                  (_use_doxygen) ? "\\copyright " : "",
                  _first_year,
                  _author);
  fprintf(of, "\n");

    // emit license
  fprintf(of, "  %s\n", (_use_doxygen) ? _license_with_doxygen : _license);
  fprintf(of, "\n");

    // close comment block
  fprintf(of, "*/\n");
  fprintf(of, "\n");

  return;
}

  /*!

     \brief Generic helper function for code generation functions.
    
     This function creates a file name for the file comment block.

     \warning This file returns a pointer to dynamically allocated memory.  It
              is the caller's responsibility to free this memory when
              appropriate.

     \param project string containing desired prepended project name
     \param file_name string containing rest of file name

     \retval "char *" string containing full file name for comment block

  */

static char * make_file_name(char *project, char *file_name)
{
  char *fn;

  if (!project)
    return NULL;

  if (!file_name)
    return NULL;

  fn = (char *)malloc(strlen(file_name) + strlen(project) + 2);
  if (!fn)
    return NULL;

  sprintf(fn, "%s-%s", project, file_name);

  return fn;
}

