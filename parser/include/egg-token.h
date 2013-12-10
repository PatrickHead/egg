/*!

  \file egg-token.h

  \brief Source code for egg-token.h

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

#ifndef EGG_TOKEN_H
#define EGG_TOKEN_H

#include "common.h"
#include "input.h"

  /*
   * Enumeration defining allowable values for egg_token_type
   */

#include "egg-token-type.h"

  /*
   * Enumeration defining direction for egg_token_add
   * function.
   */

typedef enum
{
  egg_token_before,
  egg_token_after,
  egg_token_below
} egg_token_direction;

  /*
   * Definition of a egg_token
   */

typedef struct egg_token
{
  egg_token_type t;
  struct egg_token *a;  // ascendant
  struct egg_token *d;  // descendant
  struct egg_token *p;  // previous
  struct egg_token *n;  // next
  input_location loc;  // line,offset
} egg_token;

  /*
   * Function prototypes
   */

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
