/*!

  \file egg-token.c

  \brief Source code for grammer specific token handling functions

  \version 20131211163732

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

  /*!

    \brief Create a new egg_token

    \warning This function returns a pointer to dynamically allocated memory.
             It is the caller's responsibility to free this memory when 
             appropriate.

    \param type egg_token_type

    \retval "egg_token *" new egg_token
    \retval NULL failure

  */

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

  /*!

    \brief Free the memory associated with egg_token

    \warning This function does NOT perform any unlinking of the freed token.
    \sa egg_token_unlink()

    \param t egg_token *

  */

void egg_token_free(egg_token *t)
{
  if (!t)
    return;

  free(t);

  return;
}

  /*!

    \brief Link egg_token into an existing token tree

    \param t   existing egg_token *
    \param dir egg_token_direction
    \param n   egg_token * to link

    \retval true  success
    \retval false failure

  */

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

  /*!

    \brief Delete egg_token from an existing token tree, if any

    This function unlinks egg_token from an existing token 
    tree, if required.
    Also, the memory associated with egg_token is freed.

    \param t egg_token *

  */

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

  /*!

    \brief Unlink egg_token from an existing token tree

    \warning This function does NOT perform any freeing of the unlinked token.
    \sa egg_token_free()

    \param t egg_token *

  */

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

  /*!

    \brief Returns egg_token_type of egg_token

    \param t egg_token *

    \retval egg_token_type

  */

egg_token_type egg_token_get_type(egg_token *t)
{
  if (!t)
    return egg_token_type_none;

  return t->t;
}

  /*!

    \brief Sets egg_token_type of egg_token

    \param t    egg_token *
    \param type egg_token_type

  */

void egg_token_set_type(egg_token *t, egg_token_type type)
{
  if (!t)
    return;

  t->t = type;
}

  /*!

    \brief Returns pointer to ascendant of egg_token

    \param t egg_token *

    \retval "egg_token *"

  */

egg_token *egg_token_get_ascendant(egg_token *t)
{
  if (!t)
    return NULL;

  return t->a;
}

  /*!

    \brief Sets pointer to ascendant of egg_token

    \param t existing egg_token *
    \param a ascendant of egg_token *

  */

void egg_token_set_ascendant(egg_token *t, egg_token *a)
{
  if (!t)
    return;

  t->a = a;
}

  /*!

    \brief Returns pointer to descendant of egg_token

    \param t egg_token *

    \retval "egg_token *"

  */

egg_token *egg_token_get_descendant(egg_token *t)
{
  if (!t)
    return NULL;

  return t->d;
}

  /*!

    \brief Sets pointer to descendant of egg_token

    \param t existing egg_token *
    \param d descendant of egg_token *

  */

void egg_token_set_descendant(egg_token *t, egg_token *d)
{
  if (!t)
    return;

  t->d = d;
}

  /*!

    \brief Returns pointer to previous egg_token

    \param t egg_token *

    \retval "egg_token *"

  */

egg_token *egg_token_get_previous(egg_token *t)
{
  if (!t)
    return NULL;

  return t->p;
}

  /*!

    \brief Sets pointer to previous egg_token

    \param t existing egg_token *
    \param p previous egg_token *

  */

void egg_token_set_previous(egg_token *t, egg_token *p)
{
  if (!t)
    return;

  t->p = p;
}

  /*!

    \brief Returns pointer to next egg_token

    \param t egg_token *

    \retval "egg_token *"

  */

egg_token *egg_token_get_next(egg_token *t)
{
  if (!t)
    return NULL;

  return t->n;
}

  /*!

    \brief Sets pointer to next egg_token

    \param t existing egg_token *
    \param n next egg_token *

  */

void egg_token_set_next(egg_token *t, egg_token *n)
{
  if (!t)
    return;

  t->n = n;
}

  /*!

    \brief Find next egg_token of specified egg_token_type

    \param t    existing egg_token *
    \param type egg_token_type

    \retval "egg_token *" found egg_token
    \retval NULL failure, including NOT FOUND

  */

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

  /*!

    \brief Returns string representation of egg_token

    \warning This is a recursive function, therefore parameter s can NOT point to static
              memory.

    \warning This function returns a pointer to dynamically allocated memory.
             It is the caller's responsibility to free this memory when
             appropriate.

    \param t existing egg_token *
    \param s char * of existing string, can be NULL

    \retval "char *" string, can be NULL if s is NULL

  */

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

