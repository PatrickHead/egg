/*
    callback.c
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

#include "callback.h"

typedef struct callback_entry
{
  char *tag;
  int (*enter)(void *data);
  int (*succeed)(void *data);
  int (*fail)(void *data);
} callback_entry;

static int find_entry_by_tag(callback_table *cbt, char *tag);

callback_table *callback_initialize()
{
  callback_table *cbt;

  cbt = (callback_table *)malloc(sizeof(callback_table));
  if (!cbt)
    return NULL;

  memset(cbt, 0, sizeof(callback_table));

  return cbt;
}

int callback_create(callback_table *cbt,
                    char *tag)
{
  if (!cbt)
    return -1;

  if (!tag)
    return -1;

  if ((find_entry_by_tag(cbt, tag)) < 0)
    return -1;

  if (!cbt->size)
    cbt->data = malloc(sizeof(callback_entry));
  else
    cbt->data = realloc(cbt->data, sizeof(cbt->data) + sizeof(callback_entry));
	if (!cbt->data)
		return -1;

  memset(&((callback_entry *)cbt->data)[cbt->size], 0, sizeof(cbt->data));

  if (tag)
    ((callback_entry *)cbt->data)[cbt->size].tag = strdup(tag);

  ++cbt->size;

  return 0;
}

int callback_register(callback_table *cbt,
                      char *tag,
                      callback_type type,
                      int (*function)(void *data))
{
  callback_entry *cbe;
  int i;

  if (!cbt)
    return -1;

  if (!tag)
    return -1;

  i = find_entry_by_tag(cbt, tag);
  if (i < 0)
    return -1;

  cbe  = &((callback_entry *)cbt->data)[i];

  switch (type)
  {
    case entry:
      cbe->enter = function;
      break;
    case success:
      cbe->succeed = function;
      break;
    case fail:
      cbe->fail = function;
      break;
  }

  return 0;
}

int callback_by_index(callback_table *cbt,
                      int index,
                      callback_type type,
                      void *data)
{
  int r;

  if (!cbt)
    return -1;

  if (index < 0)
    return -1;

  if (index >= sizeof(cbt->data) / sizeof(callback_entry))
    return -1;

  switch (type)
  {
    case entry:
      r = ((callback_entry *)cbt->data)[index].enter(data);
      break;
    case success:
      r = ((callback_entry *)cbt->data)[index].succeed(data);
      break;
    case fail:
      r = ((callback_entry *)cbt->data)[index].fail(data);
      break;
  }

  return r;
}

int callback_by_tag(callback_table *cbt,
                    char *tag,
                    callback_type type,
                    void *data)
{
  int i;

  if (!cbt)
    return -1;

  if (!tag)
    return -1;

  i = find_entry_by_tag(cbt, tag);
  if (i < 0)
    return -1;

  return callback_by_index(cbt, i, type, data);
}

static int find_entry_by_tag(callback_table *cbt, char *tag)
{
  int i;

  if (!cbt)
    return -1;

  if (!tag)
    return -1;

  for (i = 0; i < cbt->size; i++)
    if (!strcmp(((callback_entry *)cbt->data)[i].tag, tag))
      return i;

  return -1;
}

