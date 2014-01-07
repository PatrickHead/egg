/*!
    \file common.h

    \brief Header file for common type definitions.

    \timestamp Thu, 26 Dec 2013 04:38:43 +0000

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

#ifndef COMMON_H
#define COMMON_H

  /*!
    This is the header file for some common type definitions used in the
    embryo project, and for parsers generated by embryo from EGG grammars
  */

  /*!
    \brief Definition of a boolean type
  */

typedef enum
{
    /* \brief boolean false */
  false = 0,
    /* \brief boolean true */
  true
} boolean;

  /*!
    \brief Definition of a byte type
  */

typedef unsigned char byte;

#endif // COMMON_H

