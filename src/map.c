/*!
    @file map.c

    @brief Source code for line mapping routines.

    @timestamp Tue, 07 Oct 2014 05:45:40 +0000

    @author Patrick Head  mailto:patrickhead@gmail.com

    @copyright Copyright (C) 2013  Patrick Head

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
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

  /*!

    @file map.c

    This is the source code file for EGG grammar phrase mapping function module.

  */

  // Required system headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

  // Project specific headers

#include "egg-token.h"
#include "egg-token-util.h"

  // Module specific headers

#include "map.h"

  // Module constants

#define FALSE 0
#define TRUE 1

  // Function declarations

static void all_phrase_names(egg_token *t, phrase_map_item *pmi);

  /*!

     @brief Create an list of @e phrase_map_item.

     This function creates a list of phrase map items, each of which contain
     the phrase name of each phrase in any EGG grammar token tree.  The list is
     ordered in the same way as the EGG grammar itself.
    
     @param g egg_token * to root of EGG grammar token tree.
    
     @retval "phrase_map_item *" to head of phrase_map
     @retval NULL                failure

  */

phrase_map_item *phrase_map(egg_token *g)
{
  egg_token *ge;
  egg_token *p;
  egg_token *pn;
  egg_token *d;
  char *s;
  phrase_map_item *list = NULL;
  phrase_map_item *npmi;

  if (!g)
    return NULL;

  ge = egg_token_find(g, egg_token_type_grammar_element);
  if (ge)
  {
    while (ge)
    {
      p = egg_token_find(ge->descendant, egg_token_type_phrase);
      if (p)
      {
        pn = egg_token_find(p->descendant, egg_token_type_phrase_name);
        if (pn)
        {
          s = NULL;
          s = egg_token_to_string(pn->descendant, s);
          npmi = phrase_map_list_append_item_by_name(&list, s, FALSE);
          if (!npmi)
          {
            free(s);
            phrase_map_list_delete(list);
            return NULL;
          }
          free(s);
          d = egg_token_find(p->descendant, egg_token_type_definition);
          if (d)
            all_phrase_names(d->descendant, npmi);
        }
      }
      ge = ge->next;
    }
  }

  return list;
}

  /*!

     @brief Create an list of @e phrase_map_item of phrases referenced in a
            given phrase's definition.

     This function creates a list of phrase map items, each of which contain
     the phrase name of each phrase referenced by a phrase's definition for
     a given phrase.
    
     @param t   egg_token * to a single phrase token
     @param pmi phrase_map_item * to a phrase_map_item for a phrase-name token
    
  */

static void all_phrase_names(egg_token *t, phrase_map_item *pmi)
{
  char *s;
  phrase_map_item *npmi;

  if (!t)
    return;

  if (!pmi)
    return;

  if (t->type == egg_token_type_phrase_name)
  {
    s = NULL;
    s = egg_token_to_string(t->descendant, s);
    npmi = phrase_map_list_append_item_by_name(&(pmi->uses), s, TRUE);
    free(s);
    if (!npmi)
      return;
  }

  all_phrase_names(t->descendant, pmi);

  all_phrase_names(t->next, pmi);

  return;
}

  /*!

     @brief Create a new @e phrase_map_item structure

     This function allocates and initializes new @e phrase_map_item structure.

     @warning This function returns a pointer to dynamically allocated memory.
              It is the caller's responsibility to free this memory by calling
              the corresponding @e phrase_map_item_free function when
              appropriate.
    
     @param name string containing phrase-name
    
     @retval "phrase_map_item *" to new @e phrase_map_item
     @retval NULL                failure

  */

phrase_map_item *phrase_map_item_new(char *name)
{
  phrase_map_item *new;

  new = (phrase_map_item *)malloc(sizeof(phrase_map_item));
  if (!new)
    return NULL;

  memset(new, 0, sizeof(phrase_map_item));

  if (name)
    new->name = strdup(name);

  return new;
}

  /*!

     @brief Frees the memory associated with a dynamically allocated
            @e phrase_map_item.

     This function frees the allocated memory of a @e phrase_map_item and
     its contained phrase-name string.

     @param pmi phrase_map_item * to an existing phrase_map_item
    
  */

void phrase_map_item_free(phrase_map_item *pmi)
{
  if (!pmi)
    return;

  if (pmi->name)
    free(pmi->name);

  free(pmi);

  return;
}

  /*!

     @brief Unlinks a @e phrase_map_item from a phrase map list.

     This function unlinks a specific @e phrase_map_item from an existing
     phrase map list.

     @note The @e list argument passed may be altered by this function to
           reflect a new head of list.

     @warning This function does NOT free the allocated memory for a dynamically
              allocated @e phrase_map_item.

     @param list address of the head of an existing phrase map list
     @param pmi  phrase_map_item * of specific phrase_map_item to unlink
    
  */

void phrase_map_item_unlink(phrase_map_item **list, phrase_map_item *pmi)
{
  phrase_map_item *tpmi;
  phrase_map_item *ppmi;

  if (!list)
    return;

  if (!*list)
    return;

  if (!pmi)
    return;

  tpmi = *list;
  ppmi = NULL;

  while (tpmi)
  {
    if (tpmi == pmi)
    {
      if (ppmi)
      {
        ppmi->next = tpmi->next;
        return;
      }
      else
      {
        *list = tpmi->next;
        return;
      }
    }

    ppmi = tpmi;
    tpmi = tpmi->next;
  }

  return;
}

  /*!

     @brief Deletes a @e phrase_map_item from a phrase map list.

     This function deletes a specific @e phrase_map_item from an existing
     phrase map list and frees the allocated memory of the @e phrase_map_item.

     @note The @e list argument passed may be altered by this function to
           reflect a new head of list.

     @param list address of the head of an existing phrase map list
     @param pmi  phrase_map_item * of specific phrase_map_item to unlink
    
  */

void phrase_map_item_delete(phrase_map_item **list, phrase_map_item *pmi)
{
  phrase_map_item *tpmi;
  phrase_map_item *next;

  if (!list)
    return;

  if (!*list)
    return;

  if (!pmi)
    return;

  phrase_map_item_unlink(list, pmi);

  tpmi = pmi->uses;
  while (tpmi)
  {
    next = tpmi->next;
    phrase_map_item_free(tpmi);
    tpmi = next;
  }

  phrase_map_item_free(pmi);

  return;
}

  /*!

     @brief Deletes an entire phrase map list.

     This function deletes an entire phrase map list, freeing all associated
     memory allocated to all items in the list.

     @param list phrase_map_item * to head of phrase_map_list
    
  */

void phrase_map_list_delete(phrase_map_item *list)
{
  if (!list)
    return;

  while (list)
    phrase_map_item_delete(&list, list);

  return;
}

  /*!

     @brief Finds a @e phrase_map_item in a phrase map list by name.

     This function finds an item in a phrase map list by name and returns
     a pointer to the found item.

     @param list phrase_map_item * to head of phrase_map_list
     @param name string containing the phrase-name of the item to find
    
     @retval "phrase_map_item *" to found item
     @retval NULL                failure
  */

phrase_map_item *phrase_map_list_find_item_by_name(phrase_map_item *list,
                                                   char *name)
{
  phrase_map_item *tpmi;

  if (!list)
    return FALSE;

  if (!name)
    return FALSE;

  tpmi = list;
  while (tpmi)
  {
    if (!strcmp(tpmi->name, name))
      return tpmi;

    tpmi = tpmi->next;
  }

  return NULL;
}

  /*!

     @brief Appends a new @e phrase_map_item to the end of a phrase map list.

     This function will create a new @e phrase_map_item for a given phrase-name
     and append the new item to the end of the phrase map list.

     @note By definition, a properly formed EGG grammer will never contain
           a duplicate phrase-name for each EGG phrase, but any phrase
           definition may contain multiple references to the same phrase, so
           this function allows for duplicate names in phrase map list to
           accomodate the building of the @e uses list in each
           @e phrase_map_item in the higher level phrase map list.

     @param list address of phrase_map_item * to head of phrase map list
     @param name string containing the phrase-name of the item to find
     @param dups_allowed unsigned char flag to allow/deny duplicate phrase-name
                         in phrase map list
    
     @retval "phrase_map_item *" to found item
     @retval NULL                failure
  */

phrase_map_item *phrase_map_list_append_item_by_name(phrase_map_item **list,
                                                     char *name,
                                                     unsigned char dups_allowed)
{
  phrase_map_item *tpmi;
  phrase_map_item *npmi;

  if (!list)
     return NULL;

  if (!name)
     return NULL;

  tpmi = *list;
  while (tpmi && tpmi->next)
  {
    if (!dups_allowed)
      if (!strcmp(tpmi->name, name))
        return NULL;

    tpmi = tpmi->next;
  }

  npmi = phrase_map_item_new(name);
  if (!npmi)
    return NULL;

  if (tpmi)
    tpmi->next = npmi;
  else
    *list = npmi;

  return npmi;
}

  /*!

     @brief Returns index offset of a named @e phrase_map_item in a phrase
            map list.

     This function will locate a @e phrase_map_item in an existing phrase map
     list, and return the 0 (zero) based ordinal position of the
     @e phrase_map_item in the phrase map list.

     @param list phrase_map_item * to head of phrase_map_list
     @param name string containing the phrase-name of the item to find
    
     @retval int ordinal position of found phrase_map_item
     @retval -1  failure
  */

int phrase_map_list_get_item_index(phrase_map_item *list, char *name)
{
  phrase_map_item *tpmi;
  int index = 0;

  if (!list)
    return -1;

  if (!name)
    return -1;

  tpmi = list;
  while (tpmi)
  {
    if (!strcmp(tpmi->name, name))
      return index;

    ++index;

    tpmi = tpmi->next;
  }

  return -1;
}

  /*!

     @brief Returns a count of all @e phrase_map_item in a phrase
            map list.

     This function returns a shallow count of all @e phrase_map_item in an
     existing phrase map list.

     @param list phrase_map_item * to head of phrase_map_list
    
     @retval int count of items
     @retval -1  failure
  */

int phrase_map_list_count_items(phrase_map_item *list)
{
  phrase_map_item *tpmi;
  int count = 0;

  if (!list)
    return -1;

  tpmi = list;
  while (tpmi)
  {
    ++count;
    tpmi = tpmi->next;
  }

  return count;
}

  /*!

     @brief Reduce an EGG phrase map to just top-level phrases.
    
     This function finds all the top-level phrases in an EGG grammar phrase map.
     A top-level phrase is defined as a phrase in an EGG grammar that has no
     dependent phrases.  In other words, no other EGG grammar phrases make
     reference to a top-level phrase.@n
     @n
     This is useful for any code generation that needs to be able to make
     calls to or reports of specific sub-sets of a grammar at a top level.
     The @<PROJECT@>-walker utility is an example of the use of top-level
     phrases.

     @warning This function modifies the contents of the passed list of
              @e phrase_map_item, specifically by deleting all phrase map items
              that do not contain EGG grammar phrases that qualify as top-level
              phrases.
    
     @param list address of an array of @e phrase_map_item
    
  */

void phrase_map_list_isolate_top_level_phrases(phrase_map_item **list)
{
  phrase_map_item *ppmi;
  phrase_map_item *ppmi2;
  phrase_map_item *upmi;

  if (!list)
    return;

  if (!*list)
    return;

  ppmi = *list;
  while (ppmi)
  {
    upmi = ppmi->uses;
    while (upmi)
    {
      ppmi2 = *list;
      while (ppmi2)
      {
        if (!strcmp(ppmi2->name, upmi->name))
          if (strcmp(ppmi->name, upmi->name))
            ppmi2->name[0] = ' ';
        
        ppmi2 = ppmi2->next;
      }
      upmi = upmi->next;
    }
    ppmi = ppmi->next;
  }

  ppmi = *list;
  while (ppmi)
  {
    if (ppmi->name[0] == ' ')
      phrase_map_item_delete(list, ppmi);
    ppmi = ppmi->next;
  }

  return;
}

