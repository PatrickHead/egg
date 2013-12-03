/*
    callback.h
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

#ifndef CALLBACK_H
#define CALLBACK_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif // _GNU_SOURCE

#include <search.h>

typedef struct callback_system
{
  struct hsearch_data *ht;
} callback_system;

typedef enum { entry = 0, success, fail } callback_type;

void callback(callback_system *cbs, \
              char *tag, \
              callback_type type, \
              void *data);
void callback_create(callback_system *cbs, \
                     char *tag);
void callback_register(callback_system *cbs, \
                       char *tag, \
                       callback_type type, \
                       void (*function)(void *data));
callback_system *callback_initialize(int n_items);

#endif // CALLBACK_H

