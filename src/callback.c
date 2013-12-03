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
  void (*ef)(void *data);
  void (*sf)(void *data);
  void (*ff)(void *data);
} callback_entry;

callback_system *callback_initialize(int n_items)
{
  callback_system *cbs;

  cbs = (callback_system *)malloc(sizeof(callback_system));
  if (!cbs)
    return NULL;

  memset(cbs, 0, sizeof(callback_system));

  cbs->ht = (struct hsearch_data *)malloc(sizeof(struct hsearch_data));
  if (!cbs->ht)
  {
    free(cbs);
    return NULL;
  }

  memset(cbs->ht, 0, sizeof(struct hsearch_data));

  if (!hcreate_r(n_items, cbs->ht))
  {
    free(cbs->ht);
    free(cbs);
    return NULL;
  }

  return cbs;
}

void callback_create(callback_system *cbs,
                     char *tag)
{
}

void callback_register(callback_system *cbs,
                       char *tag,
                       callback_type type,
                       void (*function)(void *data))
{
}

void callback(callback_system *cbs,
              char *tag,
              callback_type type,
              void *data)
{
}

