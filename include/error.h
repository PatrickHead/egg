/*!
    \file error.h

    \brief Header file for generic error handling routines.

    \timestamp 20131225233843

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

#ifndef ERROR_H
#define ERROR_H

  /*!

    \file error.h

    This is the header file for a generic error messaging system.

    This error mechanism is extremely simple.  It consists of defined
    error codes, and two functions to set and retrieve the current error
    code.

  */

  /*!
    \brief Definition of error code types
  */

typedef enum
{
    /*! \brief OK */
  error_ok = 0
} error_code;

void error_set(error_code code);

error_code error_get(void);
 
#endif // ERROR_H
