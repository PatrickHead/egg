/*
    input.c
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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "input.h"

#define CHUNK 512

typedef enum
{
  source_type_none = 0,
  source_type_file,
  source_type_stdin,
  source_type_buffer
} source_type;

static struct _source
{
  source_type type;
  FILE *file;
  unsigned char *buffer;
  long  position;
  long  size;
  boolean eof;
} _source;

static long *_line_map = NULL;
static long _n_lines = 0L;

static void _clear_source(void);
static void _map_lines(void);
static long _find_line_number(long position);
long _search_line_number(long position, long ilow, long ihigh);

boolean input_initialize(char *source)
{
  static boolean first_time = true;
  byte *b = NULL;
  byte *p = NULL;
  int n_read = 0;
  int n_chunks = 0;
  struct stat st;

  if (first_time)
  {
    _clear_source();
    first_time = false;
  }

  if (_source.file || _source.buffer)
    return false;

  if (!source)
  {
    _source.type = source_type_stdin;
    
    b = p = NULL;
    n_chunks = 0;

    while (true)
    {
      b = (byte *)realloc(b, ((n_chunks + 1) * CHUNK));
      if (!p)
        p = b;
      memset(p, 0, CHUNK);
      n_read = fread(p, sizeof(byte), CHUNK, stdin);
      ++n_chunks;
      p += n_read;
      *p = 0;
      if (n_read < CHUNK)
        break;
    }

    _source.buffer = b;

    _source.size = strlen((char *)_source.buffer);

    _map_lines();

    return true;
  }
  else if (strchr(source, '\n'))
  {
    _source.type = source_type_buffer;
    _source.buffer = (byte *)source;
    _source.size = strlen((char *)_source.buffer);

    _map_lines();

    return true;
  }
  else
  {
    if (stat(source, &st))
      return false;
    _source.file = fopen(source, "r");
    if (!_source.file)
      return false;
    _source.type = source_type_file;
    _source.size = st.st_size;

		b = (byte *)malloc(_source.size + 1);
		memset(b, 0, _source.size + 1);

		fread(b, sizeof(byte), _source.size, _source.file);

    fclose(_source.file);

    _source.file = NULL;

    _source.buffer = b;

    _map_lines();

    return true;
  }

  return false;
}

void input_cleanup(void)
{
  switch (_source.type)
  {
    case source_type_file:
    case source_type_stdin:
      free(_source.buffer);
      break;
    case source_type_buffer:
      break;
    case source_type_none:
    default:
      return;
  }

  if (_line_map)
    free(_line_map);

  _clear_source();

  return;
}

byte input_byte(void)
{
  byte b;

  switch (_source.type)
  {
    case source_type_file:
    case source_type_stdin:
    case source_type_buffer:
			b = _source.buffer[_source.position];
			_source.position++;
      if (_source.position == _source.size)
        _source.eof = true;
      return b;
    default:
     return 0;
  }

  return 0;
}

long input_get_position(void)
{
  return _source.position;
}

boolean input_set_position(long pos)
{
  if (pos < 0)
    return false;

  if (pos >= _source.size)
    return false;

  switch (_source.type)
  {
    case source_type_file:
    case source_type_stdin:
    case source_type_buffer:
      if (pos >= _source.size)
        return false;
      _source.position = pos;
      _source.eof = false;
      return true;
    default:
      break;
  }

  return false;
}

boolean input_eof(void)
{
  return _source.eof;
}

boolean input_get_location(input_location *loc)
{
  long ln;
  long cp;

  if (!loc)
    return false;

  if (!_line_map)
    return false;

  cp = input_get_position();

  ln = _find_line_number(cp);

  loc->line_number = ln + 1L;
  loc->character_offset = cp - _line_map[ln] + 1L;

  return true;
}

static void _clear_source(void)
{
  memset(&_source, 0, sizeof(_source));
  return;
}

static void _map_lines(void)
{
  long curr_pos;
  byte b;

  curr_pos = input_get_position();

  _line_map = (long *)malloc(sizeof(long));
  if (!_line_map)
    return;

  _line_map[0] = 0L;

  while (!input_eof())
  {
    b = input_byte();
    if (b == '\n')
    {
      ++_n_lines;
      _line_map = (long *)realloc(_line_map, sizeof(long) * (_n_lines + 1));
      if (!_line_map)
        break;
      _line_map[_n_lines] = input_get_position();
    }
  }

  input_set_position(curr_pos);

  return;
}

static long _find_line_number(long position)
{
  return _search_line_number(position, 0L, _n_lines - 1);
}

long _search_line_number(long position, long ilow, long ihigh)
{
  long imid;
  long p1, p2;

  if (position <= 0L)
    return 0L;

  if ((ihigh - ilow) <= 1L)
    return ilow;

  imid = (ilow + ihigh) / 2L;

  if (imid >= ihigh)
    return ihigh;

  p1 = _line_map[imid];
  p2 = _line_map[imid+1];

  if ((p1 <= position) && (p2 > position))
    return imid;

  if (p1 > position)
    ihigh = imid;
  else
    ilow = imid;

  return _search_line_number(position, ilow, ihigh);
}

