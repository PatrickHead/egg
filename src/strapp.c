/*
    strapp.c
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
#include <string.h>

char *strapp(char *s, char *a)
{
  if (!a)
    return s;

  if (!s)
  {
    s = malloc(strlen(a) + 1);
    memset(s, 0, strlen(a) + 1);
  }
  else
  {
    s = realloc(s, strlen(s) + strlen(a) + 1);
  }

  strcat(s, a);

  return s;
}

