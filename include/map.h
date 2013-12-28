/*!
    \file map.h

    \brief Header file for line mapping routines.

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

#ifndef MAP_H
#define MAP_H

  /*!

    \file map.h

    This is the header file for EGG grammar phrase mapping function module.

  */

  /*!
    \brief Definition of a phrase_map_item type
  */

typedef struct phrase_map_item
{
    /*! \brief string containing phrase-name */
  char *name;
    /*! \brief pointer to next mapped phrase item */
  struct phrase_map_item *next;
    /*! \brief pointer to head of list of phrase names that this phrase uses */
  struct phrase_map_item *uses;
} phrase_map_item;

phrase_map_item *phrase_map(egg_token *grammar);

phrase_map_item *phrase_map_item_new(char *name);
void phrase_map_item_free(phrase_map_item *pmi);
void phrase_map_item_unlink(phrase_map_item **list, phrase_map_item *pmi);
void phrase_map_item_delete(phrase_map_item **list, phrase_map_item *pmi);

void phrase_map_list_delete(phrase_map_item *list);
phrase_map_item *phrase_map_list_find_item_by_name(phrase_map_item *list,
                                                   char *name);
phrase_map_item *phrase_map_list_append_item_by_name(phrase_map_item **list,
                                                     char *name,
                                                     boolean dups_allowed);
int phrase_map_list_get_item_index(phrase_map_item *list, char *name);
int phrase_map_list_count_items(phrase_map_item *list);
void phrase_map_list_isolate_top_level_phrases(phrase_map_item **list);

#endif // MAP_H

