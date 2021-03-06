/*!

  @file egg-token-util.h

  @brief Source code for egg-token-util.h

  @version 0.4.1

  @author Patrick Head mailto:patrickhead@gmail.com

  @copyright Copyright (C) 2013-2014 Patrick Head

  @license
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.@n
  @n
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.@n
  @n
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see   \<http://www.gnu.org/licenses/\>.

*/

  /*!

    @file egg-token-util.h

    This is the header file for the egg grammar token utility
    functions module.

    The egg_token_type_to_string function is defined in
    this module.

  */

#ifndef EGG_TOKEN_UTIL_H
#define EGG_TOKEN_UTIL_H

char *egg_token_type_to_string(egg_token *t);

#endif // EGG_TOKEN_UTIL_H
