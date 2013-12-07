/*
    input.h
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

#ifndef INPUT_H
#define INPUT_H

#include "common.h"

  /*@
   *  Structure to capture and track the current line and character
   *  position of the input file.
   */

typedef struct input_location
{
  int line_number;
  int character_offset;
} input_location;

boolean input_initialize(char *source);
void input_cleanup(void);

byte input_byte(void);

boolean input_eof(void);

long input_get_position(void);
boolean input_set_position(long offset);

boolean input_get_location(input_location *loc);

#endif // INPUT_H

