/*!

  \file egg-token.h

  \brief Source code for egg-token.h

  \version 0.2.2

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

  /*!

    \file egg-token.h

    This is the header file for the egg grammar token and
    token tree management functions module.

  */

#ifndef EGG_TOKEN_H
#define EGG_TOKEN_H

#include "common.h"
#include "input.h"

#include "egg-token-type.h"

  /*!
    \brief Definition of allowed directions for egg_token_add function.
  */

typedef enum
{
    /*! \brief Add new token before token (as sibling) */
  egg_token_before,
    /*! \brief Add new token after token (as sibling) */
  egg_token_after,
    /*! \brief Add new token below token (as descendant) */
  egg_token_below
} egg_token_direction;

  /*!
    \brief Definition of egg_token
  */

typedef struct egg_token
{
    /*! \brief Type of token */
  egg_token_type type;
    /*! \brief Pointer to ascendant (parent) token */
  struct egg_token *ascendant;
    /*! \brief Pointer to descendant (child) token */
  struct egg_token *descendant;
    /*! \brief Pointer to previous (sibling) token */
  struct egg_token *previous;
    /*! \brief Pointer to next (sibling) token */
  struct egg_token *next;
    /*! \brief Line + offset location of token in input source */
  input_location location;
} egg_token;

egg_token *egg_token_new(egg_token_type type);

void egg_token_free(egg_token *t);

boolean egg_token_add(egg_token *t,
  egg_token_direction dir,
  egg_token *n);

void egg_token_delete(egg_token *t);

void egg_token_unlink(egg_token *t);

egg_token_type egg_token_get_type(egg_token *t);
void egg_token_set_type(egg_token *t, egg_token_type type);

egg_token *egg_token_get_ascendant(egg_token *t);
void egg_token_set_ascendant(egg_token *t, egg_token *a);

egg_token *egg_token_get_descendant(egg_token *t);
void egg_token_set_descendant(egg_token *t, egg_token *d);

egg_token *egg_token_get_previous(egg_token *t);
void egg_token_set_previous(egg_token *t, egg_token *p);

egg_token *egg_token_get_next(egg_token *t);
void egg_token_set_next(egg_token *t, egg_token *n);

egg_token *egg_token_find(egg_token *t, egg_token_type type);

char *egg_token_to_string(egg_token *t, char *s);

#endif // EGG_TOKEN_H

