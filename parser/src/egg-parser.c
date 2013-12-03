/*
    egg-parser.c
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

#include "input.h"

#include "egg-token.h"
#include "egg-parser.h"

/*
 * nul =               /0x00/ ;
 */

egg_token *nul(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_nul);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x00)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * soh =               /0x01/ ;
 */

egg_token *soh(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_soh);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x01)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * stx =               /0x02/ ;
 */

egg_token *stx(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_stx);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x02)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * etx =               /0x03/ ;
 */

egg_token *etx(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_etx);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x03)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * eot =               /0x04/ ;
 */

egg_token *eot(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_eot);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x04)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * enq =               /0x05/ ;
 */

egg_token *enq(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_enq);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x05)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * ack =               /0x06/ ;
 */

egg_token *ack(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_ack);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x06)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * bel =               /0x07/ ;
 */

egg_token *bel(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_bel);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x07)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * bs =                /0x08/ ;
 */

egg_token *bs(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_bs);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x08)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * ht =                /0x09/ ;
 */

egg_token *ht(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_ht);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x09)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * lf =                /0x0A/ ;
 */

egg_token *lf(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_lf);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x0A)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * vt =                /0x0B/ ;
 */

egg_token *vt(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_vt);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x0B)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * ff =                /0x0C/ ;
 */

egg_token *ff(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_ff);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x0C)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * cr =                /0x0D/ ;
 */

egg_token *cr(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_cr);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x0D)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * so =                /0x0E/ ;
 */

egg_token *so(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_so);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x0E)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * si =                /0x0F/ ;
 */

egg_token *si(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_si);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x0F)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * dle =               /0x10/ ;
 */

egg_token *dle(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_dle);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x10)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * dc1 =               /0x11/ ;
 */

egg_token *dc1(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_dc1);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x11)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * dc2 =               /0x12/ ;
 */

egg_token *dc2(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_dc2);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x12)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * dc3 =               /0x13/ ;
 */

egg_token *dc3(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_dc3);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x13)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * dc4 =               /0x14/ ;
 */

egg_token *dc4(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_dc4);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x14)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * nak =               /0x15/ ;
 */

egg_token *nak(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_nak);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x15)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * syn =               /0x16/ ;
 */

egg_token *syn(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_syn);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x16)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * etb =               /0x17/ ;
 */

egg_token *etb(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_etb);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x17)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * can =               /0x18/ ;
 */

egg_token *can(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_can);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x18)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * em =                /0x19/ ;
 */

egg_token *em(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_em);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x19)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * sub =               /0x1A/ ;
 */

egg_token *sub(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_sub);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x1A)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * esc =               /0x1B/ ;
 */

egg_token *esc(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_esc);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x1B)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * fs =                /0x1C/ ;
 */

egg_token *fs(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_fs);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x1C)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * gs =                /0x1D/ ;
 */

egg_token *gs(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_gs);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x1D)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * rs =                /0x1E/ ;
 */

egg_token *rs(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_rs);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x1E)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * us =                /0x1F/ ;
 */

egg_token *us(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_us);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x1F)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * space =             /0x20/ ;
 */

egg_token *space(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_space);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x20)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * exclamation-point = /0x21/ ;
 */

egg_token *exclamation_point(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_exclamation_point);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x21)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * quote =             /0x22/ ;
 */

egg_token *quote(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_quote);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x22)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * number-sign =       /0x23/ ;
 */

egg_token *number_sign(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_number_sign);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x23)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * dollar =            /0x24/ ;
 */

egg_token *dollar(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_dollar);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x24)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * percent =           /0x25/ ;
 */

egg_token *percent(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_percent);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x25)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * ampersand =         /0x26/ ;
 */

egg_token *ampersand(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_ampersand);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x26)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * single-quote =      /0x27/ ;
 */

egg_token *single_quote(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_single_quote);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x27)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * open-parenthesis =  /0x28/ ;
 */

egg_token *open_parenthesis(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_open_parenthesis);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x28)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * close-parenthesis = /0x29/ ;
 */

egg_token *close_parenthesis(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_close_parenthesis);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x29)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * asterisk =          /0x2A/ ;
 */

egg_token *asterisk(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_asterisk);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x2A)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * plus =              /0x2B/ ;
 */

egg_token *plus(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_plus);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x2B)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * comma =             /0x2C/ ;
 */

egg_token *comma(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comma);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x2C)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * minus =             /0x2D/ ;
 */

egg_token *minus(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_minus);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x2D)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * period =            /0x2E/ ;
 */

egg_token *period(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_period);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x2E)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * slash =             /0x2F/ ;
 */

egg_token *slash(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_slash);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x2F)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * zero =              /0x30/ ;
 */

egg_token *zero(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_zero);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x30)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * one =               /0x31/ ;
 */

egg_token *one(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_one);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x31)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * two =               /0x32/ ;
 */

egg_token *two(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_two);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x32)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * three =             /0x33/ ;
 */

egg_token *three(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_three);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x33)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * four =              /0x34/ ;
 */

egg_token *four(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_four);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x34)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * five =              /0x35/ ;
 */

egg_token *five(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_five);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x35)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * six =               /0x36/ ;
 */

egg_token *six(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_six);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x36)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * seven =             /0x37/ ;
 */

egg_token *seven(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_seven);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x37)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * eight =             /0x38/ ;
 */

egg_token *eight(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_eight);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x38)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * nine =              /0x39/ ;
 */

egg_token *nine(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_nine);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x39)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * colon =             /0x3A/ ;
 */

egg_token *colon(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_colon);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x3A)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * semicolon =         /0x3B/ ;
 */

egg_token *semicolon(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_semicolon);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x3B)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * less-than =         /0x3C/ ;
 */

egg_token *less_than(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_less_than);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x3C)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * equal =             /0x3D/ ;
 */

egg_token *equal(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_equal);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x3D)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * greater-than =      /0x3E/ ;
 */

egg_token *greater_than(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_greater_than);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x3E)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * question-mark =     /0x3F/ ;
 */

egg_token *question_mark(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_question_mark);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x3F)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * at =                /0x40/ ;
 */

egg_token *at(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_at);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x40)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * A =                 /0x41/ ;
 */

egg_token *A(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_A);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x41)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * B =                 /0x42/ ;
 */

egg_token *B(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_B);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x42)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * C =                 /0x43/ ;
 */

egg_token *C(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_C);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x43)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * D =                 /0x44/ ;
 */

egg_token *D(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_D);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x44)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * E =                 /0x45/ ;
 */

egg_token *E(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_E);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x45)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * F =                 /0x46/ ;
 */

egg_token *F(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_F);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x46)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * G =                 /0x47/ ;
 */

egg_token *G(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_G);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x47)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * H =                 /0x48/ ;
 */

egg_token *H(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_H);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x48)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * I =                 /0x49/ ;
 */

egg_token *I(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_I);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x49)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * J =                 /0x4A/ ;
 */

egg_token *J(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_J);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x4A)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * K =                 /0x4B/ ;
 */

egg_token *K(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_K);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x4B)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * L =                 /0x4C/ ;
 */

egg_token *L(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_L);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x4C)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * M =                 /0x4D/ ;
 */

egg_token *M(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_M);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x4D)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * N =                 /0x4E/ ;
 */

egg_token *N(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_N);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x4E)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * O =                 /0x4F/ ;
 */

egg_token *O(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_O);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x4F)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * P =                 /0x50/ ;
 */

egg_token *P(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_P);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x50)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * Q =                 /0x51/ ;
 */

egg_token *Q(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_Q);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x51)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * R =                 /0x52/ ;
 */

egg_token *R(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_R);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x52)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * S =                 /0x53/ ;
 */

egg_token *S(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_S);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x53)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * T =                 /0x54/ ;
 */

egg_token *T(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_T);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x54)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * U =                 /0x55/ ;
 */

egg_token *U(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_U);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x55)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * V =                 /0x56/ ;
 */

egg_token *V(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_V);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x56)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * W =                 /0x57/ ;
 */

egg_token *W(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_W);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x57)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * X =                 /0x58/ ;
 */

egg_token *X(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_X);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x58)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * Y =                 /0x59/ ;
 */

egg_token *Y(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_Y);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x59)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * Z =                 /0x5A/ ;
 */

egg_token *Z(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_Z);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x5A)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * open-bracket =      /0x5B/ ;
 */

egg_token *open_bracket(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_open_bracket);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x5B)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * back-slash =        /0x5C/ ;
 */

egg_token *back_slash(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_back_slash);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x5C)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * close-bracket =     /0x5D/ ;
 */

egg_token *close_bracket(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_close_bracket);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x5D)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * carat =             /0x5E/ ;
 */

egg_token *carat(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_carat);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x5E)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * underscore =        /0x5F/ ;
 */

egg_token *underscore(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_underscore);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x5F)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * back-quote =        /0x60/ ;
 */

egg_token *back_quote(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_back_quote);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x60)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * a =                 /0x61/ ;
 */

egg_token *a(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_a);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x61)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * b =                 /0x62/ ;
 */

egg_token *b(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_b);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x62)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * c =                 /0x63/ ;
 */

egg_token *c(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_c);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x63)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * d =                 /0x64/ ;
 */

egg_token *d(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_d);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x64)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * e =                 /0x65/ ;
 */

egg_token *e(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_e);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x65)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * f =                 /0x66/ ;
 */

egg_token *f(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_f);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x66)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * g =                 /0x67/ ;
 */

egg_token *g(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_g);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x67)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * h =                 /0x68/ ;
 */

egg_token *h(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_h);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x68)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * i =                 /0x69/ ;
 */

egg_token *i(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_i);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x69)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * j =                 /0x6A/ ;
 */

egg_token *j(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_j);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x6A)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * k =                 /0x6B/ ;
 */

egg_token *k(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_k);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x6B)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * l =                 /0x6C/ ;
 */

egg_token *l(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_l);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x6C)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * m =                 /0x6D/ ;
 */

egg_token *m(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_m);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x6D)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * n =                 /0x6E/ ;
 */

egg_token *n(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_n);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x6E)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * o =                 /0x6F/ ;
 */

egg_token *o(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_o);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x6F)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * p =                 /0x70/ ;
 */

egg_token *p(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_p);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x70)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * q =                 /0x71/ ;
 */

egg_token *q(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_q);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x71)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * r =                 /0x72/ ;
 */

egg_token *r(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_r);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x72)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * s =                 /0x73/ ;
 */

egg_token *s(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_s);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x73)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * t =                 /0x74/ ;
 */

egg_token *t(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_t);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x74)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * u =                 /0x75/ ;
 */

egg_token *u(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_u);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x75)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * v =                 /0x76/ ;
 */

egg_token *v(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_v);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x76)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * w =                 /0x77/ ;
 */

egg_token *w(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_w);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x77)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * x =                 /0x78/ ;
 */

egg_token *x(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_x);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x78)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * y =                 /0x79/ ;
 */

egg_token *y(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_y);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x79)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * z =                 /0x7A/ ;
 */

egg_token *z(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_z);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x7A)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * open-brace =        /0x7B/ ;
 */

egg_token *open_brace(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_open_brace);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x7B)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * bar =               /0x7C/ ;
 */

egg_token *bar(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_bar);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x7C)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * close-brace =       /0x7D/ ;
 */

egg_token *close_brace(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_close_brace);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x7D)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * tilde =             /0x7E/ ;
 */

egg_token *tilde(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_tilde);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x7E)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * del =               /0x7F/ ;
 */

egg_token *del(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_del);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if ((input_byte()) == 0x7F)
  {
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * control-character = nul | soh | stx | etx | eot | enq | ack | bel | bs
 *                   | so | si | dle | dc1 | dc2 | dc3 | dc4 | nak | syn
 *                   | etb | can | em | sub | esc | fs | gs | rs | us
 *                   | del ;
 */

egg_token *control_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_control_character);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = nul()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = soh()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = stx()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = etx()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = eot()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = enq()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = ack()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = bel()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = bs()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = so()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = si()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = dle()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = dc1()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = dc2()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = dc3()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = dc4()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = nak()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = syn()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = etb()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = can()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = em()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = sub()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = esc()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = fs()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = gs()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = rs()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = us()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = del()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * upper-case-letter = A | B | C | D | E | F | G | H | I | J | K | L | M
 *                   | N | O | P | Q | R | S | T | U | V | W | X | Y | Z
 *                   ;
 */

egg_token *upper_case_letter(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_upper_case_letter);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = A()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = B()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = C()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = D()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = E()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = F()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = G()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = H()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = I()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = J()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = K()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = L()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = M()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = N()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = O()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = P()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = Q()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = R()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = S()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = T()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = U()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = V()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = W()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = X()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = Y()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = Z()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * lower-case-letter = a | b | c | d | e | f | g | h | i | j | k | l | m
 *                   | n | o | p | q | r | s | t | u | v | w | x | y | z
 *                   ;
 */

egg_token *lower_case_letter(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_lower_case_letter);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = a()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = b()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = c()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = d()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = e()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = f()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = g()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = h()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = i()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = j()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = k()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = l()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = m()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = n()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = o()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = p()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = q()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = r()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = s()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = t()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = u()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = v()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = w()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = x()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = y()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = z()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * letter = upper-case-letter | lower-case-letter ;
 */

egg_token *letter(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_letter);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = upper_case_letter()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = lower_case_letter()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * binary-digit = zero | one ;
 */

egg_token *binary_digit(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_binary_digit);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = zero()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = one()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * octal-digit = zero | one | two | three | four | five | six | seven ;
 */

egg_token *octal_digit(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_octal_digit);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = zero()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = one()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = two()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = three()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = four()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = five()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = six()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = seven()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * decimal-digit = zero | one | two | three | four
 *               | five | six | seven | eight | nine ;
 */

egg_token *decimal_digit(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_decimal_digit);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = zero()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = one()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = two()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = three()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = four()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = five()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = six()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = seven()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = eight()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = nine()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * hexadecimal-digit = zero | one | two | three | four
 *                   | five | six | seven | eight | nine
 *                   | A | B | C | D | E | F
 *                   | a | b | c | d | e | f ;
 */

egg_token *hexadecimal_digit(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_hexadecimal_digit);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = zero()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = one()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = two()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = three()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = four()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = five()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = six()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = seven()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = eight()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = nine()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = A()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = B()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = C()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = D()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = E()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = F()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = a()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = b()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = c()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = d()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = e()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = f()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * white-space = space | ht | lf | vt | ff | cr ;
 */

egg_token *white_space(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_white_space);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = space()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = ht()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = lf()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = vt()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = ff()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = cr()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * common-character = exclamation-point | number-sign | dollar | percent
 *                  | ampersand | plus | comma | minus | period | colon
 *                  | semicolon | less-than | equal | greater-than
 *                  | question-mark | at | open-bracket | back-slash
 *                  | close-bracket | carat | underscore | back-quote
 *                  | open-brace | bar | close-brace | tilde | letter
 *                  | decimal-digit ;
 */

egg_token *common_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_common_character);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = exclamation_point()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = number_sign()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = dollar()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = percent()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = ampersand()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = plus()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comma()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = minus()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = period()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = colon()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = semicolon()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = less_than()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = equal()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = greater_than()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = question_mark()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = at()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = open_bracket()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = back_slash()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = close_bracket()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = carat()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = underscore()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = back_quote()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = open_brace()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = bar()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = close_brace()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = tilde()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = letter()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = decimal_digit()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * literal-character = common-character
 *                   | space
 *                   | open-parenthesis
 *                   | close-parenthesis
 *                   | asterisk ;
 */

egg_token *literal_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_literal_character);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = common_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = space()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = open_parenthesis()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = close_parenthesis()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = asterisk()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * comment-basic-character = common-character
 *                         | white-space
 *                         | quote
 *                         | single-quote
 *                         | slash ;
 */

egg_token *comment_basic_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comment_basic_character);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = common_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = white_space()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = quote()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = single_quote()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = slash()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * non-comment-start-character = comment-basic-character
 *                             | close-parenthesis ;
 */

egg_token *non_comment_start_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_non_comment_start_character);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comment_basic_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = close_parenthesis()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * non-comment-end-character = comment-basic-character
 *                           | open-parenthesis ;
 */

egg_token *non_comment_end_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_non_comment_end_character);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comment_basic_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = open_parenthesis()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * non-comment-start-sequence = open-parenthesis
 *                              + non-comment-start-character ;
 */

egg_token *non_comment_start_sequence(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_non_comment_start_sequence);
  if (!nt)
    return NULL;

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
      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * non-comment-end-sequence = asterisk
 *                            + non-comment-end-character ;
 */

egg_token *non_comment_end_sequence(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_non_comment_end_sequence);
  if (!nt)
    return NULL;

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
      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * comment-character = comment-basic-character
 *                   | non-comment-start-sequence
 *                   | non-comment-end-sequence
 *                   | close-parenthesis ;
 */

egg_token *comment_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comment_character);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comment_basic_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = non_comment_start_sequence()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = non_comment_end_sequence()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = close_parenthesis()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * single-quoted-character = literal-character | quote ;
 */

egg_token *single_quoted_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_single_quoted_character);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = literal_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = quote()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * quoted-character = literal-character | single-quote ;
 */

egg_token *quoted_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_quoted_character);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = literal_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = single_quote()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * phrase-conjugator = underscore | minus ;
 */

egg_token *phrase_conjugator(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_phrase_conjugator);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = underscore()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = minus()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * phrase-name-character = letter | decimal_digit | phrase-conjugator ;
 */

egg_token *phrase_name_character(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_phrase_name_character);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = letter()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = decimal_digit()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = phrase_conjugator()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * binary-indicator = b | B ;
 */

egg_token *binary_indicator(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_binary_indicator);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = b()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = B()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * octal-indicator = o | O ;
 */

egg_token *octal_indicator(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_octal_indicator);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = o()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = O()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * hexadecimal-indicator = x | X ;
 */

egg_token *hexadecimal_indicator(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_hexadecimal_indicator);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = x()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = X()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * comment-start-symbol = open-parenthesis + asterisk ;
 */

egg_token *comment_start_symbol(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comment_start_symbol);
  if (!nt)
    return NULL;

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
      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * comment-end-symbol = asterisk + close-parenthesis ;
 */

egg_token *comment_end_symbol(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comment_end_symbol);
  if (!nt)
    return NULL;

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
      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * alternation-symbol = bar ;
 */

egg_token *alternation_symbol(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_alternation_symbol);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = bar()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * concatenation-symbol = plus ;
 */

egg_token *concatenation_symbol(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_concatenation_symbol);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = plus()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * phrase-terminator-symbol = semicolon ;
 */

egg_token *phrase_terminator_symbol(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_phrase_terminator_symbol);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = semicolon()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * binary-integer = zero
 *                  + binary-indicator
 *                  + binary-digit{1,*} ;
 */

egg_token *binary_integer(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_binary_integer);
  if (!nt)
    return NULL;

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
        return nt;
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * octal-integer = zero
 *                 + octal-indicator
 *                 + octal-digit{1,*} ;
 */

egg_token *octal_integer(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_octal_integer);
  if (!nt)
    return NULL;

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
        return nt;
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * hexadecimal-integer = zero
 *                       + hexadecimal-indicator
 *                       + hexadecimal-digit{1,*} ;
 */

egg_token *hexadecimal_integer(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_hexadecimal_integer);
  if (!nt)
    return NULL;

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
        return nt;
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * decimal-integer = decimal-digit{1,*} ;
 */

egg_token *decimal_integer(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_decimal_integer);
  if (!nt)
    return NULL;

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
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * integer = binary-integer
 *         | octal-integer
 *         | hexadecimal-integer
 *         | decimal-integer ;
 */

egg_token *integer(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_integer);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = binary_integer()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = octal_integer()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = hexadecimal_integer()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = decimal_integer()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * single-quoted-literal = single-quote
 *                         + single-quoted-character{1,*}
 *                         + single-quote ;
 */

egg_token *single_quoted_literal(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_single_quoted_literal);
  if (!nt)
    return NULL;

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
        return nt;
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * quoted-literal = quote + quoted-character{1,*} + quote ;
 */

egg_token *quoted_literal(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_quoted_literal);
  if (!nt)
    return NULL;

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
        return nt;
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * absolute-literal = slash + space{0,*} + integer + space{0,*} + slash ;
 */

egg_token *absolute_literal(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_absolute_literal);
  if (!nt)
    return NULL;

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
            return nt;
          }
        }
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * literal = single-quoted-literal | quoted-literal | absolute-literal ;
 */

egg_token *literal(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_literal);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = single_quoted_literal()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = quoted_literal()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = absolute_literal()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * comment-item = comment | comment-character ;
 */

egg_token *comment_item(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comment_item);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comment()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comment_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * comment = comment-start-symbol
 *           + comment-item{0,*}
 *           + comment-end-symbol ;
 */

egg_token *comment(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_comment);
  if (!nt)
    return NULL;

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
        return nt;
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * illumination = white-space | comment ;
 */

egg_token *illumination(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_illumination);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = white_space()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = comment()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * non-grammar-item = control-character | illumination ;
 */

egg_token *non_grammar_item(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_non_grammar_item);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = control_character()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = illumination()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * non-grammar-element = non-grammar-item{1,*} ;
 */

egg_token *non_grammar_element(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_non_grammar_element);
  if (!nt)
    return NULL;

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
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * phrase-name = letter + phrase-name-character{0,*} ;
 */

egg_token *phrase_name(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_phrase_name);
  if (!nt)
    return NULL;

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
      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * quantifier-item = integer | asterisk ;
 */

egg_token *quantifier_item(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_quantifier_item);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = integer()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = asterisk()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * quantifier-option = comma + quantifier-item ;
 */

egg_token *quantifier_option(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_quantifier_option);
  if (!nt)
    return NULL;

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
      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * quantifier = open-brace
 *              + integer
 *              + quantifier-option{0,1}
 *              + close-brace ;
 */

egg_token *quantifier(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_quantifier);
  if (!nt)
    return NULL;

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
          return nt;
        }
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * atom = literal | phrase-name ;
 */

egg_token *atom(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_atom);
  if (!nt)
    return NULL;

  t1 = nt;

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = literal()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  dir = egg_token_below;
  if (egg_token_add(t1, dir, t2 = phrase_name()))
  {
    dir = egg_token_after;
    t1 = t2;
    return nt;
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * item = atom + quantifier{0,1} ;
 */

egg_token *item(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_item);
  if (!nt)
    return NULL;

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
      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * sequence-continuation = non-grammar-element{0,1}
 *                         + concatenation-symbol
 *                         + non-grammar-element{0,1}
 *                         + item ;
 */

egg_token *sequence_continuation(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_sequence_continuation);
  if (!nt)
    return NULL;

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
          return nt;
        }
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * sequence = item + sequence-continuation{0,*} ;
 */

egg_token *sequence(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_sequence);
  if (!nt)
    return NULL;

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
      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * definition-continuation = non-grammar-element{0,1}
 *                           + alternation-symbol
 *                           + non-grammar-element{0,1}
 *                           + sequence ;
 */

egg_token *definition_continuation(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_definition_continuation);
  if (!nt)
    return NULL;

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
          return nt;
        }
      }
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * definition = sequence + definition-continuation{0,*} ;
 */

egg_token *definition(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_definition);
  if (!nt)
    return NULL;

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
      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * phrase = phrase-name
 *          + non-grammar-element{0,1}
 *          + equal
 *          + non-grammar-element{0,1}
 *          + definition
 *          + non-grammar-element{0,1}
 *          + phrase-terminator-symbol ;
 */

egg_token *phrase(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_phrase);
  if (!nt)
    return NULL;

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

  return NULL;
}

/*
 * grammar-element = non-grammar-element{0,1} + phrase ;
 */

egg_token *grammar_element(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_grammar_element);
  if (!nt)
    return NULL;

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
      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

/*
 * grammar = grammar-element{0,*} + non-grammar-element{0,1} ;
 */

egg_token *grammar(void)
{
  long pos = input_get_position();
  egg_token *nt, *t1, *t2;
  int count;
  egg_token_direction dir;

  count = 0;

  if (input_eof())
    return NULL;

  nt = t1 = t2 = NULL;

  nt = egg_token_new(egg_token_type_grammar);
  if (!nt)
    return NULL;

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
      return nt;
    }
  }

  egg_token_delete(nt);
  input_set_position(pos);

  return NULL;
}

