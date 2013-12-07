/*!
    \file mkdir_p.c

    \brief Source code for "mkdir -p" like function.

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

#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int mkdir_p(const char *pathname, mode_t mode)
{
  char *ds, *bns;
  char *dir, *base;
  struct stat st;
  int r;
  extern int errno;

  if (!pathname)
    return -1;

  r = stat(pathname, &st);
  if (!r)
  {
    if (S_ISDIR(st.st_mode))
      return 0;
    else
      return -1;
  }

  if (errno != ENOENT)
    return -1;

  ds = strdup(pathname);
  dir = dirname(ds);

  r = mkdir_p(dir, mode);
  if (r)
  {
    free(ds);
    return -1;
  }

  bns = strdup(pathname);
  base = basename(ds);

  r = mkdir(pathname, mode);

  if (ds)
    free(ds);
  if (bns)
    free(bns);

  return r;
}

