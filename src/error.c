/*!
    \file error.c

    \brief Source code for generic error handling routines.

    \note Currently, this source is not implemented in any portion of the
          \b EGG/embryo system.

    \version 20131209035052

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

#include "error.h"

static unsigned char _errorCode = 0;

  /*!

     \brief Sets error code state to a value.
    
     \param code unsigned char with error code
    
  */

void errorSet(unsigned char code)
{
  _errorCode = code;
}

  /*!

     \brief Gets current error code.
    
     \retval errorCode unsigned char of current error code

  */

unsigned char errorGet(void)
{
  return _errorCode;
}

