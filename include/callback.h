/*!
    \file callback.h

    \brief Header file for callback system.

    \version 20131207175824

    \author Patrick Head  mailto:patrickhead@gmail.com

    \copyright Copyright (C) 2013  Patrick Head

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
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CALLBACK_H
#define CALLBACK_H

typedef struct callback_entry
{
  char *tag;
  int (*enter)(void *data);
  int (*succeed)(void *data);
  int (*fail)(void *data);
} callback_entry;

typedef struct callback_table
{
  int size;
  callback_entry *callbacks;
} callback_table;

typedef enum { entry = 0, success, fail } callback_type;

int callback_by_index(callback_table *cbt,
                      int index,
                      callback_type type,
                      void *data);
int callback_by_tag(callback_table *cbt,
                    char *tag,
                    callback_type type,
                    void *data);
int callback_create(callback_table *cbt,
                    char *tag);
int callback_register(callback_table *cbt,
                      char *tag,
                      callback_type type,
                      int (*function)(void *data));
callback_table *callback_initialize(void);

#endif // CALLBACK_H

