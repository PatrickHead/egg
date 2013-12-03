/*
    generator.c
    Copyright (C) 2013  Patrick Head

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "egg-token.h"
#include "egg-token-util.h"
#include "strapp.h"
#include "map.h"

#include "generator.h"

static void generate_grammar(FILE *of, char *parser_name, egg_token *t, int level);
static void generate_phrase(FILE *of, char *parser_name, egg_token *t);
static void generate_definition(FILE *of, char *parser_name, egg_token *t);
static void generate_sequence(FILE *of, char *parser_name, egg_token *t);
static void generate_item(FILE *of, char *parser_name, egg_token *t);
static void generate_atom(FILE *of, char *parser_name, egg_token *t);
static void generate_literal(FILE *of, char *parser_name, egg_token *t);
static void generate_phrase_name(FILE *of, char *parser_name, egg_token *t);
static int get_minimum(egg_token *t);
static int get_maximum(egg_token *t);
static char *fix_identifier(char *pn);
static char *fix_quotes(char *s);
static char *str_toupper(char *s);
static char *build_literal(egg_token *t);
static char *literal_or_phrase_name(egg_token *t);
static char *long_to_bytes(unsigned long l);
static char *get_year(void);
static void emit_indent(FILE *of);
static void emit_comment_string(FILE *of, char *s);
static void emit_gnu_license(FILE *of);
void isolate_top_level_phrases(phrase_map_item **pmi);

void generate_parser_source(FILE *of, char *parser_name, egg_token *t)
{
  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  if (!t)
    return;

  fprintf(of, "/*\n");
  fprintf(of, "    %s-parser.c\n", parser_name);
  emit_gnu_license(of);
  fprintf(of, "\n");

  fprintf(of, "#include <stdlib.h>\n");
  fprintf(of, "\n");
  fprintf(of, "#include \"input.h\"\n");
  fprintf(of, "\n");
  fprintf(of, "#include \"%s-token.h\"\n", parser_name);
  fprintf(of, "#include \"%s-parser.h\"\n", parser_name);
  fprintf(of, "\n");

  generate_grammar(of, parser_name, t, 0);

  return;
}

void generate_parser_header(FILE *of, char *parser_name, egg_token *t)
{
  egg_token *ge, *p, *pn;
  char *hn;
  int hnl;
  char *pns;

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  if (!t)
    return;

  hnl = strlen(parser_name) + strlen("_parser_h") + 1;
  hn = malloc(hnl);
  memset(hn, 0, hnl);

  sprintf(hn, "%s_parser_h", parser_name);

  hn = str_toupper(hn);

  fprintf(of, "/*\n");
  fprintf(of, "    %s-parser.h\n", parser_name);
  emit_gnu_license(of);
  fprintf(of, "\n");

  fprintf(of, "#ifndef %s\n", hn);
  fprintf(of, "#define %s\n", hn);
  fprintf(of, "\n");

  if ((ge = egg_token_find(t->d, egg_token_type_grammar_element)))
  {
    while (ge)
    {
      if ((p = egg_token_find(ge->d, egg_token_type_phrase)))
      {
        if ((pn = egg_token_find(p->d, egg_token_type_phrase_name)))
        {
          pns = NULL;
          pns = egg_token_to_string(pn->d, pns);
          pns = fix_identifier(pns);

          fprintf(of, "%s_token *%s(void);\n",
                        parser_name, pns);

          free(pns);
        }
      }
      ge = ge->n;
    }
  }

  fprintf(of, "\n");
  fprintf(of, "#endif // %s\n", hn);

  free(hn);

  return;
}

void generate_token_header(FILE *of, char *parser_name)
{
  char *u_parser_name;

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  u_parser_name = str_toupper(strdup(parser_name));

  fprintf(of, "/*\n");
  fprintf(of, "    %s-token.h\n", parser_name);
  emit_gnu_license(of);
  fprintf(of, "\n");

  fprintf(of, "#ifndef %s_TOKEN_H\n", u_parser_name);
  fprintf(of, "#define %s_TOKEN_H\n", u_parser_name);
  fprintf(of, "\n");
  fprintf(of, "#include \"common.h\"\n");
  fprintf(of, "#include \"input.h\"\n");
  fprintf(of, "\n");
  fprintf(of, "  /*\n");
  fprintf(of, "   * Enumeration defining allowable values for %s_token_type\n",
                parser_name);
  fprintf(of, "   */\n");
  fprintf(of, "\n");
  fprintf(of, "#include \"%s-token-type.h\"\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "  /*\n");
  fprintf(of, "   * Enumeration defining direction for %s_token_add\n",
                parser_name);
  fprintf(of, "   * function.\n");
  fprintf(of, "   */\n");
  fprintf(of, "\n");
  fprintf(of, "typedef enum\n");
  fprintf(of, "{\n");
  fprintf(of, "  %s_token_before,\n", parser_name);
  fprintf(of, "  %s_token_after,\n", parser_name);
  fprintf(of, "  %s_token_below\n", parser_name);
  fprintf(of, "} %s_token_direction;\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "  /*\n");
  fprintf(of, "   * Definition of a %s_token\n", parser_name);
  fprintf(of, "   */\n");
  fprintf(of, "\n");
  fprintf(of, "typedef struct %s_token\n", parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  %s_token_type t;\n", parser_name);
  fprintf(of, "  struct %s_token *a;  // ascendant\n", parser_name);
  fprintf(of, "  struct %s_token *d;  // descendant\n", parser_name);
  fprintf(of, "  struct %s_token *p;  // previous\n", parser_name);
  fprintf(of, "  struct %s_token *n;  // next\n", parser_name);
  fprintf(of, "  input_location loc;  // line,offset\n");
  fprintf(of, "} %s_token;\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "  /*\n");
  fprintf(of, "   * Function prototypes\n");
  fprintf(of, "   */\n");
  fprintf(of, "\n");
  fprintf(of, "%s_token *%s_token_new(%s_token_type type);\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "void %s_token_free(%s_token *t);\n",
                parser_name, parser_name);
  fprintf(of, "\n");
  fprintf(of, "boolean %s_token_add(%s_token *t,\n",
                parser_name, parser_name);
  fprintf(of, "  %s_token_direction dir,\n", parser_name);
  fprintf(of, "  %s_token *n);\n", parser_name);
  fprintf(of, "void %s_token_delete(%s_token *t);\n",
                parser_name, parser_name);
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
  fprintf(of, "%s_token *%s_token_find(%s_token *t, %s_token_type type);\n",
                parser_name, parser_name, parser_name, parser_name);
  fprintf(of, "char *%s_token_to_string(%s_token *t, char *s);\n",
                parser_name, parser_name);
  fprintf(of, "\n");
  fprintf(of, "#endif // %s_TOKEN_H\n", u_parser_name);

  free(u_parser_name);

  return;
}

void generate_token_source(FILE *of, char *parser_name)
{
  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  fprintf(of, "/*\n");
  fprintf(of, "    %s-token.c\n", parser_name);
  emit_gnu_license(of);
  fprintf(of, "\n");

  fprintf(of, "#include <stdlib.h>\n");
  fprintf(of, "#include <string.h>\n");
  fprintf(of, "\n");
  fprintf(of, "#include \"strapp.h\"\n");
  fprintf(of, "\n");
  fprintf(of, "#include \"%s-token.h\"\n", parser_name);
  fprintf(of, "#include \"%s-token-util.h\"\n", parser_name);
  fprintf(of, "\n");
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
  fprintf(of, "  new->t = type;\n");
  fprintf(of, "\n");
  fprintf(of, "  input_get_location(&(new->loc));\n");
  fprintf(of, "\n");
  fprintf(of, "  return new;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
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
  fprintf(of, "      n->p = t->p;\n");
  fprintf(of, "      n->n = t;\n");
  fprintf(of, "      if (t->p)\n");
  fprintf(of, "        t->p->n = n;\n");
  fprintf(of, "      t->p = n;\n");
  fprintf(of, "      n->a = t->a;\n");
  fprintf(of, "\n");
  fprintf(of, "        // Fix ascendant's descendant pointer, if it is t.\n");
  fprintf(of, "        // We always want the ascendant's descendent pointer to point to\n");
  fprintf(of, "        //   the beginning of the list of descendents.\n");
  fprintf(of, "\n");
  fprintf(of, "      if (t->a)\n");
  fprintf(of, "        if (t->a->d == t)\n");
  fprintf(of, "          t->a->d = n;\n");
  fprintf(of, "\n");
  fprintf(of, "      break;\n");
  fprintf(of, "\n");
  fprintf(of, "    case %s_token_after:\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "      n->p = t;\n");
  fprintf(of, "      n->n = t->n;\n");
  fprintf(of, "      if (t->n)\n");
  fprintf(of, "        t->n->p = n;\n");
  fprintf(of, "      t->n = n;\n");
  fprintf(of, "      n->a = t->a;\n");
  fprintf(of, "\n");
  fprintf(of, "      break;\n");
  fprintf(of, "\n");
  fprintf(of, "    case %s_token_below:\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "      if (t->d)\n");
  fprintf(of, "        return false;\n");
  fprintf(of, "      t->d = n;\n");
  fprintf(of, "      n->a = t;\n");
  fprintf(of, "\n");
  fprintf(of, "      break;\n");
  fprintf(of, "  }\n");
  fprintf(of, "\n");
  fprintf(of, "  return true;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
  fprintf(of, "void %s_token_delete(%s_token *t)\n",
                parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  while (t->d)\n");
  fprintf(of, "    %s_token_delete(t->d);\n",
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
  fprintf(of, "void %s_token_unlink(%s_token *t)\n",
                parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  if (t->a)\n");
  fprintf(of, "    if (t->a->d == t)\n");
  fprintf(of, "      t->a->d = t->n;\n");
  fprintf(of, "\n");
  fprintf(of, "  if (t->p)\n");
  fprintf(of, "    t->p->n = t->n;\n");
  fprintf(of, "\n");
  fprintf(of, "  if (t->n)\n");
  fprintf(of, "    t->n->p = t->p;\n");
  fprintf(of, "\n");
  fprintf(of, "  return;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
  fprintf(of, "%s_token_type %s_token_get_type(%s_token *t)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return %s_token_type_none;\n",
                parser_name);
  fprintf(of, "\n");
  fprintf(of, "  return t->t;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
  fprintf(of, "void %s_token_set_type(%s_token *t, %s_token_type type)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  t->t = type;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
  fprintf(of, "%s_token *%s_token_get_ascendant(%s_token *t)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return NULL;\n");
  fprintf(of, "\n");
  fprintf(of, "  return t->a;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
  fprintf(of, "void %s_token_set_ascendant(%s_token *t, %s_token *a)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  t->a = a;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
  fprintf(of, "%s_token *%s_token_get_descendant(%s_token *t)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return NULL;\n");
  fprintf(of, "\n");
  fprintf(of, "  return t->d;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
  fprintf(of, "void %s_token_set_descendant(%s_token *t, %s_token *d)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  t->d = d;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
  fprintf(of, "%s_token *%s_token_get_previous(%s_token *t)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return NULL;\n");
  fprintf(of, "\n");
  fprintf(of, "  return t->p;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
  fprintf(of, "void %s_token_set_previous(%s_token *t, %s_token *p)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  t->p = p;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
  fprintf(of, "%s_token *%s_token_get_next(%s_token *t)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return NULL;\n");
  fprintf(of, "\n");
  fprintf(of, "  return t->n;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
  fprintf(of, "void %s_token_set_next(%s_token *t, %s_token *n)\n",
                parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  t->n = n;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
  fprintf(of, "%s_token *%s_token_find(%s_token *t, %s_token_type type)\n",
                parser_name, parser_name, parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  %s_token *f;\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return NULL;\n");
  fprintf(of, "\n");
  fprintf(of, "  if (t->t == type)\n");
  fprintf(of, "    return t;\n");
  fprintf(of, "\n");
  fprintf(of, "  f = %s_token_find(t->d, type);\n", parser_name);
  fprintf(of, "  if (f)\n");
  fprintf(of, "    return f;\n");
  fprintf(of, "\n");
  fprintf(of, "  f = %s_token_find(t->n, type);\n", parser_name);
  fprintf(of, "  if (f)\n");
  fprintf(of, "    return f;\n");
  fprintf(of, "\n");
  fprintf(of, "  return NULL;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");
  fprintf(of, "char *%s_token_to_string(%s_token *t, char *s)\n",
               parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return s;\n");
  fprintf(of, "\n");
  fprintf(of, "  if (!t->d)\n");
  fprintf(of, "    s = strapp(s , %s_token_type_to_string(t));\n", parser_name);
  fprintf(of, "  else\n");
  fprintf(of, "    s = %s_token_to_string(t->d, s);\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "  s = %s_token_to_string(t->n, s);\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "  return s;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

  return;
}

void generate_token_type_header(FILE *of, char *parser_name, egg_token *t)
{
  egg_token *ge, *p, *pn;
  char *hn;
  int hnl;
  char *pns;

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  if (!t)
    return;

  hnl = strlen(parser_name) + strlen("_token_type_h") + 1;
  hn = malloc(hnl);
  memset(hn, 0, hnl);

  sprintf(hn, "%s_token_type_h", parser_name);

  hn = str_toupper(hn);

  fprintf(of, "/*\n");
  fprintf(of, "    %s-token-type.h\n", parser_name);
  emit_gnu_license(of);
  fprintf(of, "\n");

  fprintf(of, "#ifndef %s\n", hn);
  fprintf(of, "#define %s\n", hn);
  fprintf(of, "\n");
  fprintf(of, "typedef enum\n");
  fprintf(of, "{\n");

  if ((ge = egg_token_find(t->d, egg_token_type_grammar_element)))
  {
    fprintf(of, "  %s_token_type_none%s\n",
                  parser_name,
                  ge->n ? "," : "");

    while (ge)
    {
      if ((p = egg_token_find(ge->d, egg_token_type_phrase)))
      {
        if ((pn = egg_token_find(p->d, egg_token_type_phrase_name)))
        {
          pns = NULL;
          pns = egg_token_to_string(pn->d, pns);
          pns = fix_identifier(pns);

          fprintf(of, "  %s_token_type_%s%s\n",
                        parser_name,
                        pns,
                        ge->n ? "," : ""
                 );

          free(pns);
        }
      }
      ge = ge->n;
    }
  }

  fprintf(of, "} %s_token_type;\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "#endif // %s\n", hn);

  free(hn);

  return;
}

void generate_token_util_source(FILE *of, char *parser_name, egg_token *t)
{
  egg_token *ge, *p, *pn;
  char *pns;
  char *val;

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  if (!t)
    return;

  fprintf(of, "/*\n");
  fprintf(of, "    %s-token-util.c\n", parser_name);
  emit_gnu_license(of);
  fprintf(of, "\n");

  fprintf(of, "#include <stdlib.h>\n");
  fprintf(of, "#include <string.h>\n");
  fprintf(of, "\n");
  fprintf(of, "#include \"%s-token.h\"\n", parser_name);
  fprintf(of, "#include \"%s-token-util.h\"\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "char *%s_token_type_to_string(%s_token *t)\n",
                parser_name, parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  char *s;\n");
  fprintf(of, "\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return NULL;\n");
  fprintf(of, "\n");
  fprintf(of, "  switch (t->t)\n");
  fprintf(of, "  {\n");
  fprintf(of, "    case %s_token_type_none:\n", parser_name);
  fprintf(of, "      s = \"<none>\";\n");
  fprintf(of, "      break;\n");

  if ((ge = egg_token_find(t->d, egg_token_type_grammar_element)))
  {

    while (ge)
    {
      if ((p = egg_token_find(ge->d, egg_token_type_phrase)))
      {
        if ((pn = egg_token_find(p->d, egg_token_type_phrase_name)))
        {
          pns = NULL;
          pns = egg_token_to_string(pn->d, pns);
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
      ge = ge->n;
    }
  }

  fprintf(of, "  }\n");
  fprintf(of, "\n");
  fprintf(of, "  return s;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

  return;
}

void generate_token_util_header(FILE *of, char *parser_name, egg_token *t)
{
  char *hn;
  int hnl;

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  if (!t)
    return;

  hnl = strlen(parser_name) + strlen("_token_util_h") + 1;
  hn = malloc(hnl);
  memset(hn, 0, hnl);

  sprintf(hn, "%s_token_util_h", parser_name);

  hn = str_toupper(hn);

  fprintf(of, "/*\n");
  fprintf(of, "    %s-token-util.h\n", parser_name);
  emit_gnu_license(of);
  fprintf(of, "\n");

  fprintf(of, "#ifndef %s\n", hn);
  fprintf(of, "#define %s\n", hn);
  fprintf(of, "\n");

  fprintf(of, "char *%s_token_type_to_string(%s_token *t);\n",
                parser_name, parser_name);

  fprintf(of, "\n");
  fprintf(of, "#endif // %s\n", hn);

  free(hn);

  return;
}

void generate_walker_source(FILE *of, char *parser_name, egg_token *t)
{
  phrase_map_item *pml;
  phrase_map_item *pmi;
  char *phrase_name;
  int opt_count = 0;

  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  if (!t)
    return;

  pml = phrase_map(t);
  isolate_top_level_phrases(&pml);

  fprintf(of, "/*\n");
  fprintf(of, "    %s-walker.c\n", parser_name);
  emit_gnu_license(of);
  fprintf(of, "\n");

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
  fprintf(of, "void usage(char *program_name);\n");
  fprintf(of, "void walk(%s_token *t, int level);\n", parser_name);
  fprintf(of, "\n");
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
    fprintf(of, "  boolean walk_%s;\n", phrase_name);
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
  fprintf(of, "void usage(char *program_name)\n");
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
  fprintf(of, "void walk(%s_token *t, int level)\n", parser_name);
  fprintf(of, "{\n");
  fprintf(of, "  if (!t)\n");
  fprintf(of, "    return;\n");
  fprintf(of, "\n");
  fprintf(of, "  printf(\"%%*.*s%%s@%%d.%%d\\n\", level, level, \" \", "
              "%s_token_type_to_string(t), "
              "t->loc.line_number, "
              "t->loc.character_offset);\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "  walk(t->d, level+1);\n");
  fprintf(of, "\n");
  fprintf(of, "  walk(t->n, level);\n");
  fprintf(of, "\n");
  fprintf(of, "  return;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

  return;
}

void generate_makefile(FILE *of, char *parser_name)
{
  if (!of)
    of = stdout;

  if (!parser_name)
    return;

  fprintf(of, "CC = gcc\n");
  fprintf(of, "COPTS = -g -Wall -O0 -I include\n");
  fprintf(of, "\n");
  fprintf(of, "all: %s-walker\n", parser_name);
  fprintf(of, "\n");
  fprintf(of, "%s-walker: bin/%s-walker\n",
                parser_name, parser_name);
  fprintf(of, "\n");
  fprintf(of, "bin/%s-walker: obj/%s-walker.o \\\n",
                parser_name, parser_name);
  fprintf(of, "\t\tobj/%s-parser.o \\\n", parser_name);
  fprintf(of, "\t\tobj/%s-token.o \\\n", parser_name);
  fprintf(of, "\t\tobj/%s-token-util.o\n", parser_name);
  fprintf(of, "\t$(CC) $(COPTS) -o bin/%s-walker \\\n", parser_name);
  fprintf(of, "\t\tobj/%s-walker.o \\\n", parser_name);
  fprintf(of, "\t\tobj/%s-parser.o \\\n", parser_name);
  fprintf(of, "\t\tobj/%s-token.o \\\n", parser_name);
  fprintf(of, "\t\tobj/%s-token-util.o \\\n", parser_name);
  fprintf(of, "\t\tobj/strapp.o \\\n");
  fprintf(of, "\t\tobj/input.o\n");
  fprintf(of, "\n");
  fprintf(of, "obj/%s-walker.o: src/%s-walker.c \\\n",
                parser_name, parser_name);
  fprintf(of, "\t\tinclude/%s-token.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-type.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-util.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-parser.h\n", parser_name);
  fprintf(of, "\t$(CC) $(COPTS) -o obj/%s-walker.o -c src/%s-walker.c\n",
                parser_name, parser_name);
  fprintf(of, "\n");
  fprintf(of, "obj/%s-parser.o: "
              "src/%s-parser.c \\\n",
                parser_name, parser_name);
  fprintf(of, "\t\tinclude/%s-parser.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-type.h\n", parser_name);
  fprintf(of, "\t$(CC) $(COPTS) "
              "-o obj/%s-parser.o "
              "-c src/%s-parser.c\n",
                parser_name, parser_name);
  fprintf(of, "\n");
  fprintf(of, "obj/%s-token.o: "
              "src/%s-token.c \\\n",
                parser_name, parser_name);
  fprintf(of, "\t\tinclude/%s-token.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-type.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-util.h\n", parser_name);
  fprintf(of, "\t$(CC) $(COPTS) "
              "-o obj/%s-token.o "
              "-c src/%s-token.c\n",
                parser_name, parser_name);
  fprintf(of, "\n");
  fprintf(of, "obj/%s-token-util.o: "
              "src/%s-token-util.c \\\n",
                parser_name, parser_name);
  fprintf(of, "\t\tinclude/%s-token.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-type.h \\\n", parser_name);
  fprintf(of, "\t\tinclude/%s-token-util.h\n", parser_name);
  fprintf(of, "\t$(CC) $(COPTS) "
              "-o obj/%s-token-util.o "
              "-c src/%s-token-util.c\n",
                parser_name, parser_name);
  fprintf(of, "\n");
  fprintf(of, "clean:\n");
  fprintf(of, "\t@rm -f obj/*.o\n");
  fprintf(of, "\t@rm -f bin/%s-walker\n", parser_name);
  fprintf(of, "\n");

  return;
}

static int current_level = 0;

static void generate_grammar(FILE *of, char *parser_name, egg_token *t, int level)
{
  if (!t) return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  switch (t->t)
  {
    case egg_token_type_phrase:
      generate_phrase(of, parser_name, t);
      break;
    default:
      break;
  }

  generate_grammar(of, parser_name, t->d, level+1);

  generate_grammar(of, parser_name, t->n, level);

  return;
}

static void generate_phrase(FILE *of, char *parser_name, egg_token *t)
{
  egg_token *pn;
  egg_token *def;
  char *pns = NULL;
  char *ds = NULL;

  if (!t)
    return;

  if (t->t != egg_token_type_phrase)
    return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  t = t->d;

  fprintf(of, "/*\n");
  ds = egg_token_to_string(t, ds);
  if (ds)
  {
    emit_comment_string(of, ds);
    free(ds);
  }
  fprintf(of, " */\n");
  fprintf(of, "\n");

  pn = egg_token_find(t, egg_token_type_phrase_name);
  if (pn)
  {
    pns = egg_token_to_string(pn->d, pns);
    if (pns)
    {
      pns = fix_identifier(pns);

      fprintf(of, "%s_token *", parser_name);
      fprintf(of, "%s", pns);
      fprintf(of, "(void)\n");
      fprintf(of, "{\n");
      fprintf(of, "  long pos = input_get_position();\n");
      fprintf(of, "  %s_token *nt, *t1, *t2;\n", parser_name);
      fprintf(of, "  int count;\n");
      fprintf(of, "  %s_token_direction dir;\n", parser_name);
      fprintf(of, "\n");
      fprintf(of, "  count = 0;\n");
      fprintf(of, "\n");
      fprintf(of, "  if (input_eof())\n");
      fprintf(of, "    return NULL;\n");
      fprintf(of, "\n");
      fprintf(of, "  nt = t1 = t2 = NULL;\n");
      fprintf(of, "\n");
      fprintf(of, "  count = 0;\n");
      fprintf(of, "\n");
      fprintf(of, "  dir = %s_token_below;\n", parser_name);
      fprintf(of, "\n");
      fprintf(of, "  nt = %s_token_new(%s_token_type_",
                    parser_name, parser_name);
      fprintf(of, "%s", pns);
      fprintf(of, ");\n");
      fprintf(of, "  if (!nt)\n");
      fprintf(of, "    return NULL;\n");
      fprintf(of, "\n");
      fprintf(of, "  t1 = nt;\n");
      fprintf(of, "\n");

      def = egg_token_find(t, egg_token_type_definition);
      generate_definition(of, parser_name, def);

      free(pns);
    }
  }

  fprintf(of, "  return NULL;\n");
  fprintf(of, "}\n");
  fprintf(of, "\n");

  return;
}

static void generate_definition(FILE *of, char *parser_name, egg_token *t)
{
  egg_token *seq;
  egg_token *cont;

  if (!t)
    return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  t = t->d;

  seq = egg_token_find(t, egg_token_type_sequence);
  if (seq)
  {
    emit_indent(of);
    fprintf(of, "  dir = %s_token_below;\n", parser_name);
    generate_sequence(of, parser_name, seq);
    fprintf(of, "\n");

    cont = seq->n;

    while (cont)
    {
      if (cont->t == egg_token_type_definition_continuation)
      {
        t = cont->d;
        seq = egg_token_find(t, egg_token_type_sequence);
        if (seq)
        {
          emit_indent(of);
          fprintf(of, "  dir = %s_token_below;\n", parser_name);
          generate_sequence(of, parser_name, seq);
          fprintf(of, "\n");
        }
      }
      cont = cont->n;
    }

    fprintf(of, "  %s_token_delete(nt);\n", parser_name);
    fprintf(of, "  input_set_position(pos);\n");
    fprintf(of, "\n");
  }

  return;
}

static void generate_sequence(FILE *of, char *parser_name, egg_token *t)
{
  egg_token *itm;
  egg_token *cont;
  int level_in = current_level;

  if (!t)
    return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  t = t->d;

  itm = egg_token_find(t, egg_token_type_item);
  if (itm)
  {
    ++current_level;

    generate_item(of, parser_name, itm);

    cont = itm->n;
    while (cont)
    {
      if (cont->t == egg_token_type_sequence_continuation)
      {
        t = cont->d;
        itm = egg_token_find(t, egg_token_type_item);
        if (itm)
        {
           ++current_level;
           generate_item(of, parser_name, itm);
        }
      }
      cont = cont->n;
    }

    emit_indent(of);
    fprintf(of, "  return nt;\n");

    while (current_level > level_in)
    {
      emit_indent(of);
      fprintf(of, "}\n");
      --current_level;
    }
  }

  current_level = 0;

  return;
}

static void generate_item(FILE *of, char *parser_name, egg_token *t)
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

  t = t->d;

  atm = egg_token_find(t, egg_token_type_atom);
  if (atm)
  {
    qty = egg_token_find(atm->n, egg_token_type_quantifier);
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
      ++current_level;
    }
    generate_atom(of, parser_name, atm);
    if (qty)
    {
      --current_level;
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

static void generate_atom(FILE *of, char *parser_name, egg_token *t)
{
  egg_token *lit;
  egg_token *pn;

  if (!t)
    return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  t = t->d;

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

static void generate_literal(FILE *of, char *parser_name, egg_token *t)
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

  t = t->d;

  lit = egg_token_find(t, egg_token_type_absolute_literal);
  if (lit)
  {
    s = egg_token_to_string(lit->d, s = NULL);
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
    s = egg_token_to_string(lit->d, s = NULL);
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
    s = egg_token_to_string(lit->d, s = NULL);
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

static void generate_phrase_name(FILE *of, char *parser_name, egg_token *t)
{
  char *pns = NULL;

  if (!t)
    return;

  if (!parser_name)
    return;

  if (!of)
    of = stdout;

  t = t->d;

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

static int get_minimum(egg_token *t)
{
  egg_token *in;
  char *ins = NULL;
  int i;

  if (!t)
    return 1;

  if (t->t != egg_token_type_quantifier)
    return 1;

  in = egg_token_find(t->d, egg_token_type_integer);
  if (in)
  {
    ins = egg_token_to_string(in->d, ins);
    if (ins)
    {
      i = atoi(ins);
      free(ins);
      return i;
    }
  }

  return 1;
}

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

  if (t->t != egg_token_type_quantifier)
    return 1;

  min = get_minimum(t);

  opt = egg_token_find(t->d, egg_token_type_quantifier_option);
  if (opt)
  {
    in = egg_token_find(opt->d, egg_token_type_integer);
    if (in)
    {
      ins = egg_token_to_string(in->d, ins);
      if (ins)
      {
        i = atoi(ins);
        free(ins);
        return i;
      }
    }
    else
    {
      as = egg_token_find(opt->d, egg_token_type_asterisk);
      if (as)
        return -1;
    }
  }
  else
    return min;

  return 1;
}

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

static char *build_literal(egg_token *t)
{
  char *s = NULL;
  char *sp1, *sp2;
  egg_token *tm;
  long l;

  if (!t)
    return NULL;

  if (t->t != egg_token_type_literal)
    return NULL;

  tm = egg_token_find(t->d, egg_token_type_absolute_literal);
  if (tm)
  {
    tm = egg_token_find(tm->d, egg_token_type_integer);
    if (tm)
    {
      s = egg_token_to_string(tm->d, s);

      switch (tm->d->t)
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

  tm = egg_token_find(t->d, egg_token_type_quoted_literal);
  if (tm)
  {
    s = egg_token_to_string(tm->d, s);
    for (sp1 = s+1, sp2 = s; *sp1; ++sp2, ++sp1)
      *sp2 = *sp1; 
    *(strchr(s, '"')) = 0;
    return s;
  }

  tm = egg_token_find(t->d, egg_token_type_single_quoted_literal);
  if (tm)
  {
    s = egg_token_to_string(tm->d, s);
    for (sp1 = s+1, sp2 = s; *sp1; ++sp2, ++sp1)
      *sp2 = *sp1; 
    *(strchr(s, '\'')) = 0;
    sp1 = fix_quotes(s);
    free(s);
    return sp1;
  }

  return NULL;
}

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

static char *literal_or_phrase_name(egg_token *t)
{
  egg_token *pn;
  egg_token *def;
  egg_token *tm;
  char *pns;

  if (!t)
    return NULL;

  if (t->t != egg_token_type_phrase)
    return NULL;

  pn = egg_token_find(t->d, egg_token_type_phrase_name);
  if (!pn)
    return NULL;

  def = egg_token_find(t->d, egg_token_type_definition);
  if (!def)
    return NULL;

  if (!(tm = egg_token_find(def->d, egg_token_type_definition_continuation)))
  {
    tm = egg_token_find(def->d, egg_token_type_sequence);
    if (tm)
    {
      if (!egg_token_find(tm->d, egg_token_type_sequence_continuation))
      {
        tm = egg_token_find(tm->d, egg_token_type_item);
        if (tm)
        {
          if (!egg_token_find(tm->n, egg_token_type_quantifier))
          {
            tm = egg_token_find(tm->d, egg_token_type_literal);
            if (tm)
              return build_literal(tm);
          }
        }
      }
    }
  }

  pns = NULL;
  return egg_token_to_string(pn->d, pns);
}

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

char *get_year(void)
{
  time_t now;
  struct tm *stm;
  static char year[5];

  memset(year, 0, 5);

  now = time(NULL);
  stm = localtime(&now);

  sprintf(year, "%4.4d", stm->tm_year + 1900);

  return year;
}

static void emit_indent(FILE *of)
{
  int i;

  if (!of)
    return;

  for (i = 0; i < current_level; i++)
    fprintf(of, "  ");

  return;
}

static void emit_comment_string(FILE *of, char *s)
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
    fprintf(of, " * %s\n", s);
    s = t+1;
    t = s;
  }

  fprintf(of, " * %s\n", s);

  return;
}

static void emit_gnu_license(FILE *of)
{
  char *yr;

  if (!of)
    of = stdout;

  yr = get_year();

  fprintf(of, "    Copyright (C) %s  Patrick Head\n", get_year());
  fprintf(of, "\n");
  fprintf(of, "    This program is free software: you can redistribute it "
              "and/or modify\n");
  fprintf(of, "    it under the terms of the GNU General Public License as "
              "published by\n");
  fprintf(of, "    the Free Software Foundation, either version 3 of the "
              "License, or\n");
  fprintf(of, "    (at your option) any later version.\n");
  fprintf(of, "\n");
  fprintf(of, "    This program is distributed in the hope that it will be "
              "useful,\n");
  fprintf(of, "    but WITHOUT ANY WARRANTY; without even the implied warranty "
              "of\n");
  fprintf(of, "    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See "
              "the\n");
  fprintf(of, "    GNU General Public License for more details.\n");
  fprintf(of, "\n");
  fprintf(of, "    You should have received a copy of the GNU General Public "
              "License\n");
  fprintf(of, "    along with this program.  If not, "
              "see <http://www.gnu.org/licenses/>.\n");
  fprintf(of, "*/\n");

  return;
}

void isolate_top_level_phrases(phrase_map_item **list)
{
  phrase_map_item *ppmi;
  phrase_map_item *ppmi2;
  phrase_map_item *upmi;

  if (!list)
    return;

  if (!*list)
    return;

  ppmi = *list;
  while (ppmi)
  {
    upmi = ppmi->uses;
    while (upmi)
    {
      ppmi2 = *list;
      while (ppmi2)
      {
        if (!strcmp(ppmi2->name, upmi->name))
          if (strcmp(ppmi->name, upmi->name))
            ppmi2->name[0] = ' ';
        
        ppmi2 = ppmi2->next;
      }
      upmi = upmi->next;
    }
    ppmi = ppmi->next;
  }

  ppmi = *list;
  while (ppmi)
  {
    if (ppmi->name[0] == ' ')
      phrase_map_item_delete(list, ppmi);
    ppmi = ppmi->next;
  }

  return;
}

