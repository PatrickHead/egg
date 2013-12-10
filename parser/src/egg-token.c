/*!

  \file egg-token.c

  \brief Source code for egg-token.c

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

#include <stdlib.h>
#include <string.h>

#include "strapp.h"

#include "egg-token.h"
#include "egg-token-util.h"

egg_token *egg_token_new(egg_token_type type)
{
  egg_token *new = NULL;

  new = malloc(sizeof(egg_token));
  if (!new)
    return NULL;

  memset(new, 0, sizeof(egg_token));

  new->t = type;

  input_get_location(&(new->loc));

  return new;
}

void egg_token_free(egg_token *t)
{
  if (!t)
    return;

  free(t);

  return;
}

boolean egg_token_add(egg_token *t, egg_token_direction dir, egg_token *n)
{
  if (!t)
    return false;

  if (!n)
    return false;

  switch (dir)
  {
    case egg_token_before:

      n->p = t->p;
      n->n = t;
      if (t->p)
        t->p->n = n;
      t->p = n;
      n->a = t->a;

        // Fix ascendant's descendant pointer, if it is t.
        // We always want the ascendant's descendent pointer to point to
        //   the beginning of the list of descendents.

      if (t->a)
        if (t->a->d == t)
          t->a->d = n;

      break;

    case egg_token_after:

      n->p = t;
      n->n = t->n;
      if (t->n)
        t->n->p = n;
      t->n = n;
      n->a = t->a;

      break;

    case egg_token_below:

      if (t->d)
        return false;
      t->d = n;
      n->a = t;

      break;
  }

  return true;
}

void egg_token_delete(egg_token *t)
{
  if (!t)
    return;

  while (t->d)
    egg_token_delete(t->d);

  egg_token_unlink(t);
  egg_token_free(t);

  return;
}

void egg_token_unlink(egg_token *t)
{
  if (!t)
    return;

  if (t->a)
    if (t->a->d == t)
      t->a->d = t->n;

  if (t->p)
    t->p->n = t->n;

  if (t->n)
    t->n->p = t->p;

  return;
}

egg_token_type egg_token_get_type(egg_token *t)
{
  if (!t)
    return egg_token_type_none;

  return t->t;
}

void egg_token_set_type(egg_token *t, egg_token_type type)
{
  if (!t)
    return;

  t->t = type;
}

egg_token *egg_token_get_ascendant(egg_token *t)
{
  if (!t)
    return NULL;

  return t->a;
}

void egg_token_set_ascendant(egg_token *t, egg_token *a)
{
  if (!t)
    return;

  t->a = a;
}

egg_token *egg_token_get_descendant(egg_token *t)
{
  if (!t)
    return NULL;

  return t->d;
}

void egg_token_set_descendant(egg_token *t, egg_token *d)
{
  if (!t)
    return;

  t->d = d;
}

egg_token *egg_token_get_previous(egg_token *t)
{
  if (!t)
    return NULL;

  return t->p;
}

void egg_token_set_previous(egg_token *t, egg_token *p)
{
  if (!t)
    return;

  t->p = p;
}

egg_token *egg_token_get_next(egg_token *t)
{
  if (!t)
    return NULL;

  return t->n;
}

void egg_token_set_next(egg_token *t, egg_token *n)
{
  if (!t)
    return;

  t->n = n;
}

egg_token *egg_token_find(egg_token *t, egg_token_type type)
{
  egg_token *f;

  if (!t)
    return NULL;

  if (t->t == type)
    return t;

  f = egg_token_find(t->d, type);
  if (f)
    return f;

  f = egg_token_find(t->n, type);
  if (f)
    return f;

  return NULL;
}

char *egg_token_to_string(egg_token *t, char *s)
{
  if (!t)
    return s;

  if (!t->d)
    s = strapp(s , egg_token_type_to_string(t));
  else
    s = egg_token_to_string(t->d, s);

  s = egg_token_to_string(t->n, s);

  return s;
}

