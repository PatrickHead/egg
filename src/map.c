/*
    map.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "egg-token.h"
#include "egg-token-util.h"

#include "map.h"

static void all_phrase_names(egg_token *t, phrase_map_item *pmi);

phrase_map_item *phrase_map(egg_token *g)
{
  egg_token *ge;
  egg_token *p;
  egg_token *pn;
  egg_token *d;
  char *s;
  phrase_map_item *list = NULL;
  phrase_map_item *npmi;

  if (!g)
    return NULL;

  ge = egg_token_find(g, egg_token_type_grammar_element);
  if (ge)
  {
    while (ge)
    {
      p = egg_token_find(ge->d, egg_token_type_phrase);
      if (p)
      {
        pn = egg_token_find(p->d, egg_token_type_phrase_name);
        if (pn)
        {
          s = NULL;
          s = egg_token_to_string(pn->d, s);
          npmi = phrase_map_list_append_item_by_name(&list, s, false);
          if (!npmi)
          {
            free(s);
            phrase_map_list_delete(list);
            return NULL;
          }
          free(s);
          d = egg_token_find(p->d, egg_token_type_definition);
          if (d)
            all_phrase_names(d->d, npmi);
        }
      }
      ge = ge->n;
    }
  }

  return list;
}

static void all_phrase_names(egg_token *t, phrase_map_item *pmi)
{
  char *s;
  phrase_map_item *npmi;

  if (!t)
    return;

  if (!pmi)
    return;

  if (t->t == egg_token_type_phrase_name)
  {
    s = NULL;
    s = egg_token_to_string(t->d, s);
    npmi = phrase_map_list_append_item_by_name(&(pmi->uses), s, true);
    free(s);
    if (!npmi)
      return;
  }

  all_phrase_names(t->d, pmi);

  all_phrase_names(t->n, pmi);

  return;
}

phrase_map_item *phrase_map_item_new(char *name)
{
  phrase_map_item *new;

  new = (phrase_map_item *)malloc(sizeof(phrase_map_item));
  if (!new)
    return NULL;

  memset(new, 0, sizeof(phrase_map_item));

  if (name)
    new->name = strdup(name);

  return new;
}

void phrase_map_item_free(phrase_map_item *pmi)
{
  if (!pmi)
    return;

  if (pmi->name)
    free(pmi->name);

  free(pmi);

  return;
}

void phrase_map_item_unlink(phrase_map_item **list, phrase_map_item *pmi)
{
  phrase_map_item *tpmi;
  phrase_map_item *ppmi;

  if (!list)
    return;

  if (!*list)
    return;

  if (!pmi)
    return;

  tpmi = *list;
  ppmi = NULL;

  while (tpmi)
  {
    if (tpmi == pmi)
    {
      if (ppmi)
      {
        ppmi->next = tpmi->next;
        return;
      }
      else
      {
        *list = tpmi->next;
        return;
      }
    }

    ppmi = tpmi;
    tpmi = tpmi->next;
  }

  return;
}

void phrase_map_item_delete(phrase_map_item **list, phrase_map_item *pmi)
{
  phrase_map_item *tpmi;
  phrase_map_item *next;

  if (!list)
    return;

  if (!*list)
    return;

  if (!pmi)
    return;

  phrase_map_item_unlink(list, pmi);

  tpmi = pmi->uses;
  while (tpmi)
  {
    next = tpmi->next;
    phrase_map_item_free(tpmi);
    tpmi = next;
  }

  phrase_map_item_free(pmi);

  return;
}

void phrase_map_list_delete(phrase_map_item *list)
{
  if (!list)
    return;

  while (list)
    phrase_map_item_delete(&list, list);

  return;
}

phrase_map_item *phrase_map_list_find_item_by_name(phrase_map_item *list,
                                                   char *name)
{
  phrase_map_item *tpmi;

  if (!list)
    return false;

  if (!name)
    return false;

  tpmi = list;
  while (tpmi)
  {
    if (!strcmp(tpmi->name, name))
      return tpmi;

    tpmi = tpmi->next;
  }

  return NULL;
}

phrase_map_item *phrase_map_list_append_item_by_name(phrase_map_item **list,
                                                     char *name,
                                                     boolean dups_allowed)
{
  phrase_map_item *tpmi;
  phrase_map_item *npmi;

  if (!list)
     return NULL;

  if (!name)
     return NULL;

  tpmi = *list;
  while (tpmi && tpmi->next)
  {
    if (!dups_allowed)
      if (!strcmp(tpmi->name, name))
        return NULL;

    tpmi = tpmi->next;
  }

  npmi = phrase_map_item_new(name);
  if (!npmi)
    return NULL;

  if (tpmi)
    tpmi->next = npmi;
  else
    *list = npmi;

  return npmi;
}

