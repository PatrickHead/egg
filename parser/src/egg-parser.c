/*!

  \file egg-parser.c

  \brief Source code for grammer phrase parsing functions

  \version 20131212072057

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

    \file egg-parser.c

    This is the source code file for the egg grammar phrase parsing
    functions module.

    An individual phrase parsing function exists for each
    egg grammar phrase.

    Also the egg_get_callback_table function is defined in
    this module.

  */


  /*!

    \file egg-parser.c

    \par "Description of Parsing Functions"
    With the exception of the egg_get_callback_table() function,
    every function in this parser has the same calling signature and 
    return value pattern:
    \n\n
      egg_token * <phrase-name>(void);
    \n\n
    Each function returns a pointer to a struct of type egg_token,
    which is set to the egg_<phrase-name>_token_type type, and possibly
    contains a child hierarchy of related tokens.

  */

#include <stdlib.h>

#include "egg-token.h"
#include "egg-parser.h"

static callback_entry _callbacks[] =
{
  { "nul", NULL, NULL, NULL },
  { "soh", NULL, NULL, NULL },
  { "stx", NULL, NULL, NULL },
  { "etx", NULL, NULL, NULL },
  { "eot", NULL, NULL, NULL },
  { "enq", NULL, NULL, NULL },
  { "ack", NULL, NULL, NULL },
  { "bel", NULL, NULL, NULL },
  { "bs", NULL, NULL, NULL },
  { "ht", NULL, NULL, NULL },
  { "lf", NULL, NULL, NULL },
  { "vt", NULL, NULL, NULL },
  { "ff", NULL, NULL, NULL },
  { "cr", NULL, NULL, NULL },
  { "so", NULL, NULL, NULL },
  { "si", NULL, NULL, NULL },
  { "dle", NULL, NULL, NULL },
  { "dc1", NULL, NULL, NULL },
  { "dc2", NULL, NULL, NULL },
  { "dc3", NULL, NULL, NULL },
  { "dc4", NULL, NULL, NULL },
  { "nak", NULL, NULL, NULL },
  { "syn", NULL, NULL, NULL },
  { "etb", NULL, NULL, NULL },
  { "can", NULL, NULL, NULL },
  { "em", NULL, NULL, NULL },
  { "sub", NULL, NULL, NULL },
  { "esc", NULL, NULL, NULL },
  { "fs", NULL, NULL, NULL },
  { "gs", NULL, NULL, NULL },
  { "rs", NULL, NULL, NULL },
  { "us", NULL, NULL, NULL },
  { "space", NULL, NULL, NULL },
  { "exclamation-point", NULL, NULL, NULL },
  { "quote", NULL, NULL, NULL },
  { "number-sign", NULL, NULL, NULL },
  { "dollar", NULL, NULL, NULL },
  { "percent", NULL, NULL, NULL },
  { "ampersand", NULL, NULL, NULL },
  { "single-quote", NULL, NULL, NULL },
  { "open-parenthesis", NULL, NULL, NULL },
  { "close-parenthesis", NULL, NULL, NULL },
  { "asterisk", NULL, NULL, NULL },
  { "plus", NULL, NULL, NULL },
  { "comma", NULL, NULL, NULL },
  { "minus", NULL, NULL, NULL },
  { "period", NULL, NULL, NULL },
  { "slash", NULL, NULL, NULL },
  { "zero", NULL, NULL, NULL },
  { "one", NULL, NULL, NULL },
  { "two", NULL, NULL, NULL },
  { "three", NULL, NULL, NULL },
  { "four", NULL, NULL, NULL },
  { "five", NULL, NULL, NULL },
  { "six", NULL, NULL, NULL },
  { "seven", NULL, NULL, NULL },
  { "eight", NULL, NULL, NULL },
  { "nine", NULL, NULL, NULL },
  { "colon", NULL, NULL, NULL },
  { "semicolon", NULL, NULL, NULL },
  { "less-than", NULL, NULL, NULL },
  { "equal", NULL, NULL, NULL },
  { "greater-than", NULL, NULL, NULL },
  { "question-mark", NULL, NULL, NULL },
  { "at", NULL, NULL, NULL },
  { "A", NULL, NULL, NULL },
  { "B", NULL, NULL, NULL },
  { "C", NULL, NULL, NULL },
  { "D", NULL, NULL, NULL },
  { "E", NULL, NULL, NULL },
  { "F", NULL, NULL, NULL },
  { "G", NULL, NULL, NULL },
  { "H", NULL, NULL, NULL },
  { "I", NULL, NULL, NULL },
  { "J", NULL, NULL, NULL },
  { "K", NULL, NULL, NULL },
  { "L", NULL, NULL, NULL },
  { "M", NULL, NULL, NULL },
  { "N", NULL, NULL, NULL },
  { "O", NULL, NULL, NULL },
  { "P", NULL, NULL, NULL },
  { "Q", NULL, NULL, NULL },
  { "R", NULL, NULL, NULL },
  { "S", NULL, NULL, NULL },
  { "T", NULL, NULL, NULL },
  { "U", NULL, NULL, NULL },
  { "V", NULL, NULL, NULL },
  { "W", NULL, NULL, NULL },
  { "X", NULL, NULL, NULL },
  { "Y", NULL, NULL, NULL },
  { "Z", NULL, NULL, NULL },
  { "open-bracket", NULL, NULL, NULL },
  { "back-slash", NULL, NULL, NULL },
  { "close-bracket", NULL, NULL, NULL },
  { "carat", NULL, NULL, NULL },
  { "underscore", NULL, NULL, NULL },
  { "back-quote", NULL, NULL, NULL },
  { "a", NULL, NULL, NULL },
  { "b", NULL, NULL, NULL },
  { "c", NULL, NULL, NULL },
  { "d", NULL, NULL, NULL },
  { "e", NULL, NULL, NULL },
  { "f", NULL, NULL, NULL },
  { "g", NULL, NULL, NULL },
  { "h", NULL, NULL, NULL },
  { "i", NULL, NULL, NULL },
  { "j", NULL, NULL, NULL },
  { "k", NULL, NULL, NULL },
  { "l", NULL, NULL, NULL },
  { "m", NULL, NULL, NULL },
  { "n", NULL, NULL, NULL },
  { "o", NULL, NULL, NULL },
  { "p", NULL, NULL, NULL },
  { "q", NULL, NULL, NULL },
  { "r", NULL, NULL, NULL },
  { "s", NULL, NULL, NULL },
  { "t", NULL, NULL, NULL },
  { "u", NULL, NULL, NULL },
  { "v", NULL, NULL, NULL },
  { "w", NULL, NULL, NULL },
  { "x", NULL, NULL, NULL },
  { "y", NULL, NULL, NULL },
  { "z", NULL, NULL, NULL },
  { "open-brace", NULL, NULL, NULL },
  { "bar", NULL, NULL, NULL },
  { "close-brace", NULL, NULL, NULL },
  { "tilde", NULL, NULL, NULL },
  { "del", NULL, NULL, NULL },
  { "control-character", NULL, NULL, NULL },
  { "upper-case-letter", NULL, NULL, NULL },
  { "lower-case-letter", NULL, NULL, NULL },
  { "letter", NULL, NULL, NULL },
  { "binary-digit", NULL, NULL, NULL },
  { "octal-digit", NULL, NULL, NULL },
  { "decimal-digit", NULL, NULL, NULL },
  { "hexadecimal-digit", NULL, NULL, NULL },
  { "white-space", NULL, NULL, NULL },
  { "common-character", NULL, NULL, NULL },
  { "literal-character", NULL, NULL, NULL },
  { "comment-basic-character", NULL, NULL, NULL },
  { "non-comment-start-character", NULL, NULL, NULL },
  { "non-comment-end-character", NULL, NULL, NULL },
  { "non-comment-start-sequence", NULL, NULL, NULL },
  { "non-comment-end-sequence", NULL, NULL, NULL },
  { "comment-character", NULL, NULL, NULL },
  { "single-quoted-character", NULL, NULL, NULL },
  { "quoted-character", NULL, NULL, NULL },
  { "phrase-conjugator", NULL, NULL, NULL },
  { "phrase-name-character", NULL, NULL, NULL },
  { "binary-indicator", NULL, NULL, NULL },
  { "octal-indicator", NULL, NULL, NULL },
  { "hexadecimal-indicator", NULL, NULL, NULL },
  { "comment-start-symbol", NULL, NULL, NULL },
  { "comment-end-symbol", NULL, NULL, NULL },
  { "alternation-symbol", NULL, NULL, NULL },
  { "concatenation-symbol", NULL, NULL, NULL },
  { "phrase-terminator-symbol", NULL, NULL, NULL },
  { "binary-integer", NULL, NULL, NULL },
  { "octal-integer", NULL, NULL, NULL },
  { "hexadecimal-integer", NULL, NULL, NULL },
  { "decimal-integer", NULL, NULL, NULL },
  { "integer", NULL, NULL, NULL },
  { "single-quoted-literal", NULL, NULL, NULL },
  { "quoted-literal", NULL, NULL, NULL },
  { "absolute-literal", NULL, NULL, NULL },
  { "literal", NULL, NULL, NULL },
  { "comment-item", NULL, NULL, NULL },
  { "comment", NULL, NULL, NULL },
  { "illumination", NULL, NULL, NULL },
  { "non-grammar-item", NULL, NULL, NULL },
  { "non-grammar-element", NULL, NULL, NULL },
  { "phrase-name", NULL, NULL, NULL },
  { "quantifier-item", NULL, NULL, NULL },
  { "quantifier-option", NULL, NULL, NULL },
  { "quantifier", NULL, NULL, NULL },
  { "atom", NULL, NULL, NULL },
  { "item", NULL, NULL, NULL },
  { "sequence-continuation", NULL, NULL, NULL },
  { "sequence", NULL, NULL, NULL },
  { "definition-continuation", NULL, NULL, NULL },
  { "definition", NULL, NULL, NULL },
  { "phrase", NULL, NULL, NULL },
  { "grammar-element", NULL, NULL, NULL },
  { "grammar", NULL, NULL, NULL }
};

static callback_table _cbt = { 184, _callbacks };

  /*!

    \brief Returns pointer to callback table.

    This function returns a pointer to the parser's callback table.  The
    caller can use this to register its own callback functions for additional
    parsing actions.

    \retval "callback_table *" pointer to head of parser callback table

  */

callback_table *egg_get_callback_table(void)
{
  return &_cbt;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    nul =               /0x00/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *nul(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    0,
                    entry,
                    (void *)egg_token_type_nul);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_nul);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      0,
                      fail,
                      (void *)egg_token_type_nul);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x00)
  {
    callback_by_index(&_cbt,
                      0,
                      success,
                      (void *)egg_token_type_nul);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    0,
                    fail,
                    (void *)egg_token_type_nul);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    soh =               /0x01/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *soh(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    1,
                    entry,
                    (void *)egg_token_type_soh);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_soh);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      1,
                      fail,
                      (void *)egg_token_type_soh);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x01)
  {
    callback_by_index(&_cbt,
                      1,
                      success,
                      (void *)egg_token_type_soh);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    1,
                    fail,
                    (void *)egg_token_type_soh);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    stx =               /0x02/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *stx(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    2,
                    entry,
                    (void *)egg_token_type_stx);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_stx);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      2,
                      fail,
                      (void *)egg_token_type_stx);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x02)
  {
    callback_by_index(&_cbt,
                      2,
                      success,
                      (void *)egg_token_type_stx);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    2,
                    fail,
                    (void *)egg_token_type_stx);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    etx =               /0x03/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *etx(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    3,
                    entry,
                    (void *)egg_token_type_etx);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_etx);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      3,
                      fail,
                      (void *)egg_token_type_etx);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x03)
  {
    callback_by_index(&_cbt,
                      3,
                      success,
                      (void *)egg_token_type_etx);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    3,
                    fail,
                    (void *)egg_token_type_etx);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    eot =               /0x04/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *eot(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    4,
                    entry,
                    (void *)egg_token_type_eot);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_eot);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      4,
                      fail,
                      (void *)egg_token_type_eot);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x04)
  {
    callback_by_index(&_cbt,
                      4,
                      success,
                      (void *)egg_token_type_eot);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    4,
                    fail,
                    (void *)egg_token_type_eot);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    enq =               /0x05/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *enq(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    5,
                    entry,
                    (void *)egg_token_type_enq);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_enq);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      5,
                      fail,
                      (void *)egg_token_type_enq);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x05)
  {
    callback_by_index(&_cbt,
                      5,
                      success,
                      (void *)egg_token_type_enq);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    5,
                    fail,
                    (void *)egg_token_type_enq);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    ack =               /0x06/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *ack(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    6,
                    entry,
                    (void *)egg_token_type_ack);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_ack);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      6,
                      fail,
                      (void *)egg_token_type_ack);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x06)
  {
    callback_by_index(&_cbt,
                      6,
                      success,
                      (void *)egg_token_type_ack);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    6,
                    fail,
                    (void *)egg_token_type_ack);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    bel =               /0x07/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *bel(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    7,
                    entry,
                    (void *)egg_token_type_bel);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_bel);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      7,
                      fail,
                      (void *)egg_token_type_bel);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x07)
  {
    callback_by_index(&_cbt,
                      7,
                      success,
                      (void *)egg_token_type_bel);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    7,
                    fail,
                    (void *)egg_token_type_bel);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    bs =                /0x08/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *bs(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    8,
                    entry,
                    (void *)egg_token_type_bs);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_bs);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      8,
                      fail,
                      (void *)egg_token_type_bs);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x08)
  {
    callback_by_index(&_cbt,
                      8,
                      success,
                      (void *)egg_token_type_bs);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    8,
                    fail,
                    (void *)egg_token_type_bs);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    ht =                /0x09/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *ht(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    9,
                    entry,
                    (void *)egg_token_type_ht);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_ht);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      9,
                      fail,
                      (void *)egg_token_type_ht);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x09)
  {
    callback_by_index(&_cbt,
                      9,
                      success,
                      (void *)egg_token_type_ht);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    9,
                    fail,
                    (void *)egg_token_type_ht);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    lf =                /0x0A/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *lf(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    10,
                    entry,
                    (void *)egg_token_type_lf);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_lf);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      10,
                      fail,
                      (void *)egg_token_type_lf);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x0A)
  {
    callback_by_index(&_cbt,
                      10,
                      success,
                      (void *)egg_token_type_lf);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    10,
                    fail,
                    (void *)egg_token_type_lf);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    vt =                /0x0B/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *vt(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    11,
                    entry,
                    (void *)egg_token_type_vt);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_vt);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      11,
                      fail,
                      (void *)egg_token_type_vt);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x0B)
  {
    callback_by_index(&_cbt,
                      11,
                      success,
                      (void *)egg_token_type_vt);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    11,
                    fail,
                    (void *)egg_token_type_vt);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    ff =                /0x0C/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *ff(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    12,
                    entry,
                    (void *)egg_token_type_ff);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_ff);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      12,
                      fail,
                      (void *)egg_token_type_ff);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x0C)
  {
    callback_by_index(&_cbt,
                      12,
                      success,
                      (void *)egg_token_type_ff);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    12,
                    fail,
                    (void *)egg_token_type_ff);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    cr =                /0x0D/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *cr(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    13,
                    entry,
                    (void *)egg_token_type_cr);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_cr);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      13,
                      fail,
                      (void *)egg_token_type_cr);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x0D)
  {
    callback_by_index(&_cbt,
                      13,
                      success,
                      (void *)egg_token_type_cr);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    13,
                    fail,
                    (void *)egg_token_type_cr);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    so =                /0x0E/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *so(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    14,
                    entry,
                    (void *)egg_token_type_so);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_so);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      14,
                      fail,
                      (void *)egg_token_type_so);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x0E)
  {
    callback_by_index(&_cbt,
                      14,
                      success,
                      (void *)egg_token_type_so);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    14,
                    fail,
                    (void *)egg_token_type_so);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    si =                /0x0F/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *si(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    15,
                    entry,
                    (void *)egg_token_type_si);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_si);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      15,
                      fail,
                      (void *)egg_token_type_si);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x0F)
  {
    callback_by_index(&_cbt,
                      15,
                      success,
                      (void *)egg_token_type_si);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    15,
                    fail,
                    (void *)egg_token_type_si);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    dle =               /0x10/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *dle(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    16,
                    entry,
                    (void *)egg_token_type_dle);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_dle);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      16,
                      fail,
                      (void *)egg_token_type_dle);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x10)
  {
    callback_by_index(&_cbt,
                      16,
                      success,
                      (void *)egg_token_type_dle);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    16,
                    fail,
                    (void *)egg_token_type_dle);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    dc1 =               /0x11/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *dc1(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    17,
                    entry,
                    (void *)egg_token_type_dc1);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_dc1);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      17,
                      fail,
                      (void *)egg_token_type_dc1);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x11)
  {
    callback_by_index(&_cbt,
                      17,
                      success,
                      (void *)egg_token_type_dc1);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    17,
                    fail,
                    (void *)egg_token_type_dc1);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    dc2 =               /0x12/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *dc2(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    18,
                    entry,
                    (void *)egg_token_type_dc2);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_dc2);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      18,
                      fail,
                      (void *)egg_token_type_dc2);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x12)
  {
    callback_by_index(&_cbt,
                      18,
                      success,
                      (void *)egg_token_type_dc2);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    18,
                    fail,
                    (void *)egg_token_type_dc2);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    dc3 =               /0x13/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *dc3(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    19,
                    entry,
                    (void *)egg_token_type_dc3);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_dc3);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      19,
                      fail,
                      (void *)egg_token_type_dc3);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x13)
  {
    callback_by_index(&_cbt,
                      19,
                      success,
                      (void *)egg_token_type_dc3);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    19,
                    fail,
                    (void *)egg_token_type_dc3);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    dc4 =               /0x14/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *dc4(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    20,
                    entry,
                    (void *)egg_token_type_dc4);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_dc4);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      20,
                      fail,
                      (void *)egg_token_type_dc4);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x14)
  {
    callback_by_index(&_cbt,
                      20,
                      success,
                      (void *)egg_token_type_dc4);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    20,
                    fail,
                    (void *)egg_token_type_dc4);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    nak =               /0x15/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *nak(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    21,
                    entry,
                    (void *)egg_token_type_nak);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_nak);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      21,
                      fail,
                      (void *)egg_token_type_nak);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x15)
  {
    callback_by_index(&_cbt,
                      21,
                      success,
                      (void *)egg_token_type_nak);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    21,
                    fail,
                    (void *)egg_token_type_nak);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    syn =               /0x16/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *syn(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    22,
                    entry,
                    (void *)egg_token_type_syn);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_syn);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      22,
                      fail,
                      (void *)egg_token_type_syn);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x16)
  {
    callback_by_index(&_cbt,
                      22,
                      success,
                      (void *)egg_token_type_syn);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    22,
                    fail,
                    (void *)egg_token_type_syn);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    etb =               /0x17/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *etb(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    23,
                    entry,
                    (void *)egg_token_type_etb);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_etb);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      23,
                      fail,
                      (void *)egg_token_type_etb);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x17)
  {
    callback_by_index(&_cbt,
                      23,
                      success,
                      (void *)egg_token_type_etb);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    23,
                    fail,
                    (void *)egg_token_type_etb);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    can =               /0x18/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *can(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    24,
                    entry,
                    (void *)egg_token_type_can);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_can);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      24,
                      fail,
                      (void *)egg_token_type_can);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x18)
  {
    callback_by_index(&_cbt,
                      24,
                      success,
                      (void *)egg_token_type_can);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    24,
                    fail,
                    (void *)egg_token_type_can);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    em =                /0x19/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *em(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    25,
                    entry,
                    (void *)egg_token_type_em);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_em);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      25,
                      fail,
                      (void *)egg_token_type_em);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x19)
  {
    callback_by_index(&_cbt,
                      25,
                      success,
                      (void *)egg_token_type_em);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    25,
                    fail,
                    (void *)egg_token_type_em);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    sub =               /0x1A/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *sub(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    26,
                    entry,
                    (void *)egg_token_type_sub);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_sub);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      26,
                      fail,
                      (void *)egg_token_type_sub);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x1A)
  {
    callback_by_index(&_cbt,
                      26,
                      success,
                      (void *)egg_token_type_sub);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    26,
                    fail,
                    (void *)egg_token_type_sub);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    esc =               /0x1B/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *esc(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    27,
                    entry,
                    (void *)egg_token_type_esc);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_esc);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      27,
                      fail,
                      (void *)egg_token_type_esc);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x1B)
  {
    callback_by_index(&_cbt,
                      27,
                      success,
                      (void *)egg_token_type_esc);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    27,
                    fail,
                    (void *)egg_token_type_esc);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    fs =                /0x1C/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *fs(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    28,
                    entry,
                    (void *)egg_token_type_fs);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_fs);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      28,
                      fail,
                      (void *)egg_token_type_fs);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x1C)
  {
    callback_by_index(&_cbt,
                      28,
                      success,
                      (void *)egg_token_type_fs);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    28,
                    fail,
                    (void *)egg_token_type_fs);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    gs =                /0x1D/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *gs(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    29,
                    entry,
                    (void *)egg_token_type_gs);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_gs);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      29,
                      fail,
                      (void *)egg_token_type_gs);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x1D)
  {
    callback_by_index(&_cbt,
                      29,
                      success,
                      (void *)egg_token_type_gs);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    29,
                    fail,
                    (void *)egg_token_type_gs);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    rs =                /0x1E/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *rs(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    30,
                    entry,
                    (void *)egg_token_type_rs);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_rs);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      30,
                      fail,
                      (void *)egg_token_type_rs);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x1E)
  {
    callback_by_index(&_cbt,
                      30,
                      success,
                      (void *)egg_token_type_rs);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    30,
                    fail,
                    (void *)egg_token_type_rs);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    us =                /0x1F/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *us(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    31,
                    entry,
                    (void *)egg_token_type_us);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_us);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      31,
                      fail,
                      (void *)egg_token_type_us);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x1F)
  {
    callback_by_index(&_cbt,
                      31,
                      success,
                      (void *)egg_token_type_us);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    31,
                    fail,
                    (void *)egg_token_type_us);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    space =             /0x20/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *space(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    32,
                    entry,
                    (void *)egg_token_type_space);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_space);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      32,
                      fail,
                      (void *)egg_token_type_space);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x20)
  {
    callback_by_index(&_cbt,
                      32,
                      success,
                      (void *)egg_token_type_space);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    32,
                    fail,
                    (void *)egg_token_type_space);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    exclamation-point = /0x21/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *exclamation_point(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    33,
                    entry,
                    (void *)egg_token_type_exclamation_point);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_exclamation_point);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      33,
                      fail,
                      (void *)egg_token_type_exclamation_point);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x21)
  {
    callback_by_index(&_cbt,
                      33,
                      success,
                      (void *)egg_token_type_exclamation_point);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    33,
                    fail,
                    (void *)egg_token_type_exclamation_point);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    quote =             /0x22/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *quote(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    34,
                    entry,
                    (void *)egg_token_type_quote);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_quote);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      34,
                      fail,
                      (void *)egg_token_type_quote);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x22)
  {
    callback_by_index(&_cbt,
                      34,
                      success,
                      (void *)egg_token_type_quote);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    34,
                    fail,
                    (void *)egg_token_type_quote);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    number-sign =       /0x23/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *number_sign(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    35,
                    entry,
                    (void *)egg_token_type_number_sign);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_number_sign);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      35,
                      fail,
                      (void *)egg_token_type_number_sign);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x23)
  {
    callback_by_index(&_cbt,
                      35,
                      success,
                      (void *)egg_token_type_number_sign);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    35,
                    fail,
                    (void *)egg_token_type_number_sign);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    dollar =            /0x24/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *dollar(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    36,
                    entry,
                    (void *)egg_token_type_dollar);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_dollar);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      36,
                      fail,
                      (void *)egg_token_type_dollar);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x24)
  {
    callback_by_index(&_cbt,
                      36,
                      success,
                      (void *)egg_token_type_dollar);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    36,
                    fail,
                    (void *)egg_token_type_dollar);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    percent =           /0x25/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *percent(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    37,
                    entry,
                    (void *)egg_token_type_percent);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_percent);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      37,
                      fail,
                      (void *)egg_token_type_percent);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x25)
  {
    callback_by_index(&_cbt,
                      37,
                      success,
                      (void *)egg_token_type_percent);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    37,
                    fail,
                    (void *)egg_token_type_percent);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    ampersand =         /0x26/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *ampersand(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    38,
                    entry,
                    (void *)egg_token_type_ampersand);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_ampersand);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      38,
                      fail,
                      (void *)egg_token_type_ampersand);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x26)
  {
    callback_by_index(&_cbt,
                      38,
                      success,
                      (void *)egg_token_type_ampersand);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    38,
                    fail,
                    (void *)egg_token_type_ampersand);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    single-quote =      /0x27/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *single_quote(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    39,
                    entry,
                    (void *)egg_token_type_single_quote);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_single_quote);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      39,
                      fail,
                      (void *)egg_token_type_single_quote);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x27)
  {
    callback_by_index(&_cbt,
                      39,
                      success,
                      (void *)egg_token_type_single_quote);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    39,
                    fail,
                    (void *)egg_token_type_single_quote);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    open-parenthesis =  /0x28/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *open_parenthesis(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    40,
                    entry,
                    (void *)egg_token_type_open_parenthesis);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_open_parenthesis);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      40,
                      fail,
                      (void *)egg_token_type_open_parenthesis);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x28)
  {
    callback_by_index(&_cbt,
                      40,
                      success,
                      (void *)egg_token_type_open_parenthesis);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    40,
                    fail,
                    (void *)egg_token_type_open_parenthesis);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    close-parenthesis = /0x29/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *close_parenthesis(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    41,
                    entry,
                    (void *)egg_token_type_close_parenthesis);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_close_parenthesis);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      41,
                      fail,
                      (void *)egg_token_type_close_parenthesis);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x29)
  {
    callback_by_index(&_cbt,
                      41,
                      success,
                      (void *)egg_token_type_close_parenthesis);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    41,
                    fail,
                    (void *)egg_token_type_close_parenthesis);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    asterisk =          /0x2A/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *asterisk(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    42,
                    entry,
                    (void *)egg_token_type_asterisk);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_asterisk);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      42,
                      fail,
                      (void *)egg_token_type_asterisk);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x2A)
  {
    callback_by_index(&_cbt,
                      42,
                      success,
                      (void *)egg_token_type_asterisk);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    42,
                    fail,
                    (void *)egg_token_type_asterisk);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    plus =              /0x2B/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *plus(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    43,
                    entry,
                    (void *)egg_token_type_plus);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_plus);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      43,
                      fail,
                      (void *)egg_token_type_plus);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x2B)
  {
    callback_by_index(&_cbt,
                      43,
                      success,
                      (void *)egg_token_type_plus);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    43,
                    fail,
                    (void *)egg_token_type_plus);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    comma =             /0x2C/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *comma(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    44,
                    entry,
                    (void *)egg_token_type_comma);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comma);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      44,
                      fail,
                      (void *)egg_token_type_comma);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x2C)
  {
    callback_by_index(&_cbt,
                      44,
                      success,
                      (void *)egg_token_type_comma);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    44,
                    fail,
                    (void *)egg_token_type_comma);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    minus =             /0x2D/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *minus(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    45,
                    entry,
                    (void *)egg_token_type_minus);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_minus);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      45,
                      fail,
                      (void *)egg_token_type_minus);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x2D)
  {
    callback_by_index(&_cbt,
                      45,
                      success,
                      (void *)egg_token_type_minus);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    45,
                    fail,
                    (void *)egg_token_type_minus);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    period =            /0x2E/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *period(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    46,
                    entry,
                    (void *)egg_token_type_period);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_period);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      46,
                      fail,
                      (void *)egg_token_type_period);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x2E)
  {
    callback_by_index(&_cbt,
                      46,
                      success,
                      (void *)egg_token_type_period);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    46,
                    fail,
                    (void *)egg_token_type_period);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    slash =             /0x2F/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *slash(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    47,
                    entry,
                    (void *)egg_token_type_slash);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_slash);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      47,
                      fail,
                      (void *)egg_token_type_slash);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x2F)
  {
    callback_by_index(&_cbt,
                      47,
                      success,
                      (void *)egg_token_type_slash);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    47,
                    fail,
                    (void *)egg_token_type_slash);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    zero =              /0x30/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *zero(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    48,
                    entry,
                    (void *)egg_token_type_zero);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_zero);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      48,
                      fail,
                      (void *)egg_token_type_zero);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x30)
  {
    callback_by_index(&_cbt,
                      48,
                      success,
                      (void *)egg_token_type_zero);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    48,
                    fail,
                    (void *)egg_token_type_zero);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    one =               /0x31/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *one(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    49,
                    entry,
                    (void *)egg_token_type_one);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_one);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      49,
                      fail,
                      (void *)egg_token_type_one);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x31)
  {
    callback_by_index(&_cbt,
                      49,
                      success,
                      (void *)egg_token_type_one);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    49,
                    fail,
                    (void *)egg_token_type_one);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    two =               /0x32/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *two(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    50,
                    entry,
                    (void *)egg_token_type_two);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_two);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      50,
                      fail,
                      (void *)egg_token_type_two);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x32)
  {
    callback_by_index(&_cbt,
                      50,
                      success,
                      (void *)egg_token_type_two);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    50,
                    fail,
                    (void *)egg_token_type_two);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    three =             /0x33/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *three(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    51,
                    entry,
                    (void *)egg_token_type_three);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_three);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      51,
                      fail,
                      (void *)egg_token_type_three);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x33)
  {
    callback_by_index(&_cbt,
                      51,
                      success,
                      (void *)egg_token_type_three);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    51,
                    fail,
                    (void *)egg_token_type_three);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    four =              /0x34/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *four(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    52,
                    entry,
                    (void *)egg_token_type_four);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_four);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      52,
                      fail,
                      (void *)egg_token_type_four);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x34)
  {
    callback_by_index(&_cbt,
                      52,
                      success,
                      (void *)egg_token_type_four);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    52,
                    fail,
                    (void *)egg_token_type_four);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    five =              /0x35/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *five(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    53,
                    entry,
                    (void *)egg_token_type_five);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_five);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      53,
                      fail,
                      (void *)egg_token_type_five);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x35)
  {
    callback_by_index(&_cbt,
                      53,
                      success,
                      (void *)egg_token_type_five);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    53,
                    fail,
                    (void *)egg_token_type_five);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    six =               /0x36/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *six(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    54,
                    entry,
                    (void *)egg_token_type_six);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_six);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      54,
                      fail,
                      (void *)egg_token_type_six);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x36)
  {
    callback_by_index(&_cbt,
                      54,
                      success,
                      (void *)egg_token_type_six);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    54,
                    fail,
                    (void *)egg_token_type_six);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    seven =             /0x37/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *seven(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    55,
                    entry,
                    (void *)egg_token_type_seven);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_seven);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      55,
                      fail,
                      (void *)egg_token_type_seven);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x37)
  {
    callback_by_index(&_cbt,
                      55,
                      success,
                      (void *)egg_token_type_seven);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    55,
                    fail,
                    (void *)egg_token_type_seven);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    eight =             /0x38/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *eight(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    56,
                    entry,
                    (void *)egg_token_type_eight);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_eight);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      56,
                      fail,
                      (void *)egg_token_type_eight);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x38)
  {
    callback_by_index(&_cbt,
                      56,
                      success,
                      (void *)egg_token_type_eight);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    56,
                    fail,
                    (void *)egg_token_type_eight);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    nine =              /0x39/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *nine(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    57,
                    entry,
                    (void *)egg_token_type_nine);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_nine);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      57,
                      fail,
                      (void *)egg_token_type_nine);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x39)
  {
    callback_by_index(&_cbt,
                      57,
                      success,
                      (void *)egg_token_type_nine);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    57,
                    fail,
                    (void *)egg_token_type_nine);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    colon =             /0x3A/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *colon(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    58,
                    entry,
                    (void *)egg_token_type_colon);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_colon);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      58,
                      fail,
                      (void *)egg_token_type_colon);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x3A)
  {
    callback_by_index(&_cbt,
                      58,
                      success,
                      (void *)egg_token_type_colon);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    58,
                    fail,
                    (void *)egg_token_type_colon);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    semicolon =         /0x3B/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *semicolon(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    59,
                    entry,
                    (void *)egg_token_type_semicolon);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_semicolon);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      59,
                      fail,
                      (void *)egg_token_type_semicolon);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x3B)
  {
    callback_by_index(&_cbt,
                      59,
                      success,
                      (void *)egg_token_type_semicolon);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    59,
                    fail,
                    (void *)egg_token_type_semicolon);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    less-than =         /0x3C/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *less_than(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    60,
                    entry,
                    (void *)egg_token_type_less_than);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_less_than);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      60,
                      fail,
                      (void *)egg_token_type_less_than);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x3C)
  {
    callback_by_index(&_cbt,
                      60,
                      success,
                      (void *)egg_token_type_less_than);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    60,
                    fail,
                    (void *)egg_token_type_less_than);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    equal =             /0x3D/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *equal(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    61,
                    entry,
                    (void *)egg_token_type_equal);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_equal);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      61,
                      fail,
                      (void *)egg_token_type_equal);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x3D)
  {
    callback_by_index(&_cbt,
                      61,
                      success,
                      (void *)egg_token_type_equal);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    61,
                    fail,
                    (void *)egg_token_type_equal);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    greater-than =      /0x3E/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *greater_than(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    62,
                    entry,
                    (void *)egg_token_type_greater_than);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_greater_than);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      62,
                      fail,
                      (void *)egg_token_type_greater_than);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x3E)
  {
    callback_by_index(&_cbt,
                      62,
                      success,
                      (void *)egg_token_type_greater_than);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    62,
                    fail,
                    (void *)egg_token_type_greater_than);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    question-mark =     /0x3F/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *question_mark(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    63,
                    entry,
                    (void *)egg_token_type_question_mark);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_question_mark);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      63,
                      fail,
                      (void *)egg_token_type_question_mark);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x3F)
  {
    callback_by_index(&_cbt,
                      63,
                      success,
                      (void *)egg_token_type_question_mark);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    63,
                    fail,
                    (void *)egg_token_type_question_mark);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    at =                /0x40/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *at(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    64,
                    entry,
                    (void *)egg_token_type_at);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_at);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      64,
                      fail,
                      (void *)egg_token_type_at);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x40)
  {
    callback_by_index(&_cbt,
                      64,
                      success,
                      (void *)egg_token_type_at);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    64,
                    fail,
                    (void *)egg_token_type_at);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    A =                 /0x41/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *A(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    65,
                    entry,
                    (void *)egg_token_type_A);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_A);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      65,
                      fail,
                      (void *)egg_token_type_A);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x41)
  {
    callback_by_index(&_cbt,
                      65,
                      success,
                      (void *)egg_token_type_A);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    65,
                    fail,
                    (void *)egg_token_type_A);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    B =                 /0x42/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *B(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    66,
                    entry,
                    (void *)egg_token_type_B);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_B);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      66,
                      fail,
                      (void *)egg_token_type_B);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x42)
  {
    callback_by_index(&_cbt,
                      66,
                      success,
                      (void *)egg_token_type_B);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    66,
                    fail,
                    (void *)egg_token_type_B);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    C =                 /0x43/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *C(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    67,
                    entry,
                    (void *)egg_token_type_C);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_C);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      67,
                      fail,
                      (void *)egg_token_type_C);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x43)
  {
    callback_by_index(&_cbt,
                      67,
                      success,
                      (void *)egg_token_type_C);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    67,
                    fail,
                    (void *)egg_token_type_C);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    D =                 /0x44/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *D(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    68,
                    entry,
                    (void *)egg_token_type_D);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_D);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      68,
                      fail,
                      (void *)egg_token_type_D);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x44)
  {
    callback_by_index(&_cbt,
                      68,
                      success,
                      (void *)egg_token_type_D);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    68,
                    fail,
                    (void *)egg_token_type_D);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    E =                 /0x45/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *E(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    69,
                    entry,
                    (void *)egg_token_type_E);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_E);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      69,
                      fail,
                      (void *)egg_token_type_E);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x45)
  {
    callback_by_index(&_cbt,
                      69,
                      success,
                      (void *)egg_token_type_E);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    69,
                    fail,
                    (void *)egg_token_type_E);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    F =                 /0x46/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *F(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    70,
                    entry,
                    (void *)egg_token_type_F);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_F);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      70,
                      fail,
                      (void *)egg_token_type_F);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x46)
  {
    callback_by_index(&_cbt,
                      70,
                      success,
                      (void *)egg_token_type_F);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    70,
                    fail,
                    (void *)egg_token_type_F);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    G =                 /0x47/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *G(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    71,
                    entry,
                    (void *)egg_token_type_G);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_G);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      71,
                      fail,
                      (void *)egg_token_type_G);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x47)
  {
    callback_by_index(&_cbt,
                      71,
                      success,
                      (void *)egg_token_type_G);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    71,
                    fail,
                    (void *)egg_token_type_G);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    H =                 /0x48/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *H(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    72,
                    entry,
                    (void *)egg_token_type_H);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_H);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      72,
                      fail,
                      (void *)egg_token_type_H);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x48)
  {
    callback_by_index(&_cbt,
                      72,
                      success,
                      (void *)egg_token_type_H);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    72,
                    fail,
                    (void *)egg_token_type_H);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    I =                 /0x49/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *I(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    73,
                    entry,
                    (void *)egg_token_type_I);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_I);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      73,
                      fail,
                      (void *)egg_token_type_I);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x49)
  {
    callback_by_index(&_cbt,
                      73,
                      success,
                      (void *)egg_token_type_I);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    73,
                    fail,
                    (void *)egg_token_type_I);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    J =                 /0x4A/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *J(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    74,
                    entry,
                    (void *)egg_token_type_J);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_J);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      74,
                      fail,
                      (void *)egg_token_type_J);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x4A)
  {
    callback_by_index(&_cbt,
                      74,
                      success,
                      (void *)egg_token_type_J);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    74,
                    fail,
                    (void *)egg_token_type_J);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    K =                 /0x4B/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *K(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    75,
                    entry,
                    (void *)egg_token_type_K);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_K);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      75,
                      fail,
                      (void *)egg_token_type_K);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x4B)
  {
    callback_by_index(&_cbt,
                      75,
                      success,
                      (void *)egg_token_type_K);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    75,
                    fail,
                    (void *)egg_token_type_K);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    L =                 /0x4C/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *L(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    76,
                    entry,
                    (void *)egg_token_type_L);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_L);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      76,
                      fail,
                      (void *)egg_token_type_L);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x4C)
  {
    callback_by_index(&_cbt,
                      76,
                      success,
                      (void *)egg_token_type_L);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    76,
                    fail,
                    (void *)egg_token_type_L);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    M =                 /0x4D/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *M(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    77,
                    entry,
                    (void *)egg_token_type_M);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_M);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      77,
                      fail,
                      (void *)egg_token_type_M);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x4D)
  {
    callback_by_index(&_cbt,
                      77,
                      success,
                      (void *)egg_token_type_M);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    77,
                    fail,
                    (void *)egg_token_type_M);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    N =                 /0x4E/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *N(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    78,
                    entry,
                    (void *)egg_token_type_N);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_N);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      78,
                      fail,
                      (void *)egg_token_type_N);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x4E)
  {
    callback_by_index(&_cbt,
                      78,
                      success,
                      (void *)egg_token_type_N);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    78,
                    fail,
                    (void *)egg_token_type_N);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    O =                 /0x4F/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *O(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    79,
                    entry,
                    (void *)egg_token_type_O);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_O);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      79,
                      fail,
                      (void *)egg_token_type_O);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x4F)
  {
    callback_by_index(&_cbt,
                      79,
                      success,
                      (void *)egg_token_type_O);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    79,
                    fail,
                    (void *)egg_token_type_O);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    P =                 /0x50/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *P(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    80,
                    entry,
                    (void *)egg_token_type_P);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_P);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      80,
                      fail,
                      (void *)egg_token_type_P);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x50)
  {
    callback_by_index(&_cbt,
                      80,
                      success,
                      (void *)egg_token_type_P);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    80,
                    fail,
                    (void *)egg_token_type_P);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    Q =                 /0x51/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *Q(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    81,
                    entry,
                    (void *)egg_token_type_Q);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_Q);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      81,
                      fail,
                      (void *)egg_token_type_Q);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x51)
  {
    callback_by_index(&_cbt,
                      81,
                      success,
                      (void *)egg_token_type_Q);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    81,
                    fail,
                    (void *)egg_token_type_Q);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    R =                 /0x52/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *R(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    82,
                    entry,
                    (void *)egg_token_type_R);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_R);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      82,
                      fail,
                      (void *)egg_token_type_R);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x52)
  {
    callback_by_index(&_cbt,
                      82,
                      success,
                      (void *)egg_token_type_R);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    82,
                    fail,
                    (void *)egg_token_type_R);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    S =                 /0x53/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *S(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    83,
                    entry,
                    (void *)egg_token_type_S);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_S);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      83,
                      fail,
                      (void *)egg_token_type_S);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x53)
  {
    callback_by_index(&_cbt,
                      83,
                      success,
                      (void *)egg_token_type_S);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    83,
                    fail,
                    (void *)egg_token_type_S);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    T =                 /0x54/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *T(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    84,
                    entry,
                    (void *)egg_token_type_T);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_T);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      84,
                      fail,
                      (void *)egg_token_type_T);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x54)
  {
    callback_by_index(&_cbt,
                      84,
                      success,
                      (void *)egg_token_type_T);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    84,
                    fail,
                    (void *)egg_token_type_T);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    U =                 /0x55/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *U(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    85,
                    entry,
                    (void *)egg_token_type_U);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_U);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      85,
                      fail,
                      (void *)egg_token_type_U);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x55)
  {
    callback_by_index(&_cbt,
                      85,
                      success,
                      (void *)egg_token_type_U);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    85,
                    fail,
                    (void *)egg_token_type_U);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    V =                 /0x56/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *V(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    86,
                    entry,
                    (void *)egg_token_type_V);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_V);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      86,
                      fail,
                      (void *)egg_token_type_V);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x56)
  {
    callback_by_index(&_cbt,
                      86,
                      success,
                      (void *)egg_token_type_V);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    86,
                    fail,
                    (void *)egg_token_type_V);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    W =                 /0x57/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *W(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    87,
                    entry,
                    (void *)egg_token_type_W);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_W);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      87,
                      fail,
                      (void *)egg_token_type_W);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x57)
  {
    callback_by_index(&_cbt,
                      87,
                      success,
                      (void *)egg_token_type_W);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    87,
                    fail,
                    (void *)egg_token_type_W);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    X =                 /0x58/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *X(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    88,
                    entry,
                    (void *)egg_token_type_X);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_X);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      88,
                      fail,
                      (void *)egg_token_type_X);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x58)
  {
    callback_by_index(&_cbt,
                      88,
                      success,
                      (void *)egg_token_type_X);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    88,
                    fail,
                    (void *)egg_token_type_X);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    Y =                 /0x59/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *Y(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    89,
                    entry,
                    (void *)egg_token_type_Y);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_Y);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      89,
                      fail,
                      (void *)egg_token_type_Y);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x59)
  {
    callback_by_index(&_cbt,
                      89,
                      success,
                      (void *)egg_token_type_Y);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    89,
                    fail,
                    (void *)egg_token_type_Y);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    Z =                 /0x5A/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *Z(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    90,
                    entry,
                    (void *)egg_token_type_Z);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_Z);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      90,
                      fail,
                      (void *)egg_token_type_Z);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x5A)
  {
    callback_by_index(&_cbt,
                      90,
                      success,
                      (void *)egg_token_type_Z);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    90,
                    fail,
                    (void *)egg_token_type_Z);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    open-bracket =      /0x5B/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *open_bracket(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    91,
                    entry,
                    (void *)egg_token_type_open_bracket);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_open_bracket);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      91,
                      fail,
                      (void *)egg_token_type_open_bracket);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x5B)
  {
    callback_by_index(&_cbt,
                      91,
                      success,
                      (void *)egg_token_type_open_bracket);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    91,
                    fail,
                    (void *)egg_token_type_open_bracket);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    back-slash =        /0x5C/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *back_slash(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    92,
                    entry,
                    (void *)egg_token_type_back_slash);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_back_slash);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      92,
                      fail,
                      (void *)egg_token_type_back_slash);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x5C)
  {
    callback_by_index(&_cbt,
                      92,
                      success,
                      (void *)egg_token_type_back_slash);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    92,
                    fail,
                    (void *)egg_token_type_back_slash);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    close-bracket =     /0x5D/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *close_bracket(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    93,
                    entry,
                    (void *)egg_token_type_close_bracket);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_close_bracket);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      93,
                      fail,
                      (void *)egg_token_type_close_bracket);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x5D)
  {
    callback_by_index(&_cbt,
                      93,
                      success,
                      (void *)egg_token_type_close_bracket);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    93,
                    fail,
                    (void *)egg_token_type_close_bracket);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    carat =             /0x5E/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *carat(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    94,
                    entry,
                    (void *)egg_token_type_carat);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_carat);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      94,
                      fail,
                      (void *)egg_token_type_carat);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x5E)
  {
    callback_by_index(&_cbt,
                      94,
                      success,
                      (void *)egg_token_type_carat);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    94,
                    fail,
                    (void *)egg_token_type_carat);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    underscore =        /0x5F/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *underscore(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    95,
                    entry,
                    (void *)egg_token_type_underscore);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_underscore);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      95,
                      fail,
                      (void *)egg_token_type_underscore);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x5F)
  {
    callback_by_index(&_cbt,
                      95,
                      success,
                      (void *)egg_token_type_underscore);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    95,
                    fail,
                    (void *)egg_token_type_underscore);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    back-quote =        /0x60/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *back_quote(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    96,
                    entry,
                    (void *)egg_token_type_back_quote);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_back_quote);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      96,
                      fail,
                      (void *)egg_token_type_back_quote);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x60)
  {
    callback_by_index(&_cbt,
                      96,
                      success,
                      (void *)egg_token_type_back_quote);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    96,
                    fail,
                    (void *)egg_token_type_back_quote);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    a =                 /0x61/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *a(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    97,
                    entry,
                    (void *)egg_token_type_a);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_a);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      97,
                      fail,
                      (void *)egg_token_type_a);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x61)
  {
    callback_by_index(&_cbt,
                      97,
                      success,
                      (void *)egg_token_type_a);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    97,
                    fail,
                    (void *)egg_token_type_a);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    b =                 /0x62/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *b(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    98,
                    entry,
                    (void *)egg_token_type_b);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_b);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      98,
                      fail,
                      (void *)egg_token_type_b);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x62)
  {
    callback_by_index(&_cbt,
                      98,
                      success,
                      (void *)egg_token_type_b);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    98,
                    fail,
                    (void *)egg_token_type_b);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    c =                 /0x63/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *c(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    99,
                    entry,
                    (void *)egg_token_type_c);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_c);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      99,
                      fail,
                      (void *)egg_token_type_c);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x63)
  {
    callback_by_index(&_cbt,
                      99,
                      success,
                      (void *)egg_token_type_c);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    99,
                    fail,
                    (void *)egg_token_type_c);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    d =                 /0x64/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *d(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    100,
                    entry,
                    (void *)egg_token_type_d);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_d);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      100,
                      fail,
                      (void *)egg_token_type_d);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x64)
  {
    callback_by_index(&_cbt,
                      100,
                      success,
                      (void *)egg_token_type_d);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    100,
                    fail,
                    (void *)egg_token_type_d);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    e =                 /0x65/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *e(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    101,
                    entry,
                    (void *)egg_token_type_e);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_e);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      101,
                      fail,
                      (void *)egg_token_type_e);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x65)
  {
    callback_by_index(&_cbt,
                      101,
                      success,
                      (void *)egg_token_type_e);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    101,
                    fail,
                    (void *)egg_token_type_e);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    f =                 /0x66/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *f(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    102,
                    entry,
                    (void *)egg_token_type_f);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_f);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      102,
                      fail,
                      (void *)egg_token_type_f);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x66)
  {
    callback_by_index(&_cbt,
                      102,
                      success,
                      (void *)egg_token_type_f);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    102,
                    fail,
                    (void *)egg_token_type_f);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    g =                 /0x67/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *g(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    103,
                    entry,
                    (void *)egg_token_type_g);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_g);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      103,
                      fail,
                      (void *)egg_token_type_g);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x67)
  {
    callback_by_index(&_cbt,
                      103,
                      success,
                      (void *)egg_token_type_g);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    103,
                    fail,
                    (void *)egg_token_type_g);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    h =                 /0x68/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *h(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    104,
                    entry,
                    (void *)egg_token_type_h);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_h);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      104,
                      fail,
                      (void *)egg_token_type_h);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x68)
  {
    callback_by_index(&_cbt,
                      104,
                      success,
                      (void *)egg_token_type_h);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    104,
                    fail,
                    (void *)egg_token_type_h);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    i =                 /0x69/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *i(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    105,
                    entry,
                    (void *)egg_token_type_i);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_i);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      105,
                      fail,
                      (void *)egg_token_type_i);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x69)
  {
    callback_by_index(&_cbt,
                      105,
                      success,
                      (void *)egg_token_type_i);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    105,
                    fail,
                    (void *)egg_token_type_i);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    j =                 /0x6A/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *j(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    106,
                    entry,
                    (void *)egg_token_type_j);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_j);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      106,
                      fail,
                      (void *)egg_token_type_j);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x6A)
  {
    callback_by_index(&_cbt,
                      106,
                      success,
                      (void *)egg_token_type_j);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    106,
                    fail,
                    (void *)egg_token_type_j);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    k =                 /0x6B/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *k(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    107,
                    entry,
                    (void *)egg_token_type_k);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_k);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      107,
                      fail,
                      (void *)egg_token_type_k);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x6B)
  {
    callback_by_index(&_cbt,
                      107,
                      success,
                      (void *)egg_token_type_k);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    107,
                    fail,
                    (void *)egg_token_type_k);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    l =                 /0x6C/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *l(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    108,
                    entry,
                    (void *)egg_token_type_l);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_l);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      108,
                      fail,
                      (void *)egg_token_type_l);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x6C)
  {
    callback_by_index(&_cbt,
                      108,
                      success,
                      (void *)egg_token_type_l);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    108,
                    fail,
                    (void *)egg_token_type_l);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    m =                 /0x6D/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *m(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    109,
                    entry,
                    (void *)egg_token_type_m);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_m);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      109,
                      fail,
                      (void *)egg_token_type_m);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x6D)
  {
    callback_by_index(&_cbt,
                      109,
                      success,
                      (void *)egg_token_type_m);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    109,
                    fail,
                    (void *)egg_token_type_m);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    n =                 /0x6E/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *n(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    110,
                    entry,
                    (void *)egg_token_type_n);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_n);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      110,
                      fail,
                      (void *)egg_token_type_n);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x6E)
  {
    callback_by_index(&_cbt,
                      110,
                      success,
                      (void *)egg_token_type_n);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    110,
                    fail,
                    (void *)egg_token_type_n);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    o =                 /0x6F/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *o(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    111,
                    entry,
                    (void *)egg_token_type_o);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_o);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      111,
                      fail,
                      (void *)egg_token_type_o);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x6F)
  {
    callback_by_index(&_cbt,
                      111,
                      success,
                      (void *)egg_token_type_o);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    111,
                    fail,
                    (void *)egg_token_type_o);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    p =                 /0x70/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *p(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    112,
                    entry,
                    (void *)egg_token_type_p);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_p);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      112,
                      fail,
                      (void *)egg_token_type_p);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x70)
  {
    callback_by_index(&_cbt,
                      112,
                      success,
                      (void *)egg_token_type_p);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    112,
                    fail,
                    (void *)egg_token_type_p);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    q =                 /0x71/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *q(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    113,
                    entry,
                    (void *)egg_token_type_q);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_q);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      113,
                      fail,
                      (void *)egg_token_type_q);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x71)
  {
    callback_by_index(&_cbt,
                      113,
                      success,
                      (void *)egg_token_type_q);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    113,
                    fail,
                    (void *)egg_token_type_q);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    r =                 /0x72/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *r(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    114,
                    entry,
                    (void *)egg_token_type_r);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_r);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      114,
                      fail,
                      (void *)egg_token_type_r);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x72)
  {
    callback_by_index(&_cbt,
                      114,
                      success,
                      (void *)egg_token_type_r);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    114,
                    fail,
                    (void *)egg_token_type_r);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    s =                 /0x73/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *s(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    115,
                    entry,
                    (void *)egg_token_type_s);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_s);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      115,
                      fail,
                      (void *)egg_token_type_s);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x73)
  {
    callback_by_index(&_cbt,
                      115,
                      success,
                      (void *)egg_token_type_s);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    115,
                    fail,
                    (void *)egg_token_type_s);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    t =                 /0x74/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *t(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    116,
                    entry,
                    (void *)egg_token_type_t);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_t);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      116,
                      fail,
                      (void *)egg_token_type_t);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x74)
  {
    callback_by_index(&_cbt,
                      116,
                      success,
                      (void *)egg_token_type_t);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    116,
                    fail,
                    (void *)egg_token_type_t);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    u =                 /0x75/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *u(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    117,
                    entry,
                    (void *)egg_token_type_u);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_u);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      117,
                      fail,
                      (void *)egg_token_type_u);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x75)
  {
    callback_by_index(&_cbt,
                      117,
                      success,
                      (void *)egg_token_type_u);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    117,
                    fail,
                    (void *)egg_token_type_u);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    v =                 /0x76/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *v(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    118,
                    entry,
                    (void *)egg_token_type_v);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_v);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      118,
                      fail,
                      (void *)egg_token_type_v);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x76)
  {
    callback_by_index(&_cbt,
                      118,
                      success,
                      (void *)egg_token_type_v);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    118,
                    fail,
                    (void *)egg_token_type_v);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    w =                 /0x77/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *w(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    119,
                    entry,
                    (void *)egg_token_type_w);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_w);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      119,
                      fail,
                      (void *)egg_token_type_w);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x77)
  {
    callback_by_index(&_cbt,
                      119,
                      success,
                      (void *)egg_token_type_w);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    119,
                    fail,
                    (void *)egg_token_type_w);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    x =                 /0x78/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *x(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    120,
                    entry,
                    (void *)egg_token_type_x);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_x);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      120,
                      fail,
                      (void *)egg_token_type_x);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x78)
  {
    callback_by_index(&_cbt,
                      120,
                      success,
                      (void *)egg_token_type_x);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    120,
                    fail,
                    (void *)egg_token_type_x);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    y =                 /0x79/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *y(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    121,
                    entry,
                    (void *)egg_token_type_y);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_y);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      121,
                      fail,
                      (void *)egg_token_type_y);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x79)
  {
    callback_by_index(&_cbt,
                      121,
                      success,
                      (void *)egg_token_type_y);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    121,
                    fail,
                    (void *)egg_token_type_y);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    z =                 /0x7A/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *z(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    122,
                    entry,
                    (void *)egg_token_type_z);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_z);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      122,
                      fail,
                      (void *)egg_token_type_z);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x7A)
  {
    callback_by_index(&_cbt,
                      122,
                      success,
                      (void *)egg_token_type_z);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    122,
                    fail,
                    (void *)egg_token_type_z);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    open-brace =        /0x7B/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *open_brace(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    123,
                    entry,
                    (void *)egg_token_type_open_brace);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_open_brace);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      123,
                      fail,
                      (void *)egg_token_type_open_brace);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x7B)
  {
    callback_by_index(&_cbt,
                      123,
                      success,
                      (void *)egg_token_type_open_brace);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    123,
                    fail,
                    (void *)egg_token_type_open_brace);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    bar =               /0x7C/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *bar(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    124,
                    entry,
                    (void *)egg_token_type_bar);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_bar);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      124,
                      fail,
                      (void *)egg_token_type_bar);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x7C)
  {
    callback_by_index(&_cbt,
                      124,
                      success,
                      (void *)egg_token_type_bar);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    124,
                    fail,
                    (void *)egg_token_type_bar);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    close-brace =       /0x7D/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *close_brace(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    125,
                    entry,
                    (void *)egg_token_type_close_brace);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_close_brace);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      125,
                      fail,
                      (void *)egg_token_type_close_brace);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x7D)
  {
    callback_by_index(&_cbt,
                      125,
                      success,
                      (void *)egg_token_type_close_brace);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    125,
                    fail,
                    (void *)egg_token_type_close_brace);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    tilde =             /0x7E/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *tilde(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    126,
                    entry,
                    (void *)egg_token_type_tilde);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_tilde);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      126,
                      fail,
                      (void *)egg_token_type_tilde);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x7E)
  {
    callback_by_index(&_cbt,
                      126,
                      success,
                      (void *)egg_token_type_tilde);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    126,
                    fail,
                    (void *)egg_token_type_tilde);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    del =               /0x7F/ ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *del(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    127,
                    entry,
                    (void *)egg_token_type_del);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_del);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      127,
                      fail,
                      (void *)egg_token_type_del);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x7F)
  {
    callback_by_index(&_cbt,
                      127,
                      success,
                      (void *)egg_token_type_del);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    127,
                    fail,
                    (void *)egg_token_type_del);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    control-character = nul | soh | stx | etx | eot | enq | ack | bel | bs
                      | so | si | dle | dc1 | dc2 | dc3 | dc4 | nak | syn
                      | etb | can | em | sub | esc | fs | gs | rs | us
                      | del ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *control_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    128,
                    entry,
                    (void *)egg_token_type_control_character);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_control_character);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      128,
                      fail,
                      (void *)egg_token_type_control_character);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = nul()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = soh()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = stx()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = etx()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = eot()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = enq()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = ack()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = bel()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = bs()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = so()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = si()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = dle()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = dc1()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = dc2()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = dc3()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = dc4()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = nak()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = syn()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = etb()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = can()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = em()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = sub()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = esc()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = fs()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = gs()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = rs()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = us()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = del()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      128,
                      success,
                      (void *)egg_token_type_control_character);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    128,
                    fail,
                    (void *)egg_token_type_control_character);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    upper-case-letter = A | B | C | D | E | F | G | H | I | J | K | L | M
                      | N | O | P | Q | R | S | T | U | V | W | X | Y | Z
                      ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *upper_case_letter(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    129,
                    entry,
                    (void *)egg_token_type_upper_case_letter);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_upper_case_letter);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      129,
                      fail,
                      (void *)egg_token_type_upper_case_letter);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = A()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = B()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = C()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = D()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = E()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = F()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = G()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = H()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = I()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = J()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = K()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = L()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = M()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = N()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = O()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = P()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = Q()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = R()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = S()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = T()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = U()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = V()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = W()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = X()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = Y()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = Z()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      129,
                      success,
                      (void *)egg_token_type_upper_case_letter);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    129,
                    fail,
                    (void *)egg_token_type_upper_case_letter);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    lower-case-letter = a | b | c | d | e | f | g | h | i | j | k | l | m
                      | n | o | p | q | r | s | t | u | v | w | x | y | z
                      ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *lower_case_letter(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    130,
                    entry,
                    (void *)egg_token_type_lower_case_letter);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_lower_case_letter);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      130,
                      fail,
                      (void *)egg_token_type_lower_case_letter);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = a()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = b()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = c()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = d()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = e()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = f()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = g()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = h()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = i()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = j()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = k()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = l()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = m()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = n()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = o()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = p()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = q()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = r()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = s()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = t()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = u()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = v()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = w()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = x()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = y()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = z()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      130,
                      success,
                      (void *)egg_token_type_lower_case_letter);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    130,
                    fail,
                    (void *)egg_token_type_lower_case_letter);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    letter = upper-case-letter | lower-case-letter ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *letter(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    131,
                    entry,
                    (void *)egg_token_type_letter);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_letter);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      131,
                      fail,
                      (void *)egg_token_type_letter);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = upper_case_letter()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      131,
                      success,
                      (void *)egg_token_type_letter);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = lower_case_letter()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      131,
                      success,
                      (void *)egg_token_type_letter);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    131,
                    fail,
                    (void *)egg_token_type_letter);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    binary-digit = zero | one ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *binary_digit(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    132,
                    entry,
                    (void *)egg_token_type_binary_digit);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_binary_digit);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      132,
                      fail,
                      (void *)egg_token_type_binary_digit);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = zero()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      132,
                      success,
                      (void *)egg_token_type_binary_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = one()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      132,
                      success,
                      (void *)egg_token_type_binary_digit);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    132,
                    fail,
                    (void *)egg_token_type_binary_digit);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    octal-digit = zero | one | two | three | four | five | six | seven ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *octal_digit(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    133,
                    entry,
                    (void *)egg_token_type_octal_digit);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_octal_digit);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      133,
                      fail,
                      (void *)egg_token_type_octal_digit);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = zero()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      133,
                      success,
                      (void *)egg_token_type_octal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = one()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      133,
                      success,
                      (void *)egg_token_type_octal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = two()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      133,
                      success,
                      (void *)egg_token_type_octal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = three()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      133,
                      success,
                      (void *)egg_token_type_octal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = four()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      133,
                      success,
                      (void *)egg_token_type_octal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = five()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      133,
                      success,
                      (void *)egg_token_type_octal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = six()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      133,
                      success,
                      (void *)egg_token_type_octal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = seven()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      133,
                      success,
                      (void *)egg_token_type_octal_digit);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    133,
                    fail,
                    (void *)egg_token_type_octal_digit);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    decimal-digit = zero | one | two | three | four
                  | five | six | seven | eight | nine ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *decimal_digit(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    134,
                    entry,
                    (void *)egg_token_type_decimal_digit);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_decimal_digit);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      134,
                      fail,
                      (void *)egg_token_type_decimal_digit);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = zero()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      134,
                      success,
                      (void *)egg_token_type_decimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = one()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      134,
                      success,
                      (void *)egg_token_type_decimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = two()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      134,
                      success,
                      (void *)egg_token_type_decimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = three()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      134,
                      success,
                      (void *)egg_token_type_decimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = four()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      134,
                      success,
                      (void *)egg_token_type_decimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = five()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      134,
                      success,
                      (void *)egg_token_type_decimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = six()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      134,
                      success,
                      (void *)egg_token_type_decimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = seven()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      134,
                      success,
                      (void *)egg_token_type_decimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = eight()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      134,
                      success,
                      (void *)egg_token_type_decimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = nine()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      134,
                      success,
                      (void *)egg_token_type_decimal_digit);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    134,
                    fail,
                    (void *)egg_token_type_decimal_digit);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    hexadecimal-digit = zero | one | two | three | four
                      | five | six | seven | eight | nine
                      | A | B | C | D | E | F
                      | a | b | c | d | e | f ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *hexadecimal_digit(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    135,
                    entry,
                    (void *)egg_token_type_hexadecimal_digit);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_hexadecimal_digit);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      135,
                      fail,
                      (void *)egg_token_type_hexadecimal_digit);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = zero()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = one()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = two()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = three()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = four()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = five()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = six()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = seven()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = eight()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = nine()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = A()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = B()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = C()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = D()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = E()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = F()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = a()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = b()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = c()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = d()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = e()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = f()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      135,
                      success,
                      (void *)egg_token_type_hexadecimal_digit);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    135,
                    fail,
                    (void *)egg_token_type_hexadecimal_digit);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    white-space = space | ht | lf | vt | ff | cr ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *white_space(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    136,
                    entry,
                    (void *)egg_token_type_white_space);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_white_space);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      136,
                      fail,
                      (void *)egg_token_type_white_space);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = space()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      136,
                      success,
                      (void *)egg_token_type_white_space);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = ht()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      136,
                      success,
                      (void *)egg_token_type_white_space);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = lf()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      136,
                      success,
                      (void *)egg_token_type_white_space);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = vt()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      136,
                      success,
                      (void *)egg_token_type_white_space);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = ff()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      136,
                      success,
                      (void *)egg_token_type_white_space);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = cr()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      136,
                      success,
                      (void *)egg_token_type_white_space);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    136,
                    fail,
                    (void *)egg_token_type_white_space);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    common-character = exclamation-point | number-sign | dollar | percent
                     | ampersand | plus | comma | minus | period | colon
                     | semicolon | less-than | equal | greater-than
                     | question-mark | at | open-bracket | back-slash
                     | close-bracket | carat | underscore | back-quote
                     | open-brace | bar | close-brace | tilde | letter
                     | decimal-digit ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *common_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    137,
                    entry,
                    (void *)egg_token_type_common_character);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_common_character);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      137,
                      fail,
                      (void *)egg_token_type_common_character);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = exclamation_point()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = number_sign()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = dollar()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = percent()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = ampersand()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = plus()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comma()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = minus()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = period()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = colon()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = semicolon()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = less_than()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = equal()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = greater_than()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = question_mark()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = at()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = open_bracket()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = back_slash()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = close_bracket()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = carat()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = underscore()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = back_quote()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = open_brace()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = bar()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = close_brace()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = tilde()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = letter()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = decimal_digit()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      137,
                      success,
                      (void *)egg_token_type_common_character);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    137,
                    fail,
                    (void *)egg_token_type_common_character);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    literal-character = common-character
                      | space
                      | open-parenthesis
                      | close-parenthesis
                      | asterisk ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *literal_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    138,
                    entry,
                    (void *)egg_token_type_literal_character);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_literal_character);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      138,
                      fail,
                      (void *)egg_token_type_literal_character);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = common_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      138,
                      success,
                      (void *)egg_token_type_literal_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = space()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      138,
                      success,
                      (void *)egg_token_type_literal_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = open_parenthesis()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      138,
                      success,
                      (void *)egg_token_type_literal_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = close_parenthesis()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      138,
                      success,
                      (void *)egg_token_type_literal_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = asterisk()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      138,
                      success,
                      (void *)egg_token_type_literal_character);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    138,
                    fail,
                    (void *)egg_token_type_literal_character);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    comment-basic-character = common-character
                            | white-space
                            | quote
                            | single-quote
                            | slash ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *comment_basic_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    139,
                    entry,
                    (void *)egg_token_type_comment_basic_character);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comment_basic_character);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      139,
                      fail,
                      (void *)egg_token_type_comment_basic_character);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = common_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      139,
                      success,
                      (void *)egg_token_type_comment_basic_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = white_space()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      139,
                      success,
                      (void *)egg_token_type_comment_basic_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = quote()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      139,
                      success,
                      (void *)egg_token_type_comment_basic_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = single_quote()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      139,
                      success,
                      (void *)egg_token_type_comment_basic_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = slash()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      139,
                      success,
                      (void *)egg_token_type_comment_basic_character);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    139,
                    fail,
                    (void *)egg_token_type_comment_basic_character);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    non-comment-start-character = comment-basic-character
                                | close-parenthesis ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *non_comment_start_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    140,
                    entry,
                    (void *)egg_token_type_non_comment_start_character);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_non_comment_start_character);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      140,
                      fail,
                      (void *)egg_token_type_non_comment_start_character);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comment_basic_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      140,
                      success,
                      (void *)egg_token_type_non_comment_start_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = close_parenthesis()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      140,
                      success,
                      (void *)egg_token_type_non_comment_start_character);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    140,
                    fail,
                    (void *)egg_token_type_non_comment_start_character);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    non-comment-end-character = comment-basic-character
                              | open-parenthesis ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *non_comment_end_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    141,
                    entry,
                    (void *)egg_token_type_non_comment_end_character);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_non_comment_end_character);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      141,
                      fail,
                      (void *)egg_token_type_non_comment_end_character);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comment_basic_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      141,
                      success,
                      (void *)egg_token_type_non_comment_end_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = open_parenthesis()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      141,
                      success,
                      (void *)egg_token_type_non_comment_end_character);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    141,
                    fail,
                    (void *)egg_token_type_non_comment_end_character);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    non-comment-start-sequence = open-parenthesis
                                 + non-comment-start-character ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *non_comment_start_sequence(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    142,
                    entry,
                    (void *)egg_token_type_non_comment_start_sequence);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_non_comment_start_sequence);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      142,
                      fail,
                      (void *)egg_token_type_non_comment_start_sequence);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = open_parenthesis()))
  {
    dir = egg_token_after;
    t1 = t2;
    if (egg_token_add(t1, dir, t2 = non_comment_start_character()))
    {
      dir = egg_token_after;
      t1 = t2;
      callback_by_index(&_cbt,
                        142,
                        success,
                        (void *)egg_token_type_non_comment_start_sequence);

      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    142,
                    fail,
                    (void *)egg_token_type_non_comment_start_sequence);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    non-comment-end-sequence = asterisk
                               + non-comment-end-character ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *non_comment_end_sequence(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    143,
                    entry,
                    (void *)egg_token_type_non_comment_end_sequence);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_non_comment_end_sequence);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      143,
                      fail,
                      (void *)egg_token_type_non_comment_end_sequence);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = asterisk()))
  {
    dir = egg_token_after;
    t1 = t2;
    if (egg_token_add(t1, dir, t2 = non_comment_end_character()))
    {
      dir = egg_token_after;
      t1 = t2;
      callback_by_index(&_cbt,
                        143,
                        success,
                        (void *)egg_token_type_non_comment_end_sequence);

      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    143,
                    fail,
                    (void *)egg_token_type_non_comment_end_sequence);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    comment-character = comment-basic-character
                      | non-comment-start-sequence
                      | non-comment-end-sequence
                      | close-parenthesis ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *comment_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    144,
                    entry,
                    (void *)egg_token_type_comment_character);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comment_character);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      144,
                      fail,
                      (void *)egg_token_type_comment_character);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comment_basic_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      144,
                      success,
                      (void *)egg_token_type_comment_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = non_comment_start_sequence()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      144,
                      success,
                      (void *)egg_token_type_comment_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = non_comment_end_sequence()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      144,
                      success,
                      (void *)egg_token_type_comment_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = close_parenthesis()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      144,
                      success,
                      (void *)egg_token_type_comment_character);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    144,
                    fail,
                    (void *)egg_token_type_comment_character);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    single-quoted-character = literal-character | quote ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *single_quoted_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    145,
                    entry,
                    (void *)egg_token_type_single_quoted_character);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_single_quoted_character);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      145,
                      fail,
                      (void *)egg_token_type_single_quoted_character);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = literal_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      145,
                      success,
                      (void *)egg_token_type_single_quoted_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = quote()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      145,
                      success,
                      (void *)egg_token_type_single_quoted_character);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    145,
                    fail,
                    (void *)egg_token_type_single_quoted_character);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    quoted-character = literal-character | single-quote ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *quoted_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    146,
                    entry,
                    (void *)egg_token_type_quoted_character);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_quoted_character);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      146,
                      fail,
                      (void *)egg_token_type_quoted_character);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = literal_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      146,
                      success,
                      (void *)egg_token_type_quoted_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = single_quote()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      146,
                      success,
                      (void *)egg_token_type_quoted_character);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    146,
                    fail,
                    (void *)egg_token_type_quoted_character);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    phrase-conjugator = underscore | minus ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *phrase_conjugator(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    147,
                    entry,
                    (void *)egg_token_type_phrase_conjugator);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_phrase_conjugator);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      147,
                      fail,
                      (void *)egg_token_type_phrase_conjugator);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = underscore()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      147,
                      success,
                      (void *)egg_token_type_phrase_conjugator);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = minus()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      147,
                      success,
                      (void *)egg_token_type_phrase_conjugator);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    147,
                    fail,
                    (void *)egg_token_type_phrase_conjugator);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    phrase-name-character = letter | decimal_digit | phrase-conjugator ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *phrase_name_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    148,
                    entry,
                    (void *)egg_token_type_phrase_name_character);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_phrase_name_character);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      148,
                      fail,
                      (void *)egg_token_type_phrase_name_character);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = letter()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      148,
                      success,
                      (void *)egg_token_type_phrase_name_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = decimal_digit()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      148,
                      success,
                      (void *)egg_token_type_phrase_name_character);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = phrase_conjugator()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      148,
                      success,
                      (void *)egg_token_type_phrase_name_character);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    148,
                    fail,
                    (void *)egg_token_type_phrase_name_character);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    binary-indicator = b | B ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *binary_indicator(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    149,
                    entry,
                    (void *)egg_token_type_binary_indicator);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_binary_indicator);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      149,
                      fail,
                      (void *)egg_token_type_binary_indicator);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = b()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      149,
                      success,
                      (void *)egg_token_type_binary_indicator);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = B()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      149,
                      success,
                      (void *)egg_token_type_binary_indicator);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    149,
                    fail,
                    (void *)egg_token_type_binary_indicator);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    octal-indicator = o | O ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *octal_indicator(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    150,
                    entry,
                    (void *)egg_token_type_octal_indicator);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_octal_indicator);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      150,
                      fail,
                      (void *)egg_token_type_octal_indicator);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = o()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      150,
                      success,
                      (void *)egg_token_type_octal_indicator);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = O()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      150,
                      success,
                      (void *)egg_token_type_octal_indicator);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    150,
                    fail,
                    (void *)egg_token_type_octal_indicator);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    hexadecimal-indicator = x | X ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *hexadecimal_indicator(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    151,
                    entry,
                    (void *)egg_token_type_hexadecimal_indicator);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_hexadecimal_indicator);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      151,
                      fail,
                      (void *)egg_token_type_hexadecimal_indicator);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = x()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      151,
                      success,
                      (void *)egg_token_type_hexadecimal_indicator);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = X()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      151,
                      success,
                      (void *)egg_token_type_hexadecimal_indicator);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    151,
                    fail,
                    (void *)egg_token_type_hexadecimal_indicator);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    comment-start-symbol = open-parenthesis + asterisk ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *comment_start_symbol(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    152,
                    entry,
                    (void *)egg_token_type_comment_start_symbol);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comment_start_symbol);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      152,
                      fail,
                      (void *)egg_token_type_comment_start_symbol);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = open_parenthesis()))
  {
    dir = egg_token_after;
    t1 = t2;
    if (egg_token_add(t1, dir, t2 = asterisk()))
    {
      dir = egg_token_after;
      t1 = t2;
      callback_by_index(&_cbt,
                        152,
                        success,
                        (void *)egg_token_type_comment_start_symbol);

      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    152,
                    fail,
                    (void *)egg_token_type_comment_start_symbol);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    comment-end-symbol = asterisk + close-parenthesis ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *comment_end_symbol(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    153,
                    entry,
                    (void *)egg_token_type_comment_end_symbol);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comment_end_symbol);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      153,
                      fail,
                      (void *)egg_token_type_comment_end_symbol);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = asterisk()))
  {
    dir = egg_token_after;
    t1 = t2;
    if (egg_token_add(t1, dir, t2 = close_parenthesis()))
    {
      dir = egg_token_after;
      t1 = t2;
      callback_by_index(&_cbt,
                        153,
                        success,
                        (void *)egg_token_type_comment_end_symbol);

      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    153,
                    fail,
                    (void *)egg_token_type_comment_end_symbol);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    alternation-symbol = bar ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *alternation_symbol(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    154,
                    entry,
                    (void *)egg_token_type_alternation_symbol);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_alternation_symbol);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      154,
                      fail,
                      (void *)egg_token_type_alternation_symbol);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = bar()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      154,
                      success,
                      (void *)egg_token_type_alternation_symbol);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    154,
                    fail,
                    (void *)egg_token_type_alternation_symbol);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    concatenation-symbol = plus ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *concatenation_symbol(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    155,
                    entry,
                    (void *)egg_token_type_concatenation_symbol);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_concatenation_symbol);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      155,
                      fail,
                      (void *)egg_token_type_concatenation_symbol);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = plus()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      155,
                      success,
                      (void *)egg_token_type_concatenation_symbol);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    155,
                    fail,
                    (void *)egg_token_type_concatenation_symbol);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    phrase-terminator-symbol = semicolon ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *phrase_terminator_symbol(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    156,
                    entry,
                    (void *)egg_token_type_phrase_terminator_symbol);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_phrase_terminator_symbol);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      156,
                      fail,
                      (void *)egg_token_type_phrase_terminator_symbol);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = semicolon()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      156,
                      success,
                      (void *)egg_token_type_phrase_terminator_symbol);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    156,
                    fail,
                    (void *)egg_token_type_phrase_terminator_symbol);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    binary-integer = zero
                     + binary-indicator
                     + binary-digit{1,*} ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *binary_integer(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    157,
                    entry,
                    (void *)egg_token_type_binary_integer);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_binary_integer);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      157,
                      fail,
                      (void *)egg_token_type_binary_integer);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = zero()))
  {
    dir = egg_token_after;
    t1 = t2;
    if (egg_token_add(t1, dir, t2 = binary_indicator()))
    {
      dir = egg_token_after;
      t1 = t2;
      count=0;
      while(true)
      {
        if (egg_token_add(t1, dir, t2 = binary_digit()))
        {
          dir = egg_token_after;
          t1 = t2;
          ++count;
        }
        else
          break;
      }
      if ((count >= 1))
      {
        callback_by_index(&_cbt,
                          157,
                          success,
                          (void *)egg_token_type_binary_integer);

        return nt;
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    157,
                    fail,
                    (void *)egg_token_type_binary_integer);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    octal-integer = zero
                    + octal-indicator
                    + octal-digit{1,*} ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *octal_integer(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    158,
                    entry,
                    (void *)egg_token_type_octal_integer);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_octal_integer);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      158,
                      fail,
                      (void *)egg_token_type_octal_integer);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = zero()))
  {
    dir = egg_token_after;
    t1 = t2;
    if (egg_token_add(t1, dir, t2 = octal_indicator()))
    {
      dir = egg_token_after;
      t1 = t2;
      count=0;
      while(true)
      {
        if (egg_token_add(t1, dir, t2 = octal_digit()))
        {
          dir = egg_token_after;
          t1 = t2;
          ++count;
        }
        else
          break;
      }
      if ((count >= 1))
      {
        callback_by_index(&_cbt,
                          158,
                          success,
                          (void *)egg_token_type_octal_integer);

        return nt;
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    158,
                    fail,
                    (void *)egg_token_type_octal_integer);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    hexadecimal-integer = zero
                          + hexadecimal-indicator
                          + hexadecimal-digit{1,*} ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *hexadecimal_integer(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    159,
                    entry,
                    (void *)egg_token_type_hexadecimal_integer);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_hexadecimal_integer);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      159,
                      fail,
                      (void *)egg_token_type_hexadecimal_integer);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = zero()))
  {
    dir = egg_token_after;
    t1 = t2;
    if (egg_token_add(t1, dir, t2 = hexadecimal_indicator()))
    {
      dir = egg_token_after;
      t1 = t2;
      count=0;
      while(true)
      {
        if (egg_token_add(t1, dir, t2 = hexadecimal_digit()))
        {
          dir = egg_token_after;
          t1 = t2;
          ++count;
        }
        else
          break;
      }
      if ((count >= 1))
      {
        callback_by_index(&_cbt,
                          159,
                          success,
                          (void *)egg_token_type_hexadecimal_integer);

        return nt;
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    159,
                    fail,
                    (void *)egg_token_type_hexadecimal_integer);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    decimal-integer = decimal-digit{1,*} ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *decimal_integer(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    160,
                    entry,
                    (void *)egg_token_type_decimal_integer);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_decimal_integer);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      160,
                      fail,
                      (void *)egg_token_type_decimal_integer);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  count=0;
  while(true)
  {
    if (egg_token_add(t1, dir, t2 = decimal_digit()))
    {
      dir = egg_token_after;
      t1 = t2;
      ++count;
    }
    else
      break;
  }
  if ((count >= 1))
  {
    callback_by_index(&_cbt,
                      160,
                      success,
                      (void *)egg_token_type_decimal_integer);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    160,
                    fail,
                    (void *)egg_token_type_decimal_integer);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    integer = binary-integer
            | octal-integer
            | hexadecimal-integer
            | decimal-integer ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *integer(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    161,
                    entry,
                    (void *)egg_token_type_integer);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_integer);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      161,
                      fail,
                      (void *)egg_token_type_integer);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = binary_integer()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      161,
                      success,
                      (void *)egg_token_type_integer);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = octal_integer()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      161,
                      success,
                      (void *)egg_token_type_integer);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = hexadecimal_integer()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      161,
                      success,
                      (void *)egg_token_type_integer);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = decimal_integer()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      161,
                      success,
                      (void *)egg_token_type_integer);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    161,
                    fail,
                    (void *)egg_token_type_integer);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    single-quoted-literal = single-quote
                            + single-quoted-character{1,*}
                            + single-quote ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *single_quoted_literal(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    162,
                    entry,
                    (void *)egg_token_type_single_quoted_literal);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_single_quoted_literal);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      162,
                      fail,
                      (void *)egg_token_type_single_quoted_literal);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = single_quote()))
  {
    dir = egg_token_after;
    t1 = t2;
    count=0;
    while(true)
    {
      if (egg_token_add(t1, dir, t2 = single_quoted_character()))
      {
        dir = egg_token_after;
        t1 = t2;
        ++count;
      }
      else
        break;
    }
    if ((count >= 1))
    {
      if (egg_token_add(t1, dir, t2 = single_quote()))
      {
        dir = egg_token_after;
        t1 = t2;
        callback_by_index(&_cbt,
                          162,
                          success,
                          (void *)egg_token_type_single_quoted_literal);

        return nt;
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    162,
                    fail,
                    (void *)egg_token_type_single_quoted_literal);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    quoted-literal = quote + quoted-character{1,*} + quote ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *quoted_literal(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    163,
                    entry,
                    (void *)egg_token_type_quoted_literal);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_quoted_literal);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      163,
                      fail,
                      (void *)egg_token_type_quoted_literal);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = quote()))
  {
    dir = egg_token_after;
    t1 = t2;
    count=0;
    while(true)
    {
      if (egg_token_add(t1, dir, t2 = quoted_character()))
      {
        dir = egg_token_after;
        t1 = t2;
        ++count;
      }
      else
        break;
    }
    if ((count >= 1))
    {
      if (egg_token_add(t1, dir, t2 = quote()))
      {
        dir = egg_token_after;
        t1 = t2;
        callback_by_index(&_cbt,
                          163,
                          success,
                          (void *)egg_token_type_quoted_literal);

        return nt;
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    163,
                    fail,
                    (void *)egg_token_type_quoted_literal);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    absolute-literal = slash + space{0,*} + integer + space{0,*} + slash ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *absolute_literal(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    164,
                    entry,
                    (void *)egg_token_type_absolute_literal);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_absolute_literal);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      164,
                      fail,
                      (void *)egg_token_type_absolute_literal);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = slash()))
  {
    dir = egg_token_after;
    t1 = t2;
    count=0;
    while(true)
    {
      if (egg_token_add(t1, dir, t2 = space()))
      {
        dir = egg_token_after;
        t1 = t2;
        ++count;
      }
      else
        break;
    }
    if ((count >= 0))
    {
      if (egg_token_add(t1, dir, t2 = integer()))
      {
        dir = egg_token_after;
        t1 = t2;
        count=0;
        while(true)
        {
          if (egg_token_add(t1, dir, t2 = space()))
          {
            dir = egg_token_after;
            t1 = t2;
            ++count;
          }
          else
            break;
        }
        if ((count >= 0))
        {
          if (egg_token_add(t1, dir, t2 = slash()))
          {
            dir = egg_token_after;
            t1 = t2;
            callback_by_index(&_cbt,
                              164,
                              success,
                              (void *)egg_token_type_absolute_literal);

            return nt;
          }
        }
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    164,
                    fail,
                    (void *)egg_token_type_absolute_literal);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    literal = single-quoted-literal | quoted-literal | absolute-literal ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *literal(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    165,
                    entry,
                    (void *)egg_token_type_literal);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_literal);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      165,
                      fail,
                      (void *)egg_token_type_literal);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = single_quoted_literal()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      165,
                      success,
                      (void *)egg_token_type_literal);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = quoted_literal()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      165,
                      success,
                      (void *)egg_token_type_literal);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = absolute_literal()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      165,
                      success,
                      (void *)egg_token_type_literal);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    165,
                    fail,
                    (void *)egg_token_type_literal);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    comment-item = comment | comment-character ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *comment_item(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    166,
                    entry,
                    (void *)egg_token_type_comment_item);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comment_item);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      166,
                      fail,
                      (void *)egg_token_type_comment_item);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comment()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      166,
                      success,
                      (void *)egg_token_type_comment_item);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comment_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      166,
                      success,
                      (void *)egg_token_type_comment_item);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    166,
                    fail,
                    (void *)egg_token_type_comment_item);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    comment = comment-start-symbol
              + comment-item{0,*}
              + comment-end-symbol ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *comment(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    167,
                    entry,
                    (void *)egg_token_type_comment);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comment);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      167,
                      fail,
                      (void *)egg_token_type_comment);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comment_start_symbol()))
  {
    dir = egg_token_after;
    t1 = t2;
    count=0;
    while(true)
    {
      if (egg_token_add(t1, dir, t2 = comment_item()))
      {
        dir = egg_token_after;
        t1 = t2;
        ++count;
      }
      else
        break;
    }
    if ((count >= 0))
    {
      if (egg_token_add(t1, dir, t2 = comment_end_symbol()))
      {
        dir = egg_token_after;
        t1 = t2;
        callback_by_index(&_cbt,
                          167,
                          success,
                          (void *)egg_token_type_comment);

        return nt;
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    167,
                    fail,
                    (void *)egg_token_type_comment);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    illumination = white-space | comment ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *illumination(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    168,
                    entry,
                    (void *)egg_token_type_illumination);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_illumination);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      168,
                      fail,
                      (void *)egg_token_type_illumination);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = white_space()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      168,
                      success,
                      (void *)egg_token_type_illumination);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comment()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      168,
                      success,
                      (void *)egg_token_type_illumination);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    168,
                    fail,
                    (void *)egg_token_type_illumination);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    non-grammar-item = control-character | illumination ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *non_grammar_item(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    169,
                    entry,
                    (void *)egg_token_type_non_grammar_item);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_non_grammar_item);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      169,
                      fail,
                      (void *)egg_token_type_non_grammar_item);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = control_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      169,
                      success,
                      (void *)egg_token_type_non_grammar_item);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = illumination()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      169,
                      success,
                      (void *)egg_token_type_non_grammar_item);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    169,
                    fail,
                    (void *)egg_token_type_non_grammar_item);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    non-grammar-element = non-grammar-item{1,*} ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *non_grammar_element(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    170,
                    entry,
                    (void *)egg_token_type_non_grammar_element);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_non_grammar_element);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      170,
                      fail,
                      (void *)egg_token_type_non_grammar_element);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  count=0;
  while(true)
  {
    if (egg_token_add(t1, dir, t2 = non_grammar_item()))
    {
      dir = egg_token_after;
      t1 = t2;
      ++count;
    }
    else
      break;
  }
  if ((count >= 1))
  {
    callback_by_index(&_cbt,
                      170,
                      success,
                      (void *)egg_token_type_non_grammar_element);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    170,
                    fail,
                    (void *)egg_token_type_non_grammar_element);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    phrase-name = letter + phrase-name-character{0,*} ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *phrase_name(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    171,
                    entry,
                    (void *)egg_token_type_phrase_name);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_phrase_name);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      171,
                      fail,
                      (void *)egg_token_type_phrase_name);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = letter()))
  {
    dir = egg_token_after;
    t1 = t2;
    count=0;
    while(true)
    {
      if (egg_token_add(t1, dir, t2 = phrase_name_character()))
      {
        dir = egg_token_after;
        t1 = t2;
        ++count;
      }
      else
        break;
    }
    if ((count >= 0))
    {
      callback_by_index(&_cbt,
                        171,
                        success,
                        (void *)egg_token_type_phrase_name);

      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    171,
                    fail,
                    (void *)egg_token_type_phrase_name);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    quantifier-item = integer | asterisk ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *quantifier_item(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    172,
                    entry,
                    (void *)egg_token_type_quantifier_item);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_quantifier_item);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      172,
                      fail,
                      (void *)egg_token_type_quantifier_item);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = integer()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      172,
                      success,
                      (void *)egg_token_type_quantifier_item);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = asterisk()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      172,
                      success,
                      (void *)egg_token_type_quantifier_item);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    172,
                    fail,
                    (void *)egg_token_type_quantifier_item);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    quantifier-option = comma + quantifier-item ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *quantifier_option(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    173,
                    entry,
                    (void *)egg_token_type_quantifier_option);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_quantifier_option);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      173,
                      fail,
                      (void *)egg_token_type_quantifier_option);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comma()))
  {
    dir = egg_token_after;
    t1 = t2;
    if (egg_token_add(t1, dir, t2 = quantifier_item()))
    {
      dir = egg_token_after;
      t1 = t2;
      callback_by_index(&_cbt,
                        173,
                        success,
                        (void *)egg_token_type_quantifier_option);

      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    173,
                    fail,
                    (void *)egg_token_type_quantifier_option);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    quantifier = open-brace
                 + integer
                 + quantifier-option{0,1}
                 + close-brace ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *quantifier(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    174,
                    entry,
                    (void *)egg_token_type_quantifier);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_quantifier);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      174,
                      fail,
                      (void *)egg_token_type_quantifier);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = open_brace()))
  {
    dir = egg_token_after;
    t1 = t2;
    if (egg_token_add(t1, dir, t2 = integer()))
    {
      dir = egg_token_after;
      t1 = t2;
      count=0;
      while(count < 1)
      {
        if (egg_token_add(t1, dir, t2 = quantifier_option()))
        {
          dir = egg_token_after;
          t1 = t2;
          ++count;
        }
        else
          break;
      }
      if ((count >= 0) && (count <= 1))
      {
        if (egg_token_add(t1, dir, t2 = close_brace()))
        {
          dir = egg_token_after;
          t1 = t2;
          callback_by_index(&_cbt,
                            174,
                            success,
                            (void *)egg_token_type_quantifier);

          return nt;
        }
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    174,
                    fail,
                    (void *)egg_token_type_quantifier);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    atom = literal | phrase-name ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *atom(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    175,
                    entry,
                    (void *)egg_token_type_atom);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_atom);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      175,
                      fail,
                      (void *)egg_token_type_atom);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = literal()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      175,
                      success,
                      (void *)egg_token_type_atom);

    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = phrase_name()))
  {
    dir = egg_token_after;
    t1 = t2;
    callback_by_index(&_cbt,
                      175,
                      success,
                      (void *)egg_token_type_atom);

    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    175,
                    fail,
                    (void *)egg_token_type_atom);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    item = atom + quantifier{0,1} ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *item(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    176,
                    entry,
                    (void *)egg_token_type_item);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_item);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      176,
                      fail,
                      (void *)egg_token_type_item);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = atom()))
  {
    dir = egg_token_after;
    t1 = t2;
    count=0;
    while(count < 1)
    {
      if (egg_token_add(t1, dir, t2 = quantifier()))
      {
        dir = egg_token_after;
        t1 = t2;
        ++count;
      }
      else
        break;
    }
    if ((count >= 0) && (count <= 1))
    {
      callback_by_index(&_cbt,
                        176,
                        success,
                        (void *)egg_token_type_item);

      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    176,
                    fail,
                    (void *)egg_token_type_item);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    sequence-continuation = non-grammar-element{0,1}
                            + concatenation-symbol
                            + non-grammar-element{0,1}
                            + item ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *sequence_continuation(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    177,
                    entry,
                    (void *)egg_token_type_sequence_continuation);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_sequence_continuation);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      177,
                      fail,
                      (void *)egg_token_type_sequence_continuation);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  count=0;
  while(count < 1)
  {
    if (egg_token_add(t1, dir, t2 = non_grammar_element()))
    {
      dir = egg_token_after;
      t1 = t2;
      ++count;
    }
    else
      break;
  }
  if ((count >= 0) && (count <= 1))
  {
    if (egg_token_add(t1, dir, t2 = concatenation_symbol()))
    {
      dir = egg_token_after;
      t1 = t2;
      count=0;
      while(count < 1)
      {
        if (egg_token_add(t1, dir, t2 = non_grammar_element()))
        {
          dir = egg_token_after;
          t1 = t2;
          ++count;
        }
        else
          break;
      }
      if ((count >= 0) && (count <= 1))
      {
        if (egg_token_add(t1, dir, t2 = item()))
        {
          dir = egg_token_after;
          t1 = t2;
          callback_by_index(&_cbt,
                            177,
                            success,
                            (void *)egg_token_type_sequence_continuation);

          return nt;
        }
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    177,
                    fail,
                    (void *)egg_token_type_sequence_continuation);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    sequence = item + sequence-continuation{0,*} ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *sequence(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    178,
                    entry,
                    (void *)egg_token_type_sequence);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_sequence);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      178,
                      fail,
                      (void *)egg_token_type_sequence);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = item()))
  {
    dir = egg_token_after;
    t1 = t2;
    count=0;
    while(true)
    {
      if (egg_token_add(t1, dir, t2 = sequence_continuation()))
      {
        dir = egg_token_after;
        t1 = t2;
        ++count;
      }
      else
        break;
    }
    if ((count >= 0))
    {
      callback_by_index(&_cbt,
                        178,
                        success,
                        (void *)egg_token_type_sequence);

      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    178,
                    fail,
                    (void *)egg_token_type_sequence);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    definition-continuation = non-grammar-element{0,1}
                              + alternation-symbol
                              + non-grammar-element{0,1}
                              + sequence ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *definition_continuation(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    179,
                    entry,
                    (void *)egg_token_type_definition_continuation);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_definition_continuation);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      179,
                      fail,
                      (void *)egg_token_type_definition_continuation);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  count=0;
  while(count < 1)
  {
    if (egg_token_add(t1, dir, t2 = non_grammar_element()))
    {
      dir = egg_token_after;
      t1 = t2;
      ++count;
    }
    else
      break;
  }
  if ((count >= 0) && (count <= 1))
  {
    if (egg_token_add(t1, dir, t2 = alternation_symbol()))
    {
      dir = egg_token_after;
      t1 = t2;
      count=0;
      while(count < 1)
      {
        if (egg_token_add(t1, dir, t2 = non_grammar_element()))
        {
          dir = egg_token_after;
          t1 = t2;
          ++count;
        }
        else
          break;
      }
      if ((count >= 0) && (count <= 1))
      {
        if (egg_token_add(t1, dir, t2 = sequence()))
        {
          dir = egg_token_after;
          t1 = t2;
          callback_by_index(&_cbt,
                            179,
                            success,
                            (void *)egg_token_type_definition_continuation);

          return nt;
        }
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    179,
                    fail,
                    (void *)egg_token_type_definition_continuation);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    definition = sequence + definition-continuation{0,*} ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *definition(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    180,
                    entry,
                    (void *)egg_token_type_definition);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_definition);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      180,
                      fail,
                      (void *)egg_token_type_definition);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = sequence()))
  {
    dir = egg_token_after;
    t1 = t2;
    count=0;
    while(true)
    {
      if (egg_token_add(t1, dir, t2 = definition_continuation()))
      {
        dir = egg_token_after;
        t1 = t2;
        ++count;
      }
      else
        break;
    }
    if ((count >= 0))
    {
      callback_by_index(&_cbt,
                        180,
                        success,
                        (void *)egg_token_type_definition);

      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    180,
                    fail,
                    (void *)egg_token_type_definition);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    phrase = phrase-name
             + non-grammar-element{0,1}
             + equal
             + non-grammar-element{0,1}
             + definition
             + non-grammar-element{0,1}
             + phrase-terminator-symbol ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *phrase(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    181,
                    entry,
                    (void *)egg_token_type_phrase);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_phrase);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      181,
                      fail,
                      (void *)egg_token_type_phrase);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = phrase_name()))
  {
    dir = egg_token_after;
    t1 = t2;
    count=0;
    while(count < 1)
    {
      if (egg_token_add(t1, dir, t2 = non_grammar_element()))
      {
        dir = egg_token_after;
        t1 = t2;
        ++count;
      }
      else
        break;
    }
    if ((count >= 0) && (count <= 1))
    {
      if (egg_token_add(t1, dir, t2 = equal()))
      {
        dir = egg_token_after;
        t1 = t2;
        count=0;
        while(count < 1)
        {
          if (egg_token_add(t1, dir, t2 = non_grammar_element()))
          {
            dir = egg_token_after;
            t1 = t2;
            ++count;
          }
          else
            break;
        }
        if ((count >= 0) && (count <= 1))
        {
          if (egg_token_add(t1, dir, t2 = definition()))
          {
            dir = egg_token_after;
            t1 = t2;
            count=0;
            while(count < 1)
            {
              if (egg_token_add(t1, dir, t2 = non_grammar_element()))
              {
                dir = egg_token_after;
                t1 = t2;
                ++count;
              }
              else
                break;
            }
            if ((count >= 0) && (count <= 1))
            {
              if (egg_token_add(t1, dir, t2 = phrase_terminator_symbol()))
              {
                dir = egg_token_after;
                t1 = t2;
                callback_by_index(&_cbt,
                                  181,
                                  success,
                                  (void *)egg_token_type_phrase);

                return nt;
              }
            }
          }
        }
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    181,
                    fail,
                    (void *)egg_token_type_phrase);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    grammar-element = non-grammar-element{0,1} + phrase ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *grammar_element(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    182,
                    entry,
                    (void *)egg_token_type_grammar_element);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_grammar_element);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      182,
                      fail,
                      (void *)egg_token_type_grammar_element);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  count=0;
  while(count < 1)
  {
    if (egg_token_add(t1, dir, t2 = non_grammar_element()))
    {
      dir = egg_token_after;
      t1 = t2;
      ++count;
    }
    else
      break;
  }
  if ((count >= 0) && (count <= 1))
  {
    if (egg_token_add(t1, dir, t2 = phrase()))
    {
      dir = egg_token_after;
      t1 = t2;
      callback_by_index(&_cbt,
                        182,
                        success,
                        (void *)egg_token_type_grammar_element);

      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    182,
                    fail,
                    (void *)egg_token_type_grammar_element);

  return NULL;
}

  /*!

    \par "EGG Phrase Definition"
    \verbatim
    grammar = grammar-element{0,*} + non-grammar-element{0,1} ;
    \endverbatim

    \retval "egg_token *" on synctactical match of phrase
    \retval NULL on error including NO MATCH

 */

egg_token *grammar(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  callback_by_index(&_cbt,
                    183,
                    entry,
                    (void *)egg_token_type_grammar);

  if (input_eof())
    return NULL;

  count = 0;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_grammar);
  if (!nt)
  {
    callback_by_index(&_cbt,
                      183,
                      fail,
                      (void *)egg_token_type_grammar);
    return NULL;
  }

  t1 = nt;

  dir = egg_token_below;
  count=0;
  while(true)
  {
    if (egg_token_add(t1, dir, t2 = grammar_element()))
    {
      dir = egg_token_after;
      t1 = t2;
      ++count;
    }
    else
      break;
  }
  if ((count >= 0))
  {
    count=0;
    while(count < 1)
    {
      if (egg_token_add(t1, dir, t2 = non_grammar_element()))
      {
        dir = egg_token_after;
        t1 = t2;
        ++count;
      }
      else
        break;
    }
    if ((count >= 0) && (count <= 1))
    {
      callback_by_index(&_cbt,
                        183,
                        success,
                        (void *)egg_token_type_grammar);

      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  callback_by_index(&_cbt,
                    183,
                    fail,
                    (void *)egg_token_type_grammar);

  return NULL;
}

